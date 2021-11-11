//initial function definitions from Dr. Lancaster's video

#include "wav.h"
void Wav::readFile(const std::string &fileName){
    std::ifstream wav_file(fileName, std::ios::binary | std::ios::in);
    if(wav_file.is_open()){
        wav_file.read((char*)&header, sizeof(wav_header)); //read into `header` by reading a number of bytes equivalent to the size of the struct
        buffer = new unsigned char[header.buffer_size]; //allocate memory for the buffer
        wav_file.read((char*)buffer, header.buffer_size); //read remainder of file equal to buffer size into buffer
        wav_file.close();
    }
}

void Wav::writeFile(const std::string &fileName){
    std::ofstream wav_file(fileName, std::ios::binary | std::ios::out);
    wav_file.write((char*)&header, sizeof(wav_header));
    wav_file.write((char*)buffer, header.buffer_size);
    wav_file.close();
}

unsigned char* Wav::getBuffer(){
    return buffer;
}

int Wav::getBufferSize() const{
    return header.buffer_size;
}

Wav::~Wav(){
    if(buffer != NULL){
        delete[] buffer;
    }
}

