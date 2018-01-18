#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <opencv2/opencv.hpp>

class KeyFrame
{
    public:
        long int id;
        cv::Mat pose;

        // NB: non viene memorizzato l'indice del map point, in quanto questo è dato
        // dalla posizione i nel vector.
        // Bisogna rispettare le specifiche del file PBA e inserire le observation con 
        // gli id dei map points ord
        std::vector<cv::KeyPoint> vObs_pos;

        // Calibration parameters
        float fx, fy, cx, cy;
        
};

#endif