/**
 * @file wav.cpp
 * @brief Implementation file for the Wav class.
 * 
 * Adapted from Dr. Lancaster's video.
 */

#include "wav.h"

/**
 * Read the input file and store WAV information to `header` and `buffer`.
 * 
 * No error-checking or error output is currently provided.
 * 
 * @param fileName The input file path.
 */
void Wav::readFile(const std::string &fileName){
    std::ifstream wav_file(fileName, std::ios::binary | std::ios::in);
    if(wav_file.is_open()){
        wav_file.read((char*)&header, sizeof(wav_header)); //read into `header` by reading a number of bytes equivalent to the size of the struct
        buffer = new unsigned char[header.buffer_size]; //allocate memory for the buffer
        wav_file.read((char*)buffer, header.buffer_size); //read remainder of file equal to buffer size into buffer
        wav_file.close();
    }
}

/**
 * Write to the output file using the WAV information stored in `header` and `buffer`.
 * 
 * No error-checking or error output is currently provided.
 * 
 * @param fileName The output file path.
 */
void Wav::writeFile(const std::string &fileName){
    std::ofstream wav_file(fileName, std::ios::binary | std::ios::out);
    wav_file.write((char*)&header, sizeof(wav_header));
    wav_file.write((char*)buffer, header.buffer_size);
    wav_file.close();
}

/**
 * Get the full contents of the buffer (i.e. audio data).
 * 
 * @return The buffer.
 */
unsigned char* Wav::getBuffer(){
    return buffer;
}

/**
 * Get the size of the buffer (i.e. audio data).
 * 
 * @return The buffer.
 */
int Wav::getBufferSize() const{
    return header.buffer_size;
}

/**
 * Destructor for the Wav class.
 * 
 * Ensures that if the Wav class's destructor is called, the memory 
 * allocated for the buffer is deallocated as well.
 */
Wav::~Wav(){
    if(buffer != NULL){
        delete[] buffer;
    }
}

