/*
    exposing the basics of the RSA306B class to python3
*/

#ifndef H_python_access
#define H_python_access

#include "../program_core/control/globalz.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// rsa_config.cpp
void config_set_vars(double cf_hz, double ref_dbm);

// rsa_device.cpp
void device_connect();
void device_run();
void device_stop();
void device_disconnect();
void device_reset();

// rsa_spectrum.cpp
void  spectrum_disable();
void  spectrum_enable();
void  spectrum_set_vars(int trace_length, double span, double rbw);
void  spectrum_acquire();
float spectrum_find_peak();
char* spectrum_write_csv();
char* spectrum_scanner
(
    double fstart, 
    double fstop, 
    double threshold, 
    int    loitering,
    double reflevel,
    double rbw,
    double span,
    int    tlen
);


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON

#endif    // H_python_access


////////~~~~~~~~END>  dummy.h
