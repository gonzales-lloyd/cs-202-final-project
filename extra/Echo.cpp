#include "Echo.h"

void Echo::processBuffer(unsigned char* buffer, int bufferSize) override {
	double gain;
	int delay;
	unsigned char* temp[bufferSize];

	std::cout << "Enter what position you want the delay to start:";
	std::cin >> delay;

	std::cout << "Enter what you want the gain to be, less than 1:";
	std::cin >> gain;

	for (int i = 0; i < bufferSize; i++) { 
		temp[i] = buffer[i];
	}


	for (i = 0; i < bufferSize; i++) { 
		if (i > delay) { 
			temp[i] = temp[i] + gain * temp[i - delay];
		}
		else { 
			temp[i] = temp[i];
		}
	}

	for (i = 0; i < bufferSize; i++) { 
		buffer[i] = buffer[i] + temp[i+delay];
						
}
