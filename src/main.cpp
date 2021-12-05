/**
 * @file main.cpp
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief The driver file.
 * 
 * @bug Invalid inputs on main menu are not cleared and cause segfaults
 * 
 * This file should only be used for the console version, where applicable.
 * 
 */

#include "wav.h"
#include "wavmanip.h"
#include <iomanip>

bool cinFailCheck(){
    if(std::cin.fail()){
        std::cout << "Invalid value entered - returning to start." << std::endl;
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        return true;
    }
    return false;
}

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
                WavManipulation::normalize(wav_obj);
            }else if(userInput == "2"){
                int delay;
                double gain;

                std::cout << "Enter what position you want the delay to start: ";
                std::cin >> delay;
                if(cinFailCheck()){continue;}

                std::cout << "Enter what you want the gain to be, less than 1: ";
                std::cin >> gain;
                if(cinFailCheck()){continue;}
                WavManipulation::echo(wav_obj, gain, delay, 0.5, 0.5);
            }else if(userInput == "3"){
                double gain;

                std::cout << "Enter the desired scale factor: ";
                std::cin >> gain;

                if(cinFailCheck()){continue;}

                WavManipulation::adjust_gain(wav_obj, gain);
            }else if(userInput == "4"){
                int delay;
                double prop;
                double gain;

                std::cout << "Enter the delay in samples: ";
                std::cin >> delay;
                if(cinFailCheck()){continue;}

                std::cout << "Enter the prop: ";
                std::cin >> prop;
                if(cinFailCheck()){continue;}

                std::cout << "Enter what you want the gain to be: ";
                std::cin >> gain;
                if(cinFailCheck()){continue;}

                WavManipulation::lowpass(wav_obj, delay, prop, gain);
            }else if(userInput == "5"){
                double threshold;
                double attenuation_factor;

                std::cout << "Enter the sample amplitude threshold to start attenuating audio, from 0 to 1 (1 being the max amplitude of the audio): ";
                std::cin >> threshold;
                std::cout << threshold << std::endl;
                if(cinFailCheck()){continue;}

                std::cout << "Enter the attenuation factor for samples over the threshold, from 0 to 1 (1 restricts all audio to the threshold, 0 leaves audio unchanged): ";
                std::cin >> attenuation_factor;
                if(cinFailCheck()){continue;}
                WavManipulation::compress(wav_obj, threshold, attenuation_factor);
            }else{
                std::cout << "Invalid option - returning to start." << std::endl;
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                continue;
            }
            std::cout << "Please enter the save location:" << std::endl;
            std::string newpath;
            std::cin >> newpath;
            try{
                wav_obj.rewriteBuffer();
                wav_obj.writeFile(newpath);
                std::cout << "File \"" << newpath << "\" saved."
                          << "\n" << "============================================" << "\n" << std::endl;
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
    //return consoleLoop();

    /*
    std::string path;
    if(argc != 2){
        std::cerr << "./wav_manager <wav filepath>" << std::endl;
        return 1;
    }else{
        path = argv[1];
    }
    */

    std::string path = "test_files/echotest.wav";

    Wav wav_obj;
    wav_obj.readFile(path);
    //WavManipulation::normalize(wav_obj);
    WavManipulation::echo(wav_obj, 0.0, 2.5, 0.5, -1);
    //WavManipulation::adjust_gain(wav_obj,10);

    wav_obj.rewriteBuffer();
    wav_obj.writeFile("out.wav");
    //a.save("out.wav");


    /*
    Wav wav_obj;
    wav_obj.readFile(path);
    std::cout << std::hex << std::setfill('0') << std::setw(2) << wav_obj.buffer[0] << std::endl;
    std::cout << std::dec;
    std::cout << wav_obj.getMetaData() << std::endl;
    wavManipulation::gain_adjustment(wav_obj, 0.01);
    wav_obj.writeFile("out.wav");
    */
    
    
    /* AudioFile<double> a;
    bool loadedOK = a.load(path);

    Wav wav_obj;
    wav_obj.readFile(path);

    for (int i = 0; i < a.getNumSamplesPerChannel(); i++){
        for (int channel = 0; channel < a.getNumChannels(); channel++){
            wav_obj.audioData[channel][i] *= 0.1;
        }
    } */
    return 0;
}