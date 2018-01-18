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
            Parser(char* in);
            ~Parser();
            

            char* GetInputFile() { return in_file; }

            void ParseFile(std::vector<KeyFrame*> &vKf, std::vector<MapPoint*> &vMp);

        private:
            char *in_file;

    };
    struct observation
    {
        int keyframe_id;
        int mappoint_id;
        cv::KeyPoint pos;
    };
}

#endif