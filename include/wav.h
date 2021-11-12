/**
 * @file wav.h
 * @brief Header file for the Wav class.
 */

#include <fstream>
#include <iostream>
#include <string>
#include "wavheader.h"

/**
 * Class for representing and performing file I/O on a WAV file.
 */
class Wav{
public: //change to private as necessary
    wav_header header;
    unsigned char* buffer; //i.e. the sound data after the header
public:
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