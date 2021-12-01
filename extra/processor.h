#include <iostream>

class Processor { 
private:

public: 
	virtual void processBuffer(unsigned char* buffer,int bufferSize) = 0;
};
