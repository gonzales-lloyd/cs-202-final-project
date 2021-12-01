#include "wav.h"
#include <algorithm>
#include <cmath>

class WavManipulation{
public:
    static void adjust_gain(Wav &wav_obj, float scale); 
    static void echo(Wav &wav_obj, double gain, int delay);
    static void normalize(Wav &wav_obj);
};