/*
    variables needed for the API group "SPECTRUM" 
    SPECTRUM_AquireTrace()
    SPECTRUM_GetEnable()
    SPECTRUM_GetLimits()
    SPECTRUM_GetSettings()
    SPECTRUM_GetTrace()
    SPECTRUM_GetTraceInfo()
    SPECTRUM_GetTraceType()
    SPECTRUM_SetDefault()
    SPECTRUM_SetEnable()
    SPECTRUM_SetSettings()
    SPECTRUM_SetTraceType()
    SPECTRUM_WaitForTraceReady()

    active :

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"
*/

#ifndef H_rsa306b_spectrum_struct
#define H_rsa306b_spectrum_struct


#include "../../control/resourcez.h"


struct rsa306b_spectrum_struct
{


// limiting constants


    bool is_enabled_measurement;                     // indicates if the device is enabled for measurement
    RSA_API::Spectrum_Settings settings_type;        // has 2 enums...above
    RSA_API::Spectrum_Limits limits_type;            // all vars
    double array_frequency[SPECTRUM_DATA_LENGTH];    // corresponding frequency to match "data_trace"

    bool is_enabled_trace[TRACES_AVAILABLE];                          // indicates which of the 3 traces is available
    RSA_API::SpectrumTraces traces_select[TRACES_AVAILABLE];          // match by index
    RSA_API::SpectrumDetectors detectors_select[TRACES_AVAILABLE];    // detection method of the trace
    RSA_API::Spectrum_TraceInfo trace_info_type[TRACES_AVAILABLE];    // bit check + time stamp, depending on trace aquired
    int peak_index[TRACES_AVAILABLE];                                 // peak index for trace, INIT_INT if not processed
    int trace_points_acquired[TRACES_AVAILABLE];                      // updated after API call, data for each trace
    float array_power[TRACES_AVAILABLE][SPECTRUM_DATA_LENGTH];        // the vertical units measured, for each of the 3 traces

    // put the float** and double* as a std::vector<std::vector<float>>, std::vector<double>
    // apply the .size() and .resize(), only using the float** and double* to acquire in scope
};
typedef struct rsa306b_spectrum_struct rsa306b_spectrum_struct;


#endif


////////~~~~~~~~END>  rsa306b_spectrum_struct.h
