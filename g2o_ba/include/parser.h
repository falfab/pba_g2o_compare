#ifndef PARSER_H
#define PARSER_H

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

        private:
            char *in_file;
            char *out_file;

    };
}

#endif