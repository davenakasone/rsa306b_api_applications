IDIR = .
LDIR = .
SDIR = .

EXEC = cpp_if_stream
MAIN_FILE = main.cpp
CC = g++

CFLAGS = -Wall -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

raw :
	rm -f $(EXEC)
	$(CC) -o $(EXEC) $(CFLAGS) $(MAIN_FILE) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)	
	@echo [ ${EXEC} ] compiled, check the export

clean :
	rm -f $(EXEC)
	rm -f if_stream_test.r3f