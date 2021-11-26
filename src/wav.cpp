/**
 * @file wav.cpp
 * @brief Implementation file for the Wav class.
 * 
 * Adapted from Dr. Lancaster's video.
 */

#include "wav.h"

/**
 * How the public implementation (AudioFile.h) works:
 * 
 * 1. Define a 2D vector std::vector<std::vector<T>> that holds all of the samples. 
 *    This vector is split into vector[channel][sampleIndex].
 * 2. Use the header data correctly to do things
 * 3. Validate the header data
 * 4. Once done, read through the number of bytes specified in the header
 *    and convert everything to a double
 */

/**
 * Read the input file and store WAV information to `header` and `buffer`.
 * THIS SHOULD BE THE CONSTRUCTOR SO THE WAV HEADER CAN'T BE READ BEFOREHAND
 * No error-checking or error output is currently provided.
 * 
 * @param fileName The input file path.
 */
void Wav::readFile(const std::string &fileName){
    std::ifstream wav_file(fileName, std::ios::binary | std::ios::in);
    if(wav_file.is_open()){
        this->fileName = fileName;

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

std::string Wav::getHeaderData() const{
    std::stringstream result;

    result << "\n" << "=====RIFF DESCRIPTOR====="
           << "\n" << "Chunk ID: " << header.chunk_id[0] << header.chunk_id[1] << header.chunk_id[2] << header.chunk_id[3]
           << "\n" << "Size of file excluding first 8 bytes: " << header.wav_size
           << "\n" << "Format: " << header.format[0] << header.format[1] << header.format[2] << header.format[3]
           << "\n" << "=====SUBCHUNK 1====="
           << "\n" << "Subchunk 1 header: " << header.fmt_header[0] << header.fmt_header[1] << header.fmt_header[2] << header.fmt_header[3]
           << "\n" << "Subchunk 1 size: " << header.fmt_chunk_size
           << "\n" << "Audio format (1 is linear PCM): " << header. audio_format
           << "\n" << "Number of audio channels: " << header.num_channels
           << "\n" << "Sample rate: " << header.sample_rate
           << "\n" << "Byte rate: " << header.byte_rate
           << "\n" << "Sample size*channel count (bytes): " << header.sample_alignment
           << "\n" << "Bits per sample: " << header.bits_per_sample
           << "\n" << "=====SUBCHUNK 2====="
           << "\n" << "Subchunk 2 header: " << header.data_header[0] << header.data_header[1] << header.data_header[2] << header.data_header[3]
           << "\n" << "Buffer size: " << header.buffer_size;

    return result.str();
}

std::string Wav::getMetaData() const{
    std::stringstream result;

    std::string channel_output;
    if(header.num_channels==1){
        channel_output = "1 (Mono)";
    }else if(header.num_channels==2){
        channel_output = "2 (Stereo)";
    }else{
        channel_output = std::to_string(header.num_channels);
        channel_output.append(" (Unknown)");
    }

    result << "Filename: " << fileName
           << "\n" << "Sample rate: " << header.sample_rate << " hz"
           << "\n" << "Bits per sample: " << header.bits_per_sample 
           << "\n" << "Channels: " << channel_output;
    
    return result.str();
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

