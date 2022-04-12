# child shell can't control the parent shell
#     so, be sure to export and source after making the target
#     or, change .bashrc / make a bash script
SHELL := /bin/bash
CC = g++
IDIR = ./api_resourcez/
LDIR = ./api_resourcez/
SDIR = ./sourcez/
TDIR = ./testz/
OUTPUTS_R3F = $(TDIR)test_outputs_r3f/
OUTPUTS_TXT = $(TDIR)test_outputs_txt/
EXEC = klass
CFLAGS = -Wall -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared


SOURCE_FILES = $(SDIR)aaa_main.cpp \
$(SDIR)rsa306b_class__gp.cpp \
$(SDIR)rsa306b_class_ALIGN.cpp \
$(SDIR)rsa306b_class_AUDIO_private.cpp \
$(SDIR)rsa306b_class_AUDIO_public.cpp \
$(SDIR)rsa306b_class_CONFIG.cpp \
$(SDIR)rsa306b_class_CONFIG_get_set.cpp \
$(SDIR)rsa306b_class_DEVICE.cpp \
$(SDIR)rsa306b_class_DEVICE_get_set.cpp \
$(SDIR)rsa306b_class_REFTIME.cpp \
$(SDIR)rsa306b_class_REFTIME_get.cpp \
$(SDIR)rsa306b_class_REFTIME_set.cpp \
$(SDIR)rsa306b_class_SPECTRUM_get.cpp \
$(SDIR)rsa306b_class_SPECTRUM_private.cpp \
$(SDIR)rsa306b_class_SPECTRUM_public.cpp \
$(SDIR)rsa306b_class_SPECTRUM_set.cpp \
$(SDIR)rsa306b_class_TRIG_private.cpp \
$(SDIR)rsa306b_class_TRIG_public.cpp \
$(TDIR)test_selector.cpp \
$(TDIR)unit_test_1.cpp \
$(TDIR)unit_test_2.cpp \
$(TDIR)unit_test_3.cpp \
$(TDIR)unit_test_4.cpp \
$(TDIR)unit_test_5.cpp \
$(TDIR)unit_test_6.cpp \
$(TDIR)unit_test_7.cpp \
$(TDIR)unit_test_8.cpp \
$(TDIR)vvv_994.cpp \
$(TDIR)vvv_995.cpp \
$(TDIR)vvv_996.cpp \
$(TDIR)vvv_997.cpp \
$(TDIR)vvv_998.cpp \
$(TDIR)unit_test_999.cpp \
$(TDIR)wait_enter_clear.cpp


# the executable is first deleted, then a clean build occurs
# copy and paste the last 2 lines when terminal is frist used
#     need to "export" the API resources
#     need to "source the python virtual environment 
raw :
	rm -f $(EXEC)
	$(CC) -o $(EXEC) $(CFLAGS) $(SOURCE_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 	
	@echo [ ${EXEC} ] compiled 
	@echo "be sure to export the RSA shared object library variable \
and source the python3 virtual environment"
	@echo "...copy and paste in terminal:"
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)
	source /home/unlv/Desktop/rsa306b_api_applications/rsa_venv/rsa/bin/activate


# the executable is deleted
# output file directories are deleted, removing all output files
# empty output file directories are made
#	vvv_997 : makes "*.txt" files in "test_outputs_txt"
#	vvv_994 : makes "*.r3f" files in "test_outputs_r3f"
# issue "make clean" if files are too large for github
clean :
	rm -f $(EXEC)
	rm -rf $(OUTPUTS_R3F)
	mkdir $(OUTPUTS_R3F)
	rm -rf $(OUTPUTS_TXT)
	mkdir $(OUTPUTS_TXT)
