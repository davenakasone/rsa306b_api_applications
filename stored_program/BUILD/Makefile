# child shell can't control the parent shell
#     so, be sure to export and source after making the target
#     or, change .bashrc / make a bash script
# issue "$ make -j" to build on all availible cores (slow compile time)
# "CFLAGS = -Wall -lpthread -std=c++17 -O3 -I $(IDIR)" for maximum optimization
# pthread should be included already, use $ldd on the Tektronix shared objects
# consider optimizations as performance needs grow (+ macros)
#
########################### TARGETS #############################################################
# $ make alone                                 compile stand-alone program
# $ make shared                                compile shared library
# $ make all                                   compile stand-alone program and shared library
# $ make clear_data_processed                  delete "processed data"
# $ make clear_data_raw                        delete "raw data"
# $ make clear_data                            delete all data
# $ make clear_logs                            deletes all the debugging logs
# $ make clear                                 delets data and logs, but keeps compiled binaries
# $ make clean                                 delete all: data, compiled binaries, and logs
#################################################################################################


SHELL := /bin/bash
CC = g++
CFLAGS = -Wall -std=c++17 -o
EXEC = ../RUN/oo
MY_LIB_SO = ../RUN/shared_objects/libRSA306B.so
LIB_DIR = ~/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/
RPATH	= -L $(LIB_DIR)
LIB_RSA_API = -lRSA_API
LIB_CYUSB = -lcyusb_shared

SDIR = ../SRC/cpp_classes/program_core/
TDIR = ../SRC/cpp_classes/program_test/
PYDIR = ../SRC/cpp_classes/python_interface/
DDIR = $(SDIR)control/de_bug/
UDIR = $(SDIR)common_utility/
DATA_IO = ../DATA/
DATA_IO_PROCESSED = $(DATA_IO)data_processed/
DATA_IO_RAW = $(DATA_IO)data_raw/
DLOGZ = ../DOC/debug_logs/
TDIR_U = $(TDIR)units/
TDIR_T = $(TDIR)tasks/


SOURCE_FILES_SO =\
$(UDIR)cu_codez.cpp \
$(UDIR)cu_common_utility.cpp \
$(UDIR)cu_timing.cpp \
$(UDIR)cu_wchar_2_char.cpp \
$(DDIR)de_bug.cpp \
$(DDIR)debug_functions.cpp \
$(SDIR)control/globalz.cpp \
$(SDIR)r3f_manager/r3fc_file_decode.cpp \
$(SDIR)r3f_manager/r3fc_file_process.cpp \
$(SDIR)r3f_manager/r3fc_handle_adc.cpp \
$(SDIR)r3f_manager/r3fc_plot_maker.cpp \
$(SDIR)r3f_manager/r3fc_private.cpp \
$(SDIR)r3f_manager/r3fc_public.cpp \
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
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_copy.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_get.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_print_init.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_user1.cpp \
$(SDIR)rsa306b/rsa306b_DEVICE/rsa306b_device_user2.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_class.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_confirm.cpp \
$(SDIR)rsa306b/rsa306b_GP/rsa306b_gp_print.cpp \
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
$(SDIR)rsa306b/rsa306b_IQSTREAM/rsa306b_iqstream_acquire.cpp \
$(SDIR)rsa306b/rsa306b_IQSTREAM/rsa306b_iqstream_copy.cpp \
$(SDIR)rsa306b/rsa306b_IQSTREAM/rsa306b_iqstream_get.cpp \
$(SDIR)rsa306b/rsa306b_IQSTREAM/rsa306b_iqstream_print_init_check.cpp \
$(SDIR)rsa306b/rsa306b_IQSTREAM/rsa306b_iqstream_set.cpp \
$(SDIR)rsa306b/rsa306b_IQSTREAM/rsa306b_iqstream_user.cpp \
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
$(SDIR)siq_manager/siq_common.cpp \
$(SDIR)siq_manager/siq_decode.cpp \
$(SDIR)siq_manager/siq_error_codes.cpp \
$(SDIR)siq_manager/siq_init_copy.cpp \
$(SDIR)siq_manager/siq_loader.cpp \
$(SDIR)siq_manager/siq_printer.cpp \
$(SDIR)siq_manager/siq_write_csv.cpp \
$(PYDIR)dummy.cpp


SOURCE_FILES_ALL =$(SDIR)main.cpp \
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
$(TDIR)wait_enter_clear.cpp \
$(SOURCE_FILES_SO)


# 1st TARGET
# stdout is cleared
# the executable is first deleted, then a clean build occurs
# user must export library path 
# designed to be run with unit tests, no python
alone :
	clear
	rm -f $(EXEC)
	$(CC) $(CFLAGS) $(EXEC) $(SOURCE_FILES_ALL) $(RPATH) $(LIB_RSA_API) $(LIB_CYUSB)
	@echo "[ ${EXEC} ] compiled"
	@echo "...copy and paste in terminal:"
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LIB_DIR)


# stdout is cleared
# shared library "*.so" file is deleted
# user must export library path 
# user must activate the python environmnet (if using python tools)
shared :
	clear
	rm -f $(MY_LIB_SO)
	g++ -std=c++17 -Wall -fPIC -shared -o $(MY_LIB_SO) $(SOURCE_FILES_SO) $(RPATH) $(LIB_RSA_API) $(LIB_CYUSB)
	@echo "[ ${MY_LIB_SO} ] is compiled and ready"
	@echo "...copy and paste in terminal:"
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LIB_DIR)
	@echo "source /home/unlv/Desktop/rsa306b_api_applications/stored_program/py_rsa_venv/bin"


# builds both binaries
all : alone shared
	@echo "built a stand alone executable [ $(MY_LIB_SO) ] and a shared library [ $(EXEC) ]"


# stdout is cleared
# the executable is deleted
# "data_processed" file directory is deleted, removing all processed data files
# empty file directory is made
# "data_raw" file directory is preserved
clear_data_processed :
	clear
	rm -rf $(DATA_IO_PROCESSED)
	mkdir $(DATA_IO_PROCESSED)
	clear
	@echo 'all data outputs were deleted'


# stdout is cleared
# the executable is deleted
# "data_raw" file directory is deleted, removing all raw data files
# empty file directory is made
# "data_processed" file directory is preserved
clear_data_raw :
	clear
	rm -rf $(DATA_IO_RAW)
	mkdir $(DATA_IO_RAW)
	clear
	@echo 'all data inputs were deleted'


# does not delete executables or debug logs, just the data
clear_data : clear_data_raw clear_data_processed
	@echo 'all data inputs and outputs were deleted'


# delete all the debug logs
clear_logs :
	clear
	rm -rf $(DLOGZ)
	mkdir $(DLOGZ)
	clear
	@echo 'all debug logs were deleted'


# deletes data and debug logs
clear : clear_data clear_logs
	clear
	@echo 'debug logs and data were deleted'


# stdout is cleared
# the executable is deleted
# the shared library is delted
# everything in DATA directory gets deleted (raw and processed data)
# issue "make clean" if files are too large for github
clean : clear
	rm -f $(EXEC)
	rm -f $(MY_LIB_SO)
	clear
	@echo 'all data inputs and outputs were deleted'
	@echo 'all compiled binaries were deleted'
	@echo 'all debug logs were deleted'
