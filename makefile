all: wav_manager

wav_manager: driver.o wav.o 
	g++ -o wav_manager driver.o wav.o

driver.o: driver.cpp wav.o
	g++ -c driver.cpp

wav.o: wav.cpp wav.h wavheader.h
	g++ -c wav.cpp

clean:
	rm *.o wav_manager