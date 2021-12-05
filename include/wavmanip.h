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
#include <cmath>

#ifndef WAVMANIP_H
#define WAVMANIP_H

class WavManipulation{
public:
    static void adjust_gain(Wav &wav_obj, float scale); 
    static void echo(Wav& wav_obj, double start_sec, double end_sec, double decay_factor, double delay);
    static void normalize(Wav &wav_obj);
    static void compress(Wav &wav_obj, double threshold, double attenuation);
    static void lowpass(Wav &wav_obj, int delay, double gain);
};

#endif