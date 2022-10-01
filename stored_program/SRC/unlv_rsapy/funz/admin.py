"""
    adminstrative function
"""

import os
import sys


def lsf() :
    print("lsf     ()        list availible interactive functions")
    print("clear   ()        clear the terminal")
    print("stop    ()        exit the program\n")

    print("config  (cf_Hz, ref_dBm)        set the center frequecny and reference level\n")

    print("dcon    ()        device connect")
    print("drun    ()        device RUN")
    print("dstop   ()        device STOP")
    print("ddis    ()        disconnect")
    print("dprun   ()        device prepare for run")
    print("dtran   ()        device strart frame transfer, effective 'drun'")
    print("dreset  ()        device reset, will crash program if called\n")
    
    print("soff    ()                                                           disable spectrum measurement")
    print("son     ()                                                           enable spectrum measuremet")
    print("sset    (tlen, span, rbw)                                            set spectrum parameters")
    print("sacq    ()                                                           acquire a spectrum trace, returns 0 if successful")
    print("spdx    ()                                                           returns value of highest power measurement in the trace")
    print("scsv    ()                                                           spectrum writes CSV and returns specified file-name")
    print("sspin   (reps, cf, dbm, tlen, span, rbw, thresh)                     collect spectrum traces with specified settings")
    print("sscan   (fstart, fstop, dbm, tlen, span, rbw, thresh, loiter)        collect spectrum traces across a large range of frequencies, manual")
    print("sauto   (fstart, fstop, dbm, tlen, span, rbw, thresh, loiter)        collect spectrum traces across a large range of frequencies, automatic\n")

    print("api_n   ()        get RSA API status number 'return code' of most recent call, as an type<int>")
    print("api_m   ()        get RSA API message corresponding to the status number as an type<str>\n")

    print("bset    (bw)                      set the IQBLK bandwidth, in Hz")
    print("bacq    ()                        acquire IQBLK data")
    print("bcsv    ()                        write IQBLK data to a CSV")
    print("bspin   (rep, cf, dbm, bw)        sit on selected center frequency and collect IQBLK data, graphed each repitition")
    print("\n\n")


def clear() :
    os.system("clear")


def stop() :
    sys.exit("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")


########~~~~~~~~END>  admin.py
