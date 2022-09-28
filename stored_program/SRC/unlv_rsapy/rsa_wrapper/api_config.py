"""
    the RSA-306B API group "CONFIG"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so


def config(cf= 315e6, dbm= -9.99) -> None :
    rsa_so.config_set_vars(ctypes.c_double(cf), ctypes.c_double(dbm))


########~~~~~~~~END>  api_config.py
