"""
    opens a valid CSV (n, 3)
    this function is expecting the CSV to have a "time", "I" and "Q" column
    when a valid CSV is opened and read, a plot is made

    independent (x-axis) = frequency [in Hz]
    dependent (y-axis)   = power [in dBm]
"""

from tkinter import N
import matplotlib.pyplot
import pandas


def plot_iqblk(input_file_path_name, verbose=True) -> None :
    label_time = "time"
    label_i = "I"
    label_q = "Q"
    fptr = None
    try :
        fptr = open(input_file_path_name, "r")
    except FileNotFoundError :
        print(f"file not found:  {input_file_path_name}")
        return
    except :
        print("unknown error occured")
        return
    fptr.close()

    fields = [label_time, label_i, label_q]   
    data_frame = pandas.read_csv(input_file_path_name, skiprows=1, header=None, names=fields)
    rows, cols = data_frame.shape
    if verbose :
        print(data_frame.head(5))
        print(f"rows  :  {rows}")
        print(f"cols  :  {cols}")
    
    data_time = data_frame[label_time]
    data_i = data_frame[label_i]
    data_q = data_frame[label_q]
    matplotlib.pyplot.xlabel(f"{label_time} (us)")
    matplotlib.pyplot.ylabel(f"ADC reading")
    matplotlib.pyplot.title(f"{label_i} and {label_q}  vs  {label_time}")
    matplotlib.pyplot.plot(data_time, data_i, label=label_i)
    matplotlib.pyplot.plot(data_time, data_q, label=label_q)
    matplotlib.pyplot.legend()
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()


########~~~~~~~~END>  plot_iqblk.py
