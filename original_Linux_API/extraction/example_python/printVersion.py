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
print 'API Version #: ' + str(version.value)

