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
     * Read the WAV file at a certain path.
     * 
     * @param fileName The file's path.
     */
    void readFile(const std::string &fileName);
    void writeFile(const std::string &fileName);
    int getBufferSize() const;
    unsigned char* getBuffer();

    ~Wav();
};