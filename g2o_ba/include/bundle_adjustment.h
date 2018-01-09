#ifndef BUNDLE_ADJUSTMENT
#define BUNDLE_ADJUSTMENT

#include "keyframe.h"
#include "mappoint.h"


class BundleAdjustment {
    public:
        void Execute(const std::vector<KeyFrame *> &vpKFs, const std::vector<MapPoint *> &vpMP);
};

#endif