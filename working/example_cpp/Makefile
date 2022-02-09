EXEC	=	cppLoad
SRC_FILES=	cppLoad.cpp consumers.cpp
CC	=	g++

#Change "." to directory containing header files
IDIR	=	.
#Change "." to directory of API libraries
LDIR	=	.

CFLAGS	=	-std=c++14 -I$(IDIR)
LDFLAGS	=	-L$(LDIR)
LDLIBS	=	-lRSA_API
LDLIUSBS	=	-lcyusb_shared

cppLoad: cppLoad.cpp
	$(CC) -o $(EXEC) $(CFLAGS) $(SRC_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
