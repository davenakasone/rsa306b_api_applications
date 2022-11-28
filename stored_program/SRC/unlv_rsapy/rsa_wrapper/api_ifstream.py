"""
    the RSA-306B API group "IFSTREAM"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so


def ifset(ms= 10, use_r3f=True) -> int :
    """ifstream set; select recording time in milli-seconds and destination (direct or to file)"""
    # rsa_so.ifstream_set_vars.restype = ctypes.c_int
    result = rsa_so.ifstream_set_vars(ctypes.c_int(ms), ctypes.c_bool(use_r3f))
    return int(result)

def ifacq() -> int :
    """ifstream acquire; used if data destination is direct (not to a file)"""
    # rsa_so.ifstream_acq_direct.restype = ctypes.c_int
    result = rsa_so.ifstream_acq_direct()
    return int(result)

def ifcsv() -> str :
    """ifstream write CSV; used if data destination is direct (not to a file), ADC values"""
    # rsa_so.ifstream_write_csv.restype = ctypes.c_char_p
    temp = rsa_so.ifstream_write_csv()
    result = temp.decode()
    return result

def ifrec() -> str :
    """ifstream record r3f file; used if data destination is to a file (not direct)"""
    # rsa_so.ifstream_record_r3f.restype = ctypes.c_char_p
    temp = rsa_so.ifstream_record_r3f()
    result = temp.decode()
    return result

def ifeq() -> str :
    """ifstream write CSV; used if data destination is direct (not to a file), equalization values"""
    # rsa_so.ifstream_equalization.restype = ctypes.c_char_p
    temp = rsa_so.ifstream_equalization()
    result = temp.decode()
    return result
    
    
########~~~~~~~~END>  api_ifstream.py
