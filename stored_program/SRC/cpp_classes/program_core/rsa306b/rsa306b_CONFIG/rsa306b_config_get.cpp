// /*
//     API group "CONFIG", getters

//     public :
//         #  none
    
//     private :
//         < 1 >  _config_get_vars()
//         < 2 >  _config_get_reference_level_dbm()
//         < 3 >  _config_get_center_frequency_hz()
//         < 4 >  _config_get_min_center_frequency_hz()
//         < 5 >  _config_get_max_center_frequency_hz()
//         < 6 >  _config_get_external_reference_frequency_hz()
//         < 7 >  _config_get_frequency_reference_source_select()
// */

// #include "../rsa306b_class.h"



// /*
//     < 1 > private
// */
// CODEZ rsa306b_class::_config_get_vars()
// {
// #ifdef DEBUG_GETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

//     this->_config_get_reference_level_dbm();
//     this->_config_get_center_frequency_hz();
//     this->_config_get_min_center_frequency_hz();
//     this->_config_get_max_center_frequency_hz();
//     this->_config_get_external_reference_frequency_hz();
//     this->_config_get_frequency_reference_source_select();
// }


// ////~~~~


// /*
//     < 2 > private
// */
// CODEZ rsa306b_class::_config_get_reference_level_dbm()
// {
// #ifdef DEBUG_GETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

//     this->_api_status = 
//         RSA_API::CONFIG_GetReferenceLevel(
//             &this->_vars.config.reference_level_dbm);
//     this->_report_api_status();
//     this->_config_copy_reference_level_dbm();
// }


// ////~~~~


// /*
//     < 3 > private
// */
// CODEZ rsa306b_class::_config_get_center_frequency_hz()
// {
// #ifdef DEBUG_GETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

//     this->_api_status = 
//         RSA_API::CONFIG_GetCenterFreq(
//             &this->_vars.config.center_frequency_hz);
//     this->_report_api_status();
//     this->_config_copy_center_frequency_hz();
// }


// ////~~~~


// /*
//     < 4 > private
// */
// CODEZ rsa306b_class::_config_get_min_center_frequency_hz()
// {
// #ifdef DEBUG_GETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

//     this->_api_status = 
//         RSA_API::CONFIG_GetMinCenterFreq(
//             &this->_vars.config.min_center_frequency_hz);
//     this->_report_api_status();
//     this->_config_copy_min_center_frequency_hz();
// }


// ////~~~~


// /*
//     < 5 > private
// */
// CODEZ rsa306b_class::_config_get_max_center_frequency_hz()
// {
// #ifdef DEBUG_GETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

//     this->_api_status = 
//         RSA_API::CONFIG_GetMaxCenterFreq(
//             &this->_vars.config.max_center_frequency_hz);
//     this->_report_api_status();
//     this->_config_copy_max_center_frequency_hz();
// }


// ////~~~~


// /*
//     < 6 > private
// */
// CODEZ rsa306b_class::_config_get_external_reference_frequency_hz()
// {
// #ifdef DEBUG_GETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

//     this->_api_status = 
//         RSA_API::CONFIG_GetExternalRefFrequency(
//             &this->_vars.config.external_reference_frequency_hz);
//     this->_report_api_status();
//     this->_config_copy_external_reference_frequency_hz();
// }


// ////~~~~


// /*
//     < 7 > private
// */
// CODEZ rsa306b_class::_config_get_frequency_reference_source_select()
// {
// #ifdef DEBUG_GETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

//     this->_api_status = 
//         RSA_API::CONFIG_GetFrequencyReferenceSource(
//             &this->_vars.config.frequency_reference_source_select);
//     this->_report_api_status();
//     this->_config_copy_frequency_reference_source_select();
// }


// ////////~~~~~~~~END>  rsa306b_config_get.cpp
