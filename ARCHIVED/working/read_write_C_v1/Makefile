EXEC = rwC
SRC_FILES =	rw_C.c
CC = gcc

IDIR	=	.
LDIR	=	.

CFLAGS = -Wall -I$(IDIR)
LDFLAGS	= -L$(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

rwC: rw_C.c
	$(CC) -o $(EXEC) $(CFLAGS) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 

clean:
	rm -f $(EXEC)