#ifndef KEYFRAME_H
#define KEYFRAME_H

#include <opencv2/core/core.hpp>

class KeyFrame
{
    public:
        long int id;
        cv::Mat pose;

        // Calibration parameters
        float fx, fy, cx, cy;
        
};

#endif