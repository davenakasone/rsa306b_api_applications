"""
    special functions
    exposes the API features of the C++ compiled binary to the python user
"""

import matplotlib.pyplot
import pandas

import ctypes
from ..configuration import rsa_so

from ..funz.plot_spectrum import plot_spectrum
from ..funz.plot_if import plot_if
from ..funz.plot_iq import plot_iq
from ..funz.plot_eq import plot_eq
from ..funz.admin import clear

def scand(smode=2, fstart = 10.0e6, fstop= 5.7e9, refl= -2.3, thresh=-44.4) -> None :
    """scan and dump"""
    directory = rsa_so.scan_dump(\
        ctypes.c_int(smode),
        ctypes.c_double(fstart),
        ctypes.c_double(fstop), 
        ctypes.c_double(refl), 
        ctypes.c_double(thresh))
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

def sauto(fstart=30e6, fstop=5.7e9, dbm=-25.5, tlen=999, span=20e6, rbw=10e4, thresh=-55.6, loiter=3) -> None :
    """scan, automatic average and pass through specified range, no stopping"""
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


def bscan(fstart=30e6, fstop=5.7e9, dbm=-25.5, tlen=999, span=35e6, rbw=10.0e5, thresh=-55.6, loiter=2) -> None :
    "get background then scan, similar to sauto (with addition of the background trace"
    discard = None
    discard = input("enter any key to get the BACKGROUND spectrum: ")
    temp_b = rsa_so.spectrum_scanner_b1(\
        ctypes.c_double(fstart),\
        ctypes.c_double(fstop),\
        ctypes.c_double(thresh),\
        ctypes.c_int(loiter),\
        ctypes.c_double(dbm),\
        ctypes.c_double(rbw),\
        ctypes.c_double(span),\
        ctypes.c_int(tlen))
    discard = input("enter any key to get the ACTIVE spectrum: ")
    temp_a = rsa_so.spectrum_scanner_b2(\
        ctypes.c_double(fstart),\
        ctypes.c_double(fstop),\
        ctypes.c_double(thresh),\
        ctypes.c_int(loiter),\
        ctypes.c_double(dbm),\
        ctypes.c_double(rbw),\
        ctypes.c_double(span),\
        ctypes.c_int(tlen))
    if (temp_a is None) or (temp_b is None) :
            print("no files were found")
            return
    ofile_a = temp_a.decode()
    ofile_b = temp_b.decode()
    if (len(ofile_a) > 1) and (len(ofile_b) > 1) :
        label_xx = "frequency"
        label_yy = "power"
        fptr_a = None
        fptr_b = None
        try :
            fptr_a = open(ofile_a, "r")
        except FileNotFoundError :
            print(f"file not found:  {ofile_a}")
            return
        except :
            print("unknown error occured")
            return
        try :
            fptr_b = open(ofile_b, "r")
        except FileNotFoundError :
            print(f"file not found:  {ofile_b}")
            return
        except :
            print("unknown error occured")
            return
        fptr_a.close()
        fptr_b.close()
        fields = [label_xx, label_yy]   
        data_frame_a = pandas.read_csv(ofile_a, skiprows=2, header=None, names=fields)
        data_frame_b = pandas.read_csv(ofile_b, skiprows=2, header=None, names=fields)
        xx_a = data_frame_a[label_xx]
        yy_a = data_frame_a[label_yy]
        xx_b = data_frame_b[label_xx]
        yy_b = data_frame_b[label_yy]
        matplotlib.pyplot.xlabel(f"{label_xx} (Hz)")
        matplotlib.pyplot.ylabel(f"{label_yy} (dBm)")
        matplotlib.pyplot.title(f"{label_xx}  vs  {label_yy}")
        matplotlib.pyplot.plot(xx_a, yy_a, "b-")
        matplotlib.pyplot.plot(xx_b, yy_b, "r-")
        matplotlib.pyplot.legend(['background', 'active'])
        matplotlib.pyplot.gcf().autofmt_xdate()
        matplotlib.pyplot.show()
    else :
        print("sauto() failed")


########~~~~~~~~END>  special.py
