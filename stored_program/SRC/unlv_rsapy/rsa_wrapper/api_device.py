"""
    the RSA-306B API group "DEVICE"
    exposes the API features of the C++ compiled binary to the python user
"""

from ..configuration import rsa_so


def dcon() -> None :
    rsa_so.device_connect()

def ddis() -> None :
    rsa_so.device_disconnect()

def drun() -> None :
    rsa_so.device_run()

def dstop() -> None :
    rsa_so.device_stop()


########~~~~~~~~END>  api_device.py
