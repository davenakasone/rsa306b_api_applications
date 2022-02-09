#Running on fresh install of Ubuntu 16.04 or CentOS 7.3

#Copy Cyrpess USB config file to /etc
sudo cp cyusb.conf /etc/

#Create group plugdev if it doesn't already exist
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../

#Add user to plugdev group
sudo usermod -a -G plugdev <username>

#Create file and add the following line to /etc/udev/rules.d/Tektronix.rules
SUBSYSTEM=="usb", ATTR{idVendor}=="0699", MODE="0666", GROUP="plugdev", ATTR{power/autosuspend}="-1", ATTR{power/control}="on", ATTR{bMaxPower}="500mA"

#Change permissions on rules file:
sudo chmod a+r /etc/udev/rules.d/Tektronix.rules

#reboot

#Test connection to RSA with pyLoad.py
#Make sure python is installed and *.so files are present in correct location
cd example_python
python pyLoad.py

#OR with cLoad
cd example_c
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../
./cLoad

#You should see the API version and device serial number and nomenclature
