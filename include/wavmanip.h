#include "wav.h"


class wavManipulation{
public:
    template <typename T>
    static void gain_adjustment(Wav<T>& wav_obj, float scale){
        for(int i = 0; i<wav_obj.header.buffer_size; i++){
            std::cout << wav_obj.buffer[i] << std::endl;  
        }
    } 
};