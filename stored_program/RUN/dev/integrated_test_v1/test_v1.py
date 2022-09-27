# trying shared library technique

# must issue in every terminal:
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/

# run interactivley                  $ python3 -i dummy.py
# run as a script                    $ ./dummy.py
# run as a top-level module          $ python3 dummy.py


DATA_PROCESSED =                                          "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_processed/"
DATA_RAW =                                                "/home/unlv/Desktop/rsa306b_api_applications/stored_program/DATA/data_raw/"
HELP_MESSAGE_1 =  "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/"
HELP_MESSAGE_2 =                                   "source /home/unlv/Desktop/rsa306b_api_applications/py_rsa_venv/bin/activate"
SO_DIR =                                                  "/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/libRSA306B.so"
rsa_so = None

import ctypes
import os
import sys

from plot_spectrum import plot_spectrum

try :
    rsa_so = ctypes.CDLL(SO_DIR)
except :
    print("\nDid you run this ???")
    print(f"\t$ {HELP_MESSAGE_1}")
    print(f"\t$ {HELP_MESSAGE_2}")
    print("\nIs the file-path-name of the library correct ???")
    print(f"\t{SO_DIR}")
    sys.exit("failed to find the library or path was not exported")

def clear() :
    os.system("clear")

def lsf() :
    print("lsf     ()                         list availible interactive functions")
    print("clear   ()                         clear the terminal")
    print("stop    ()                         exit the program")
    print("config  (cf_Hz, ref_dBm)           set the center frequecny and reference level")
    print("drun    ()                         device RUN")
    print("dstop   ()                         device STOP")
    print("ddis    ()                         disconnect")
    print("dcon    ()                         device connect")
    print("soff    ()                         disable spectrum measurement")
    print("son     ()                         enable spectrum measuremet")
    print("sset    (tlen, span, rbw)          set spectrum parameters")
    print("sacq    ()                         acquire a spectrum trace")
    print("spdx    ()                         returns value of highest power measurement in the trace")
    print("scsv    (fn)                       spectrum writes CSV to specified file-name")
    print("sspin   ()                         collect spectrum traces with specified settings")
    print("sscan   ()                         collect spectrum traces across a large range of frequencies, manual")
    print("sauto   ()                         collect spectrum traces across a large range of frequencies, automatic")
    print("\n\n")

def stop() :
    sys.exit("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")

clear()
lsf()


#####################################################################################################################
#####################################################################################################################


def config(cf= 315e6, dbm= -9.99) :
    rsa_so.config_set_vars(ctypes.c_double(cf), ctypes.c_double(dbm))

def dcon() :
    rsa_so.device_connect()

def ddis() :
    rsa_so.device_disconnect()

def drun() :
    rsa_so.device_run()

def dstop() :
    rsa_so.device_stop()

def soff() :
    rsa_so.spectrum_disable()

def son() :
    rsa_so.spectrum_enable()

def sset(tlen= 1111, span=30e6, rbw=10e3) :
    rsa_so.spectrum_set_vars(ctypes.c_int(tlen), ctypes.c_double(span), ctypes.c_double(rbw))

def sacq() :
    rsa_so.spectrum_acquire()

def spdx() :
    rsa_so.spectrum_find_peak.restype = ctypes.c_float
    return rsa_so.spectrum_find_peak()

def scsv() :
    rsa_so.spectrum_write_csv.restype = ctypes.c_char_p
    temp = rsa_so.spectrum_write_csv()
    ofile = temp.decode()
    return ofile

def sspin(repz=7, cf=315e6, dbm=-25.5, tlen=1111, span=5e6, rbw=1e3, thresh=-35.6) :
    #dcon()
    config(cf, dbm)
    sset(tlen, span, rbw)
    son()
    drun()
    for xx in range(0, repz) :
        sacq()
        pmax = spdx()
        
        if pmax > thresh :
            print(f"{xx:2d} ) {pmax:0.5f}  dBm   ...writing CSV")
            dataf = scsv()
            plot_spectrum(dataf)
        else :
            print(f"{xx:2d} ) {pmax:0.5f}  dBm   ...just noise")
    soff()
    dstop()
    #ddis()

def sscan(fstart=1e6, fstop=1000e6, dbm=-25.5, tlen=3333, span=20e6, rbw=10e3, thresh=-55.6, loiter=4, olap=1e6) :
    #dcon()
    hitz = 0
    repz = int((fstop-fstart)/span)
    for xx in range(0, repz+1) :
        cf = (xx*span + span) - olap
        config(cf, dbm)
        sset(tlen, span, rbw)
        son()
        drun()
        for yy in range(0, loiter) :
            sacq()
            pmax = spdx()
            if pmax > thresh :
                print(f"{xx:7d} )  cf:  {cf/1e6:15.3f}  MHz  ,  max dBm:{pmax:9.3f}  dBm   ...writing CSV")
                dataf = scsv()
                plot_spectrum(dataf)
                hitz = hitz + 1
            else :
                print(f"{xx:7d} )  cf:  {cf/1e6:15.3f}  MHz  ,  max dBm:{pmax:9.3f}  dBm   ...noise")
    print(f"\n\tscan complete, found {hitz} traces of interest")
    soff()
    dstop()
    #ddis()

def sauto(fstart=10e6, fstop=400e6, dbm=-25.5, tlen=999, span=10e6, rbw=10e3, thresh=-55.6, loiter=3) :
    #dcon()
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








































####~~~~


# if __name__ == "__main__" :
#     main()


########~~~~~~~~END>  test_v1.py