#include "parser.h"
#include <iostream>
#include <fstream>

namespace driver
{
Parser::Parser(char *in, char *out) : in_file(in), out_file(out) {}

void Parser::ParseFile(std::vector<KeyFrame *> &vKf, std::vector<MapPoint *> &vMp)
{
    std::ifstream file(in_file, std::ios_base::app); //apro lo stream sul file da leggere
    if (file.is_open())
    {
        //lettura della prima riga di intestazione
        int numKF, numMP, numOBS;
        file >> numKF >> numMP >> numOBS; //leggo la prima riga di intestazione
        std::cout << numKF << " " << numMP << " " << numOBS << std::endl;

        //lettura Observations
        std::vector<observation_ids> vObs_id;
        for (int i = 1; i <= numOBS; i++)
        {
            int idKF, idMP;
            float xn, yn;
            file >> idKF >> idMP >> xn >> yn;
            std::cout << idKF << " " << idMP << " " << xn << " " << yn << std::endl;

            observation_ids ids;
            ids.keyframe_id = idKF;
            ids.mappoint_id = idMP;
            vObs_id.push_back(ids);
        }

        //lettura KeyFrames
        // i = 1;
        for (int i = 0; i < numKF; i++)
        {
            float r1, r2, r3;
            float t1, t2, t3;
            float f, k1, k2;
            file >> r1 >> r2 >> r3 >> t1 >> t2 >> t3 >> f >> k1 >> k2;
            std::cout << r1 << " " << r2 << " " << r3 << " " << t1 << " " << t2 << " " << t3 << " " << f << " " << k1 << " " << k2 << std::endl;

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
            keyframe->cx = 0; //TODO: chidere cosa va qui
            keyframe->cy = 0; //TODO: chidere cosa va qui

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
            std::vector<KeyFrame *> vObs;
            for (auto ob : vObs_id)
                if (ob.mappoint_id == i)
                    vObs.push_back(vKf.at(ob.keyframe_id));
            mp->observations = vObs;
            vMp.push_back(mp);
        }
        file.close();
    }
    else
        std::cout << "Unable to open file";
}
} // end namespace driver