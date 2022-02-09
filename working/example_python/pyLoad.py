from time import sleep
from ctypes import *

#instantiate the RSA driver
RTLD_LAZY = 0x0001
LAZYLOAD = RTLD_LAZY | RTLD_GLOBAL
rsa = CDLL("../libRSA_API.so",LAZYLOAD)
usbapi = CDLL("../libcyusb_shared.so",LAZYLOAD)

def GetErrorString(error):
	rsa.DEVICE_GetErrorString.restype = c_char_p
	errorString = rsa.DEVICE_GetErrorString(error)
	return errorString

error = 0

DEVSRCH_MAX_NUM_DEVICES = 20
DEVSRCH_SERIAL_MAX_STRLEN = 100
DEVSRCH_TYPE_MAX_STRLEN = 20
DEVINFO_MAX_STRLEN = 100


version = (c_char * DEVINFO_MAX_STRLEN)()
error = rsa.DEVICE_GetAPIVersion(version)
if error != 0:
	sys.exit(GetErrorString(error))
print (f"API Version #:  {version.value}")

print ('')
print ('Searching for devices...')
numDevices = c_int()
deviceIDs = (c_int * DEVSRCH_MAX_NUM_DEVICES)() 
deviceSNs = ((c_char * DEVSRCH_MAX_NUM_DEVICES) * DEVSRCH_SERIAL_MAX_STRLEN)()
deviceTypes = ((c_char * DEVSRCH_MAX_NUM_DEVICES) * DEVSRCH_TYPE_MAX_STRLEN)()
error = rsa.DEVICE_Search(byref(numDevices), deviceIDs, deviceSNs, deviceTypes)
if error != 0:
	sys.exit(GetErrorString(error))
foundDevices = {id: (deviceSNs[id].value, deviceTypes[id].value) for id in deviceIDs}

print (f"Found  {numDevices.value}  devices[s]")
print (f"{foundDevices}")

if numDevices == 0:
	sys.exit('No devices found')

print (' ')
rsa.DEVICE_Connect(foundDevices.keys()[0])

sn = (c_char * DEVINFO_MAX_STRLEN)()
rsa.DEVICE_GetSerialNumber(sn)
print (f"Serial #: ' {sn.value}")

rsa.DEVICE_Disconnect()

