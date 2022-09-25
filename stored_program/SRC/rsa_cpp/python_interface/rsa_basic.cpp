/*
    source code for the python interface
*/

#include "rsa_basic.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


void config_set_vars(double cf_hz, double ref_dbm)
{
    X_rsa.vars.config.center_frequency_hz = cf_hz;
    X_rsa.vars.config.reference_level_dbm = ref_dbm;
    X_rsa.config_set_vars();
}


void device_connect()
{
    X_rsa.device_connect();
}


void device_run()
{
    X_rsa.device_run();
}


void device_stop()
{
    X_rsa.device_stop();
}


void device_disconnect()
{
    X_rsa.device_disconnect();
}


void spectrum_disable()
{
    X_rsa.vars.spectrum.is_enabled_measurement = false;
    X_rsa.spectrum_set_vars();
}


void spectrum_enable()
{
    X_rsa.vars.spectrum.is_enabled_measurement = true;
    X_rsa.spectrum_set_vars();
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
    X_rsa.spectrum_set_vars();
}


void spectrum_acquire()
{
    X_rsa.spectrum_acquire_data(RSA_API::SpectrumTrace1);    // python users only get trace[0]
}


float spectrum_find_peak()
{
    X_rsa.spectrum_find_peak_index(RSA_API::SpectrumTrace1);  // python users only get trace[0]
    std::size_t peak_index = X_rsa.vars.spectrum.peak_index[RSA_API::SpectrumTrace1];
    return X_rsa.vars.spectrum.trace_power_v[RSA_API::SpectrumTrace1][peak_index];
}


char* spectrum_write_csv()
{
    X_rsa.cutil.helper[0] = '\0';
    X_rsa.spectrum_make_frequency_v();
    X_rsa.spectrum_write_csv(X_rsa.cutil.helper, RSA_API::SpectrumTrace1);  // python users only get trace[0]
    return X_rsa.cutil.helper;
}



#ifdef __cplusplus      
}
#endif

#endif


////////~~~~~~~~END>  rsa_basic.cpp
