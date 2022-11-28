"""
build out the C++ binders, hooks, and wrappers for the R3F file manager
"""

import ctypes
from ..configuration import rsa_so


def r3f_eql() -> str:
    # rsa_so.get_r3f_csv_equalization.restype = ctypes.c_char_p
    temp = rsa_so.get_r3f_csv_equalization()
    result = temp.decode()
    return result

def r3f_adc() -> str:
    # rsa_so.get_r3f_csv_adc.restype = ctypes.c_char_p
    temp = rsa_so.get_r3f_csv_adc()
    result = temp.decode()
    return result
    

########~~~~~~~~END>  r3f_utility.py
