/**
 * @file main.cpp
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief The driver file.
 * 
 * This file should only be used for the console version, where applicable.
 * 
 */

#include "menulogic.h"

/**
 * Main function.
 */
int main (int argc, char *argv[]){
    return MenuLogic::consoleLoop();

    //The code below remains for debugging purposes.
    /* 
    std::string path;
    if(argc != 2){
        std::cerr << "./wav_manager <wav filepath>" << std::endl;
        return 1;
    }else{
        path = argv[1];
    }

    std::string path = "test_files/echotest.wav";

    Wav wav_obj;
    wav_obj.readFile(path);
    //WavManipulation::normalize(wav_obj);
    WavManipulation::echo(wav_obj, 0.0, 2.5, 0.5, -1);
    //WavManipulation::adjust_gain(wav_obj,10);

    wav_obj.rewriteBuffer();
    wav_obj.writeFile("out.wav");
    //a.save("out.wav");

    return 0;
    */
}