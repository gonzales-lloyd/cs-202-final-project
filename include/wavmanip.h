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
     * @param decay_factor The scaling factor of each echo.
     * @param delay The delay between each echo, in seconds.
     */
    static void echo(Wav& wav_obj, double start_sec, double end_sec, double decay_factor, double delay);
    /**
     * @brief Normalize the audio of a Wav object.
     * 
     * In other words, identify the sample with the highest amplitude, and scale the rest of the audio 
     * such that the identified sample has the maximum amplitude.
     * 
     * @param wav_obj The Wav object to normalize.
     */
    static void normalize(Wav &wav_obj);
    /**
     * @brief Compress audio that exceeds a certain threshold in a Wav object.
     * 
     * For example: If the threshold is set to be 90% of the maximum amplitude and the attenuation
     * factor is set to 0.5, then a sample that is 110% of the maximum amplitude would be 
     * attenuated to 100%. 
     * 
     * Note that both `threshold` and `attenuation` are clamped to 0.0 and 1.0. If either variable
     * goes outside these bounds, then they are automatically set to either the maximum or minimum bound
     * as necessary.
     * 
     * @param wav_obj A Wav object.
     * @param threshold The threshold, as a decimal from 0 to 1.
     * @param attenuation The scaling factor of audio that exceeds the threshold, as a decimal from 0 to 1.
     */
    static void compress(Wav &wav_obj, double threshold, double attenuation);
    /**
     * @brief Apply a low-pass filter to the audio data in a Wav object.
     * 
     * We're not quite sure if this works, but it adheres to the diagram posted in the
     * CS202 Discord channel.
     * 
     * @param wav_obj A Wav object.
     * @param delay The delay of the filter in samples (not seconds).
     * @param gain The gain of delayed samples.
     */
    static void lowpass(Wav &wav_obj, int delay, double gain);
};

#endif