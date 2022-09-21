# just a quick way to compile and run the experiments

SHELL      := /bin/bash
CC          = g++
CFLAGS      = -Wall -std=c++17 -o
EXEC        = exp
LIB_DIR     = ~/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/
RPATH	    = -L $(LIB_DIR)
LIB_RSA_API = -lRSA_API
LIB_CYUSB   = -lcyusb_shared

SOURCE_FILES = main.cpp \
AUDIO_GetVolume.cpp

raw :
	clear
	rm -f $(EXEC)
	$(CC) $(CFLAGS) $(EXEC) $(SOURCE_FILES) $(RPATH) $(LIB_RSA_API) $(LIB_CYUSB)
	@echo "[ ${EXEC} ] compiled"
	@echo "...copy and paste in terminal:"
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LIB_DIR)


########~~~~~~~~END>  Makefile
