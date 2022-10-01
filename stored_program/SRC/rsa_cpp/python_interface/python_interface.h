/*
    exposing the basics of the RSA306B class to python3
*/

#ifndef H_python_interface
#define H_python_interface

#include "../program_core/control/globalz.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// rsa_gp.cpp
int api_status();
char* api_status_message();

// rsa_iqblk.cpp
void  iqblk_set_vars(double bw_hz);
int   iqblk_acquire();
char* iqblk_make_csv();

// rsa_config.cpp
void config_set_vars(double cf_hz, double ref_dbm);

// rsa_device.cpp
void device_connect();
void device_disconnect();
void device_prepare_for_run();
void device_reset();
void device_run();
void device_start_transfer();
void device_stop();

// rsa_spectrum.cpp
void  spectrum_disable();
void  spectrum_enable();
int   spectrum_acquire();
float spectrum_find_peak();
char* spectrum_write_csv();
void  spectrum_set_vars
(
    int    trace_length, 
    double span, 
    double rbw
);
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


////////~~~~~~~~END>  python_interface.h
