"""
    the RSA-306B API group "IQSTREAM"
    exposes the API features of the C++ compiled binary to the python user
"""

import ctypes
from ..configuration import rsa_so


def iqset(ms= 10, bw= 20.0e6, use_siq=True) -> int :
    """IQSTREAM set; specify acquisition time, bandwidth, and destination (direct or to file)"""
    # rsa_so.iqstream_set_vars.restype = ctypes.c_int
    result = rsa_so.iqstream_set_vars(ctypes.c_int(ms), ctypes.c_double(bw), ctypes.c_bool(use_siq))
    return int(result)

def iqacq() -> int :
    """IQSTREAM acquire; used for a direct acquition (not to a file)"""
    # rsa_so.iqstream_acq_direct.restype = ctypes.c_int
    result = rsa_so.iqstream_acq_direct()
    return int(result)

def iqcsv() -> str :
    """IQSTREAM acquire; used after a direct acquition (not to a file), dumps the data to CSV"""
    # rsa_so.iqstream_write_csv.restype = ctypes.c_char_p
    temp = rsa_so.iqstream_write_csv()
    result = temp.decode()
    return result

def iqrec() -> str :
    """IQSTREAM record SIQ file; data acquisiton for streaming to file (not direct)"""
    # rsa_so.iqstream_record_siq.restype = ctypes.c_char_p
    temp = rsa_so.iqstream_record_siq()
    result = temp.decode()
    return result
    
    
########~~~~~~~~END>  api_iqstream.py
