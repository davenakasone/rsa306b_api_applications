/*
    variables needed for the API group "SPECTRUM" 
*/

#ifndef H_rsa306b_spectrum_struct
#define H_rsa306b_spectrum_struct


#include "../../control/resourcez.h"


struct rsa306b_spectrum_struct
{
    bool is_enabled_measurement;                   // indicates if the device is enabled for measurement
    RSA_API::Spectrum_Settings settings_type;      // has 2 enums...above
    RSA_API::Spectrum_Limits limits_type;          // all vars
    int trace_points_acquired;                     // updated after API call
    double array_frequency[SPECTRUM_DATA_LENGTH];    // corresponding frequency to match "data_trace"
    
    bool is_enabled_trace[TRACES_AVAILABLE];                          // indicates which of the 3 traces is available
    RSA_API::SpectrumTraces traces_select[TRACES_AVAILABLE];          // match by index
    RSA_API::SpectrumDetectors detectors_select[TRACES_AVAILABLE];    // detection method of the trace
    RSA_API::Spectrum_TraceInfo trace_info_type[TRACES_AVAILABLE];    // bit check + time stamp, depending on trace aquired
    float array_power[TRACES_AVAILABLE][SPECTRUM_DATA_LENGTH];        // the vertical units measured, for each of the 3 traces
    int peak_index[TRACES_AVAILABLE];                                 // peak index for trace, INIT_INT if not processed
};
typedef struct rsa306b_spectrum_struct rsa306b_spectrum_struct;


#endif


////////~~~~~~~~END>  rsa306b_spectrum_struct.h
