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

def dreset() -> None :
    rsa_so.device_reset()

def dprun() -> None :
    rsa_so.device_prepare_for_run()

def dtran() -> None :
    rsa_so.device_start_transfer()


########~~~~~~~~END>  api_device.py
