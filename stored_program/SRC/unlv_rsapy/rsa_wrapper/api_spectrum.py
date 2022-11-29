"""
    the RSA-306B API group "SPECTRUM"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes

from ..configuration import rsa_so
from ..funz.plot_spectrum import plot_spectrum


def soff() -> None :
    """spectrum off; disables spectrum group so other groups can take measurements"""
    rsa_so.spectrum_disable()

def son() -> None :
    """spectrum on; enables the spectrum group for acquiring power vs frequency data"""
    rsa_so.spectrum_enable()

def sset(tlen= 1111, span=30e6, rbw=10e3) -> int :
    """spectrum set; select trace length, span, and resolution bandwidth"""
    result = rsa_so.spectrum_set_vars(ctypes.c_int(tlen), ctypes.c_double(span), ctypes.c_double(rbw))
    if int(result) != 0 :
        print(f"sset() failed,  {int(result)}")
    return int(result)

def sacq() -> int :
    """spectrum acquire; power vs frequency data is obtained"""
    result = rsa_so.spectrum_acquire()
    return int(result)

def sfpi() -> float :
    """spectrum find peak index; get the highest power level measured in the last trace"""
    result = rsa_so.spectrum_find_peak()
    return float(result)

def scsv() -> str :
    """spectrum write CSV; makes frequency table and dumps frequency + power data into a CSV"""
    temp = rsa_so.spectrum_write_csv()
    ofile = temp.decode()
    return ofile


########~~~~~~~~END>  api_spectrum.py
