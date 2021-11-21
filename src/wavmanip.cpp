#include "wavmanip.h"
#include <cmath>

void wavManipulation::gain_adjustment(Wav &wav_obj, float scale){
    for(int i = 0; i<wav_obj.header.buffer_size; i++){
        auto sample = wav_obj.buffer[i];
        if(sample<0){
            wav_obj.buffer[i] = std::abs(wav_obj.buffer[i]) * -scale;
        }else{
            wav_obj.buffer[i] = std::abs(wav_obj.buffer[i]) * scale;
        }
    }
}