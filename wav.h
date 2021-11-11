#include <fstream>
#include <iostream>
#include <string>
#include "wavheader.h"

class Wav{
private:
    wav_header header;
    unsigned char* buffer; //i.e. the sound data after the header
public:
    void readFile(const std::string &fileName);
    void writeFile(const std::string &fileName);
    int getBufferSize() const;
    unsigned char* getBuffer();

    ~Wav();
};