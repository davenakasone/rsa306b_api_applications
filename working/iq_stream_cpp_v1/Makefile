IDIR = .
LDIR = .
SDIR = .

EXEC = cpp_iq
MAIN_FILE = cpp_iq.cpp
SRC_FILES = implementations.cpp
CC = g++

CFLAGS = -Wall -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

$(EXEC): $(MAIN_FILE)
	$(CC) -o $(EXEC) $(CFLAGS) $(MAIN_FILE) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(LDIR)	
	echo ${EXEC} compiled, library path was probably sourced
#echo "program complied"
#echo "be sure to source the library path"

clean:
	rm -f $(EXEC)