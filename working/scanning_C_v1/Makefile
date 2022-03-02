EXEC = scan
MAIN_FILE = scan.c
SRC_FILES =
CC = gcc

IDIR	= .
LDIR	= .

CFLAGS = -Wall -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

$(EXEC): scan.c
	$(CC) -o $(EXEC) $(CFLAGS) $(MAIN_FILE) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(LDIR)	
	echo "program complied"
	echo "be sure to source the library path"

clean:
	rm -f $(EXEC)
