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
        loadAudioData();
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

void Wav::loadAudioData(){
    /**
     * This code is adapted from https://github.com/adamstark/AudioFile/blob/master/AudioFile.h.
     * The rewritten code below only supports 8 and 16 bit (where this should have been checked
     * as part of the header checks.)
     * 
     * Understanding *how* the 24-bit implementation works is a bit outside of my understanding.
     * Implementing either 24 or 32-bit into this function would be no better than copy-pasting
     * the public implementation, so I haven't.
     * 
     * -Lloyd Gonzales
     */

    //Number of samples inside buffer
    int numSamples = header.buffer_size / (header.num_channels * header.bits_per_sample / 8); 
    //Prepare vector to support the number of channels ahead of time
    //Note that the vector is audioData[channel][sample number]
    audioData.resize(header.num_channels);

    //iterate over sample, then channel
    for(int i=0; i<numSamples; i++){
        for(int channel=0; channel<header.num_channels; channel++){
            /**
             * In the buffer array, the position/index of the next relevant audio sample, 
             * taking into consideration the number of channels, is equal to (sample_alignment *i).
             * Each index of i would jump over a full sample, including however many number of channels
             * are in each sample. So, to divide a single sample into its channels, it's necessary to
             * get the offset as well by using bits_per_sample to get the sample of a given channel.
             */
            int samplePos = (header.sample_alignment * i) + (channel * header.bits_per_sample);

            if(header.bits_per_sample == 8){
                //get 1 byte of data from the buffer starting from the index we've determined
                //this happens to simply be equivalent to saying buffer[samplePos]
                //note that in WAV files, samples of 8-bit are unsigned; 9-bit and higher are signed
                unsigned char data = buffer[samplePos];
                //now convert this to a double
                //to do so, treat data as if it were signed and divide by the max of a signed char
                double sample = (double)(data-128)/(double)(128.0);
                //and push this to the relevant position in audioData
                audioData[channel].push_back(sample);
            }else if(header.bits_per_sample == 16){
                /**
                 * Since our buffer is stored as a series of signed shorts, we'd need
                 * to get the two bytes and convert it to its equivalent integer value
                 * manually. To do so, assuming LE (which should be true), then we first
                 * get the most significant byte and shift it 8 bits down.
                 * 
                 * Pretend our sample is as follows:
                 * SamplePos
                 * v
                 * 00100100 10001000
                 * (36)     (136)
                 * 
                 * To combine these two values, we can't just add them together.
                 * Instead, we start by declaring a 16-bit signed short:
                 * `signed short data;`
                 * 00000000 00000000
                 * 
                 * For the left side of the expression, we take the second byte and treat it as a short:
                 * `signed short data = buffer[samplePos+1] << 8`
                 * 00000000 10001000 -> 10001000 00000000
                 * (136)                (-30720)
                 * 
                 * Then, in the right sie of the expression, we OR it with the first byte:
                 * `signed short data = data | buffer[samplePos]
                 * 10001000 00000000 -> 10001000 00100100
                 * (-30720)             (-30684)
                 * 
                 * The process of combining the two bytes LE is complete.
                 */
                signed short data = (buffer[samplePos+1] << 8) | buffer[samplePos];
                //and convert to double by dividing by the max of a signed short
                double sample = (double)(data)/(double)(32768.0);
                //and push this to the relevant place in audioData
                audioData[channel].push_back(sample);
            }else{
                throw std::logic_error("Attempted to decode non 8/16-bit buffer");
            }
        }
    }
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

