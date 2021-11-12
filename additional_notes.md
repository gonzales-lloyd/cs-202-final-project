Notes:
 - include/ is all .h files
 - src/ is all .cpp files
 - doc/ is the outputted Doxygen files
 - obj/ are the intermediate output/object files
 - test_files/ are some random WAV files i found on the internet related to this same project

 For the Doxyfile, everything's been set up. If future configuration is necessary, check INPUT tag to ensure directories are good, and EXTRACT_ALL for private members

makefile supports intermediate object files using `obj/*.o`, but if conventional intermediate files are necessary we might have to change this