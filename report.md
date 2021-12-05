**This replaces README.md when it is no longer needed at the project's submission.**

All header files and functions must be documented using the Doxygen Javadoc format. The README page should include

    A line saying whether this is a basic or challenge level project
    The full names of each team member
    The contribution of each team member
    A UML diagram showing the basic design
    A section detailing issues, including any functionality that is missing
    A section detailing the challenges that you encountered in the project
    Instructions for building the application if anything is required beyond make

# CS 202 Fall 2021 Final Project
A program for basic processing on 8-bit and 16-bit WAV files. 

This is a **challenge level** project.

## Members and contributions
 - **Austin Zube** - Documentation, writeups
 - **Grant Pellegrini** - High-level processors
 - **Lloyd Gonzales** - Project structuring and setup (Doxyfile, makefile, folder structure); Wav class implementation; processor integration; main menu/`main.cpp`; Qt

## Build instructions
*Note: precompiled binaries for Linux are available under Releases. In addition, the documentation is available on Github Pages under https://gonzales-lloyd.github.io/cs-202-final-project/index.html (note that this link may change if Github Classroom is used).* 

To build the base program, `wav_manager`, simply run `make` in the source directory.

To generate the documentation, ensure you have `doxygen` installed from your package manager. Then, run `make docs` or `doxygen Doxyfile` from the source directory.

To generate the GUI version of the program...
## UML diagram

## Known issues and missing functionality
- No protection against the length of audioData being changed by an external class, which would cause the Wav class to break when trying to rewrite the buffer to a file
- No protection or checks if the header structure is different from expected
- If the file name to `readFile()` is invalid, a segfault occurs
- Does not reject non-PCM and non-8/16 bit data, when it can only support PCM and 8/16-bit data

## Challenges encountered