// /*
//     API group "SPECTRUM", initializing

//     public :
//         < 1 >  spectrum_default()
    
//     private :
//         < 1 >  _spectrum_default()
//         < 2 >  _spectrum_init()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > public
// */
// CODEZ rsa306b_class::spectrum_default()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif  

//     if (this->_vars.device.is_connected == false)
//     {
//         #ifdef DEBUG_MIN
//             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
//                 this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
//             debug_record(true);
//         #endif
//         return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
//     }
//     this->_spectrum_default();
// }


// ////~~~~


// /*
//     < 1 > private
// */
// CODEZ rsa306b_class::_spectrum_default()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif  

//     if (this->_vars.device.is_connected == false)
//     {
//         #ifdef DEBUG_MIN
//             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
//                 this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
//             debug_record(true);
//         #endif
//         return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
//     }
//     this->device_stop();
//     this->_api_status = RSA_API::SPECTRUM_SetDefault();
//     this->_report_api_status();
//     this->_spectrum_get_vars();
// }


// ////~~~~


// /*
//     < 2 > private
//     don't need to touch "trace_info_type" or "limits_type"
// */
// CODEZ rsa306b_class::_spectrum_init()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     // the traces have to be assigned, they match the enum and never change
//     this->_vars.spectrum.traces_select[0] = RSA_API::SpectrumTrace1;
//     this->_vars.spectrum.traces_select[1] = RSA_API::SpectrumTrace2;
//     this->_vars.spectrum.traces_select[2] = RSA_API::SpectrumTrace3;

//     // everything else is as usual
//     this->_vars.spectrum.is_enabled_measurement = false;

//     for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
//     {
//         this->_vars.spectrum.is_enabled_trace[ii] = false;
//         this->_vars.spectrum.trace_points_acquired[ii] = INIT_INT;
//         this->_vars.spectrum.peak_index[ii] = INIT_INT;
//         this->_vars.spectrum.detectors_select[ii] = RSA_API::SpectrumDetector_AverageVRMS;
//         for(int jj = 0; jj < SPECTRUM_DATA_LENGTH; jj++)
//         {
//             if (ii == 0) 
//             {
//                 this->_vars.spectrum.array_frequency[jj] = INIT_DOUBLE;
//             }
//             this->_vars.spectrum.array_power[ii][jj] = INIT_FLOAT;
//         }
//     }

//     this->_vars.spectrum.settings_type.span         = INIT_DOUBLE;
//     this->_vars.spectrum.settings_type.rbw          = INIT_DOUBLE;
//     this->_vars.spectrum.settings_type.enableVBW    = false;
//     this->_vars.spectrum.settings_type.traceLength  = INIT_INT;
//     this->_vars.spectrum.settings_type.window       = RSA_API::SpectrumWindow_FlatTop;
//     this->_vars.spectrum.settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_Amp;

//     this->_spectrum_copy_vars();
// }


// ////////~~~~~~~~END>  rsa306b_spectrum_init_default.cpp
