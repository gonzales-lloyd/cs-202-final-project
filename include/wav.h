/**
 * @file wav.h
 * @brief Header file for the Wav class.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "wavheader.h"

#ifndef WAV_CLASS
#define WAV_CLASS
/**
 * Class for representing a WAV file.
 */
class Wav{
public: //change to private as necessary
    wav_header header;
    signed short* buffer; //i.e. the sound data after the header
    //maybe worth considering a template for buffers of various sizes? (8,16, 32 etc)
    //isValid() (check for standard wav structure, reject otherwise)
public:
    /**
     * Print the full metadata contained in the WAV header.
     * Does NOT fit assignment requirements, and is provided for debug.
     */
    std::string getHeaderData() const;
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
    signed short* getBuffer();
    /**
     * Class destructor.
     */
    ~Wav();
};
#endif