""""
    package init for "unlv_rsapy"
    the collection of modules designed to expose RSA-306B features to the user
    it is basically a C++ wrapper, packaged into python3

    connects to the shared object and lets the user do research
"""


# get the shared object
from .configuration import rsa_so


# get the constants
from .configuration import DATA_PROCESSED
from .configuration import DATA_RAW
from .configuration import HELP_MESSAGE_1
from .configuration import HELP_MESSAGE_2
from .configuration import SO_DIR


# get the functions
from .funz.admin import clear
from .funz.admin import lsf
from .funz.admin import stop
from .funz.plot_spectrum import plot_spectrum


# get the R3F file manager wrappers
from .r3f_wrapper.r3fw import r3fw


# get the RSA-306B wrappers
from .rsa_wrapper.api_device import dcon
from .rsa_wrapper.api_device import ddis
from .rsa_wrapper.api_device import drun
from .rsa_wrapper.api_device import dstop
from .rsa_wrapper.api_device import dreset
from .rsa_wrapper.api_device import dprun
from .rsa_wrapper.api_device import dtran

from .rsa_wrapper.api_config import config

from .rsa_wrapper.api_gp import api_n
from .rsa_wrapper.api_gp import api_m

from .rsa_wrapper.api_iqblk import bset
from .rsa_wrapper.api_iqblk import bacq
from .rsa_wrapper.api_iqblk import bcsv

from .rsa_wrapper.api_spectrum import soff
from .rsa_wrapper.api_spectrum import son
from .rsa_wrapper.api_spectrum import sset
from .rsa_wrapper.api_spectrum import sacq
from .rsa_wrapper.api_spectrum import sfpi
from .rsa_wrapper.api_spectrum import scsv
from .rsa_wrapper.api_spectrum import sauto


# get the RSA-306B applied concepts
from .rsa_wrapper.f_iqblk import bspin
from .rsa_wrapper.f_spectrum import sspin
from .rsa_wrapper.f_spectrum import sscan


# get the SIQ file manager wrappers
from .siq_wrapper.siqw import siqw


########~~~~~~~~END>  __init__.py
