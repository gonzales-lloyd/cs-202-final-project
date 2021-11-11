//Adapted from Dr. Lancaster's video and the WAV format link provided
//int = 4 bytes, short = 2, char used where applicable
typedef struct wav_header {
    //riff chunk descriptor
    char chunk_id[4]; //contains "RIFF"
    int wav_size;
    char format[4]; //should contain "WAVE"
    
    //wav/fmt subchunk
    char fmt_header[4]; //should contain "fmt "
    int fmt_chunk_size; //should be 16, the size of the remainder of the subchunk
    short audio_format; //if 1, indicates compression-less
    short num_channels; //mono=1, stereo=2
    int sample_rate; //sample rate: 8000hz, 44100hz, etc
    int byte_rate;//equal to sample rate * channel count * bitspersample/8
    short sample_alignment;//equal to bytes for one sample * the number of channels
    short bits_per_sample;

    //data subchunk
    char data_header[4]; //should contain "data"
    int data_bytes; //number of bytes in data, equal to sample count * channels * sample byte size

} wav_header;