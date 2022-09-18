// /*
//     API group "IFSTREAM", setters

//     revise these later, put in more validation

//     public :
//         #  none
    
//     private :
//         < 1 >  _ifstream_set_vars()
//         < 2 >  _ifstream_set_file_name_suffix()
//         < 3 >  _ifstream_set_file_path()
//         < 4 >  _ifstream_set_file_name_base()
//         < 5 >  _ifstream_set_file_length_ms()
//         < 6 >  _ifstream_set_file_count()
//         < 7 >  _ifstream_set_output_configuration_select()
//         < 8 >  _ifstream_set_is_enabled_adc()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > private
// */
// CODEZ rsa306b_class::_ifstream_set_vars()
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

//     this->_ifstream_set_file_name_suffix();
//     this->_ifstream_set_file_path();
//     this->_ifstream_set_file_name_base();
//     this->_ifstream_set_file_length_ms();
//     this->_ifstream_set_file_count();
//     this->_ifstream_set_output_configuration_select();
//     //this->_ifstream_set_is_enabled_adc(); user should not touch this
// }


// ////~~~~


// /*
//     < 2 > private
// */
// CODEZ rsa306b_class::_ifstream_set_file_name_suffix()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
//     this->_vars.ifstream.file_name_suffix = this->vars.ifstream.file_name_suffix;
//     this->_api_status = 
//         RSA_API::IFSTREAM_SetDiskFilenameSuffix(
//             this->_vars.ifstream.file_name_suffix);
//     this->_report_api_status();
// }


// ////~~~~


// /*
//     < 3 > private
// */
// CODEZ rsa306b_class::_ifstream_set_file_path()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
//     strcpy(this->_vars.ifstream.file_path, this->vars.ifstream.file_path);
//     this->_api_status =
//         RSA_API::IFSTREAM_SetDiskFilePath(
//             this->_vars.ifstream.file_path);
//     this->_report_api_status();
// }


// ////~~~~


// /*
//     < 4 > private
// */
// CODEZ rsa306b_class::_ifstream_set_file_name_base()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
//     strcpy(this->_vars.ifstream.file_name_base, this->vars.ifstream.file_name_base);
//     this->_api_status = 
//         RSA_API::IFSTREAM_SetDiskFilenameBase(
//             this->_vars.ifstream.file_name_base);
//     this->_report_api_status();
// }


// ////~~~~


// /*
//     < 5 > private
// */
// CODEZ rsa306b_class::_ifstream_set_file_length_ms()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
//     this->_vars.ifstream.file_length_ms = this->vars.ifstream.file_length_ms;
//     this->_api_status =
//         RSA_API::IFSTREAM_SetDiskFileLength(
//             this->_vars.ifstream.file_length_ms);
//     this->_report_api_status();
// }


// ////~~~~


// /*
//     < 6 > private
// */
// CODEZ rsa306b_class::_ifstream_set_file_count()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
//     this->_vars.ifstream.file_count = this->vars.ifstream.file_count;
//     this->_api_status = 
//         RSA_API::IFSTREAM_SetDiskFileCount(
//             this->_vars.ifstream.file_count);
//     this->_report_api_status();
// }


// ////~~~~


// /*
//     < 7 > private
// */
// CODEZ rsa306b_class::_ifstream_set_output_configuration_select()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
//     this->_vars.ifstream.output_configuration_select = this->vars.ifstream.output_configuration_select;
//     this->_api_status = 
//         RSA_API::IFSTREAM_SetOutputConfiguration(
//             this->_vars.ifstream.output_configuration_select);
//     this->_report_api_status();
// }


// ////~~~~


// /*
//     < 8 > private
// */
// CODEZ rsa306b_class::_ifstream_set_is_enabled_adc()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
//     this->_vars.ifstream.is_enabled_adc = this->vars.ifstream.is_enabled_adc;
//     this->_api_status =
//         RSA_API::IFSTREAM_SetEnable(
//             this->_vars.ifstream.is_enabled_adc);
//     this->_report_api_status();
//     this->_ifstream_copy_is_enabled_adc();
// }


// ////////~~~~~~~~END>  rsa306b_ifstream_set.cpp
