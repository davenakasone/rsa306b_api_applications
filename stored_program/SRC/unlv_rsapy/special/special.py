"""
    special functions
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so

from ..funz.plot_spectrum import plot_spectrum
from ..funz.plot_if import plot_if
from ..funz.plot_iq import plot_iq
from ..funz.plot_eq import plot_eq
from ..funz.admin import clear

def scand(fstart = 10.0e6, fstop= 2.0e9, refl= -2.3, thresh=-44.4) -> None :
    rsa_so.scan_dump.restype = ctypes.c_char_p
    rsa_so.file_select.restype = ctypes.c_char_p
    directory = rsa_so.scan_dump(ctypes.c_double(fstart), ctypes.c_double(fstop), ctypes.c_double(refl), ctypes.c_double(thresh))
    while True :
        temp = rsa_so.file_select(directory)
        if temp is None :
            print("no files were found")
            return
        ofile = temp.decode()
        if ofile.find("_ADC_") > 0 :
            plot_if(ofile)
        elif ofile.find("_EQL_") > 0 :
            plot_eq(ofile)
        elif ofile.find("_IQ_") > 0 :
            plot_iq(ofile)
        else :
            plot_spectrum(ofile)
        selected = input("enter 0 to stop : ")
        if int(selected) == 0 :
            break
        clear()

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
    if temp is None :
            print("no files were found")
            return
    ofile = temp.decode()
    if len(ofile) > 1 :
        plot_spectrum(ofile)
    else :
        print("sauto() failed")


########~~~~~~~~END>  special.py
