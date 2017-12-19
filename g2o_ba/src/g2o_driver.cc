#include <iostream>

#include "parser.h"

/**
 *  @Author: Falezza Fabio
 *  This is a driver for bundle adjustment done with g2o.
 *  Usage:
 *  g2o_driver [input_file] [output_file]
 *  
 *  if out it is not specified then result will be printed on stdout.
 * 
 *  Input files must be compatible as specified here http://grail.cs.washington.edu/projects/bal/
 */

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        std::cout << "Wrong usage of the driver. open g2o_driver.cc for more info" << std::endl;
        return 0;
    }
    char *input_filename = argv[1];  //first argument must be input filename
    char *output_filename = argv[2]; //second argument must be output filename

    std::cout << "input_filename: " << input_filename << std::endl;
    std::cout << "output_file: " << output_filename << std::endl;

    driver::Parser *parser = new driver::Parser(input_filename, output_filename);

    delete parser;
    return 0;
}