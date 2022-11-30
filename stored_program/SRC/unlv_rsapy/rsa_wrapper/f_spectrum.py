"""
    functions that use the API group "SPECTRUM
"""

from .api_config import config
from .api_device import drun
from .api_device import dstop
from .api_spectrum import scsv
from .api_spectrum import sset
from .api_spectrum import son
from .api_spectrum import soff
from .api_spectrum import sacq
from .api_spectrum import sfpi
from ..funz.plot_spectrum import plot_spectrum


def sspin(repz=7, cf=315.0e6, dbm=-25.5, tlen=1111, span=10.0e6, rbw=1.0e3, thresh=-35.6) -> None :
    """spectrum spin; sits on range of interest and collects specified number of spectrum traces"""
    dstop()
    if config(cf, dbm) != 0 :
        return
    if sset(tlen, span, rbw) != 0 :
        return
    son()
    drun()
    for xx in range(0, repz) :
        if sacq() == 0 :
            pmax = sfpi()
            if pmax > thresh :
                print(f"{xx:2d} )  cf={cf/1e6:0.3f} Mhz  ,  power={pmax:9.2f}  dBm   ...writing CSV")
                dataf = scsv()
                plot_spectrum(dataf)
            else :
                print(f"{xx:2d} )  cf={cf/1e6:0.3f} Mhz  ,  power={pmax:9.2f}  dBm   ...just noise")
        else :
            print("acquisition failed")
    soff()
    dstop()


def sscan(fstart=1.0e6, fstop=1000.0e6, dbm=-35.5, tlen=999, span=10.0e6, rbw=10.0e3, thresh=-55.6, loiter=4) -> None :
    """spectrum scan; spans a large range; if threshold is exceeded, immidatley saves data and plots"""
    dstop()
    hitz = 0
    repz = int((fstop-fstart)/span)
    for xx in range(0, repz+1) :
        cf = (xx*span + span)
        if config(cf, dbm) != 0 :
            return
        if sset(tlen, span, rbw) != 0 :
            return
        son()
        drun()
        for yy in range(0, loiter) :
            if sacq() == 0 :
                pmax = sfpi()
                if pmax > thresh :
                    print(f"{xx:7d} )  cf:  {cf/1e6:15.3f}  MHz  ,  max dBm:{pmax:9.3f}  dBm   ...writing CSV")
                    dataf = scsv()
                    plot_spectrum(dataf)
                    hitz = hitz + 1
                else :
                    print(f"{xx:7d} )  cf:  {cf/1e6:15.3f}  MHz  ,  max dBm:{pmax:9.3f}  dBm   ...noise")
            else :
                print("acquisition failed")
            dstop()
            
    print(f"\n\tscan complete, found {hitz} traces of interest")
    soff()


def sdet(cf= 315.0e6, dbm= -17.7, repz= 5) :
    """spectrum acquisition, detailed focus on specified cf and dBm"""
    sspin(repz, cf, dbm, tlen=33333, span=40e6, rbw=1.0e3, thresh=dbm*1.2) 
    

########~~~~~~~~END>  f_spectrum.py
