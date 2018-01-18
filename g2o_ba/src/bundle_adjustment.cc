#include "bundle_adjustment.h"

#include "thirdparty/g2o/g2o/core/block_solver.h"
#include "thirdparty/g2o/g2o/core/optimization_algorithm_levenberg.h"
#include "thirdparty/g2o/g2o/solvers/linear_solver_eigen.h"
#include "thirdparty/g2o/g2o/types/types_six_dof_expmap.h"
#include "thirdparty/g2o/g2o/core/robust_kernel_impl.h"
#include "thirdparty/g2o/g2o/solvers/linear_solver_dense.h"
#include "thirdparty/g2o/g2o/types/types_seven_dof_expmap.h"

#include <opencv2/opencv.hpp>

#include "converter.h"

bool *pbStopFlag = false;
const bool bRobust = true;
const int nIterations = 20;
const int nLoopKF = 0;

/**
 *  @Author: Falezza Fabio, Davide Miglioranzi
 *  This is the bundle adjustment execution. It is taken from ORB-SLAM 2, but it is simplier
 */

long int BundleAdjustment::Execute(const std::vector<KeyFrame *> &vpKFs, const std::vector<MapPoint *> &vpMP)
{
    // Optimizer setup
    std::vector<bool> vbNotIncludedMP;
    vbNotIncludedMP.resize(vpMP.size());

    g2o::SparseOptimizer optimizer;
    g2o::BlockSolver_6_3::LinearSolverType *linearSolver;

    linearSolver = new g2o::LinearSolverEigen<g2o::BlockSolver_6_3::PoseMatrixType>();

    g2o::BlockSolver_6_3 *solver_ptr = new g2o::BlockSolver_6_3(linearSolver);

    g2o::OptimizationAlgorithmLevenberg *solver = new g2o::OptimizationAlgorithmLevenberg(solver_ptr);
    optimizer.setAlgorithm(solver);

    if (pbStopFlag)
        optimizer.setForceStopFlag(pbStopFlag);

    long unsigned int maxKFid = 0;

    // CICLA PER OGNI KEYFRAME:
    //      - POSA che viene convertita in Quaternion
    //      - ID
    //      - FIXED è true <=> ID == 0
    //      - aggiorna maxID

    // Set KeyFrame vertices
    for (size_t i = 0; i < vpKFs.size(); i++)
    {
        KeyFrame *pKF = vpKFs[i];
        g2o::VertexSE3Expmap *vSE3 = new g2o::VertexSE3Expmap();
        vSE3->setEstimate(Converter::toSE3Quat(pKF->pose));

        vSE3->setId(pKF->id);
        vSE3->setFixed(pKF->id == 0);
        optimizer.addVertex(vSE3);
        if (pKF->id > maxKFid)
            maxKFid = pKF->id;
    }

    const float thHuber2D = sqrt(5.99);
    const float thHuber3D = sqrt(7.815);

    // CICLA PER OGNI MAPPOINT:
    //      - WORLD POS che viene convertita in vettore 3d
    //      - ID dato da mnId + maxKFid + 1
    //      - OBSERVATIONS DEL MAPPOINT (nelle prime righe c'e scritto il mapping fra keyframe e mappoint)

    // Set MapPoint vertices
    for (size_t i = 0; i < vpMP.size(); i++)
    {
        MapPoint *pMP = vpMP[i];
        g2o::VertexSBAPointXYZ *vPoint = new g2o::VertexSBAPointXYZ();
        vPoint->setEstimate(Converter::toVector3d(pMP->world_pose));
        const int id = pMP->id + maxKFid + 1;
        vPoint->setId(id);
        vPoint->setMarginalized(true);
        optimizer.addVertex(vPoint);

        const std::map<KeyFrame *, size_t> observations = pMP->mObs;

        int nEdges = 0;
        //SET EDGES
        for (std::map<KeyFrame *, size_t>::const_iterator mit = observations.begin(); mit != observations.end(); mit++)
        {

            KeyFrame *pKF = mit->first;
            if (pKF->id > maxKFid)
                continue;

            nEdges++;

            const cv::KeyPoint &kpUn = pKF->vObs_pos[mit->second];

            Eigen::Matrix<double, 2, 1> obs;
            obs << kpUn.pt.x, kpUn.pt.y;

            g2o::EdgeSE3ProjectXYZ *e = new g2o::EdgeSE3ProjectXYZ();

            e->setVertex(0, dynamic_cast<g2o::OptimizableGraph::Vertex *>(optimizer.vertex(id)));
            e->setVertex(1, dynamic_cast<g2o::OptimizableGraph::Vertex *>(optimizer.vertex(pKF->id)));
            e->setMeasurement(obs);
            e->setInformation(Eigen::Matrix2d::Identity());

            if (bRobust)
            {
                g2o::RobustKernelHuber *rk = new g2o::RobustKernelHuber;
                e->setRobustKernel(rk);
                rk->setDelta(thHuber2D);
            }
            e->fx = pKF->fx;
            e->fy = pKF->fy;
            e->cx = pKF->cx;
            e->cy = pKF->cy;
            optimizer.addEdge(e);
        }
        if (nEdges == 0)
        {
            optimizer.removeVertex(vPoint);
            vbNotIncludedMP[i] = true;
        }
        else
        {
            vbNotIncludedMP[i] = false;
        }
    }

    // Optimize!
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    optimizer.initializeOptimization();
    optimizer.optimize(nIterations);
    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    // Recover optimized data

    //Keyframes
    for (size_t i = 0; i < vpKFs.size(); i++)
    {
        KeyFrame *pKF = vpKFs[i];
        g2o::VertexSE3Expmap *vSE3 = static_cast<g2o::VertexSE3Expmap *>(optimizer.vertex(pKF->id));
        g2o::SE3Quat SE3quat = vSE3->estimate();
        if (nLoopKF == 0)
        {
            pKF->pose = (Converter::toCvMat(SE3quat));
        }
    }
    //Points
    for (size_t i = 0; i < vpMP.size(); i++)
    {
        if (vbNotIncludedMP[i])
            continue;

        MapPoint *pMP = vpMP[i];
        g2o::VertexSBAPointXYZ *vPoint = static_cast<g2o::VertexSBAPointXYZ *>(optimizer.vertex(pMP->id + maxKFid + 1));

        if (nLoopKF == 0)
        {
            pMP->world_pose = (Converter::toCvMat(vPoint->estimate()));
        }
    }
    return duration;
}
