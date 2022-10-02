"""
    top-level control point for the RSA-206B
    user can operate all:
        - hardware control (settings, diagnostic checks, ect)  "device management"
        - data acquisition (collect data and write it to a file
    
    write a script, program, or use as an interactive session
    best for an interactive session
"""


import importlib.util
import sys
sys.path.append("../SRC")  # the packace is in "?/rsa306b_api_applications/stored_program/SRC/unlv_rsapy"

#import unlv_rsapy as unlv   # best if writing a program or script
from unlv_rsapy import *     # best for interactive mode


####~~~~
lsf()










####~~~~


# if __name__ == '__main__' :
#     main()


########~~~~~~~~END>  top.py
