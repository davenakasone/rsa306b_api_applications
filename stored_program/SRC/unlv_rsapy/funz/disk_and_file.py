"""
    use these to make sure the disk does not overflow
    shutil makes things easy
    the idea is to delete the data directory if over 90% of the disk space is used (< 10% free)
    by this time, the uploader should have taken all the files to cloud storage
"""

import ctypes
import os
import shutil
from ..configuration import rsa_so
from ..configuration import DATA_DIR
from ..configuration import DATA_SEQUENCED
from ..configuration import DATA_RAW
from ..configuration import DATA_PROCESSED
from ..configuration import GDRIVE_DIR
from ..configuration import GDRIVE_DIR_SEQUENCED
from ..configuration import GDRIVE_DIR_RAW
from ..configuration import GDRIVE_DIR_PROCESSED
from .plot_eq import plot_eq
from .plot_if import plot_if
from .plot_iq import plot_iq
from .plot_spectrum import plot_spectrum
from .admin import clear

def uploader(verbose=True) :
    """upload files"""
    def upload(src, dest, verb=verbose) :
        """helper"""
        if verb is True :
            print("\n")
        srcf = os.listdir(src)
        destf = os.listdir(dest)
        for f in srcf :
            if f not in destf :
                p_src = os.path.join(src, f)
                p_dest = os.path.join(dest, f)
                try :
                    shutil.move(p_src, p_dest)
                except :
                    if verb is True :
                        print(f"already there:  {p_dest}")
                else :
                    if verb is True :
                        print(f"{src} -->\n\t{p_dest}")
            else :
                if verb is True :
                    print(f"duplicate:  {f}")
    try :
        os.mkdir(GDRIVE_DIR)
    except :
        if verbose is True :
            print(f"already exists: {GDRIVE_DIR}")
    try :
        os.mkdir(GDRIVE_DIR_PROCESSED)
    except :
        if verbose is True :
            print(f"already exists: {GDRIVE_DIR_PROCESSED}")
    try :
        os.mkdir(GDRIVE_DIR_RAW)
    except :
        if verbose is True :
            print(f"already exists: {GDRIVE_DIR_RAW}")
    try :
        os.mkdir(GDRIVE_DIR_SEQUENCED)
    except :
        if verbose is True :
            print(f"already exists: {GDRIVE_DIR_SEQUENCED}")
    upload(DATA_RAW, GDRIVE_DIR_RAW, verbose)
    upload(DATA_PROCESSED, GDRIVE_DIR_PROCESSED, verbose)
    upload(DATA_SEQUENCED, GDRIVE_DIR_SEQUENCED, verbose)
    if verbose is True :
        print("\n\tUPLOADS COMPLETE\n")

def deldata() -> None :
    """delete all data files"""
    result = rsa_so.delete_data()

def cdisk(verbose= True) -> None :
    """check the disk space, delete data if it gets too full"""
    path = "/"
    statz = shutil.disk_usage(path)
    # there are 2^30 bytes in a gigabyte
    total: float = float(statz.total / 2.0**30) 
    used: float = float(statz.used / 2.0**30)
    free: float = float(statz.free / 2.0**30)
    pfull: float = used / total
    if verbose is True :
        print(f"\ntotal=  {total:0.2f} GB  ,  used= {used:0.2f} GB  ,  free= {free:0.2f}  GB   -->  {pfull*100:0.2f} % full")
    if pfull > 0.9 :
        if verbose is True :
            print(f"-->  {pfull*100:0.2f} % full...deleting {DATA_DIR}")
        deldata()
    
def fplot() -> None :
    """file plot, for convienence"""
    def dspin(dname: str) -> None :
        """spin files in selected directory"""
        while True :
            temp = rsa_so.file_select(dname.encode())
            if temp is None :
                print(f"released:  {dname}")
                return
            ofile = temp.decode()
            print("\n[0] QUIT / return")
            print("[1] plot_eq()")
            print("[2] plot_if()")
            print("[3] plot_iq()")
            print("[4] plot_spectrum()")
            pselect = int(input(f"select poltter for {ofile}  : "))
            if (pselect != 1) and (pselect != 2) and (pselect != 3) and (pselect != 4) :
                print(f"\n\t{pselect}")
                return
            if pselect == 1 :
                try :
                    plot_eq(ofile)
                except :
                    print("plot_eq() failed")
            if pselect == 2 :
                try :
                    plot_if(ofile)
                except :
                    print("plot_if() failed")
            if pselect == 3 :
                try :
                    plot_iq(ofile)
                except :
                    print("plot_iq() failed")
            if pselect == 4 :
                try :
                    plot_spectrum(ofile)
                except :
                    print("plot_spectrum() failed")
    print(f"\n[1] {DATA_PROCESSED}")
    print(f"[2] {DATA_RAW}")
    print(f"[3] {DATA_SEQUENCED}")
    task = int(input("make a selection : "))
    if (task != 1) and (task != 2) and (task != 3) :
        print(f"\nbad selection:  {task}")
        return
    if task == 1 :
        dspin(DATA_PROCESSED)
    if task == 2 :
        dspin(DATA_RAW)
    if task == 3 :
        dlist = []
        contents = os.listdir(DATA_SEQUENCED)
        for idx in range(0, len(contents)) :
            if os.path.isdir(DATA_SEQUENCED + contents[idx] + '/') :
                dlist.append(DATA_SEQUENCED + contents[idx] + '/')
        if len(dlist) < 1 :
            print(f"\nno directories in:  {DATA_SEQUENCED}")
            return
        print("\n")
        for idx in range(0, len(dlist)) :
            print(f"[{idx+1:3d}]  {dlist[idx]}")
        dselect = 0
        dselect = int(input("select a directory: "))
        if (dselect < 1) or (dselect > len(dlist)) :
            print(f"\nbad selection:  {dselect}")
            return
        dspin(dlist[dselect-1])


########~~~~~~~~END>  disk_and_file.py
