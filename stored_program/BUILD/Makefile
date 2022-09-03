# child shell can't control the parent shell
#     so, be sure to export and source after making the target
#     or, change .bashrc / make a bash script
# issue "$ make -j" to build on all availible cores (slow compile time)
# "CFLAGS = -Wall -lpthread -std=c++17 -O3 -I $(IDIR)" for maximum optimization
SHELL := /bin/bash
CC = g++
IDIR = ../SRC/cpp_class_v2/api_resourcez/
LDIR = /home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/
SDIR = ../SRC/cpp_class_v2/program_core/
TDIR = ../SRC/cpp_class_v2/program_test/
DATA_IO = ../DATA/

EXEC = ../RUN/oo
CFLAGS = -Wall -std=c++17 -I $(IDIR)
LDFLAGS	= -L $(LDIR)
LIB_1 = -lRSA_API
LIB_2 = -lcyusb_shared
LIB_3 = -lpthread

DATA_IO_PROCESSED = $(DATA_IO)data_processed/
DATA_IO_RAW = $(DATA_IO)data_raw/
TDIR_U = $(TDIR)units/
TDIR_T = $(TDIR)tasks/

SOURCE_FILES_SO =\
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
$(SDIR)siq_manager/siq_write_csv.cpp


SOURCE_FILES_ALL = $(SDIR)main.cpp \
$(TDIR_T)task_500.cpp \
$(TDIR_T)task_989.cpp \
$(TDIR_T)task_990.cpp \
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
$(TDIR)wait_enter_clear.cpp \
$(SOURCE_FILES_SO)


# stdout is cleared
# the executable is first deleted, then a clean build occurs
# user must export library path 
# user must activate the python environmnet (if using python tools)
raw :
	clear
	rm -f $(EXEC)
	$(CC) -o $(EXEC) $(CFLAGS) $(SOURCE_FILES_ALL) $(LDFLAGS) $(LIB_1) $(LIB_2)	$(LIB_3)
	@echo [ ${EXEC} ] compiled 
	@echo "...copy and paste in terminal:"
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LDIR)
#source /home/unlv/Desktop/rsa306b_api_applications/rsa_venv/rsa/bin/activate   use a boost binder 


# stdout is cleared
# the executable is deleted
# "data_processed" file directory is deleted, removing all processed data files
# empty file directory is made
# "data_raw" file directory is preserved
clear_data_processed :
	clear
	rm -f $(EXEC)
	rm -rf $(DATA_IO_PROCESSED)
	mkdir $(DATA_IO_PROCESSED)
	clear
	@echo 'all outputs were deleted'


# stdout is cleared
# the executable is deleted
# "data_raw" file directory is deleted, removing all raw data files
# empty file directory is made
# "data_processed" file directory is preserved
clear_data_raw :
	clear
	rm -f $(EXEC)
	rm -rf $(DATA_IO_RAW)
	mkdir $(DATA_IO_RAW)
	clear
	@echo 'all inputs were deleted'


# stdout is cleared
# the executable is deleted
# everything in DATA directory gets deleted (raw and processed data)
# issue "make clean" if files are too large for github
clean : clear_data_raw clear_data_processed
	clear
	@echo 'all inputs and outputs were deleted'