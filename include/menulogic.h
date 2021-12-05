/**
 * @file wav.h
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Header file for the main menu logic.
 * 
 * MenuLogic holds all the relevant logic for getting input from the user through the 
 * console interface.
 */

#include "wav.h"
#include "wavmanip.h"
#include <iomanip>

#ifndef MENULOGIC_H
#define MENULOGIC_H

class MenuLogic{
private:
    static bool normalizeMenu(Wav &wav_obj);
    static bool echoMenu(Wav &wav_obj);
    static bool gainMenu(Wav &wav_obj);
    static bool lowPassMenu(Wav &wav_obj);
    static bool compressionMenu(Wav &wav_obj);

    static bool cinFailCheck();

    static bool promptSave(Wav &wav_obj);
public:
    static int consoleLoop();
};
#endif