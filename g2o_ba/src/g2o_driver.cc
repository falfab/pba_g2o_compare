#include <iostream>

#include "parser.h"
#include "mappoint.h"
#include "keyframe.h"
#include "bundle_adjustment.h"

#include <fstream>
#include <chrono>

/**
 *  @Author: Falezza Fabio, Davide Miglioranzi
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

    if (argc < 2)
    {
        std::cout << "Wrong usage of the driver. open g2o_driver.cc for more info" << std::endl;
        return 0;
    }
    char *input_filename = argv[1]; //first argument must be input filename

    std::cout << "input_filename: " << input_filename << std::endl;

    driver::Parser *parser = new driver::Parser(input_filename);

    std::vector<MapPoint *> vMp;
    std::vector<KeyFrame *> vKf;

    std::cout << "Parsing file..." << std::endl;
    parser->ParseFile(vKf, vMp);
    std::cout << "DONE." << std::endl;

    BundleAdjustment *ba = new BundleAdjustment();

    std::cout << "Running bundle adjustment..." << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    long int opt_duration = ba->Execute(vKf, vMp);
    std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    std::cout << "DONE." << std::endl;

    std::cout << "Optimization execution time: " << opt_duration << " ms." << std::endl;
    std::cout << "Total execution time       : " << duration << " ms." << std::endl;

    std::ofstream file;
    file.open("../../times/g2o.csv", std::ios_base::app);
    file << duration << ";" << opt_duration << ";" << std::endl;
    file.close();

    // delete parser;
    return 0;
}