IDIR = .
LDIR = .
SDIR = .
RESOURCES = LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)

EXEC = scanner
MAIN_FILE = main.cpp
SRC_FILES =
CC = g++

CFLAGS = -Wall -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

$(EXEC): $(MAIN_FILE)
	$(CC) -o $(EXEC) $(CFLAGS) $(MAIN_FILE) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	export $(RESOURCES)
	@echo "${EXEC} compiled, library variable sourced"

clean:
	rm -f $(EXEC)