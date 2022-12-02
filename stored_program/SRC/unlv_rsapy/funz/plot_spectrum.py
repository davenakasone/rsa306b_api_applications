"""
    opens a valid CSV (n, 2)
    this function is expecting the CSV to have a "frequency" and "power" column
    when a valid CSV is opened and read, a plot is made

    independent (x-axis) = frequency [in Hz]
    dependent (y-axis)   = power [in dBm]
"""

# from tkinter import N
import matplotlib.pyplot
import pandas


def plot_spectrum(input_file_path_name, verbose=True) -> None:
    """called to plot frequency vs power data from a CSV file for a single spectrum trace"""
    label_xx = "frequency"
    label_yy = "power"
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

    fields = [label_xx, label_yy]   
    data_frame = pandas.read_csv(input_file_path_name, skiprows=2, header=None, names=fields)
    rows, cols = data_frame.shape
    if verbose :
        print(data_frame.head(5))
        print(f"rows  :  {rows}")
        print(f"cols  :  {cols}")
    
    xx = data_frame[label_xx]
    yy = data_frame[label_yy]
    matplotlib.pyplot.xlabel(f"{label_xx} (Hz)")
    matplotlib.pyplot.ylabel(f"{label_yy} (dBm)")
    matplotlib.pyplot.title(f"{label_xx}  vs  {label_yy}")
    matplotlib.pyplot.plot(xx, yy, 'g-')
    matplotlib.pyplot.gcf().autofmt_xdate()
    matplotlib.pyplot.show()


########~~~~~~~~END>  plot_spectrum.py
