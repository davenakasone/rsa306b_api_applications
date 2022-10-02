"""
    functions that use the API group "IQSTREAM"
"""

from .api_config import config
from .api_device import drun
from .api_device import dstop
from .api_iqstream import iqacq
from .api_iqstream import iqcsv
from .api_iqstream import iqrec
from .api_iqstream import iqset
from ..funz.plot_iq import plot_iq


def iqcsvx(repz= 3, cf=315.0e6, dbm=-33.3, bw=20.0e6) -> None :
    dstop()
    if config(cf, dbm) != 0 :
        return
    if iqset(ms=10, bw=bw, use_siq=False) :
        return

    drun()
    for xx in range(0, repz) :
        if iqacq() == 0 :
            dataf = iqcsv()
            print(f"see:  {dataf}")
            plot_iq(dataf)
        else :
            print("acquisition failed")
    dstop()


def iqrecx(repz= 3, cf=315.0e6, dbm=-33.3, ms=10, bw=20.0e6) -> None :
    dstop()
    if config(cf, dbm) != 0 :
        return
    if iqset(ms=ms, bw=bw, use_siq=True) != 0 :
        return

    drun()
    for xx in range(0, repz) :
        dataf = iqrec()
        if len(dataf) > 1 :
            print(f"see:  {dataf}")
        else :
            print("streaming SIQ file failed")            
    dstop()

########~~~~~~~~END>  f_iqstream.py
