"""
    the RSA-306B API group "CONFIG"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so


def config(cf= 315e6, dbm= -9.99) -> int :
    """API group config is the gateway to setting reference level and center frequency"""
    # rsa_so.config_set_vars.restype = ctypes.c_int
    result = rsa_so.config_set_vars(ctypes.c_double(cf), ctypes.c_double(dbm))
    if int(result) != 0 :
        print(f"config() failed,  {int(result)}")
    return int(result)


########~~~~~~~~END>  api_config.py
