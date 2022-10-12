/*
    source code for the python interface
    API group 'SPECTRUM'

        < 1 >  spectrum_disable()
        < 2 >  spectrum_enable()
        < 3 >  spectrum_acquire()
        < 4 >  spectrum_find_peak()
        < 5 >  spectrum_write_csv()
        < 6 >  spectrum_set_vars()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
void spectrum_disable()
{
    X_rsa.vars.spectrum.is_enabled_measurement = false;
    (void)X_rsa.spectrum_set_vars();
}

// < 2 >
void spectrum_enable()
{
    X_rsa.vars.spectrum.is_enabled_measurement = true;
    (void)X_rsa.spectrum_set_vars();
}

// < 3 >
int spectrum_acquire()
{
    return static_cast<int>(X_rsa.spectrum_acquire_data(RSA_API::SpectrumTrace1));    // python users only get trace[0]
}

// < 4 >
float spectrum_find_peak()
{
    (void)X_rsa.spectrum_find_peak_index(RSA_API::SpectrumTrace1);  // python users only get trace[0]
    std::size_t peak_index = X_rsa.vars.spectrum.peak_index[RSA_API::SpectrumTrace1];
    return X_rsa.vars.spectrum.trace_power_v[RSA_API::SpectrumTrace1][peak_index];
}

// < 5 >
char* spectrum_write_csv()
{
    X_rsa.cutil.helper[0] = '\0';
    (void)X_rsa.spectrum_make_frequency_v();
    (void)X_rsa.spectrum_write_csv(X_rsa.cutil.helper, RSA_API::SpectrumTrace1);  // python users only get trace[0]
    return X_rsa.cutil.helper;
}

// < 6 >
int spectrum_set_vars(int trace_length, double span, double rbw)
{
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace1] = true;   // python users only get trace[0]
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace2] = false;
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace3] = false;
    X_rsa.vars.spectrum.detector_select[RSA_API::SpectrumTrace1] = RSA_API::SpectrumDetector_PosPeak;
    X_rsa.vars.spectrum.settings_type.enableVBW = false;
    X_rsa.vars.spectrum.settings_type.rbw = rbw;
    X_rsa.vars.spectrum.settings_type.span = span;
    X_rsa.vars.spectrum.settings_type.traceLength = trace_length;
    X_rsa.vars.spectrum.settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_dBm;
    X_rsa.vars.spectrum.settings_type.window = RSA_API::SpectrumWindow_Kaiser;
    return static_cast<int>(X_rsa.spectrum_set_vars());
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_spectrum.cpp
