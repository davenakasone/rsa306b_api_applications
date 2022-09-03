#!../py_rsa_venv/bin/python


import os
import subprocess

def main() :
    
    # compile the C++ class
    send_command("cd ../SRC/cpp_classv2/")
    send_command("make clean")
    print("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")


####~~~~


def send_command(command) :
    print(f"\n\t{command}  ,  {os.system(command)}\n")


####~~~~


if __name__ == "__main__" :
    main()


########~~~~~~~~END>  test.py
