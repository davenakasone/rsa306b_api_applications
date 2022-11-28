"""
    the RSA-306B API group "DEVICE"
    exposes the API features of the C++ compiled binary to the python user
"""

from ..configuration import rsa_so


def dcon() -> None :
    """device connect"""
    rsa_so.device_connect()

def ddis() -> None :
    """device disconnect"""
    rsa_so.device_disconnect()

def drun() -> None :
    """device run"""
    rsa_so.device_run()

def dstop() -> None :
    """device stop"""
    rsa_so.device_stop()

def dreset() -> None :
    """device reset, be careful with this one"""
    rsa_so.device_reset()

def dprun() -> None :
    """device prepare for run"""
    rsa_so.device_prepare_for_run()

def dtran() -> None :
    """device start transfer"""
    rsa_so.device_start_transfer()


########~~~~~~~~END>  api_device.py
