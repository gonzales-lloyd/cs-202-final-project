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
public: //change to private as necessary
    wav_header header;
    unsigned char* buffer; //i.e. the sound data after the header - only used for file i/o
    std::string fileName;
    std::vector<std::vector<double>> audioData;
    int numSamples; //must be recalculated whenever audioData's size might be changed
    //isValid() (check for standard wav structure, reject otherwise)
public:
    /**
     * Get the full metadata contained in the WAV header, returning a formatted string.
     * Does NOT fit assignment requirements, and is provided for debug.
     * 
     * @return A formatted string containing WAV header data.
     */
    std::string getHeaderData() const;
    /**
     * Get the metadata of the WAV file required by the assignment.
     * 
     * @return A formatted string containing the WAV metadata from the assignment.
     */
    std::string getMetaData() const;
    /**
     * Loads all audio data into the audioData buffer as doubles.
     */
    void loadAudioData();
    /**
     * Rewrites the buffer using the current contents of audioData.
     */
    void rewriteBuffer();
    /**
     * Return value, or the maximum bounds passed in if value exceeds them.
     * 
     * Manual implementation of std::clamp from C++17.
     */
    template <typename T>
    T clamp (T value, T minValue, T maxValue);
    /**
     * Read the WAV file at a certain path, loading data into this class.
     * 
     * @param fileName The file's path.
     */
    void readFile(const std::string &fileName);
    /**
     * Write to a WAV file at a certain path, using data from this class.
     * 
     * @param fileName The file's path.
     */
    void writeFile(const std::string &fileName);
    /**
     * Get the size of the buffer.
     */
    int getBufferSize() const;
    /**
     * Return the buffer.
     */
    unsigned char* getBuffer();
    /**
     * Class destructor.
     */
    ~Wav();

};
#endif