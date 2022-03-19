IDIR = .
LDIR = .
SDIR = .

EXEC = cppIQ
MAIN_FILE = main.cpp
CC = g++

CFLAGS = -Wall -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

$(EXEC) : $(MAIN_FILE)
	$(CC) -o $(EXEC) $(CFLAGS) $(MAIN_FILE) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)	
	@echo ${EXEC} compiled, check the export

clean :
	rm -f $(EXEC)
