/**
 * @file wavmanip.cpp
 * @author Grant Pellegrini (GrantPellegrini)
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Header file for the WavManipulation class.
 * 
 * WavManipulation is a set of static functions that process Wav objects 
 * in varying ways. They *do not* change the length of the audio data.
 * 
 * @par 
 * The following processors are available:
 *  - Gain adjustment (adjust_gain)
 *  - Echo (echo)
 *  - Normalization (normalize)
 */

#include "wav.h"
#include <algorithm>

class WavManipulation{
public:
    static void adjust_gain(Wav &wav_obj, float scale); 
    static void echo(Wav &wav_obj, double gain, int delay);
    static void normalize(Wav &wav_obj);
};