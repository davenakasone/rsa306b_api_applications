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


// rsa_config.cpp
int config_set_vars(double cf_hz, double ref_dbm);

// rsa_device.cpp
void device_connect();
void device_disconnect();
void device_prepare_for_run();
void device_reset();
void device_run();
void device_start_transfer();
void device_stop();

// rsa_gp.cpp
int   api_status();
char* api_status_message();

// rsa_ifstream.cpp
int   ifstream_set_vars(int record_ms, bool stream_file);
int   ifstream_acq_direct();
char* ifstream_write_csv();
char* ifstream_record_r3f();
char* ifstream_equalization();

// rsa_iqblk.cpp
int   iqblk_set_vars(double bw_hz);
int   iqblk_acquire();
char* iqblk_write_csv();

// rsa_iqstream.cpp
int   iqstream_set_vars(int record_ms, double bw_hz, bool stream_file);
int   iqstream_acq_direct();
char* iqstream_write_csv();
char* iqstream_record_siq();

// rsa_spectrum.cpp
void  spectrum_disable();
void  spectrum_enable();
int   spectrum_acquire();
float spectrum_find_peak();
char* spectrum_write_csv();
int   spectrum_set_vars
(
    int    trace_length, 
    double span, 
    double rbw
);

// raw_r3f.cpp
char* get_r3f_csv_equalization();
char* get_r3f_csv_adc();

// raw_siq.cpp
char* get_siq_csv();

// special
char* scan_dump                    
(
    const int    smode,
    const double fstart, 
    const double fstop, 
    const double reflevel,
    const double threshold
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
char* spectrum_scanner_b1
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
char* spectrum_scanner_b2
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
char* trigger_dump
(
    const int    loitering,
    const double fstart, 
    const double fstop, 
    const double reflevel,
    const double triglevel,
    const double rbw,
    const double span,
    const int    tlen,
    int          record_ms
);

// c_utility.cpp
void delete_data();
char* file_select(char* directory);


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON

#endif    // H_python_access


////////~~~~~~~~END>  python_interface.h
