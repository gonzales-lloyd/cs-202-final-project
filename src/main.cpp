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
    std::string path = "test_files/CantinaBand3.wav";
    Wav wav_obj;
    wav_obj.readFile(path);
    std::cout << std::hex << std::setfill('0') << std::setw(2) << wav_obj.buffer[0] << std::endl;
    std::cout << std::dec;
    //std::cout << wav_obj.getHeaderData() << std::endl;
    wavManipulation::gain_adjustment(wav_obj, 2);
    wav_obj.writeFile("out.wav");
    
    return 0;
} 