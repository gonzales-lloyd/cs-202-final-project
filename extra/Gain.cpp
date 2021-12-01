#include "Gain.h"

void Gain::processBuffer(unsigned char* buffer, int bufferSize) override { 
	double scalar; 

	std::cout << "Enter what you would like the scaling factor to be: ";
	std::cin >> scalar;

	for (int i = 0; i < bufferSize; i++) { 
		buffer[i] = buffer[i] * scalar;
		if (buffer[i] > 255) { 
			buffer[i] = 255;
		}
	}
}
