/**
 * @file wav.h
 * @brief Header file for the Wav class.
 */

#include <fstream>
#include <iostream>
#include <string>
#include "wavheader.h"

class WavIO{
public:
    static int getByteSize(const std::string &fileName){
        std::ifstream wav_file(fileName, std::ios::binary | std::ios::in);
        if(wav_file.is_open()){
            wav_header header;
            wav_file.read((char*)&header, sizeof(wav_header)); //read into `header` by reading a number of bytes equivalent to the size of the struct
            wav_file.close();
            return header.bits_per_sample;
        }else{
            return -1;
        }
    }
};

#ifndef WAV_CLASS
#define WAV_CLASS
/**
 * Class for representing and performing file I/O on a WAV file.
 * 
 * https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
 */
template <typename T>
class Wav{
public: //change to private as necessary
    wav_header header;
    T* buffer; //i.e. the sound data after the header
    //maybe worth considering a template for buffers of various sizes? (8,16, 32 etc)
public:
    /**        //for(int i = 0; i<wav_obj.header.buffer_size; i++){
        //    std::cout << wav_obj.buffer[i] << std::endl;
        //}
     * Read the WAV file at a certain path, loading data into this class.
     * 
     * @param fileName The file's path.
     */
    void readFile(const std::string &fileName){
        std::ifstream wav_file(fileName, std::ios::binary | std::ios::in);
        if(wav_file.is_open()){
            wav_file.read((char*)&header, sizeof(wav_header)); //read into `header` by reading a number of bytes equivalent to the size of the struct
            buffer = new T[header.buffer_size]; //allocate memory for the buffer
            wav_file.read((char*)buffer, header.buffer_size); //read remainder of file equal to buffer size into buffer
            wav_file.close();
        }
    }
    /**
     * Write to a WAV file at a certain path, using data from this class.
     * 
     * @param fileName The file's path.
     */
    void writeFile(const std::string &fileName){
        std::ofstream wav_file(fileName, std::ios::binary | std::ios::out);
        wav_file.write((char*)&header, sizeof(wav_header));
        wav_file.write((char*)buffer, header.buffer_size);
        wav_file.close();
    }
    /**
     * Get the size of the buffer.
     */
    int getBufferSize() const{
        return header.buffer_size;
    }
    /**
     * Return the buffer.
     */
    T* getBuffer(){
        return buffer;
    }
    /**
     * Class destructor.
     */
    ~Wav(){
        if(buffer != NULL){
            delete[] buffer;
        }
    }
};
#endif