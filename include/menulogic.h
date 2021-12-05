/**
 * @file wav.h
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Header file for the MenuLogic class.
 * 
 */

#include "wav.h"
#include "wavmanip.h"
#include <iomanip>

#ifndef MENULOGIC_H
#define MENULOGIC_H

/**
 * @brief Class holding the relevant logic for the console interface, 
 * including the main menu and prompting the user for inputs.
 */
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