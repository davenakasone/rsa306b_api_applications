CC = g++
IDIR = ./api_resourcez/
LDIR = ./api_resourcez/
SDIR = ./sourcez/
TDIR = ./testz/
EXEC = klass
CFLAGS = -Wall -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

SOURCE_FILES = $(SDIR)aaa_main.cpp \
$(SDIR)rsa306b_class__gp.cpp \
$(SDIR)rsa306b_class_DEVICE.cpp \
$(SDIR)rsa306b_class_DEVICE_get_set.cpp \
$(SDIR)rsa306b_class_REFTIME_get.cpp \
$(SDIR)rsa306b_class_REFTIME_set.cpp \
$(TDIR)test_selector.cpp \
$(TDIR)unit_test_1.cpp \
$(TDIR)unit_test_2.cpp \
$(TDIR)unit_test_999.cpp \
$(TDIR)wait_enter_clear.cpp

$(EXEC) : $(MAIN_FILE)
	$(CC) -o $(EXEC) $(CFLAGS) $(SOURCE_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)	
	@echo [ ${EXEC} ] compiled, check the export

clean :
	rm -f $(EXEC)
