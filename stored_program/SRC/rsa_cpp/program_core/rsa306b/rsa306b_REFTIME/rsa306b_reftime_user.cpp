// /*
//     API group "REFTIME", user functions

//     public :
//         < 1 >  reftime_reset()
//         < 2 >  reftime_get_vars()
//         < 3 >  reftime_timestamp_2_time()
//         < 4 >  reftime_time_2_timestamp()
    
//     private :
//         < 1 >  _reftime_make_dts()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > public
// */
// CODEZ rsa306b_class::reftime_reset()
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

//     this->_api_status = 
//         RSA_API::REFTIME_SetReferenceTime(0, 0, 0);
//     this->_reftime_get_start();
// }


// ////~~~~


// /*
//     < 2 > public
// */
// CODEZ rsa306b_class::reftime_get_vars()
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
//     this->_reftime_get_vars();
// }


// ////~~~~


// /*
//     < 3 > public
// */
// CODEZ rsa306b_class::reftime_timestamp_2_time()
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
//     this->_vars.reftime.helper.timestamp = this->vars.reftime.helper.timestamp;
//     this->_api_status =
//         RSA_API::REFTIME_GetTimeFromTimestamp(
//             this->_vars.reftime.helper.timestamp,
//             &this->_vars.reftime.helper.seconds,
//             &this->_vars.reftime.helper.nanos);
//     this->_report_api_status();
//     this->_reftime_copy_helper();
// }


// ////~~~~


// /*
//     < 4 > public
// */
// CODEZ rsa306b_class::reftime_time_2_timestamp()
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
//     this->_vars.reftime.helper.seconds = this->vars.reftime.helper.seconds;
//     this->_vars.reftime.helper.nanos = this->vars.reftime.helper.nanos;
//     this->_api_status =
//         RSA_API::REFTIME_GetTimestampFromTime(
//             this->_vars.reftime.helper.seconds,
//             this->_vars.reftime.helper.nanos,
//             &this->_vars.reftime.helper.timestamp);
//     this->_report_api_status();
//     this->_reftime_copy_helper();
// }


// ////~~~~


// /*
//     < 1 > public
// */
// CODEZ rsa306b_class::_reftime_make_dts()
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
//     this->_reftime_get_current();
//     (void)memset(this->_vars.reftime.dts, '\0', BUF_C);
//     struct tm * tm_ptr = NULL;
//     tm_ptr = gmtime(&this->_vars.reftime.current.seconds);
//     if (tm_ptr == NULL)
//     {    
//         #ifdef DEBUG_MIN
//             (void)snprintf(X_ddts, sizeof(X_ddts), "<time.h> failed");
//             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
//             debug_record(true);
//         #endif
//         return;
//     }
    
//     (void)strftime(this->_vars.reftime.dts, BUF_C,
//         "dts_%Y_%m_%d_%a_%H_%M_%S_%Z_nano_", tm_ptr);
//     (void)snprintf(this->_vars.gp.helper, BUF_E-1, "%ld", 
//         this->_vars.reftime.current.nanos);
//     (void)strcat(this->_vars.reftime.dts, this->_vars.gp.helper);
//     this->_reftime_copy_dts();
// }


// ////////~~~~~~~~END>  rsa306b_reftime_user.cpp