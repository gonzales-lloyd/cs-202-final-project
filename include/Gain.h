#include <iostream>
#include "processor.h"

class Gain : public Processor {
 private:

public: 
	void processBuffer(unsigned char* buffer, int bufferSize) override {}
};
