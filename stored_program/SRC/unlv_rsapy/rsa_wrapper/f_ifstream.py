"""
    functions that use the API group "IFSTREAM"
"""

from .api_config import config
from .api_device import drun
from .api_device import dstop
from .api_ifstream import ifacq
from .api_ifstream import ifcsv
from .api_ifstream import ifset
from .api_ifstream import ifeq
from .api_ifstream import ifrec
from ..funz.plot_if import plot_if
from ..funz.plot_eq import plot_eq


def ifcsvx(repz= 3, cf=315.0e6, dbm=-33.3) -> None :
    dstop()
    if config(cf, dbm) != 0 :
        return
    if ifset(ms=10, use_r3f=False) :
        return

    drun()
    for xx in range(0, repz) :
        if ifacq() == 0 :
            dataf = ifcsv()
            print(f"see:  {dataf}")
            plot_if(dataf)
        else :
            print("acquisition failed")
    dstop()


def ifrecx(repz= 3, cf=315.0e6, dbm=-33.3, ms=10) -> None :
    dstop()
    if config(cf, dbm) != 0 :
        return
    if ifset(ms=ms, use_r3f=True) != 0 :
        return

    drun()
    for xx in range(0, repz) :
        dataf = ifrec()
        if len(dataf) > 1 :
            print(f"see:  {dataf}")
        else :
            print("streaming R3F file failed")            
    dstop()


def ifeqx(repz= 3, cf=315.0e6, dbm=-33.3) -> None :
    dstop()
    if config(cf, dbm) != 0 :
        return
    if ifset() :
        return

    for xx in range(0, repz) :
        eqf = ifeq()
        if len(eqf) > 1 :
            print(f"see:  {eqf}")
            plot_eq(eqf)
        else :
            print("failed to get equalization parameters")
            

########~~~~~~~~END>  f_ifstream.py
