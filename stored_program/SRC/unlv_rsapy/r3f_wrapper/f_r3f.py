"""
build out the C++ binders, hooks, and wrappers for the R3F file manager
"""


from .r3f_utility import r3f_adc
from .r3f_utility import r3f_eql
from ..funz.plot_eq import plot_eq
from ..funz.plot_if import plot_if


def r3f_eqlp() -> None :
    catcher = r3f_eql()
    if catcher == "" :
        print("no r3f files are available")
        return
    plot_eq(catcher)

def r3f_adcp() -> None :
    catcher = r3f_adc()
    if catcher == "" :
        print("no r3f files are available")
        return
    plot_if(catcher)
    

########~~~~~~~~END>  f_r3f.py
