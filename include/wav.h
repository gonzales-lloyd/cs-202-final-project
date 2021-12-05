/**
 * @file wav.h
 * @brief Header file for the Wav class.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "wavheader.h"

#ifndef WAV_CLASS
#define WAV_CLASS
/**
 * Class for representing a WAV file.
 */
class Wav{
public:
    std::vector<std::vector<double>> audioData;

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
    T clamp (T value, T minValue, T maxValue);
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
     * Class destructor.
     */
    ~Wav();

};
#endif