"""
build out the C++ binders, hooks, and wrappers for the SIQ file manager
"""


from .siq_utility import siq_csv
from ..funz.plot_iq import plot_iq


def siq_csvp() -> None :
    catcher = siq_csv()
    if catcher == "" :
        print("no siq files are available")
        return
    plot_iq(catcher)
    

########~~~~~~~~END>  f_siq.py
