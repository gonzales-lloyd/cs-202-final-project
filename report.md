# CS 202 Fall 2021 Final Project
A program for basic processing on 8-bit and 16-bit WAV files. 

This is a **challenge level** project.

## Members and contributions
 - **Austin Zube** - Documentation, writeups
 - **Grant Pellegrini** - All processors
 - **Lloyd Gonzales** - Project structuring and setup (Doxyfile, makefile, folder structure); Wav class implementation; processor integration; main menu logic; Qt

## Build instructions
Note: the documentation is available on Github Pages under https://gonzales-lloyd.github.io/cs-202-final-project/index.html.

To build the base program, `wav_manager`, run `make` in the source directory.

To generate the documentation, ensure you have `doxygen` installed from your package manager. Then, run `make docs` or `doxygen Doxyfile` from the source directory.

To generate the GUI version of the program, you may use Qt Creator to open `cs202-final-project.pro`, and run it in debug mode.

Alternatively, to generate the GUI version:
- Create a build folder in the location of your choice
- Run `qmake cs202-final-project.pro`, inserting the full path to the project file as necessary
- Run `make`

Note that release versions made through `qmake` or other means may fail. See [Design oversights](#design-oversights) for a workaround.
## UML diagram

## Known issues and missing functionality

### Bugs
- If the end time passed into `WavManipulation::echo()` is too large, the program hangs (other extreme inputs of correct data types may cause similar behavior)
### Design oversights
- No protection against the length of audioData being changed by an external class, which would cause the Wav class to break when trying to rewrite the buffer to a file
- The template call to `Wav::clamp` in `WavManip` will cause Qt release builds to fail. To fix, locate the following lines in `wavmanip.cpp`, under the `compress()` function:
```
threshold = Wav::clamp<double>(threshold, 0.0, 1.0);
attenuation_factor = Wav::clamp<double>(attenuation_factor, 0.0, 1.0);
```
and either delete them or replace these lines with:
```
threshold = std::max(threshold, 0.0);
threshold = std::min(threshold, 1.0);
attenuation_factor = std::max(attenuation_factor, 0.0);
attenuation_factor = std::min(attenuation_factor, 1.0);
```
### Other
- Unsure what low-pass filter should sound like, but it is implemented according to the diagram sent in the Discord server
- GUI does not run on Windows without additionally adding several DLL files must also be manually added to the executable folder and to \platforms\... (see https://stackoverflow.com/questions/20495620/qt-5-1-1-application-failed-to-start-because-platform-plugin-windows-is-missi); `windeployqt` fails to correctly add dependencies
- The Wav class provides `fileLoaded`, an attribute flag denoting whether an audio file has been successfully loaded or not. This flag is only internally used for deciding whether to free the internal buffer or not, but it may be relevant if the class were to ever be used as a library.

## Challenges encountered