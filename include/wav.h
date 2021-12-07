/**
 * @file wav.h
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Header file for the Wav class.
 * 
 */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "wavheader.h"

#ifndef WAV_H
#define WAV_H
/**
 * @brief Class used for representing a WAV file.
 * 
 * Wav is a class that represents the audio data and header of a WAV file.
 * It also handles file I/O for the WAV file, providing an interface for interacting 
 * with header and buffer data. The header and buffer data is written and read 
 * according to the information provided at http://soundfile.sapp.org/doc/WaveFormat/.
 */
class Wav{
public:
    /**
     * @brief The vector containing the audio data as samples from -1.0 to 1.0.
     * 
     * @bug Modifying the length of the vectors causes buffer rewriting to fail.
     * 
     * This vector uses doubles to hold all of the audio data. The format of the vector 
     * is `audioData[sample][channel]`. 
     */
    std::vector<std::vector<double>> audioData;
    /**
     * @brief Flag denoting whether a file has been successfully loaded or not.
     * 
     * A Wav object should generally not be operated on until this is `true`.
     */
    bool fileLoaded = false;
private:
    wav_header header;
    unsigned char* buffer; //i.e. the sound data after the header - only used for file i/o
    
    std::string fileName;
    
    int samplesPerChannel; //samples per channel - must be updated whenever a length-modifying action happens
public:
    /**
     * @brief Get the audio format, where 1 indicates PCM and others indicate compression.
     * 
     * @return The audio format ID.
     */
    short getAudioFormat() const;
    /**
     * @brief Get the number of channels of the audio file.
     * 
     * @return The number of channels.
     */
    short getNumChannels() const;
    /**
     * @brief Get the sample rate of the audio file.
     * 
     * @return The sample rate in hertz.
     */
    int getSampleRate() const;
    /**
     * @brief Get the number of samples per channel in the audio file.
     * 
     * @return The number of samples per channel.
     */
    int getSamplesPerChannel() const;
    /**
     * @brief Calculates the position of a sample in seconds based on the sample rate.
     * 
     * @return The integer position of the sample in audioData.
     */
    int secondAsSample(double sec) const;
    /**
     * @brief Get the full metadata contained in the WAV header, returning a formatted string.
     * 
     * Does NOT fit assignment requirements, and is provided for debug.
     * 
     * @return A formatted string containing WAV header data.
     */
    std::string getHeaderData() const;
    /**
     * @brief Get the metadata of the WAV file required by the assignment.
     * 
     * @return A formatted string containing the WAV metadata from the assignment.
     */
    std::string getMetaData() const;
    /**
     * @brief Loads all audio data into the audioData buffer as doubles.
     */
    void loadAudioData();
    /**
     * @brief Rewrites the buffer using the current contents of audioData.
     */
    void rewriteBuffer();
    /**
     * @brief Return `value`, or the maximum bounds passed in if `value` exceeds them.
     * 
     * Manual implementation of std::clamp from C++17.
     */
    template <typename T>
    static T clamp (T value, T minValue, T maxValue);
    /**
     * @brief Read the WAV file at a certain path, loading data into this class.
     * 
     * @param fileName The file's path.
     */
    void readFile(const std::string &fileName);
    /**
     * @brief Write to a WAV file at a certain path, using data from this class.
     * 
     * @param fileName The file's path.
     */
    void writeFile(const std::string &fileName);
    /**
     * @brief Check the header strings to see if it appears valid.
     * 
     * This is done by checking the individual characters of the chunk headers, which
     * are "RIFF", "WAVE", "fmt ", and "data".
     * 
     * @return true if the chunk headers appear to be valid.
     * @return false if the chunk headers don't appear to be valid.
     */
    bool checkHeader() const;
    /**
     * Class destructor.
     */
    ~Wav();
    /**
     * @brief Free the buffer.
     */
    void freebuffer();

};
#endif