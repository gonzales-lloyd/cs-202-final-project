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
 - **Grant Pellegrini** - All processors
 - **Lloyd Gonzales** - Project structuring and setup (Doxyfile, makefile, folder structure); Wav class implementation; processor integration; main menu logic; Qt

## Build instructions
*Note: precompiled binaries for Linux are available under Releases. In addition, the documentation is available on Github Pages under https://gonzales-lloyd.github.io/cs-202-final-project/index.html (note that this link may change if Github Classroom is used).* 

To build the base program, `wav_manager`, simply run `make` in the source directory.

To generate the documentation, ensure you have `doxygen` installed from your package manager. Then, run `make docs` or `doxygen Doxyfile` from the source directory.

To generate the GUI version of the program...
## UML diagram

## Known issues and missing functionality

### Bugs
- If the file name to `Wav::readFile()` is invalid, a segfault occurs
- If the end time passed into `WavManipulation::echo()` is too large, the program hangs (other extreme inputs of correct data types may cause similar behavior)
### Design oversights
- No protection against the length of audioData being changed by an external class, which would cause the Wav class to break when trying to rewrite the buffer to a file
- No protection or checks if the header structure is different from expected
### Design oversights
- Unsure what low-pass filter should sound like, but it is implemented according to the diagram sent in the Discord server
- GUI does not run on Windows without additionally adding several DLL files must also be manually added to the executable folder and to \platforms\... (see https://stackoverflow.com/questions/20495620/qt-5-1-1-application-failed-to-start-because-platform-plugin-windows-is-missi); `windeployqt` fails to correctly add dependencies

## Challenges encountered