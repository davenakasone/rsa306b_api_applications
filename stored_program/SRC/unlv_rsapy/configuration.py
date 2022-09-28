"""
    handle to the shared object / library
    lets python interface with the C++ compiled binary

    constants used for hardware, data I/O, and other program needs
"""

import ctypes
import sys


DATA_PROCESSED =                                          "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_processed/"
DATA_RAW =                                                "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_raw/"
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
    

########~~~~~~~~END>  shared_object.py
