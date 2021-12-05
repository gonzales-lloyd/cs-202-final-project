/**
 * @file wavmanip.cpp
 * @author Grant Pellegrini (GrantPellegrini)
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Header file for the WavManipulation class.
 * 
 */

#include "wav.h"
#include <algorithm>
#include <cmath>

#ifndef WAVMANIP_H
#define WAVMANIP_H

/**
 * @brief Class containing the WAV processor functions.
 * 
 * WavManipulation is a set of static functions that process Wav objects 
 * in varying ways. They *do not* change the length of the audio data.
 * 
 * The following processors are available:
 *  - Gain adjustment (adjust_gain)
 *  - Echo (echo)
 *  - Normalization (normalize)
 *  - Compression (compress)
 *  - Low-pass filter (lowpass)
 * 
 */
class WavManipulation{
public:
    /**
     * @brief Scale the amplitude of the audio data contained in a Wav object.
     * 
     * @param wav_obj A Wav object.
     * @param scale The factor to scale the audio by.
     */
    static void adjust_gain(Wav &wav_obj, float scale); 
    /**
     * @brief Generate an echo of the selected audio in a Wav object.
     * 
     * @bug Excessive values for `end_sec` appear to cause the program to stall.
     * 
     * This implementation does not behave like the Audacity implementation or the
     * implementation used in Dr. Lancaster's echo videos. 
     * 
     * To generate an echo, this function isolates the audio selected by the `start_sec` 
     * and `end_sec` parameters, and then starts repeating the audio (typically softer each time) 
     * after the end of the audio selection. The delay allows the echoes to overlap (if negative) or
     * be followed by silence on each echo (if positive).
     * 
     * Note that the decay factor is multiplicative - after one echo, a decay factor of 0.5 causes
     * the next echo to have an amplitude 0.25 times that of the original selection.
     * 
     * @param wav_obj A Wav object.
     * @param start_sec The start time of the selection, in seconds.
     * @param end_sec The end time of the selection, in seconds.
     * @param decay_factor 
     * @param delay 
     */
    static void echo(Wav& wav_obj, double start_sec, double end_sec, double decay_factor, double delay);
    static void normalize(Wav &wav_obj);
    static void compress(Wav &wav_obj, double threshold, double attenuation);
    static void lowpass(Wav &wav_obj, int delay, double gain);
};

#endif