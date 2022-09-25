import csv
import py_compile
from tkinter import N
import matplotlib.pyplot
import numpy
import pandas


def plot_spectrum(input_file_path_name, verbose=True) :
    label_xx = "frequency"
    label_yy = "power"
    # fptr = open(input_file_path_name, "r")
    # csv_reader = csv.reader(fptr)
    # csv_header = next(csv_reader)
    # fptr.close()
    fields = [label_xx, label_yy]
   
    data_frame = pandas.read_csv(input_file_path_name, skiprows=2, header=None, names=fields)
    rows, cols = data_frame.shape
    if verbose :
        #print(data_frame)
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
    
    
    
    
    
    
    
    
    
    
    
    
    
    # label_xx = "frequency"
    # label_yy = "power"
    # xx = []
    # yy = []
    # fptr = open(input_file_path_name, "r")
    # count  = 0
    # while True :
    #     if count < 3 :
    #         line = fptr.readline().strip()
    #     else :
    #         line = fptr.readline().strip()
    #         temp = line.split(",")
    #         #print(f"{temp[0]}   {temp[1]}")
    #         xx_val = float(temp[0])
    #         yy_val = float(temp[1])
    #         if temp == '' :
    #             break
    #         xx.append(xx_val)
    #         yy.append(yy_val)
    #     count = count + 1
    #     if not line :
    #         break
    
    # matplotlib.pyplot.xlabel(f"{label_xx} (Hz)")
    # matplotlib.pyplot.ylabel(f"{label_yy} (dBm)")
    # matplotlib.pyplot.title(f"{label_xx}  vs  {label_yy}")
    # matplotlib.pyplot.plot(xx, yy)
    # matplotlib.pyplot.gcf().autofmt_xdate()
    # matplotlib.pyplot.show()






    # adc = []
    # axis_time = []
    # field = "ADC"
    # line = None
    # fptr = open(input_file_path_name, "r")
    # count = 0
    # while True :
    #     if count == 0 :
    #         line = fptr.readline().rstrip()
    #         if line != field :
    #             print(f"wrong field, expected '{field}', received '{line}'")
    #             return
    #     else :
    #         line = fptr.readline()
    #         temp = line.split(",")
    #         tempn = temp[0]
    #         if tempn == '' :
    #             break
    #         adc.append(float(tempn))
    #         axis_time.append(count-1)
    #     count = count + 1
    #     if not line :
    #         break
    # fptr.close()    
    # if len(adc) != len(axis_time) :
    #     print(f"bad time series, Time series:  {len(axis_time)},  ADC values:  {len(adc)}")
    #     return

    # matplotlib.pyplot.xlabel("time")
    # matplotlib.pyplot.ylabel("ADC reading")
    # matplotlib.pyplot.title(f"ADC Time Series")
    # matplotlib.pyplot.plot(axis_time[0:1000], adc[0:1000])
    # matplotlib.pyplot.gcf().autofmt_xdate()
    # matplotlib.pyplot.show()






    # label_xx = "frequency"
    # label_yy = "power"
    # fptr = open(input_file_path_name, "r")
    # csv_reader = csv.reader(fptr)
    # csv_header = next(csv_reader)
    # fptr.close()
    # fields = [csv_header[0], csv_header[1]]
    # if csv_header[0] != label_xx :
    #     print(f"field 1, mismatch, expected '{label_xx}', received '{csv_header[0]}")
    #     return
    # if csv_header[1] != label_yy :
    #     print(f"field 2, mismatch, expected '{label_yy}', received '{csv_header[1]}")
    #     return

    # data_frame = pandas.read_csv(input_file_path_name, skiprows=1, header=None, names=fields)
    # rows, cols = data_frame.shape
    # if verbose :
    #     print(data_frame)
    #     print(f"rows  :  {rows}")
    #     print(f"cols  :  {cols}")
    
    # xx = data_frame[label_xx]
    # yy = data_frame[label_yy]
    # matplotlib.pyplot.xlabel(f"{label_xx} (Hz)")
    # matplotlib.pyplot.ylabel(f"{label_yy} (dBm)")
    # matplotlib.pyplot.title(f"{label_xx}  vs  {label_yy}")
    # matplotlib.pyplot.plot(xx, yy)
    # matplotlib.pyplot.gcf().autofmt_xdate()
    # matplotlib.pyplot.show()
