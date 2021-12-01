#include "Normalizer.h"


void Normalizer::processBuffer(unsigned char* buffer, int bufferSize) override { 
	int audio_cap;
	int max_value = 0;

	std::cout << "Enter what you would like the cap to be: ";
	std::cin >> audio_cap;

	for (int i = 0; i < bufferSize; i++) { 
		if(buffer[i] > max_value) { 
			max_value = buffer[i];
		}
	}
	
	for (int w = 0; w < bufferSize; w++) { 
		buffer[w] = buffer[w] * (1 / max_value); 
		if(buffer[w] > audio_cap) { 
			buffer[w] = audio_cap;
		}
	}
}

