EXEC	=	cLoad
SRC_FILES=	cLoad.c
CC	=	gcc

#Change "." to directory containing header files
IDIR	=	..
#Change "." to directory of API libraries
LDIR	=	..

CFLAGS	=	-std=c99 -I$(IDIR)
LDFLAGS	=	-L$(LDIR)
LDLIBS	=	-lRSA_API
LDLIUSBS	=	-lcyusb_shared

cLoad: cLoad.c
	$(CC) -o $(EXEC) $(CFLAGS) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
