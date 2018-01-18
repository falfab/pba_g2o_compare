#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <opencv2/core/core.hpp>
#include "keyframe.h"

class MapPoint 
{
    public:
    long int id;
    cv::Mat world_pose;
    
    // Keyframes observing the point 
    std::vector<KeyFrame*> observations;

    std::map<KeyFrame*, size_t> mObs;
};

#endif