"""
    graphs
"""

import csv
from tkinter import N
import matplotlib.pyplot
import numpy
import pandas


#input_directory = "../../DATA/data_processed/"
input_directory = "./"

input_file_spectrum = "_12565703927726_freqVpow_trace_0.csv"
input_file_adc = ""
input_file_iq = "_12569464859436_int32_freeRun.csv"
input_file_triple = ""

def main() :
    plot_2vars(f"{input_directory}{input_file_spectrum}", "frequency", "power")   # for spectrum files
    plot_2vars(f"{input_directory}{input_file_iq}", "I", "Q")                     # for IQ files
    print("\n\tDONE\n")
    

####~~~~


def plot_2vars(input_file_path_name, label_xx, label_yy) :
    fptr = open(input_file_path_name, "r")
    csv_reader = csv.reader(fptr)
    csv_header = next(csv_reader)
    fptr.close()
    fields = [csv_header[0], csv_header[1]]
    print(fields)

    data_frame = pandas.read_csv(input_file_path_name, skiprows=1, header=None, names=fields)
    print(data_frame)
    
    xx = data_frame[label_xx]
    yy = data_frame[label_yy]
    matplotlib.pyplot.xlabel("frequency")
    matplotlib.pyplot.ylabel("power")
    matplotlib.pyplot.title(f"X({label_xx}) vs Y({label_yy})")
    matplotlib.pyplot.plot(xx, yy)
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()


####~~~~


if __name__ == '__main__' :
    main()


########~~~~~~~~END>  test.py
