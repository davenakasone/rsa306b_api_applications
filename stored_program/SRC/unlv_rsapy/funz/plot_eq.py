"""
    opens a valid CSV (n, 3)
    this function is expecting the CSV to have a "frequency", "scaling power", and "phase" column
    when a valid CSV is opened and read, a plot is made

    independent (x-axis) = frequency(in Hz)
    dependent (y-axis)   = scale and phase
"""

from tkinter import N
import matplotlib.pyplot
import pandas


def plot_eq(input_file_path_name, verbose=True) -> None :
    label_f = "frequency"
    label_s = "scaling"
    label_p = "phase"
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

    fields = [label_f, label_s, label_p]   
    data_frame = pandas.read_csv(input_file_path_name, skiprows=1, header=None, names=fields)
    rows, cols = data_frame.shape
    if verbose :
        print(data_frame.head(5))
        print(f"rows  :  {rows}")
        print(f"cols  :  {cols}")
    
    data_f = data_frame[label_f]
    data_s = data_frame[label_s]
    data_p = data_frame[label_p]
    matplotlib.pyplot.xlabel(f"{label_f} (Hz)")
    matplotlib.pyplot.ylabel(f"Magnitude and Phase")
    matplotlib.pyplot.title(f"{label_s} and {label_p}  vs  {label_f}")
    matplotlib.pyplot.plot(data_f, data_s, label=label_s)
    matplotlib.pyplot.plot(data_f, data_p, label=label_p)
    matplotlib.pyplot.legend()
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()


########~~~~~~~~END>  plot_eq.py
