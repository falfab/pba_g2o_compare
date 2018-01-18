#ifndef BUNDLE_ADJUSTMENT
#define BUNDLE_ADJUSTMENT

#include "keyframe.h"
#include "mappoint.h"
#include <chrono>

class BundleAdjustment {
    public:
        long int Execute(const std::vector<KeyFrame *> &vpKFs, const std::vector<MapPoint *> &vpMP);
};

#endif