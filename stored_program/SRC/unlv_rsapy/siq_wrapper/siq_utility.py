"""
build out the C++ binders, hooks, and wrappers for the SIQ file manager
"""

import ctypes
from ..configuration import rsa_so


def siq_csv() -> str:
    rsa_so.get_siq_csv.restype = ctypes.c_char_p
    temp = rsa_so.get_siq_csv()
    result = temp.decode()
    return result


########~~~~~~~~END>  siq_utility.py
