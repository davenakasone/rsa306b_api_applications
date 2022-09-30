/*
    source code for the python interface
    API group 'DEVICE'
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


void device_connect()
{
    (void)X_rsa.device_connect();
}


void device_run()
{
    (void)X_rsa.device_run();
}


void device_stop()
{
    (void)X_rsa.device_stop();
}


void device_disconnect()
{
    (void)X_rsa.device_disconnect();
}

void device_reset()
{
    (void)X_rsa.device_reset();
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_device.cpp
