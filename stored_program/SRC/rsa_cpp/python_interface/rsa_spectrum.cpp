/*
    source code for the python interface
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


void spectrum_disable()
{
    X_rsa.vars.spectrum.is_enabled_measurement = false;
    (void)X_rsa.spectrum_set_vars();
}


void spectrum_enable()
{
    X_rsa.vars.spectrum.is_enabled_measurement = true;
    (void)X_rsa.spectrum_set_vars();
}


void spectrum_set_vars(int trace_length, double span, double rbw)
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
    (void)X_rsa.spectrum_set_vars();
}


void spectrum_acquire()
{
    (void)X_rsa.spectrum_acquire_data(RSA_API::SpectrumTrace1);    // python users only get trace[0]
}


float spectrum_find_peak()
{
    (void)X_rsa.spectrum_find_peak_index(RSA_API::SpectrumTrace1);  // python users only get trace[0]
    std::size_t peak_index = X_rsa.vars.spectrum.peak_index[RSA_API::SpectrumTrace1];
    return X_rsa.vars.spectrum.trace_power_v[RSA_API::SpectrumTrace1][peak_index];
}


char* spectrum_write_csv()
{
    X_rsa.cutil.helper[0] = '\0';
    (void)X_rsa.spectrum_make_frequency_v();
    (void)X_rsa.spectrum_write_csv(X_rsa.cutil.helper, RSA_API::SpectrumTrace1);  // python users only get trace[0]
    return X_rsa.cutil.helper;
}

char* spectrum_scanner
(
    double fstart, 
    double fstop, 
    double threshold, 
    int loitering,
    double reflevel,
    double rbw,
    double span,
    int tlen
)
{
    X_rsa.cutil.helper[0] = '\0';
    (void)X_rsa.spectrum_scanner
        (
            RSA_API::SpectrumTrace1, // python users only get trace[0]
            fstart, 
            fstop, 
            threshold, 
            loitering, 
            X_rsa.cutil.helper, 
            reflevel, 
            rbw, 
            span, 
            tlen
        );
    return X_rsa.cutil.helper;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_spectrum.cpp
