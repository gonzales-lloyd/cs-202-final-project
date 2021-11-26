/**
 * @file main.cpp
 * @brief The driver file.
 */

#include "wav.h"
#include "wavmanip.h"
#include <iomanip>

#include "AudioFile.h"

/**
 * Program logic console.
 */
int consoleLoop(){
    std::cout << "CS 202 Final Project"
              << "\n" << "Group 33: Austin Zube, Grant Pellegrini, Lloyd Gonzales"
              << "\n" << "WAV manipulation program"
              << "\n" << "============================================"
              << std::endl;
    while(true){
        std::string filepath;
        std::cout << "Enter filepath of wav file ('q' to quit): " << std::endl; 
        std::cin >> filepath;
        if(filepath == "q"){
            break;
        }else{
            Wav wav_obj;
            try{
                wav_obj.readFile(filepath);
            }catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                std::cout << "Please try again." << std::endl;
                continue;
            }
            std::cout << "Load successful."
                      << "\n" << "============================================" 
                      << std::endl;
            std::cout << wav_obj.getMetaData()
                      << "\n" << "============================================" 
                      << std::endl;
            std::string userInput;
            std::cout << "Select option:"
                      << "\n" << "==Processors=="
                      << "\n" << "1 - Normalization"
                      << "\n" << "2 - Echo"
                      << "\n" << "3 - Gain adjustment"
                      << "\n" << "4 - Low-pass filter"
                      << "\n" << "5 - Compression/limiting"
                      << "\n" << "==Commands=="
                      << "\n" << "r - Return to main menu and select another file"
                      << "\n" << "q - Quit program" 
                      << std::endl;
            //a switch block would have been preferable
            std::cin >> userInput;
            if(userInput == "q"){
                break;
            }else if(userInput == "r"){
                continue;
            }else if(userInput == "1"){
                
            }else if(userInput == "2"){

            }else if(userInput == "3"){

            }else if(userInput == "4"){

            }else if(userInput == "5"){

            }else{
                std::cout << "Invalid option - returning to main menu." << std::endl;
                continue;
            }
            std::cout << "Please enter the save location:" << std::endl;
            std::string newpath;
            std::cin >> newpath;
            try{
                wav_obj.rewriteBuffer();
                wav_obj.writeFile(newpath);
            }catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                std::cout << "Please try again." << std::endl;
                continue;
            }
        }
    }
    return 0;
}

/**
 * Main function.
 */
int main (int argc, char *argv[]){
    return consoleLoop();

    std::string path;
    if(argc != 2){
        std::cerr << "./wav_manager <wav filepath>" << std::endl;
        return 1;
    }else{
        path = argv[1];
    }
    /*
    
    Wav wav_obj;
    wav_obj.readFile(path);
    std::cout << std::hex << std::setfill('0') << std::setw(2) << wav_obj.buffer[0] << std::endl;
    std::cout << std::dec;
    std::cout << wav_obj.getMetaData() << std::endl;
    wavManipulation::gain_adjustment(wav_obj, 0.01);
    wav_obj.writeFile("out.wav");
    */
    
    AudioFile<double> a;
    bool loadedOK = a.load(path);

    /* If you hit this assert then the file path above
     probably doesn't refer to a valid audio file */
    assert (loadedOK);

    Wav wav_obj;
    wav_obj.readFile(path);

    for (int i = 0; i < a.getNumSamplesPerChannel(); i++){
        for (int channel = 0; channel < a.getNumChannels(); channel++){
            wav_obj.audioData[channel][i] *= 0.1;
        }
    }

    wav_obj.rewriteBuffer();
    wav_obj.writeFile("out.wav");
    //a.save("out.wav");
    
    return 0;
} 