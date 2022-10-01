/*
    source code for the python interface
    API group 'DEVICE'

        < 1 >  device_connect()
        < 2 >  device_disconnect()
        < 3 >  device_prepare_for_run()
        < 4 >  void device_reset()
        < 5 >  void device_run()
        < 6 >  void device_start_transfer()
        < 7 >  void device_stop()

    put the temperature check in if the user will be in a hot environment
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
void device_connect()  
{
    (void)X_rsa.device_connect();
}

// < 2 >
void device_disconnect()
{
    (void)X_rsa.device_disconnect();
}

// < 3 >
void device_prepare_for_run()
{
    (void)X_rsa.device_prepare_for_run();
}

// < 4 >
void device_reset()
{
    (void)X_rsa.device_reset();
}

// < 5 >
void device_run()
{
    (void)X_rsa.device_run();
}

// < 6 >
void device_start_transfer()
{
    (void)X_rsa.device_start_frame_transfer();
}

// < 7 >
void device_stop()
{
    (void)X_rsa.device_stop();
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_device.cpp
