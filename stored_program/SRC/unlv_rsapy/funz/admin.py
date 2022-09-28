"""
    adminstrative function
"""

import os
import sys

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


def clear() :
    os.system("clear")


def stop() :
    sys.exit("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")


########~~~~~~~~END>  admin.py
