/**
 * @file main.cpp
 * @brief The driver file.
 */

#include "wav.h"
#include "wavmanip.h"
#include <iomanip>

/**
 * Main function.
 */
int main (int argc, char *argv[]){
    std::string path;
    if(argc != 2){
        std::cerr << "./wav_manager <wav filepath>" << std::endl;
        return 1;
    }else{
        path = argv[1];
    }
    
    Wav wav_obj;
    wav_obj.readFile(path);
    std::cout << std::hex << std::setfill('0') << std::setw(2) << wav_obj.buffer[0] << std::endl;
    std::cout << std::dec;
    std::cout << wav_obj.getMetaData() << std::endl;
    wavManipulation::gain_adjustment(wav_obj, 2);
    wav_obj.writeFile("out.wav");
    
    return 0;
} 