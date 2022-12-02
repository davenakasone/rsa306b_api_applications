"""
    adminstrative functions
"""

import os
import sys


def clear() :
    os.system("clear")


def stop() :
    sys.exit("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")

def lsfl() :
    clear()
    print("\n")
    print("lsf  ()        list available functions by group")
    print("lsfl ()        list every availible interactive function")
    print("clear()        clear the terminal")
    print("stop ()        exit the program")
    lsf_a(False)
    lsf_b(False)
    lsf_c(False)
    lsf_d(False)
    lsf_if(False)
    lsf_iq(False)
    lsf_s(False)
    lsf_r3f(False)
    lsf_siq(False)
    lspec(False)
    lsf_u(False)
    lsf_p(False)
    print("\n")

def lsf() :
    clear()
    print("\n")
    # general use adminstrative functions
    print("lsfl ()        list every availible interactive function")
    print("clear()        clear the terminal")
    print("stop ()        exit the program\n")
    # API info functions
    print("lsf_a  ()        list API return status functions")
    print("lsf_b  ()        list IQBLKfunctions")
    print("lsf_c  ()        list CONFIG functions")
    print("lsf_d  ()        list DEVICE functions")
    print("lsf_if ()        list IFSTREAM functions")
    print("lsf_iq ()        list IQSTREAM functions")
    print("lsf_s  ()        list SPECTRUM functions")
    # file manager functions
    print("lsf_r3f()        list r3f file manager functions")
    print("lsf_siq()        list siq file manager functions")
    # combined / specialized functions
    print("lspec  ()        list the special functions")
    # utilities + plotting functions
    print("lsf_u  ()        list the utility functions")
    print("lsf_p  ()        list the plotting functions")
    print("\n")


def lsf_a(spacer= True) -> None:
    if spacer == True :
        print("\n")
    print("api_n   ()        get RSA API status as a type<int>")
    print("api_m   ()        get RSA API message as type<str>")
    if spacer == True :
        print("\n")

def lsf_b(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("bset    (bw)                      set the IQBLK bandwidth in Hz, returns 0 if successful")
    print("bacq    ()                        acquire IQBLK data")
    print("bcsv    ()                        write IQBLK data to CSV, returns file name")
    print("bspin   (rep, cf, dbm, bw)        sit on center frequency and collect IQBLK data")
    if spacer == True :
        print("\n")

def lsf_c(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("config(cf_Hz, ref_dBm)        set the center frequecny and reference level")
    if spacer == True :
        print("\n")

def lsf_d(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("dcon    ()        device connect")
    print("drun    ()        device RUN")
    print("dstop   ()        device STOP")
    print("ddis    ()        disconnect")
    print("dprun   ()        device prepare for run")
    print("dtran   ()        device strart frame transfer, effective 'drun'")
    print("dreset  ()        device reset, will crash program if called")
    if spacer == True :
        print("\n")

def lsf_if(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("ifset   (ms, bw, use_siq)          set IFSTREAM, returns 0 if successful")
    print("ifacq   ()                         acquire IFSTREAM data, returns 0 if successful")
    print("ifcsv   ()                         write IFSTREAM data to CSV, returns file name")
    print("ifrec   ()                         record *.r3f IFSTREAM file to disk, returns file name")
    print("ifeq    ()                         write equalization parameters to CSV")
    print("ifcsvx  (repz, cf, dbm)            writes 'repz' IFSTREAM data acquisitions to CSV files")
    print("ifrecx  (repz, cf, dbm, ms)        writes 'repz' IFSTREAM data acquisitions to R3F files")
    print("ifeqx   (repz, cf, dbm, ms)        writes 'repz' equalization parameters to CSV")
    if spacer == True :
        print("\n")

def lsf_iq(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("iqset   (ms, bw, use_siq)              set IQSTREAM, returns 0 if successful")
    print("iqacq   ()                             acquire IQSTREAM data, returns 0 if successful")
    print("iqcsv   ()                             write IQSTREAM data to CSV, returns file name")
    print("iqrec   ()                             record *.siq IQSTREAM file to disk, returns file name")
    print("iqcsvx  (repz, cf, dbm, bw)            writes 'repz' IQSTREAM data acquisitions to CSV files")
    print("iqrecx  (repz, cf, dbm, ms, bw)        writes 'repz' IQSTREAM data acquisitions to SIQ files")
    if spacer == True :
        print("\n")

def lsf_s(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("soff    ()                                                           disable spectrum measurement")
    print("son     ()                                                           enable spectrum measuremet")
    print("sset    (tlen, span, rbw)                                            set spectrum parameters, returns 0 if successful")
    print("sacq    ()                                                           acquire a spectrum trace, returns 0 if successful")
    print("sfpi    ()                                                           returns value of highest power measurement in the trace")
    print("scsv    ()                                                           writes SPECTRUM data to CSV, returns file name")
    print("sspin   (reps, cf, dbm, tlen, span, rbw, thresh)                     collect spectrum traces at fixed center frequency")
    print("sscan   (fstart, fstop, dbm, tlen, span, rbw, thresh, loiter)        collect spectrum traces across a range of frequencies, manual")
    print("sdet    (cf, dbm, repz)                                              detailed version of sspin()")
    if spacer == True :
        print("\n")

def lsf_r3f(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("r3f_adc ()        see available r3f files, convert to ADC csv, returns file")
    print("r3f_eql ()        see available r3f files, convert to equalization csv, returns file")
    print("r3f_adcp()        same as r3f_adc(), new file is plotted")
    print("r3f_eqlp()        same as r3f_eql(), new file is plotted")
    if spacer == True :
        print("\n")

def lsf_siq(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("siq_csv ()        see available SIQ files, convert to CSV, returns file")
    print("siq_csvp()        same as siq_csv(), new file is plotted")
    if spacer == True :
        print("\n")

def lspec(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("sauto   (fstart, fstop, dbm, tlen, span, rbw, thresh, loiter)          collect spectrum traces across a range of frequencies, automatic")
    print("scand   (fstart, fstop, refl, thresh)                                  span and scan a range, DUMP: spectrum, R3F, and SIQ")
    print("bscan   (fstart, fstop, dbm, tlen, span, rbw, thresh, loiter)          similar to sauto(), but collects 2 scans")
    print("diffscan(fstart, fstop, dbm, tlen, span, rbw, thresh, loiter, nfloor)  like bscan(), but only plots differences from nfloor")
    if spacer == True :
        print("\n")

def lsf_u(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("uploader()                                               moves files to upload area, DATA directory is emptied")
    print("deldata ()                                               deletes every file and directory in root data IO, full reset")
    print("cdisk   ()                                               checks disk space, deletes data if over 90%% full")
    print("fplot   ()                                               traverse data and plot files at will")
    print("testd   (dayz, hourz, minutez, secondz, sleepz)          duration test of the program")
    if spacer == True :
        print("\n")

def lsf_p(spacer= True) -> None :
    if spacer == True :
        print("\n")
    print("plot_eq      ()        plot equalization parameters, acqusition + file is required")
    print("plot_if      ()        plot ADC values from intermideate frequency (IF), acqusition + file is required")
    print("plot_iq      ()        plot intermediate and quadrature values (IQ), acqusition + file is required")
    print("plot_spectrum()        plot spectrum data (frequeny + power), acqusition + file is required")
    if spacer == True :
        print("\n")


########~~~~~~~~END>  admin.py
