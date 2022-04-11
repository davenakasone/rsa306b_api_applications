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

raw :
	rm -f $(EXEC)
	$(CC) -o $(EXEC) $(CFLAGS) $(MAIN_FILE) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	@echo [ ${EXEC} ] compiled
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)	
	
clean :
	rm -f $(EXEC)
