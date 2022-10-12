"""
    the RSA-306B API group "SPECTRUM"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes

from ..configuration import rsa_so
from ..funz.plot_spectrum import plot_spectrum


def soff() -> None :
    rsa_so.spectrum_disable()

def son() -> None :
    rsa_so.spectrum_enable()

def sset(tlen= 1111, span=30e6, rbw=10e3) -> int :
    rsa_so.spectrum_set_vars.restype = ctypes.c_int
    result = rsa_so.spectrum_set_vars(ctypes.c_int(tlen), ctypes.c_double(span), ctypes.c_double(rbw))
    if int(result) != 0 :
        print(f"sset() failed,  {int(result)}")
    return int(result)

def sacq() -> int :
    rsa_so.spectrum_acquire.restype = ctypes.c_int
    result = rsa_so.spectrum_acquire()
    return int(result)

def sfpi() -> float :
    rsa_so.spectrum_find_peak.restype = ctypes.c_float
    result = rsa_so.spectrum_find_peak()
    return float(result)

def scsv() -> str :
    rsa_so.spectrum_write_csv.restype = ctypes.c_char_p
    temp = rsa_so.spectrum_write_csv()
    ofile = temp.decode()
    return ofile


########~~~~~~~~END>  api_spectrum.py
