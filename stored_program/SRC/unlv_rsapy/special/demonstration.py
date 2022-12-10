"""
    for the presentation
"""

import ctypes
import matplotlib.pyplot as plt
import numpy
import pandas
import time

from ..configuration import rsa_so
from ..rsa_wrapper.api_config import config
from ..rsa_wrapper.api_device import dcon
from ..rsa_wrapper.api_device import drun 
from ..rsa_wrapper.api_device import dstop
from ..rsa_wrapper.api_spectrum import sset
from ..rsa_wrapper.api_spectrum import soff
from ..rsa_wrapper.api_spectrum import son
from ..rsa_wrapper.api_spectrum import sacq
from ..rsa_wrapper.api_spectrum import scsv
from ..rsa_wrapper.api_ifstream import ifset
from ..rsa_wrapper.api_ifstream import ifacq
from ..rsa_wrapper.api_ifstream import ifcsv
from ..rsa_wrapper.api_iqstream import iqset
from ..rsa_wrapper.api_iqstream import iqacq
from ..rsa_wrapper.api_iqstream import iqcsv


def rdemo(fstart=50e6, fstop=1.0e9, cf=315.0e6, dbm=-15.5, tlen=1111, span=10.0e6, rbw=1.0e3, ftime=5000, nfloor=-10.0) -> None :
    plt.rcParams["figure.figsize"] = [7.00, 3.50]
    plt.rcParams["figure.autolayout"] = True
    
    # spectrum single
    dstop()
    if config(cf, dbm) != 0 :
        return
    if sset(tlen, span, rbw) != 0 :
        return
    drun()
    son()
    if sacq() != 0 :
        return
    dataf = scsv()
    dstop()
    if len(dataf) < 1 :
        return
    label_xx = "frequency"
    label_yy = "power"
    fptr = None
    try :
        fptr = open(dataf, "r")
    except FileNotFoundError :
        print(f"file not found:  {dataf}")
        return
    except :
        print("unknown error occured")
        return
    fptr.close()
    fields = [label_xx, label_yy]   
    data_frame = pandas.read_csv(dataf, skiprows=2, header=None, names=fields)
    xx = data_frame[label_xx]
    yy = data_frame[label_yy]
    fig = plt.figure()
    timer = fig.canvas.new_timer(interval= 2*ftime)
    timer.add_callback(plt.close)
    manager = plt.get_current_fig_manager()
    manager.full_screen_toggle()
    plt.xlabel(f"{label_xx} (Hz)")
    plt.ylabel(f"{label_yy} (dBm)")
    plt.title(f"{label_xx}  vs  {label_yy}")
    plt.plot(xx, yy, 'g-')
    plt.gcf().autofmt_xdate()
    timer.start()
    plt.show()
    time.sleep(ftime/1000)

    # IQ
    dstop()
    result = rsa_so.iqstream_set_vars(ctypes.c_int(1), ctypes.c_double(span), ctypes.c_bool(False))
    if result != 0 :
        return
    drun()
    if iqacq() != 0 :
        return
    dataf = iqcsv()
    if len(dataf) < 1 :
        return
    dstop()
    label_time = "time"
    label_i = "I"
    label_q = "Q"
    fptr = None
    try :
        fptr = open(dataf, "r")
    except FileNotFoundError :
        print(f"file not found:  {dataf}")
        return
    except :
        print("unknown error occured")
        return
    fptr.close()
    fields = [label_time, label_i, label_q]   
    data_frame = pandas.read_csv(dataf, skiprows=1, header=None, names=fields)
    data_time = data_frame[label_time]
    data_i = data_frame[label_i]
    data_q = data_frame[label_q]
    fig = plt.figure()
    timer = fig.canvas.new_timer(interval= 2*ftime)
    timer.add_callback(plt.close)
    manager = plt.get_current_fig_manager()
    manager.full_screen_toggle()
    plt.xlabel(f"{label_time} (s)")
    plt.ylabel(f"ADC reading")
    plt.title(f"{label_i} and {label_q}  vs  {label_time}")
    plt.plot(data_time, data_i, label=label_i)
    plt.plot(data_time, data_q, label=label_q)
    plt.legend()
    plt.gcf().autofmt_xdate()
    timer.start()
    plt.show()
    time.sleep(ftime/1000)

    # ADC / IF
    dstop()
    ifset(ms=10, use_r3f=False)
    drun()
    if ifacq() != 0 :
        return
    dstop()
    dataf = ifcsv()
    if len(dataf) < 1 :
        return
    label_xx = "time"
    label_yy = "ADC Value"
    fptr = None
    try :
        fptr = open(dataf, "r")
    except FileNotFoundError :
        print(f"file not found:  {dataf}")
        return
    except :
        print("unknown error occured")
        return
    fptr.close()

    fields = [label_xx, label_yy]   
    data_frame = pandas.read_csv(dataf, skiprows=2, header=None, names=fields)
    xx = data_frame[label_xx]
    yy = data_frame[label_yy]
    fig = plt.figure()
    timer = fig.canvas.new_timer(interval= 2*ftime)
    timer.add_callback(plt.close)
    manager = plt.get_current_fig_manager()
    manager.full_screen_toggle()
    plt.xlabel(f"{label_xx} (s)")
    plt.ylabel(f"{label_yy} (dn)")
    plt.title(f"{label_xx}  vs  {label_yy}")
    plt.plot(xx, yy, 'm-')
    plt.gcf().autofmt_xdate()
    timer.start()
    plt.show()
    time.sleep(ftime/1000)

    # spectrum scan
    label_xx = "frequency"
    label_yy = "power"
    drun()
    son()
    temp = rsa_so.spectrum_scanner(\
        ctypes.c_double(fstart),\
        ctypes.c_double(fstop),\
        ctypes.c_double(dbm*2),\
        ctypes.c_int(2),\
        ctypes.c_double(dbm),\
        ctypes.c_double(rbw),\
        ctypes.c_double(span),\
        ctypes.c_int(tlen))
    if temp is None :
            return
    dataf = temp.decode()
    if len(dataf) < 1 :
        return
    try :
        fptr = open(dataf, "r")
    except FileNotFoundError :
        print(f"file not found:  {dataf}")
        return
    except :
        print("unknown error occured")
        return
    fptr.close()
    fields = [label_xx, label_yy]   
    data_frame = pandas.read_csv(dataf, skiprows=2, header=None, names=fields)
    xx = data_frame[label_xx]
    yy = data_frame[label_yy]
    fig = plt.figure()
    timer = fig.canvas.new_timer(interval= 2*ftime)
    timer.add_callback(plt.close)
    manager = plt.get_current_fig_manager()
    manager.full_screen_toggle()
    plt.xlabel(f"{label_xx} (Hz)")
    plt.ylabel(f"{label_yy} (dBm)")
    plt.title(f"{label_xx}  vs  {label_yy}")
    plt.plot(xx, yy, 'g-')
    plt.gcf().autofmt_xdate()
    timer.start()
    plt.show()
    dstop()
    time.sleep(ftime/1000)

    # spectrum difference
    drun()
    son()
    temp_b = rsa_so.spectrum_scanner_b1(\
        ctypes.c_double(fstart),\
        ctypes.c_double(fstop),\
        ctypes.c_double(dbm*2),\
        ctypes.c_int(2),\
        ctypes.c_double(dbm),\
        ctypes.c_double(rbw),\
        ctypes.c_double(span),\
        ctypes.c_int(tlen))
    temp_a = rsa_so.spectrum_scanner_b2(\
        ctypes.c_double(fstart),\
        ctypes.c_double(fstop),\
        ctypes.c_double(dbm*2),\
        ctypes.c_int(2),\
        ctypes.c_double(dbm),\
        ctypes.c_double(rbw),\
        ctypes.c_double(span),\
        ctypes.c_int(tlen))
    ofile_a = temp_a.decode()
    ofile_b = temp_b.decode()
    if (len(ofile_a) < 1) or (len(ofile_b) < 1) :
        print("scpectrum scanner failed")
        return
    fptr_a = None
    fptr_b = None
    try :
        fptr_a = open(ofile_a, "r")
    except FileNotFoundError :
        return
    except :
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
    fig = plt.figure()
    timer = fig.canvas.new_timer(interval= 2*ftime)
    timer.add_callback(plt.close)
    manager = plt.get_current_fig_manager()
    manager.full_screen_toggle()
    plt.xlabel(f"{label_xx} (Hz)")
    plt.ylabel(f"DIFFERENCE  {label_yy} (dBm)")
    plt.title(f"[[[ Active - Background ]]]    {label_xx}  vs  {label_yy}")
    for ii in range(0, yy.size) :
        if (yy[ii] < (-1) * numpy.abs(nfloor)) or (yy[ii] > numpy.abs(nfloor)) :
            plt.plot(xx_b[ii], yy[ii], "r.")
    plt.plot(xx_b, pavg, "b--", linewidth=3)
    plt.plot(xx_b, hi_floor, "b:", linewidth=3)
    plt.plot(xx_b, lo_floor, "b:", linewidth=3)
    timer.start()
    plt.show()
    dstop()


########~~~~~~~~END>  demonstration.py