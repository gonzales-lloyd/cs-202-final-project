/**
 * @file menulogic.cpp
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Implementation file for the MenuLogic class.
 */

#include "menulogic.h"

bool MenuLogic::cinFailCheck(){
    if(std::cin.fail()){
        std::cout << "Invalid value entered - returning to start." << std::endl;
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        return true;
    }
    return false;
}

bool MenuLogic::normalizeMenu(Wav &wav_obj){
    //well, there's nothing to ask but that could change one day
    WavManipulation::normalize(wav_obj);
    return true;
}

bool MenuLogic::echoMenu(Wav &wav_obj){
    double start_sec, end_sec, decay_factor, delay;

    std::cout << "Enter the start of the audio to be echoed, in seconds: " << "\n>>> ";
    std::cin >> start_sec;
    if(cinFailCheck()){return false;}

    std::cout << "Enter the end of the audio to be echoed, in seconds: " << "\n>>> ";
    std::cin >> end_sec;
    if(cinFailCheck()){return false;}

    std::cout << "Enter the decay factor (for example, 0.5 halves the amplitude of the echoed audio each time): " << "\n>>> ";
    std::cin >> decay_factor;
    if(cinFailCheck()){return false;}

    std::cout << "Enter the delay between each audio, in seconds (negative delays cause overlapping audio after the first echo): " << "\n>>> ";
    std::cin >> delay;
    if(cinFailCheck()){return false;}

    WavManipulation::echo(wav_obj, start_sec, end_sec, decay_factor, delay);
    return true;
}

bool MenuLogic::gainMenu(Wav &wav_obj){
    double gain;

    std::cout << "Enter the desired scale factor: " << "\n>>> ";
    std::cin >> gain;

    if(cinFailCheck()){return false;}

    WavManipulation::adjust_gain(wav_obj, gain);
    return true;
}

bool MenuLogic::lowPassMenu(Wav &wav_obj){
        int delay;
        double gain;

        std::cout << "Enter the delay (in samples): " << "\n>>> ";
        std::cin >> delay;
        if(cinFailCheck()){return false;}

        std::cout << "Enter what you want the gain to be: " << "\n>>> ";
        std::cin >> gain;
        if(cinFailCheck()){return false;}

        WavManipulation::lowpass(wav_obj, delay, gain);
        return true;
}

bool MenuLogic::compressionMenu(Wav &wav_obj){
    double threshold;
    double attenuation_factor;

    std::cout << "Enter the sample amplitude threshold to start attenuating audio, from 0 to 1 (1 being the max amplitude of the audio): " << "\n>>> ";
    std::cin >> threshold;
    std::cout << threshold << std::endl;
    if(cinFailCheck()){return false;}

    std::cout << "Enter the attenuation factor for samples over the threshold, from 0 to 1 (1 restricts all audio to the threshold, 0 leaves audio unchanged): " << "\n>>> ";
    std::cin >> attenuation_factor;
    if(cinFailCheck()){return false;}

    WavManipulation::compress(wav_obj, threshold, attenuation_factor);
    return true;
}

bool MenuLogic::promptSave(Wav &wav_obj){
    std::cout << "Please enter the save location:" << "\n>>> ";
    std::string newpath;
    std::cin >> newpath;
    try{
        wav_obj.writeFile(newpath);
        std::cout << "File \"" << newpath << "\" saved."
                    << "\n" << "============================================" << std::endl;
    }catch(const std::runtime_error &e){
        std::cout << e.what() << std::endl;
        std::cout << "Please try again." << std::endl;
        return false;
    }
    return true;
}

int MenuLogic::consoleLoop(){
    std::cout << "CS 202 Final Project"
              << "\n" << "Group 33: Austin Zube, Grant Pellegrini, Lloyd Gonzales"
              << "\n" << "WAV manipulation program"
              << "\n" << "============================================"
              << std::endl;
    while(true){
        //ask for filepath
        std::string filepath;
        std::cout << "Enter filepath of wav file ('q' to quit): " << "\n>>> "; 
        std::cin >> filepath;
        if(filepath == "q"){
            break;
        }else{
            //initialize wav object
            Wav wav_obj;
            try{
                wav_obj.readFile(filepath);
            }catch(const std::runtime_error &e){
                std::cout << e.what() << std::endl;
                std::cout << "Please try again." << std::endl;
                continue;
            }
            //print metadata and options
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
                      << "\n>>> ";
            std::cin >> userInput;
            //option logic
            if(userInput == "q"){
                break;
            }else if(userInput == "r"){
                continue;
            }else if(userInput == "1"){
                if(!normalizeMenu(wav_obj)){
                    continue;
                }
            }else if(userInput == "2"){
                if(!echoMenu(wav_obj)){
                    continue;
                }
            }else if(userInput == "3"){
                if(!gainMenu(wav_obj)){
                    continue;
                }
            }else if(userInput == "4"){
                if(!lowPassMenu(wav_obj)){
                    continue;
                }
            }else if(userInput == "5"){
                if(!compressionMenu(wav_obj)){
                    continue;
                }
            }else{
                std::cout << "Invalid option - returning to start." << std::endl;
                std::cin.clear();
                std::cin.ignore(10000,'\n');
                continue;
            }
            //save logic
            //it doesn't really matter if we continue or not since this is the end
            //but what if we wanted to allow the user to chain processors in the future?
            if(!promptSave(wav_obj)){
                continue;
            }
        }
    }
    return 0;
}