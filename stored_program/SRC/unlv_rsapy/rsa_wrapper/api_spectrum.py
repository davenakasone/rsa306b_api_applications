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

def sset(tlen= 1111, span=30e6, rbw=10e3) -> None :
    rsa_so.spectrum_set_vars(ctypes.c_int(tlen), ctypes.c_double(span), ctypes.c_double(rbw))

def sacq() -> None :
    rsa_so.spectrum_acquire()

def sfpi() -> int :
    rsa_so.spectrum_find_peak.restype = ctypes.c_float
    return rsa_so.spectrum_find_peak()

def scsv() -> str :
    rsa_so.spectrum_write_csv.restype = ctypes.c_char_p
    temp = rsa_so.spectrum_write_csv()
    ofile = temp.decode()
    return ofile

def sauto(fstart=10e6, fstop=400e6, dbm=-25.5, tlen=999, span=10e6, rbw=10e3, thresh=-55.6, loiter=3) -> None :
    rsa_so.spectrum_scanner.restype = ctypes.c_char_p
    temp = rsa_so.spectrum_scanner(\
        ctypes.c_double(fstart),\
        ctypes.c_double(fstop),\
        ctypes.c_double(thresh),\
        ctypes.c_int(loiter),\
        ctypes.c_double(dbm),\
        ctypes.c_double(rbw),\
        ctypes.c_double(span),\
        ctypes.c_int(tlen))
    ofile = temp.decode()
    plot_spectrum(ofile)


########~~~~~~~~END>  api_spectrum.py
