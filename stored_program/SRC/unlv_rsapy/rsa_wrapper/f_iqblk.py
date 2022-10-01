"""
    functions that use the API group "IQBLK"
"""

from .api_config import config
from .api_device import drun
from .api_device import dstop
from .api_iqblk import bset
from .api_iqblk import bacq
from .api_iqblk import bcsv
from ..funz.plot_iqblk import plot_iqblk


def bspin(repz=7, cf=315.02e6, dbm=-22.22, bw=20.0e6) -> None :
    dstop()
    config(cf, dbm)
    bset(bw)
    drun()
    for xx in range(0, repz) :
        if bacq() == 0 :
            ofile = bcsv()
            plot_iqblk(ofile)
        else :
            print("acquisition failed")
    dstop()


########~~~~~~~~END>  f_iqblk.py
