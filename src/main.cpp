/**
 * @file main.cpp
 * @brief The driver file.
 */

#include "wav.h"

/**
 * Main function.
 */
int main (int argc, char *argv[]){
    std::string path = "test_files/CantinaBand3.wav";
    Wav wav_obj;
    wav_obj.readFile(path);
    std::cout << wav_obj.getBufferSize() << std::endl;
    return 0;
} 