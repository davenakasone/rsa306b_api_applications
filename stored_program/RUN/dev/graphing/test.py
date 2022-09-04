"""
    graphs
"""

import csv
import py_compile
from tkinter import N
import matplotlib.pyplot
import numpy
import pandas

VERBOSE = True    # prints output as processing occurs

# for development
input_directory     = "./"
input_file_spectrum = "_656818283207_freqVpow_trace_0.csv"
input_file_adc      = "ifstream_315MHz_2.csv"
input_file_iqb      = "IQblk_315MHz_2.csv"
input_file_iqs      = "IQstream_315MHz_2.csv"


# real inputs
# input_directory     = "../../../DATA/data_processed/"
# input_file_spectrum = "_204608131306_freqVpow_trace_0.csv"
# input_file_adc      = "ifstream_315MHz_0.csv"
# input_file_iqb      = "IQblk_315MHz_0.csv"
# input_file_iqs      = "IQstream_315MHz_0.csv"



def main() :
    plot_spectrum(f"{input_directory}{input_file_spectrum}", VERBOSE)
    plot_iq(f"{input_directory}{input_file_iqs}", VERBOSE)
    plot_iq(f"{input_directory}{input_file_iqb}", VERBOSE)
    plot_adc(f"{input_directory}{input_file_adc}", VERBOSE)
    print("\n\tDONE\n")
    

####~~~~


def plot_spectrum(input_file_path_name, verbose=VERBOSE) :
    label_xx = "frequency"
    label_yy = "power"
    fptr = open(input_file_path_name, "r")
    csv_reader = csv.reader(fptr)
    csv_header = next(csv_reader)
    fptr.close()
    fields = [csv_header[0], csv_header[1]]
    if csv_header[0] != label_xx :
        print(f"field 1, mismatch, expected '{label_xx}', received '{csv_header[0]}")
        return
    if csv_header[1] != label_yy :
        print(f"field 2, mismatch, expected '{label_yy}', received '{csv_header[1]}")
        return

    data_frame = pandas.read_csv(input_file_path_name, skiprows=1, header=None, names=fields)
    rows, cols = data_frame.shape
    if verbose :
        print(data_frame)
        print(f"rows  :  {rows}")
        print(f"cols  :  {cols}")
    
    xx = data_frame[label_xx]
    yy = data_frame[label_yy]
    matplotlib.pyplot.xlabel(f"{label_xx} (Hz)")
    matplotlib.pyplot.ylabel(f"{label_yy} (dBm)")
    matplotlib.pyplot.title(f"{label_xx}  vs  {label_yy}")
    matplotlib.pyplot.plot(xx, yy)
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()


####~~~~


def plot_iq(input_file_path_name, verbose=VERBOSE) :
    label_i = "I"
    label_q = "Q"
    fptr = open(input_file_path_name, "r")
    csv_reader = csv.reader(fptr)
    csv_header = next(csv_reader)
    fptr.close()
    fields = [csv_header[0], csv_header[1]]
    if csv_header[0] != label_i :
        print(f"field 1, mismatch, expected '{label_i}', received '{csv_header[0]}")
        return
    if csv_header[1] != label_q :
        print(f"field 2, mismatch, expected '{label_q}', received '{csv_header[1]}")
        return
    
    data_frame = pandas.read_csv(input_file_path_name, skiprows=1, header=None, names=fields)
    rows, cols = data_frame.shape
    if verbose :
        print(data_frame)
        print(f"rows  :  {rows}")
        print(f"cols  :  {cols}")

    ii = data_frame[label_i]
    qq = data_frame[label_q]
    axis_time = numpy.linspace(0, rows-1, num=rows)

    matplotlib.pyplot.xlabel("time")
    matplotlib.pyplot.ylabel("I/Q value in ADC")
    matplotlib.pyplot.title(f"{label_i} and {label_q}  vs Time")
    matplotlib.pyplot.plot(axis_time, ii, label="I")
    matplotlib.pyplot.plot(axis_time, qq, label="Q")
    matplotlib.pyplot.legend()
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()


####~~~~


def plot_adc(input_file_path_name, verbose=VERBOSE) :
    adc = []
    axis_time = []
    field = "ADC"
    line = None
    fptr = open(input_file_path_name, "r")
    count = 0
    while True :
        if count == 0 :
            line = fptr.readline().rstrip()
            if line != field :
                print(f"wrong field, expected '{field}', received '{line}'")
                return
        else :
            line = fptr.readline()
            temp = line.split(",")
            tempn = temp[0]
            if tempn == '' :
                break
            adc.append(float(tempn))
            axis_time.append(count-1)
        count = count + 1
        if not line :
            break
    fptr.close()    
    if len(adc) != len(axis_time) :
        print(f"bad time series, Time series:  {len(axis_time)},  ADC values:  {len(adc)}")
        return

    matplotlib.pyplot.xlabel("time")
    matplotlib.pyplot.ylabel("ADC reading")
    matplotlib.pyplot.title(f"ADC Time Series")
    matplotlib.pyplot.plot(axis_time[0:1000], adc[0:1000])
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()
    

####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  test.py
