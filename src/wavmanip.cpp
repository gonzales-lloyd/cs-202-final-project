/**
 * @file wavmanip.cpp
 * @author Grant Pellegrini (GrantPellegrini)
 * @author Lloyd Gonzales (gonzales-lloyd)
 * @brief Implementation file for the WavManipulation class.
 */

#include "wavmanip.h"

void WavManipulation::adjust_gain(Wav &wav_obj, float scale){
    for(int i = 0; i<wav_obj.getSamplesPerChannel(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
                wav_obj.audioData[channel][i] *= scale;
        }
    }
}

void WavManipulation::echo(Wav& wav_obj, double start_sec, double end_sec, double decay_factor, double delay){
    auto temp = wav_obj.audioData;

    /*
     * steps:
     * 
     * isolate echoed audio using start_sec and end_sec
     * go to the array position of end_sec+delay
     * multiply echoed audio by decay_factor*iteration and place in temp[][]
     * (note that for any given iteration, the original audio is located at current_pos - ((iteration*iteration_length)+selection_length))
     * go to the end of this iteration+delay
     * repeat
     * add temp to audioData (or just do in-place)
    */

    //calculate number of iterations
    //length of each iteration is delay+(end_sec-start-sec)
    //so the iteration count is equal to (samplesPerChannel-end_sec)/iteration_length rounded up

    int iterations = 0;
    int selection_length = wav_obj.secondAsSample(end_sec-start_sec);
    int iteration_length = wav_obj.secondAsSample(delay+(end_sec-start_sec)); //in samples
    int first_iteration_position = wav_obj.secondAsSample(end_sec+delay);
    if(first_iteration_position > wav_obj.getSamplesPerChannel()){
        //then the first iteration wouldn't even be in the length of the audio, so do nothing
        iterations = 0;
    }else{
        iterations = ceil((double)(wav_obj.getSamplesPerChannel()-first_iteration_position)/iteration_length);
    }

    for(int iteration = 0; iteration<iterations; iteration++){
        double iteration_scale = std::pow(decay_factor, iteration+1);
        int iteration_start_position = first_iteration_position + (iteration*iteration_length);

        for(int i = iteration_start_position; i<wav_obj.getSamplesPerChannel(); i++){
            int echo_selection = i - ((iteration*iteration_length)+selection_length);
            for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
                if(i>0 && echo_selection>0){
                    temp[channel][i] += iteration_scale * wav_obj.audioData[channel][echo_selection];
                }
            }
        }
    }

    for(int i = 0; i<wav_obj.getSamplesPerChannel(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
            wav_obj.audioData[channel][i] += temp[channel][i];
		}
    }
}

void WavManipulation::normalize(Wav& wav_obj){
    //C++11: https://stackoverflow.com/questions/9874802/how-can-i-get-the-maximum-or-minimum-value-in-a-vector
    //https://stackoverflow.com/questions/10158756/using-stdmax-element-on-a-vectordouble
    //double max = *std::max_element(wav_obj.audioData.begin(), wav_obj.audioData.end());

    //can't get the above to work
    double max_value = 0;
    for(int i = 0; i<wav_obj.getSamplesPerChannel(); i++){
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

void WavManipulation::compress(Wav &wav_obj, double threshold, double attenuation_factor){
    threshold = Wav::clamp<double>(threshold, 0.0, 1.0);
    attenuation_factor = Wav::clamp<double>(attenuation_factor, 0.0, 1.0);

    for(int i = 0; i<wav_obj.getSamplesPerChannel(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
            double sample = wav_obj.audioData[channel][i];
            if(std::abs(sample) > threshold){
                double difference = std::abs(sample)-threshold;
                if(sample > 0){
                    wav_obj.audioData[channel][i] -= difference*attenuation_factor;
                }else{
                    wav_obj.audioData[channel][i] += difference*attenuation_factor;
                }
            }
        }
    }
}

void WavManipulation::lowpass(Wav &wav_obj, int delay, double gain){
    //based on Dr. Lancaster's diagram, low-pass is just a one-iteration echo?
    //uses grant's one-iteration echo algorithm
    auto temp = wav_obj.audioData;

    for(int i = 0; i<wav_obj.getSamplesPerChannel(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
            if (i > delay){ 
			    temp[channel][i] += gain * temp[channel][i - delay];
		    }
		}
    }

    for(int i = 0; i<wav_obj.getSamplesPerChannel(); i++){
        for(int channel = 0; channel<wav_obj.getNumChannels(); channel++){
            if(i+delay < wav_obj.getSamplesPerChannel()){
                wav_obj.audioData[channel][i] += temp[channel][i + delay];
            }
		}
    }
}