EXEC = cLoad
SRC_FILES = cLoad.c
CC = gcc

IDIR = .
LDIR = .

CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -I $(IDIR)
LDFLAGS = -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

cLoad: cLoad.c
	$(CC) -o $(EXEC) $(CFLAGS) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)
	@echo "${EXEC} compiled, verify the export"

clean:
	rm -f $(EXEC)