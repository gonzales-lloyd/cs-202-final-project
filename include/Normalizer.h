#include <iostream>
#include "wav.h"

class Normalization : public Processor { 
private:

public: 
	void processBuffer(unsigned char* buffer, int bufferSize) override {}
};
