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
    int bits_per_sample = WavIO::getByteSize(path);
    if(bits_per_sample <= 8){
        Wav<unsigned char> wav_obj;
    }else if(bits_per_sample <=16){
        Wav<short> wav_obj;
    }

    wav_obj.readFile(path);
    std::cout << std::hex << std::setfill('0') << std::setw(2) << wav_obj.buffer[0] << std::endl;
    std::cout << std::dec;
    wavManipulation::gain_adjustment(wav_obj, 0.2);
    
    return 0;
} 