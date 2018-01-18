#include "parser.h"
#include <iostream>
#include <fstream>

#define CX 0
#define CY 0

/**
 *  @Author: Falezza Fabio, Davide Miglioranzi
 *  This is the class which parse the files in PBA file format
 */

namespace driver
{
Parser::Parser(char *in) : in_file(in) {}

void Parser::ParseFile(std::vector<KeyFrame *> &vKf, std::vector<MapPoint *> &vMp)
{
    std::ifstream file(in_file, std::ios_base::app); //apro lo stream sul file da leggere
    if (file.is_open())
    {
        //lettura della prima riga di intestazione
        int numKF, numMP, numOBS;
        file >> numKF >> numMP >> numOBS; //leggo la prima riga di intestazione

        //lettura Observations
        std::vector<observation> vObs;
        for (int i = 1; i <= numOBS; i++)
        {
            int idKF, idMP;
            float xn, yn;
            file >> idKF >> idMP >> xn >> yn;
            observation obs;
            obs.keyframe_id = idKF;
            obs.mappoint_id = idMP;
            obs.pos.pt.x = xn;
            obs.pos.pt.y = yn;
            vObs.push_back(obs);
        }

        //lettura KeyFrames
        // i = 1;
        for (int i = 0; i < numKF; i++)
        {
            float r1, r2, r3;
            float t1, t2, t3;
            float f, k1, k2;
            file >> r1 >> r2 >> r3 >> t1 >> t2 >> t3 >> f >> k1 >> k2;
            cv::Mat rotVec = (cv::Mat_<float>(3, 1) << t1, t2, t3); //salvo le rotazioni in un vettore
            cv::Mat rotMat = cv::Mat::zeros(4, 4, CV_64F);
            cv::Rodrigues(rotVec, rotMat); //converto il vettore delle rotazioni in matrice 3x3
            cv::Mat poseMat = (cv::Mat_<float>(4, 4) << rotMat.at<float>(0, 0), rotMat.at<float>(0, 1), rotMat.at<float>(0, 2), t1,
                               rotMat.at<float>(1, 0), rotMat.at<float>(1, 1), rotMat.at<float>(1, 2), t2,
                               rotMat.at<float>(2, 0), rotMat.at<float>(2, 1), rotMat.at<float>(2, 2), t3,
                               0, 0, 0, 1);
            KeyFrame *keyframe = new KeyFrame();
            keyframe->id = i;
            keyframe->pose = poseMat;
            keyframe->fx = f;
            keyframe->fy = f;
            keyframe->cx = CX;
            keyframe->cy = CY;

            for (auto obs : vObs)
                if (obs.keyframe_id == i)
                    keyframe->vObs_pos.push_back(obs.pos);

            vKf.push_back(keyframe);
        }

        //lettura MapPoints
        for (int i = 0; i < numMP; i++)
        {
            float x, y, z;
            file >> x >> y >> z;

            MapPoint *mp = new MapPoint();
            mp->id = i;
            mp->world_pose = (cv::Mat_<float>(3, 1) << x, y, z);
            std::map<KeyFrame *, size_t> mObs;
            for (auto ob : vObs)
                if (ob.mappoint_id == i)
                    mp->mObs.insert(std::pair<KeyFrame *, size_t>(vKf.at(ob.keyframe_id), ob.mappoint_id));
            vMp.push_back(mp);
        }
        file.close();
    }
    else
        std::cout << "Unable to open file";
}
} // end namespace driver