"""
    test the program for a specified duration
    testing the special functions is best because they are built on the core capabilities
    if the program does not crash and success message is displayed, the test passed
"""

import ctypes
import datetime
import time
from .admin import clear
from .admin import stop
from .disk_and_file import cdisk
from ..configuration import rsa_so


def testd(dayz=0, hourz=0, minutez=0, secondz=30, sleepz=3) -> None :
    """duration test of the program"""
    duration = datetime.timedelta(days=dayz, hours=hourz, minutes=minutez, seconds=secondz)
    start_time = datetime.datetime.now()
    current_time = datetime.datetime.now()
    tdiff = current_time - start_time
    iterz = 0

    while (duration.days >= tdiff.days) and (duration.seconds >= tdiff.seconds) :
        clear()
        try :
            # test the dump-files (spectrum, IQ, IF, includes all raw)
            tempd = rsa_so.scan_dump(\
                ctypes.c_int(2),
                ctypes.c_double(30.0e6),
                ctypes.c_double(5.7e9), 
                ctypes.c_double(-11.11), 
                ctypes.c_double(-33.33))
            directory = tempd.decode()
            # test the spectrum scanner 
            temps = rsa_so.spectrum_scanner(\
                ctypes.c_double(30.e6),\
                ctypes.c_double(5.7e9),\
                ctypes.c_double(-55.55),\
                ctypes.c_int(5),\
                ctypes.c_double(-12.22),\
                ctypes.c_double(1.0e5),\
                ctypes.c_double(35.0e6),\
                ctypes.c_int(1111))
            ofile = temps.decode()
        except :
            print("\n\n\t!!! TEST FAILED !!!\n\n")
            stop()
        
        current_time = datetime.datetime.now()
        tdiff = current_time - start_time
        if len(directory) < 1 :
            print("\n\tno files to dump\n")
        else :
            print(f"\n\tdumped files in:  {directory}\n")
        if len(ofile) < 1 :
            print("\n\tno scanner data\n")
        else :
            print(f"\n\tscanner data: {ofile}\n")
        iterz = iterz + 1
        run_s = tdiff.seconds
        dhrz = divmod(run_s, 60*60)
        run_s = run_s - (dhrz[0] * 60 * 60)
        dminz = divmod(run_s, 60)
        run_s = run_s - (dminz[0] * 60)
        print(f"\n@ {current_time}  ,  ", end='')
        print(f"ELAPSED[days={tdiff.days}, {dhrz[0]:02d}:{dminz[0]:02d}:{run_s:02d}]  ,  ", end='')
        print(f"successful iterations: {iterz}\n")
        cdisk()
        try :
            time.sleep(sleepz)
        except KeyboardInterrupt :
            print("\n\n\tduration test aborted...\n")
            return
        else :
            pass

    print("\n\n\t~ TEST SUCCESS ~ TEST SUCCESS ~ TEST SUCCESS ~ \n\n")


########~~~~~~~~END>  tester.py
