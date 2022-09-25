/*
    looking around
*/

#include "../testz.h"

#ifdef UNIT_TESTINGG


void task_991()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  try the new integration\n", __func__);
X_util.timer_split_start();                    
#endif    
////~~~~

    
    X_rsa.device_connect();

    (void)sprintf(X_rsa.cutil.helper, "%s%s%s", 
        DATA_DIRECTORY_PROCESSED, 
        SPECTRUM_FILE_NAME_BASE, 
        DATA_OUTPUT_EXTENSTION);
    
    X_rsa.vars.config.center_frequency_hz = 315.0e6;
    X_rsa.vars.config.reference_level_dbm = -9.99;
    X_rsa.config_set_vars();

    X_rsa.vars.spectrum.is_enabled_measurement = true;
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace1] = true;
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace2] = false;
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace3] = false;
    X_rsa.vars.spectrum.detector_select[RSA_API::SpectrumTrace1] = RSA_API::SpectrumDetector_PosPeak;
    X_rsa.vars.spectrum.settings_type.enableVBW = false;
    X_rsa.vars.spectrum.settings_type.rbw = 10.0e3;
    X_rsa.vars.spectrum.settings_type.span = 10.0e6;
    X_rsa.vars.spectrum.settings_type.traceLength = 3333;
    X_rsa.vars.spectrum.settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_dBm;
    X_rsa.vars.spectrum.settings_type.window = RSA_API::SpectrumWindow_Kaiser;
    X_rsa.spectrum_set_vars();

    X_rsa.device_run();

    X_rsa.device_stop();
    

////~~~~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif

/////////~~~~~~~~END>  task_991.cpp
