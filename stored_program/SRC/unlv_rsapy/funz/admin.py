"""
    adminstrative function
"""

import os
import sys


def clear() :
    os.system("clear")


def stop() :
    sys.exit("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")


def lsf() :
    clear()
    print("\nlsf     ()                                                           list availible interactive functions")
    print("clear   ()                                                           clear the terminal")
    print("stop    ()                                                           exit the program\n")

    print("config  (cf_Hz, ref_dBm)                                             set the center frequecny and reference level\n")

    print("dcon    ()                                                           device connect")
    print("drun    ()                                                           device RUN")
    print("dstop   ()                                                           device STOP")
    print("ddis    ()                                                           disconnect")
    print("dprun   ()                                                           device prepare for run")
    print("dtran   ()                                                           device strart frame transfer, effective 'drun'")
    print("dreset  ()                                                           device reset, will crash program if called\n")

    print("api_n   ()                                                           get RSA API status as a type<int>")
    print("api_m   ()                                                           get RSA API message as type<str>\n")

    print("ifset   (ms, bw, use_siq)                                            set IFSTREAM, returns 0 if successful")
    print("ifacq   ()                                                           acquire IFSTREAM data, returns 0 if successful")
    print("ifcsv   ()                                                           write IFSTREAM data to CSV, returns file name")
    print("ifrec   ()                                                           record *.r3f IFSTREAM file to disk, returns file name")
    print("ifeq    ()                                                           write equalization parameters to CSV")
    print("ifcsvx  (repz, cf, dbm)                                              writes 'repz' IFSTREAM data acquisitions to CSV files")
    print("iqrecx  (repz, cf, dbm, ms)                                          writes 'repz' IFSTREAM data acquisitions to R3F files")
    print("ifeqx   (repz, cf, dbm, ms)                                          writes 'repz' equalization parameters to CSV\n")

    print("bset    (bw)                                                         set the IQBLK bandwidth in Hz, returns 0 if successful")
    print("bacq    ()                                                           acquire IQBLK data")
    print("bcsv    ()                                                           write IQBLK data to CSV, returns file name")
    print("bspin   (rep, cf, dbm, bw)                                           sit on center frequency and collect IQBLK data\n")

    print("iqset   (ms, bw, use_siq)                                            set IQSTREAM, returns 0 if successful")
    print("iqacq   ()                                                           acquire IQSTREAM data, returns 0 if successful")
    print("iqcsv   ()                                                           write IQSTREAM data to CSV, returns file name")
    print("iqrec   ()                                                           record *.siq IQSTREAM file to disk, returns file name")
    print("iqcsvx  (repz, cf, dbm, bw)                                          writes 'repz' IQSTREAM data acquisitions to CSV files")
    print("iqrecx  (repz, cf, dbm, ms, bw)                                      writes 'repz' IQSTREAM data acquisitions to SIQ files\n")
    
    print("soff    ()                                                           disable spectrum measurement")
    print("son     ()                                                           enable spectrum measuremet")
    print("sset    (tlen, span, rbw)                                            set spectrum parameters, returns 0 if successful")
    print("sacq    ()                                                           acquire a spectrum trace, returns 0 if successful")
    print("sfpi    ()                                                           returns value of highest power measurement in the trace")
    print("scsv    ()                                                           writes SPECTRUM data to CSV, returns file name")
    print("sspin   (reps, cf, dbm, tlen, span, rbw, thresh)                     collect spectrum traces at fixed center frequency")
    print("sscan   (fstart, fstop, dbm, tlen, span, rbw, thresh, loiter)        collect spectrum traces across a range of frequencies, manual")
    print("sauto   (fstart, fstop, dbm, tlen, span, rbw, thresh, loiter)        collect spectrum traces across a range of frequencies, automatic\n")

    print("\n\n")


########~~~~~~~~END>  admin.py
