#ifndef PARSER_H
#define PARSER_H

#include "keyframe.h"
#include "mappoint.h"

#include <opencv2/opencv.hpp>

namespace driver 
{
    class Parser
        {
        public:
            // constructor
            Parser(char* in, char* out);
            ~Parser();
            

            char* GetInputFile() { return in_file; }
            char* GetOutputFile() { return out_file; }

            // std::vector<KeyFrame*> ParseKeyFrames();
            // std::vector<MapPoint*> ParseMapPoints();

            void ParseFile(std::vector<KeyFrame*> &vKf, std::vector<MapPoint*> &vMp);

        private:
            char *in_file;
            char *out_file;

    };
    struct observation_ids
    {
        int keyframe_id;
        int mappoint_id;
    };
}

#endif