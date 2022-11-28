"""
build out the C++ binders, hooks, and wrappers for the SIQ file manager
"""

import ctypes
from ..configuration import rsa_so


def siq_csv() -> str :
    """SIQ manager lists all acquired raw .siq files, user makes a selection, file is processed"""
    # rsa_so.get_siq_csv.restype = ctypes.c_char_p
    temp = rsa_so.get_siq_csv()
    result = temp.decode()
    return result


########~~~~~~~~END>  siq_utility.py
