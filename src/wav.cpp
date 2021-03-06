/**
 * @file wav.cpp
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Implementation file for the Wav class.
 * 
 * @bug Undefined behavior if Wav object used before a file has been loaded
 * @bug No protection or checks against the length of audioData being changed
 */

#include "wav.h"

bool Wav::checkHeader() const{
    bool riff_good = (header.chunk_id[0] == 'R' && header.chunk_id[1] == 'I' && header.chunk_id[2] == 'F' && header.chunk_id[3] == 'F');
    bool format_good = (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E');
    bool fmt_header_good = (header.fmt_header[0] == 'f' && header.fmt_header[1] == 'm' && header.fmt_header[2] == 't' && header.fmt_header[3] == ' ');
    bool data_good = (header.data_header[0] == 'd' && header.data_header[1] == 'a' && header.data_header[2] == 't' && header.data_header[3] == 'a');
    
    if(riff_good && format_good && fmt_header_good && data_good){
        return true;
    }
    return false;
}

void Wav::readFile(const std::string &fileName){
    std::ifstream wav_file(fileName, std::ios::binary | std::ios::in);
    if(wav_file.is_open()){
        this->fileName = fileName;
        wav_file.read((char*)&header, sizeof(wav_header)); //read into `header` by reading a number of bytes equivalent to the size of the struct
        if(!checkHeader()){
            //alright, semantically speaking this isn't an exception
            //but this appears to be the simplest way to kick out the user
            throw std::runtime_error("This doesn't appear to be a WAV file! (The header data does not appear to be formatted as expected.)");
        }
        
        buffer = new unsigned char[header.buffer_size]; //allocate memory for the buffer
        wav_file.read((char*)buffer, header.buffer_size); //read remainder of file equal to buffer size into buffer
        
        loadAudioData();
        wav_file.clear();
        wav_file.close();
        fileLoaded = true;
    }else{
        wav_file.clear();
        throw std::runtime_error("Couldn't open file");
    }
}

void Wav::writeFile(const std::string &fileName){
    rewriteBuffer();
    std::ofstream wav_file(fileName, std::ios::binary | std::ios::out);
    if(wav_file.is_open()){
        wav_file.write((char*)&header, sizeof(wav_header));
        wav_file.write((char*)buffer, header.buffer_size);
        wav_file.close();
    }else{
        throw std::runtime_error("Couldn't open file");
    }
}

void Wav::loadAudioData(){
    /*
     * This code is adapted from Dr. Lancaster's video.
     * 
     * A previous commmit used methodology from https://github.com/adamstark/AudioFile/blob/master/AudioFile.h.
     * This originally manually converted the bytes in `buffer` into individual int16s or 32s.
     * It has been replaced with Dr. Lancaster's array cast method instead.
     * 
     * The following multiline comment describes the old method for forming the 16-bit samples.
     * -Lloyd Gonzales
    */

    /*
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

    //check if PCM, warn otherwise
    if(header.audio_format != 1){
        std::cout << "This audio does not appear to be in PCM form. Bad things may happen." << std::endl;
    }

    samplesPerChannel = header.buffer_size / (header.num_channels * header.bits_per_sample / 8);
    if(header.bits_per_sample == 8){
        for(int i = 0; i<samplesPerChannel; i++){
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
        for(int i = 0; i<samplesPerChannel; i++){
            for(int channel = 0; channel<header.num_channels; channel++){
                signed short data = shortBuffer[(i*header.num_channels)+channel];
                //and convert to double by dividing by the max of a signed short
                double sample = (double)(data)/(double)(32768.0);
                //and push this to the relevant place in audioData
                audioData[channel].push_back(sample);
            }
        }
    }else{
        //alright, semantically speaking this isn't an exception
        //but this appears to be the simplest way to kick out the user
        throw std::runtime_error("This program only supports 8- and 16-bit audio!");
    }
}

void Wav::rewriteBuffer(){
    //there needs to be a check here to see if the buffer needs to be reallocated if the length of AudioData has changed
    if(header.bits_per_sample == 8){
        for(int i = 0; i<samplesPerChannel; i++){
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
        for(int i = 0; i<samplesPerChannel; i++){
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
        //this should never happen
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

short Wav::getAudioFormat() const{
    return header.audio_format;
}

short Wav::getNumChannels() const{
    return header.num_channels;
}

int Wav::getSampleRate() const{
    return header.sample_rate;
}

int Wav::getSamplesPerChannel() const{
    return samplesPerChannel;
}

int Wav::secondAsSample(double sec) const{
    int result = header.sample_rate*sec;
    return result;
}

Wav::~Wav(){
    freebuffer();
}

void Wav::freebuffer(){
    if(fileLoaded){
        delete[] buffer;
    }
}
