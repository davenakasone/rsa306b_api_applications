"""
    the RSA-306B API group "GP"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so


def api_n() -> int :
    """get the current API status code number"""
    result = rsa_so.api_status()
    return int(result)

def api_m() -> str :
    """get the current API status code string"""
    temp = rsa_so.api_status_message()
    result = temp.decode()
    return result


########~~~~~~~~END>  api_gp.py
