// /*
//     API group "IQBLK"

//     public :
//         #  none
    
//     private :
//         < 1 >  _iqblk_get_vars()
//         < 2 >  _iqblk_get_acq_info_type()
//         < 3 >  _iqblk_get_sample_rate()
//         < 4 >  _iqblk_get_bandwidth_hz()
//         < 5 >  _iqblk_get_max_bandwidth_hz()
//         < 6 >  _iqblk_get_min_bandwidth_hz()
//         < 7 >  _iqblk_get_max_record_length()
//         < 8 >  _iqblk_get_record_length()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > private
// */
// CODEZ rsa306b_class::_iqblk_get_vars()
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

//     this->_iqblk_get_acq_info_type();
//     this->_iqblk_get_sample_rate();
//     this->_iqblk_get_bandwidth_hz();
//     this->_iqblk_get_max_bandwidth_hz();
//     this->_iqblk_get_min_bandwidth_hz();
//     this->_iqblk_get_max_record_length();
// }


// ////~~~~


// /*
//     < 2 > private
// */
// CODEZ rsa306b_class::_iqblk_get_acq_info_type()
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
//     this->_api_status =
//         RSA_API::IQBLK_GetIQAcqInfo(
//             &this->_vars.iqblk.acq_info_type);
//     this->_report_api_status();
//     this->_iqblk_bitcheck();
//     this->_iqblk_copy_acq_info_type();
// }


// ////~~~~


// /*
//     < 3 > private
// */
// CODEZ rsa306b_class::_iqblk_get_sample_rate()
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
//     this->_api_status =
//         RSA_API::IQBLK_GetIQSampleRate(
//             &this->_vars.iqblk.sample_rate);
//     this->_report_api_status();
//     this->_iqblk_copy_sample_rate();
// }


// ////~~~~


// /*
//     < 4 > private
// */
// CODEZ rsa306b_class::_iqblk_get_bandwidth_hz()
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
//     this->_api_status =
//         RSA_API::IQBLK_GetIQBandwidth(
//             &this->_vars.iqblk.bandwidth_hz);
//     this->_report_api_status();
//     this->_iqblk_copy_bandwidth_hz();
// }


// ////~~~~


// /*
//     < 5 > private
// */
// CODEZ rsa306b_class::_iqblk_get_max_bandwidth_hz()
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
//     this->_api_status =
//         RSA_API::IQBLK_GetMaxIQBandwidth(
//             &this->_vars.iqblk.max_bandwidth_hz);
//     this->_report_api_status();
//     this->_iqblk_copy_max_bandwidth_hz();
// }


// ////~~~~


// /*
//     < 6 > private
// */
// CODEZ rsa306b_class::_iqblk_get_min_bandwidth_hz()
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
//     this->_api_status =
//         RSA_API::IQBLK_GetMinIQBandwidth(
//             &this->_vars.iqblk.min_bandwidth_hz);
//     this->_report_api_status();
//     this->_iqblk_copy_min_bandwidth_hz();
// }


// ////~~~~


// /*
//     < 7 > private
// */
// CODEZ rsa306b_class::_iqblk_get_max_record_length()
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
//     this->_api_status =
//         RSA_API::IQBLK_GetMaxIQRecordLength(
//             &this->_vars.iqblk.max_record_length);
//     this->_report_api_status();
//     this->_iqblk_copy_max_record_length();
// }


// ////~~~~


// /*
//     < 8 > private
// */
// CODEZ rsa306b_class::_iqblk_get_record_length()
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
//     this->_api_status =
//         RSA_API::IQBLK_GetIQRecordLength(
//             &this->_vars.iqblk.record_length);
//     this->_report_api_status();
//     this->_iqblk_copy_record_length();
// }


// ////////~~~~~~~~END>  rsa306b_iqblk_get.cpp
