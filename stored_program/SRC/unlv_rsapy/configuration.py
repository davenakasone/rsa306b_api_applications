"""
    handle to the shared object / library
    lets python interface with the C++ compiled binary

    constants used for hardware, data I/O, and other program needs
"""

import ctypes
import sys

DATA_DIR             =                                    "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/"
DATA_PROCESSED       =                                    "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_processed/"
DATA_RAW             =                                    "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_raw/"
DATA_SEQUENCED       =                                    "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_sequenced/"
GDRIVE_DIR           =                                    "/home/unlv/Desktop/GOOGLE_DRIVE/ee497_498/DATA_IO/"
GDRIVE_DIR_RAW       =                                    "/home/unlv/Desktop/GOOGLE_DRIVE/ee497_498/DATA_IO/raw/"
GDRIVE_DIR_PROCESSED =                                    "/home/unlv/Desktop/GOOGLE_DRIVE/ee497_498/DATA_IO/processed"
GDRIVE_DIR_SEQUENCED =                                    "/home/unlv/Desktop/GOOGLE_DRIVE/ee497_498/DATA_IO/sequenced"
HELP_MESSAGE_1 =  "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/"
HELP_MESSAGE_2 =                                   "source /home/unlv/Desktop/rsa306b_api_applications/py_rsa_venv/bin/activate"
SO_DIR =                                                  "/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/libRSA306B.so"

try :
    rsa_so = ctypes.CDLL(SO_DIR)
except :
    print("\nDid you run this ???")
    print(f"\t$ {HELP_MESSAGE_1}")
    print(f"\t$ {HELP_MESSAGE_2}")
    print("\nIs the file-path-name of the library correct ???")
    print(f"\t{SO_DIR}")
    sys.exit("failed to find the library or path was not exported")

rsa_so.scan_dump.restype = ctypes.c_char_p
rsa_so.file_select.restype = ctypes.c_char_p
rsa_so.spectrum_scanner.restype = ctypes.c_char_p
rsa_so.spectrum_scanner_b1.restype = ctypes.c_char_p
rsa_so.spectrum_scanner_b2.restype = ctypes.c_char_p
rsa_so.get_r3f_csv_equalization.restype = ctypes.c_char_p
rsa_so.get_r3f_csv_adc.restype = ctypes.c_char_p
rsa_so.get_siq_csv.restype = ctypes.c_char_p
rsa_so.spectrum_set_vars.restype = ctypes.c_int
rsa_so.spectrum_acquire.restype = ctypes.c_int
rsa_so.spectrum_find_peak.restype = ctypes.c_float
rsa_so.spectrum_write_csv.restype = ctypes.c_char_p
rsa_so.iqstream_set_vars.restype = ctypes.c_int
rsa_so.iqstream_acq_direct.restype = ctypes.c_int
rsa_so.iqstream_write_csv.restype = ctypes.c_char_p
rsa_so.iqstream_record_siq.restype = ctypes.c_char_p
rsa_so.iqblk_set_vars.restype = ctypes.c_int
rsa_so.iqblk_acquire.restype = ctypes.c_int
rsa_so.iqblk_write_csv.restype = ctypes.c_char_p
rsa_so.ifstream_set_vars.restype = ctypes.c_int
rsa_so.ifstream_acq_direct.restype = ctypes.c_int
rsa_so.ifstream_write_csv.restype = ctypes.c_char_p
rsa_so.ifstream_record_r3f.restype = ctypes.c_char_p
rsa_so.ifstream_equalization.restype = ctypes.c_char_p
rsa_so.api_status.restype = ctypes.c_int
rsa_so.api_status_message.restype = ctypes.c_char_p
rsa_so.config_set_vars.restype = ctypes.c_int


########~~~~~~~~END>  shared_object.py
