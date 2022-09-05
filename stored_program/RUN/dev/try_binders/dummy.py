# trying shared library technique

# must issue in every terminal:
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/

# run interactivley                  $ python3 -i dummy.py
# run as a script                    $ ./dummy.py
# run as a top-level module          $ python3 dummy.py


import ctypes
import os
import sys
def clear() :
    os.system("clear")
def lsf() :
    print("lsf()             list availible interactive functions")
    print("clear()           clear the terminal")
    print("stop()            exit the program")
    print("fint(int)         given an integer, value is incremented")
    print("connect()         connects the RSA-306B")
    print("printd()          print API group DEVICE")
    print("destroy()         call the destructor on the RSA API object")
    print("\n\n")
def stop() :
    sys.exit("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")

HELP_MESSAGE = "$  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/"
SO_DIR = "/home/unlv/Desktop/rsa306b_api_applications/stored_program/RUN/shared_objects/libRSA306B.so"
rsa_so = None

try :
    rsa_so = ctypes.CDLL(SO_DIR)
except :
    print("\nDid you run this ???")
    print(f"\t{HELP_MESSAGE}")
    print("\nIs the file-path-name of the library correct ???")
    print(f"\t{SO_DIR}")
    sys.exit("\n\tfailed to find the library or path was not exported\n")

rsa_so.dummy_plus_plus_by_val.restype = ctypes.c_int
clear()
lsf()


def fint(int_in=1) :
    i_in = ctypes.c_int(int_in)
    i_out = rsa_so.dummy_plus_plus_by_val(i_in)
    print(f"x = {int_in}, calling function to increment...")
    print(f"x = {i_out}, x++")

def connect() :
    rsa_so.dcon()

def printd() :
    rsa_so.print_d()

# def destroy() :
#     rsa_so.destructor()

####~~~~


# if __name__ == "__main__" :
#     main()


########~~~~~~~~END>  dummy.py