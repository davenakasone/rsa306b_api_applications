""""
    package init for "unlv_rsapy"
    the collection of modules designed to expose RSA-306B features to the user
    it is basically a C++ wrapper, packaged into python3

    connects to the shared object and lets the user do research
"""


# get the shared object
from .configuration import rsa_so


# get the constants
from .configuration import DATA_DIR
from .configuration import DATA_PROCESSED
from .configuration import DATA_RAW
from .configuration import DATA_SEQUENCED
from .configuration import HELP_MESSAGE_1
from .configuration import HELP_MESSAGE_2
from .configuration import SO_DIR


# get the functions and utilities
from .funz.admin import stop
from .funz.admin import clear
from .funz.admin import lsfl
from .funz.admin import lsf
from .funz.admin import lsf_a
from .funz.admin import lsf_b
from .funz.admin import lsf_c
from .funz.admin import lsf_d
from .funz.admin import lsf_if
from .funz.admin import lsf_iq
from .funz.admin import lsf_s
from .funz.admin import lsf_r3f
from .funz.admin import lsf_siq
from .funz.admin import lspec
from .funz.admin import lsf_u
from .funz.admin import lsf_p
from .funz.plot_eq import plot_eq
from .funz.plot_if import plot_if
from .funz.plot_iq import plot_iq
from .funz.plot_spectrum import plot_spectrum
from .funz.disk_and_file import uploader
from .funz.disk_and_file import deldata
from .funz.disk_and_file import cdisk
from .funz.disk_and_file import fplot
from .funz.tester import testd


# get the R3F file manager wrappers
from .r3f_wrapper.r3f_utility import r3f_adc
from .r3f_wrapper.r3f_utility import r3f_eql
from .r3f_wrapper.f_r3f import r3f_adcp
from .r3f_wrapper.f_r3f import r3f_eqlp


# get the SIQ file manager wrappers
from .siq_wrapper.siq_utility import siq_csv
from .siq_wrapper.f_siq import siq_csvp


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

from .rsa_wrapper.api_ifstream import ifset
from .rsa_wrapper.api_ifstream import ifacq
from .rsa_wrapper.api_ifstream import ifcsv
from .rsa_wrapper.api_ifstream import ifrec
from .rsa_wrapper.api_ifstream import ifeq

from .rsa_wrapper.f_ifstream import ifcsvx
from .rsa_wrapper.f_ifstream import ifrecx
from .rsa_wrapper.f_ifstream import ifeqx

from .rsa_wrapper.api_iqblk import bset
from .rsa_wrapper.api_iqblk import bacq
from .rsa_wrapper.api_iqblk import bcsv
from .rsa_wrapper.f_iqblk import bspin

from .rsa_wrapper.api_iqstream import iqacq
from .rsa_wrapper.api_iqstream import iqcsv
from .rsa_wrapper.api_iqstream import iqrec
from .rsa_wrapper.api_iqstream import iqset
from .rsa_wrapper.f_iqstream import iqcsvx
from .rsa_wrapper.f_iqstream import iqrecx

from .rsa_wrapper.api_spectrum import soff
from .rsa_wrapper.api_spectrum import son
from .rsa_wrapper.api_spectrum import sset
from .rsa_wrapper.api_spectrum import sacq
from .rsa_wrapper.api_spectrum import sfpi
from .rsa_wrapper.api_spectrum import scsv
from .rsa_wrapper.f_spectrum import sspin
from .rsa_wrapper.f_spectrum import sscan
from .rsa_wrapper.f_spectrum import sdet


# get the specialized functions
from .special.special import sdump
from .special.special import sauto
from .special.special import bscan
from .special.special import diffscan
from .special.special import tdump
from .special.demonstration import rdemo

########~~~~~~~~END>  __init__.py
