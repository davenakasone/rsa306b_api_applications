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
BLANK_IO = clear.txt
BLANK_MSG = directory cleared

EXEC = oo
CFLAGS = -Wall -lpthread -std=c++17 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LDLIBS = -lRSA_API
LDLIUSBS = -lcyusb_shared

OUTPUTS_BIN = $(TDIR)$(TDIR_IO)outputs_bin/
OUTPUTS_DPX = $(TDIR)$(TDIR_IO)outputs_dpx/
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
$(SDIR)r3f_manager/r3fc_file_decode.cpp \
$(SDIR)r3f_manager/r3fc_file_process.cpp \
$(SDIR)r3f_manager/r3fc_handle_adc.cpp \
$(SDIR)r3f_manager/r3fc_plot_maker.cpp \
$(SDIR)r3f_manager/r3fc_private.cpp \
$(SDIR)r3f_manager/r3fc_public.cpp \
$(SDIR)cpu_timer/cpu_timer_class.cpp \
$(SDIR)rsa306b/rsa306b_ALIGN/rsa306b_align_get_copy.cpp \
$(SDIR)rsa306b/rsa306b_ALIGN/rsa306b_align_print_init.cpp \
$(SDIR)rsa306b/rsa306b_ALIGN/rsa306b_align_user.cpp \
$(SDIR)rsa306b/rsa306b_AUDIO/rsa306b_audio_copy.cpp \
$(SDIR)rsa306b/rsa306b_AUDIO/rsa306b_audio_get.cpp \
$(SDIR)rsa306b/rsa306b_AUDIO/rsa306b_audio_print_init.cpp \
$(SDIR)rsa306b/rsa306b_AUDIO/rsa306b_audio_set.cpp \
$(SDIR)rsa306b/rsa306b_CONFIG/rsa306b_config_copy.cpp \
$(SDIR)rsa306b/rsa306b_CONFIG/rsa306b_config_get.cpp \
$(SDIR)rsa306b/rsa306b_CONFIG/rsa306b_config_print_init.cpp \
$(SDIR)rsa306b/rsa306b_CONFIG/rsa306b_config_set.cpp \
$(SDIR)rsa306b/rsa306b_CONFIG/rsa306b_config_user.cpp \
$(SDIR)rsa306b/rsa306b_AUDIO/rsa306b_audio_user.cpp \
$(SDIR)rsa306b/rsa306b_CONST/rsa306b_constants_cons_dest.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_copy.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_get.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_print_init.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_user1.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_user2.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_class_cons_dest.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_confirm.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_copy.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_init.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_print.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_utility.cpp \
$(SDIR)rsa306b/rsa306b_IFSTREAM/rsa306b_ifstream_copy.cpp \
$(SDIR)rsa306b/rsa306b_IFSTREAM/rsa306b_ifstream_get.cpp \
$(SDIR)rsa306b/rsa306b_IFSTREAM/rsa306b_ifstream_print_init.cpp \
$(SDIR)rsa306b/rsa306b_IFSTREAM/rsa306b_ifstream_set.cpp \
$(SDIR)rsa306b/rsa306b_IFSTREAM/rsa306b_ifstream_user.cpp \
$(SDIR)rsa306b/rsa306b_IQBLK/rsa306b_iqblk_copy.cpp \
$(SDIR)rsa306b/rsa306b_IQBLK/rsa306b_iqblk_get.cpp \
$(SDIR)rsa306b/rsa306b_IQBLK/rsa306b_iqblk_print_init_check.cpp \
$(SDIR)rsa306b/rsa306b_IQBLK/rsa306b_iqblk_set.cpp \
$(SDIR)rsa306b/rsa306b_IQBLK/rsa306b_iqblk_user.cpp \
$(SDIR)rsa306b/rsa306b_IQSTREAM/rsa306b_istream_print_init_check.cpp \
$(SDIR)rsa306b/rsa306b_REFTIME/rsa306b_reftime_copy.cpp \
$(SDIR)rsa306b/rsa306b_REFTIME/rsa306b_reftime_get.cpp \
$(SDIR)rsa306b/rsa306b_REFTIME/rsa306b_reftime_print_init.cpp \
$(SDIR)rsa306b/rsa306b_REFTIME/rsa306b_reftime_user.cpp \
$(SDIR)rsa306b/rsa306b_SPECTRUM/rsa306b_spectrum_copy.cpp \
$(SDIR)rsa306b/rsa306b_SPECTRUM/rsa306b_spectrum_get.cpp \
$(SDIR)rsa306b/rsa306b_SPECTRUM/rsa306b_spectrum_init_default.cpp \
$(SDIR)rsa306b/rsa306b_SPECTRUM/rsa306b_spectrum_print.cpp \
$(SDIR)rsa306b/rsa306b_SPECTRUM/rsa306b_spectrum_set.cpp \
$(SDIR)rsa306b/rsa306b_SPECTRUM/rsa306b_spectrum_user.cpp \
$(SDIR)rsa306b/rsa306b_TRIG/rsa306b_trig_copy.cpp \
$(SDIR)rsa306b/rsa306b_TRIG/rsa306b_trig_get.cpp \
$(SDIR)rsa306b/rsa306b_TRIG/rsa306b_trig_print_init.cpp \
$(SDIR)rsa306b/rsa306b_TRIG/rsa306b_trig_set.cpp \
$(SDIR)rsa306b/rsa306b_TRIG/rsa306b_trig_user.cpp \
$(TDIR_T)task_991.cpp \
$(TDIR_T)task_992.cpp \
$(TDIR_T)task_993.cpp \
$(TDIR_T)task_994.cpp \
$(TDIR_T)task_995.cpp \
$(TDIR_T)task_996.cpp \
$(TDIR_T)task_997.cpp \
$(TDIR_T)task_998.cpp \
$(TDIR_T)task_999.cpp \
$(TDIR_U)unit_test_0.cpp \
$(TDIR_U)unit_test_1.cpp \
$(TDIR_U)unit_test_2.cpp \
$(TDIR_U)unit_test_3.cpp \
$(TDIR_U)unit_test_4.cpp \
$(TDIR_U)unit_test_5.cpp \
$(TDIR_U)unit_test_6.cpp \
$(TDIR_U)unit_test_7.cpp \
$(TDIR_U)unit_test_8.cpp \
$(TDIR_U)unit_test_9.cpp \
$(TDIR_U)unit_test_10.cpp \
$(TDIR_U)unit_test_11.cpp \
$(TDIR)test_selector.cpp \
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
	rm -rf $(OUTPUTS_DPX)
	rm -rf $(OUTPUTS_R3F)
	rm -rf $(OUTPUTS_SIG)
	rm -rf $(OUTPUTS_TXT)
	mkdir $(OUTPUTS_BIN)
	mkdir $(OUTPUTS_DPX)
	mkdir $(OUTPUTS_R3F)
	mkdir $(OUTPUTS_SIG)
	mkdir $(OUTPUTS_TXT)
	printf '$(BLANK_MSG)' > $(OUTPUTS_BIN)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(OUTPUTS_DPX)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(OUTPUTS_R3F)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(OUTPUTS_SIG)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(OUTPUTS_TXT)$(BLANK_IO)
	clear
	@echo 'all outputs were deleted'


# stdout is cleared
# the executable is deleted
# input file directories are deleted, removing all input files
# empty input file directories are made
# output file directories are preserved
#    requires input:  
#		unit_test_xxx()
clear_inputs :
	clear
	rm -f $(EXEC)
	rm -rf $(INPUTS_BIN)
	rm -rf $(INPUTS_DPX)
	rm -rf $(INPUTS_R3F)
	rm -rf $(INPUTS_SIG)
	rm -rf $(INPUTS_TXT)
	mkdir $(INPUTS_BIN)
	mkdir $(INPUTS_DPX)
	mkdir $(INPUTS_R3F)
	mkdir $(INPUTS_SIG)
	mkdir $(INPUTS_TXT)
	printf '$(BLANK_MSG)' > $(INPUTS_BIN)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(INPUTS_DPX)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(INPUTS_R3F)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(INPUTS_SIG)$(BLANK_IO)
	printf '$(BLANK_MSG)' > $(INPUTS_TXT)$(BLANK_IO)
	clear
	@echo 'all inputs were deleted'


# stdout is cleared
# the executable is deleted
# input and output file directories are deleted, removing all output files
# issue "make clean" if files are too large for github
#	makes output:
#		unit_test_8 ()
clean : clear_inputs clear_outputs
	clear
	@echo 'all inputs and outputs were deleted'