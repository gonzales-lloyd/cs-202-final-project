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
    }else{
        throw std::runtime_error("Couldn't open file");
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
     * This code is adapted from Dr. Lancaster's video.
     * 
     * A previous commmit used methodology from https://github.com/adamstark/AudioFile/blob/master/AudioFile.h.
     * This originally manually converted the bytes in `buffer` into individual int16s or 32s.
     * It has been replaced with Dr. Lancaster's array cast method instead.
     * 
     * The following multiline comment describes the old method for forming the 16-bit samples.
     * -Lloyd Gonzales
     */

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
     * The process of combining the two bytes LE is complete. The process can be used similarly
     * for other byte sizes, as well.
     */

    //Prepare vector to support the number of channels ahead of time
    //Note that the vector is audioData[channel][sample number]
    audioData.resize(header.num_channels);

    int numSamples = header.buffer_size / (header.num_channels * header.bits_per_sample / 8);
    if(header.bits_per_sample == 8){
        for(int i = 0; i<numSamples; i++){
            for(int channel = 0; channel<header.num_channels; channel++){
                unsigned char data = buffer[(i*header.num_channels)+channel];
                //now convert this to a double
                //to do so, treat data as if it were signed and divide by the max of a signed char
                double sample = (double)(data-128)/(double)(128.0);
                //and push this to the relevant position in audioData
                audioData[channel].push_back(sample);
            }
        }
    }else if (header.bits_per_sample == 16){
        signed short* shortBuffer = reinterpret_cast<signed short*>(buffer);
        for(int i = 0; i<numSamples; i++){
            for(int channel = 0; channel<header.num_channels; channel++){
                signed short data = shortBuffer[(i*header.num_channels)+channel];
                //and convert to double by dividing by the max of a signed short
                double sample = (double)(data)/(double)(32768.0);
                //and push this to the relevant place in audioData
                audioData[channel].push_back(sample);
            }
        }
    }else{
        throw std::logic_error("Attempted to decode non 8/16-bit buffer");
    }
}

void Wav::rewriteBuffer(){
    int numSamples = header.buffer_size / (header.num_channels * header.bits_per_sample / 8);
    if(header.bits_per_sample == 8){
        for(int i = 0; i<numSamples; i++){
            for(int channel = 0; channel<header.num_channels; channel++){
                //ensure sample is within double bounds
                double sample = clamp(audioData[channel][i], -1.0, 1.0);
                //undo our signed assumption from earlier
                sample = (sample + 1.0) / 2.0;
                //and turn it back into an unsigned char
                unsigned char sampleAsInt = (unsigned char)(sample*255.0);
                //rewrite 1:1 back into buffer
                buffer[(i*header.num_channels)+channel] = sampleAsInt;

            }
        }
    }else if (header.bits_per_sample == 16){
        signed short* shortBuffer = reinterpret_cast<signed short*>(buffer);
        for(int i = 0; i<numSamples; i++){
            for(int channel = 0; channel<header.num_channels; channel++){
                //ensure sample is within double bounds
                double sample = clamp(audioData[channel][i], -1.0, 1.0);
                //undo the signed short to double conversion from earlier
                signed int sampleAsInt = (signed int)(sample*32767.0);
                //write into shortBuffer
                shortBuffer[(i*header.num_channels)+channel] = sampleAsInt;
            }
        }
        //finally, recast buffer and rewrite
        buffer = reinterpret_cast<unsigned char*>(buffer);
    }else{
        throw std::logic_error("Attempted to decode non 8/16-bit buffer");
    }
}

template <typename T>
T Wav::clamp(T value, T minvalue, T maxValue){
    value = std::min(value, maxValue);
    value = std::max(value, minvalue);
    return value;
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

