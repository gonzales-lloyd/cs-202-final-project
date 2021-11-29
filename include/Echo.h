#include <iostream>
#include "wav.h"

class Echo : public Processor { 
private: 

public: 
	void processBuffer(unsigned char* buffer, int bufferSize) override {}
};

