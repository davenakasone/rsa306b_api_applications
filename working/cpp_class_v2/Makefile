# child shell can't control the parent shell
#     so, be sure to export and source after making the target
#     or, change .bashrc / make a bash script
SHELL := /bin/bash
CC = g++
IDIR = ./api_resourcez/
LDIR = ./api_resourcez/
SDIR = ./program_core/
TDIR = ./program_test/
TDIR_IO = data/
TDIR_U = $(TDIR)units/
TDIR_T = $(TDIR)tasks/

EXEC = oo
CFLAGS = -Wall -lpthread -std=c++14 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

OUTPUTS_BIN = $(TDIR)$(TDIR_IO)outputs_bin/
OUTPUTS_R3F = $(TDIR)$(TDIR_IO)outputs_dpx/
OUTPUTS_R3F = $(TDIR)$(TDIR_IO)outputs_r3f/
OUTPUTS_SIG = $(TDIR)$(TDIR_IO)outputs_sig/
OUTPUTS_TXT = $(TDIR)$(TDIR_IO)outputs_txt/

INPUTS_BIN = $(TDIR)$(TDIR_IO)inputs_bin/
INPUTS_DPX = $(TDIR)$(TDIR_IO)inputs_dpx/
INPUTS_R3F = $(TDIR)$(TDIR_IO)inputs_r3f/
INPUTS_SIG = $(TDIR)$(TDIR_IO)inputs_sig/
INPUTS_TXT = $(TDIR)$(TDIR_IO)inputs_txt/

SOURCE_FILES = $(SDIR)main.cpp \
$(SDIR)control/globalz.cpp \
$(SDIR)cpu_timer/cpu_timer_class.cpp \
$(SDIR)rsa306b/rsa306b_CONST/rsa306b_constants_cons_dest.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_class_cons_dest.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_confirm.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_copy.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_init.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_print.cpp \
$(TDIR_T)task_998.cpp \
$(TDIR_T)task_999.cpp \
$(TDIR_U)unit_test_1.cpp \
$(TDIR)test_selector.cpp \
$(TDIR)unit_test_0.cpp \
$(TDIR)wait_enter_clear.cpp


# stdout is cleared
# the executable is first deleted, then a clean build occurs
# user must export library path 
# user must activate the python environmnet (if using python tools)
raw :
	clear
	rm -f $(EXEC)
	$(CC) -o $(EXEC) $(CFLAGS) $(SOURCE_FILES) $(LDFLAGS) $(LDLIBS) $(LDLIUSBS) 	
	@echo [ ${EXEC} ] compiled 
	@echo "...copy and paste in terminal:"
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)
#source /home/unlv/Desktop/rsa306b_api_applications/rsa_venv/rsa/bin/activate   use a boost binder 


# stdout is cleared
# the executable is deleted
# output file directories are deleted, removing all output files
# empty output file directories are made
# input file directories are preserved
#    produces output:  unit_test_xxx.cpp
clear_outputs :
	clear
	rm -f $(EXEC)
	rm -rf $(OUTPUTS_BIN)
	mkdir $(OUTPUTS_BIN)potatoe.txt
	rm -rf $(OUTPUTS_DPX)
	mkdir $(OUTPUTS_DPX)potatoe.txt
	rm -rf $(OUTPUTS_R3F)
	mkdir $(OUTPUTS_R3F)potatoe.txt
	rm -rf $(OUTPUTS_SIG)
	mkdir $(OUTPUTS_SIG)potatoe.txt
	rm -rf $(OUTPUTS_TXT)
	mkdir $(OUTPUTS_TXT)potatoe.txt


# stdout is cleared
# the executable is deleted
# input file directories are deleted, removing all input files
# empty input file directories are made
# output file directories are preserved
#    requires input:  unit_test_xxx.cpp
clear_inputs :
	clear
	rm -f $(EXEC)
	rm -rf $(INPUTS_BIN)
	mkdir $(INPUTS_BIN)potatoe.txt
	rm -rf $(INPUTS_DPX)
	mkdir $(INPUTS_DPX)potatoe.txt
	rm -rf $(INPUTS_R3F)
	mkdir $(INPUTS_R3F)potatoe.txt
	rm -rf $(INPUTS_SIG)
	mkdir $(INPUTS_SIG)potatoe.txt
	rm -rf $(INPUTS_TXT)
	mkdir $(INPUTS_TXT)potatoe.txt


# stdout is cleared
# the executable is deleted
# input and output file directories are deleted, removing all output files
# empty output file directories are made
# empty input file directories are made
# issue "make clean" if files are too large for github
clean :
	clear
	rm -f $(EXEC)
	rm -rf $(TDIR)$(TDIR_IO)
	mkdir $(OUTPUTS_BIN)potatoe.txt
	mkdir $(OUTPUTS_DPX)potatoe.txt
	mkdir $(OUTPUTS_R3F)potatoe.txt
	mkdir $(OUTPUTS_SIG)potatoe.txt
	mkdir $(OUTPUTS_TXT)potatoe.txt
	mkdir $(INPUTS_BIN)potatoe.txt
	mkdir $(INPUTS_DPX)potatoe.txt
	mkdir $(INPUTS_R3F)potatoe.txt
	mkdir $(INPUTS_SIG)potatoe.txt
	mkdir $(INPUTS_TXT)potatoe.txt
