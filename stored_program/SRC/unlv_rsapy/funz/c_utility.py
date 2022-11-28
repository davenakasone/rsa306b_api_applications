"""
    common utilities from implemented in C++
    exposes the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so


def ddata() -> None :
    """delete all data files"""
    result = rsa_so.delete_data()


########~~~~~~~~END>  c_utility.py
