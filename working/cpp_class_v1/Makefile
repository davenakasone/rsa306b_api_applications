CC = g++
IDIR = ./api_resourcez/
LDIR = ./api_resourcez/
SDIR = ./sourcez/
EXEC = klass
CFLAGS = -Wall -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

SOURCE_FILES = $(SDIR)aaa_main.cpp \
$(SDIR)rsa306b_class.cpp \
$(SDIR)tester.cpp

$(EXEC) : $(MAIN_FILE)
	$(CC) -o $(EXEC) $(CFLAGS) $(SOURCE_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)	
	@echo ${EXEC} compiled, check the export

clean :
	rm -f $(EXEC)
