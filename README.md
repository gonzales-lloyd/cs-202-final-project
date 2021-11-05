


# CS 202 Semester Project, F21
The semester project is a group project. It counts for four programming assignments. As noted below, if a group successfully completes the challenge level, a grade of 120% is possible.

## Contents
- [[#Overview|Overview]]
- [[#Project Levels|Project Levels]]
- [[#Project Description|Project Description]]
	- [[#Background|Background]]
		- [[#Sample Rates|Sample Rates]]
		- [[#Quantization (bit depth)|Quantization (bit depth)]]
		- [[#File Formats and Compression|File Formats and Compression]]
- [[#Basic Level Requirements|Basic Level Requirements]]
	- [[#Program Flow|Program Flow]]
	- [[#Required Processors|Required Processors]]
- [[#Challenge Level Requirements|Challenge Level Requirements]]
	- [[#Program Flow|Program Flow]]
	- [[#Required Processors|Required Processors]]
- [[#Architectural Requirements (Basic and Challenge)|Architectural Requirements (Basic and Challenge)]]
	- [[#Documentation|Documentation]]
- [[#Grading|Grading]]
- [[#What to Turn In|What to Turn In]]

## Overview
This project is designed to provide experience in
-   working with binary files and pre-defined file formats
-   manipulating data in arrays in a variety of formats
-   developing a terminal-based user interface
-   using inheritance, abstract classes and interfaces, and composition
-   developing a modular design using good design and development principles
    

## Project Levels
-   Base Level: All groups must attempt the base level project, which consists of building the application as described here with a console user interface.
-   Challenge Level: A group can make a maximum of 120 by adding a graphical user interface using the Qt framework.
    

## Project Description
In this project, you will create an application that can load audio data from `wav` files, manipulate the data to add common audio effects such as echo and compression and save the files for later playback.

### Background
Digital audio files consist of thousands of _samples_. A sample is a measurement of the amplitude of the signal coming from a microphone or electronic instrument at an instant in time. The process of turning the sampled value into a binary number is called _quantization_. The process is referred to as _pulse code modulation_.

#### Sample Rates
Modern digital audio systems typically record 44,100 or 48,000 samples per second per channel, so a stereo recording collects 88,200 or 176,400 samples, respectively, for every second of audio recorded. The sample rate directly affects the system frequency response.

#### Quantization (bit depth)
The number of bits used to store a sample determines the accuracy of the sample. The higher number of bits used, the more accurate and less noisy the samples. Typical sample formats are 8, 16, 24, and 32 bits. We will be using wav files that are either 8 or 16 bits, and either mono or stereo.

For more information, see [https://www.izotope.com/en/learn/digital-audio-basics-sample-rate-and-bit-depth.html](https://www.izotope.com/en/learn/digital-audio-basics-sample-rate-and-bit-depth.html)

#### File Formats and Compression
Audio files are binary rather than text. The data can be compressed (not zip!) in order to reduce the file size or they can contain uncompressed sample values. Compressed formats include mp3 and AAC. We will be working with uncompressed files in the `wav` file format. The format for a `wav` file can be found here: [http://soundfile.sapp.org/doc/WaveFormat/](http://soundfile.sapp.org/doc/WaveFormat/)

Handling binary wav files is explained here: [https://www.youtube.com/watch?v=7uQjw5PY63s](https://www.youtube.com/watch?v=7uQjw5PY63s) 

## Basic Level Requirements
The basic level application presents the user with a console interface.

### Program Flow
The following pseudo-code shows the required application flow for the base level console version:

```
Start: Present start menu  
If user selects quit, exit program  
Else  
 Request filename from user  
 Open file specified by filename  
 If file does not exist or file is not wav file  
 display error message and goto start  
 else  
 read file metadata  
(1) display metadata to user  
 present user with processor menu  
 If user selects processor option  
 request output filename  
 run processor  
 save file  
 goto Start  
```  

**Start Menu**

The base start should allow the user to enter the name of a wav file or exit the application.

**File Metadata**

The data to be displayed in step (1):

-   filename
    
-   sample rate
    
-   bits per sample
    
-   stereo or mono
    

### Required Processors
The following are the processes to be implemented
-   normalization
    -   Algorithm: The largest sample value in the data is found, and then the data is scaled so that that value is the maximum possible value. This maximizes the amplitude of the final waveform.
    -   Example for floating-point data
        -   Original data: n = {0,0.2,0.4,0,-0.3}
        -   Largest absolute value: 0.4, so scaling value s = 1/0.4 = 2.5
        -   Scaled result: n_scaled = {0, 0.5,1,0,-0.75}
-   echo
    -   Algorithm: Samples are copied, scaled, and added to later locations in the sample buffer to create an echo effect.
-   gain adjustment
    -   Algorithm: Samples are multiplied by a scaling factor that raises or lowers the overall amplitude of the wave file
        
## Challenge Level Requirements
For the challenge level, you will build a graphical user interface (GUI) using the Qt Framework ([https://www.qt.io/](https://www.qt.io/)). This framework gives you the ability to build and distribute a cross-platform desktop or mobile application using C++ as the development language. The framework is free for open source and academic work and can be downloaded from the link above. The framework is very popular, so you will find many examples and tutorials online.

### Program Flow
The basic flow for the GUI version is the same as the console, but of course adapted for a GUI application flow with menus, etc.

### Required Processors
The challenge-level application includes all the processors from the basic level. In addition, it must include the following processors:
-   low-pass filter
    -   Remove high frequency components from the signal
-   compression / limiting
    -   The dynamic range of the signal is compressed using a non-linear map of input to output. This is commonly used to limit loud peaks in the sound, and gives an overall impression of higher volume.
        
## Architectural Requirements (Basic and Challenge)
The system design is to be modular to facilitate dividing up the development work, and more importantly, to aid in testing and expansion of the application's capabilities. The required modules are
-   File management: manages reading and writing of files in the required formats
-   User interaction: manages the console user interaction. In the case of the challenge version using Qt, the module should provide a single point of entry to the processors, etc.
-   Processing: management of sample buffers, application of processors, etc. Each module will consist of one or more classes that are access through one or more interfaces.
    
As needed, you can add more modules.

### Documentation
All header files and functions must be documented using the Doxygen Javadoc format. The README page should include
-   A line saying whether this is a basic or challenge level project
-   The full names of each team member
-   The contribution of each team member
-   A UML diagram showing the basic design
-   A section detailing issues, including any functionality that is missing
-   A section detailing the challenges that you encountered in the project
-   Instructions for building the application if anything is required beyond _make_

The Doxygen files should be generated into a folder called _docs._

## Grading
This project will be graded using standard grading with partial credit. There will not be an opportunity for redo, as this project is due toward the end of the semester and there will not be time for redo and grading.

Grading will be based on

-   use of Git
    
-   correct use of C++ features such as templates, inheritance, interfaces, exceptions, and composition
    
-   correctness of the implementation of the required processes
    
-   runtime stability
    

See the rubric for details.

## What to Turn In
All source code must be managed in Github, and the repository URL turned in to WebCampus. Include the team member names and your group number in the submission.
