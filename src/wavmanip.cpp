#include "wavmanip.h"

void WavManipulation::adjust_gain(Wav &wav_obj, float scale){
    for(int i = 0; i<wav_obj.getSamplesPerChannel(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
                wav_obj.audioData[channel][i] *= scale;
        }
    }
}

void WavManipulation::echo(Wav& wav_obj, double gain, int delay){
    //where delay is in samples!!
    auto temp = wav_obj.audioData;

    for(int i = 0; i<wav_obj.getNumChannels(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
            if (i > delay){ 
			    temp[channel][i] += gain * temp[channel][i - delay];
		    }
		}
    }

    for(int i = 0; i<wav_obj.getNumChannels(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
            if(i+delay < wav_obj.getNumChannels()){
                wav_obj.audioData[channel][i] += temp[channel][i + delay];
            }
		}
    }
}

void WavManipulation::normalize(Wav& wav_obj){
    //C++11: https://stackoverflow.com/questions/9874802/how-can-i-get-the-maximum-or-minimum-value-in-a-vector
    //https://stackoverflow.com/questions/10158756/using-stdmax-element-on-a-vectordouble
    //double max = *std::max_element(wav_obj.audioData.begin(), wav_obj.audioData.end());

    //can't get the above to work
    double max_value = 0;
    for(int i = 0; i<wav_obj.getNumChannels(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
            double sample = wav_obj.audioData[channel][i];
            if(std::abs(sample) > max_value){
                max_value = std::abs(sample);
            }
        }
    }
    std::cout << "Max value was " << max_value << ", so a gain of " << (1/max_value) << " was applied" << std::endl;
    adjust_gain(wav_obj, (1/max_value));
}