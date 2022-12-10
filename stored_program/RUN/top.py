"""
    top-level control point for the RSA-206B
    user can operate all:
        - hardware control (settings, diagnostic checks, ect)  "device management"
        - data acquisition (collect data and write it to a file
    
    write a script, program, or use as an interactive session
    best for an interactive session
"""

from pytimedinput import timedKey

import importlib.util
import sys
sys.path.append("../SRC")  # the packace is in "?/rsa306b_api_applications/stored_program/SRC/unlv_rsapy"

#import unlv_rsapy as unlv   # best if writing a program or script
from unlv_rsapy import *     # best for interactive mode


####~~~~
lsf()

def rrdemo() -> None :
    dcon()
    while True :
        rdemo(fstart=50e6, fstop=6.0e9, cf=315.0e6, dbm=-5.5, tlen=1111, span=30.0e6, rbw=1.0e3, ftime=5000, nfloor=15.0)
        cdisk()
        deldata()
        print("")
        userText, timedOut = timedKey(prompt="press any key to quit: ", allowCharacters="", resetOnInput=True, timeout=10)
        if timedOut is True :
            continue
        else :
            stop()





####~~~~


# if __name__ == '__main__' :
#     main()


########~~~~~~~~END>  top.py
