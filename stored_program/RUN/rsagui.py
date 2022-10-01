"""
    top-level control point for the RSA-206B
    user can operate all:
        - hardware control (settings, diagnostic checks, ect)  "device management"
        - data acquisition (collect data and write it to a file
    
    made for using a gui
"""

from tkinter import N
import tkinter

import importlib.util
import sys
sys.path.append("../SRC")  # the packace is in "?/rsa306b_api_applications/stored_program/SRC/unlv_rsapy"

#import unlv_rsapy as unlv   # best if writing a program or script
#from unlv_rsapy import *     # best for interactive mode


####~~~~


rootw = tkinter.Tk()
rwidth  = rootw.winfo_screenwidth()
rheight = rootw.winfo_screenheight()
rootw.geometry(f"{rwidth}x{rheight}")
rootw.title("RSA-306B")

tkinter.Label(rootw, text='UNLV').grid(row=0, column=0)
tkinter.Label(rootw, text='spectrometry').grid(row=1, column=1)

rootw.mainloop()









####~~~~


# if __name__ == '__main__' :
#     main()


########~~~~~~~~END>  rsagui.py
