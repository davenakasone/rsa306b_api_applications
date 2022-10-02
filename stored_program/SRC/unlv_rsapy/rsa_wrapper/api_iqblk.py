"""
    the RSA-306B API group "IQBLK"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so


def bset(bw= 20.0e6) -> None :
    rsa_so.iqblk_set_vars.restype = ctypes.c_int
    result = rsa_so.iqblk_set_vars(ctypes.c_double(bw))
    if int(result) != 0 :
        print(f"bset() failed,  {int(result)}")
    return int(result)

def bacq() -> int :
    rsa_so.iqblk_acquire.restype = ctypes.c_int
    result = rsa_so.iqblk_acquire()
    return int(result)

def bcsv() -> str :
    rsa_so.iqblk_write_csv.restype = ctypes.c_char_p
    temp = rsa_so.iqblk_write_csv()
    result = temp.decode()
    return result
    
    
########~~~~~~~~END>  api_iqblk.py
