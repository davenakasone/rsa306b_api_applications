"""
    special functions
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
import matplotlib.pyplot
import numpy
import pandas

from ..configuration import rsa_so

from ..funz.plot_spectrum import plot_spectrum
from ..funz.plot_if import plot_if
from ..funz.plot_iq import plot_iq
from ..funz.plot_eq import plot_eq
from ..funz.admin import clear


def sdump(smode=2, fstart = 10.0e6, fstop= 5.7e9, refl= -20.3, thresh=-44.4) -> None :
    """scan and dump"""
    directory = rsa_so.scan_dump(\
        ctypes.c_int(smode),
        ctypes.c_double(fstart),
        ctypes.c_double(fstop), 
        ctypes.c_double(refl), 
        ctypes.c_double(thresh))
    print("\nneed to wait for file managers to parse files...")
    while True :
        print("\nenter 0 to stop -->")
        temp = rsa_so.file_select(directory)
        if temp is None :
            print(f"released:  {directory}")
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
        clear()


def sauto(fstart=30e6, fstop=5.7e9, dbm=-15.5, tlen=999, span=20e6, rbw=10e4, thresh=-55.6, loiter=3) -> None :
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


def bscan(fstart=30e6, fstop=5.7e9, dbm=-15.5, tlen=999, span=30e6, rbw=10.0e5, thresh=-55.6, loiter=2) -> None :
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
    if (len(ofile_a) < 1) or (len(ofile_b) < 1) :
        print("scpectrum scanner failed")
        return
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
    matplotlib.pyplot.plot(xx_b, yy_b, "b--")
    matplotlib.pyplot.plot(xx_a, yy_a, "r-")
    matplotlib.pyplot.legend(['background', 'active'])
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()


def diffscan(fstart=30e6, fstop=5.7e9, dbm=-15.5, tlen=3333, span=30e6, rbw=10.0e5, thresh=-55.6, loiter=3, nfloor=20.0) -> None :
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
    if (len(ofile_a) < 1) or (len(ofile_b) < 1) :
        print("scpectrum scanner failed")
        return
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
    yy_a = data_frame_a[label_yy].to_numpy()
    xx_b = data_frame_b[label_xx].to_numpy()
    yy_b = data_frame_b[label_yy].to_numpy()
    yy = numpy.array(yy_a - yy_b)
    pavg = numpy.zeros_like(yy)
    hi_floor = numpy.full_like(yy, numpy.abs(nfloor))
    lo_floor = numpy.full_like(yy, (-1) * numpy.abs(nfloor))
    matplotlib.pyplot.xlabel(f"{label_xx} (Hz)")
    matplotlib.pyplot.ylabel(f"DIFFERENCE  {label_yy} (dBm)")
    matplotlib.pyplot.title(f"[[[ Active - Background ]]]    {label_xx}  vs  {label_yy}")
    for ii in range(0, yy.size) :
        if (yy[ii] < (-1) * numpy.abs(nfloor)) or (yy[ii] > numpy.abs(nfloor)) :
            matplotlib.pyplot.plot(xx_b[ii], yy[ii], "r.")
    matplotlib.pyplot.plot(xx_b, pavg, "b--", linewidth=3)
    matplotlib.pyplot.plot(xx_b, hi_floor, "b:", linewidth=3)
    matplotlib.pyplot.plot(xx_b, lo_floor, "b:", linewidth=3)
    matplotlib.pyplot.show()


def tdump(loiter=3, fstart=30.0e6, fstop=1.0e9, rlvl=-1.1, tlvl=-33.33, rbw=1.0e4, span=30.0e6, tlen=3333, recms=2) -> None :
    """when triggered, scan and dump"""
    directory = rsa_so.trigger_dump(\
        ctypes.c_int(loiter),
        ctypes.c_double(fstart),
        ctypes.c_double(fstop), 
        ctypes.c_double(rlvl), 
        ctypes.c_double(tlvl), 
        ctypes.c_double(rbw),
        ctypes.c_double(span),  
        ctypes.c_int(tlen),
        ctypes.c_int(recms))
    print("\nneed to wait for file managers to parse files...")
    while True :
        print("\nenter 0 to stop -->")
        temp = rsa_so.file_select(directory)
        if temp is None :
            print(f"released:  {directory}")
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
        clear()


########~~~~~~~~END>  special.py
