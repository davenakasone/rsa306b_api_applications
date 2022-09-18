// /*
//     API group "CONFIG", setters

//     public :
//         #  none
    
//     private :
//         < 1 >  _config_set_vars()
//         < 2 >  _config_set_reference_level_dbm()
//         < 3 >  _config_set_center_frequency_hz()
//         < 4 >  _config_set_external_reference_frequency_source_select()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > private
// */
// CODEZ rsa306b_class::_config_set_vars()
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
//     this->device_stop();

//     // vars.config.reference_level_dbm
//     if (this->vars.config.reference_level_dbm == this->_vars.config.reference_level_dbm)
//     {
//         #ifdef DEBUG_MAX
//             printf("\n\tno change in the reference level\n");
//         #endif
//     }
//     else
//     {
//         this->_vars.gp.call_status = this->_config_set_reference_level_dbm();
//         if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
//         {
//             return this->constants.CALL_FAILURE;
//         }
//     }
//     // vars.config.center_frequency_hz
//     if (this->vars.config.center_frequency_hz == this->_vars.config.center_frequency_hz)
//     {
//         #ifdef DEBUG_MAX
//             printf("\n\tno change in the center frequency\n");
//         #endif
//     }
//     else
//     {
//         this->_vars.gp.call_status = this->_config_set_center_frequency_hz();
//         if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
//         {
//             return this->constants.CALL_FAILURE;
//         }
//     }
//     // vars.config.frequency_reference_source_select
//     if (this->vars.config.frequency_reference_source_select == this->_vars.config.frequency_reference_source_select)
//     {
//         #ifdef DEBUG_MAX
//             (void)printf("\n\tno change in the frequency source\n");
//         #endif
//     }
//     else
//     {
//         this->_vars.gp.call_status = this->_config_set_external_reference_frequency_source_select();
//         if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
//         {
//             return this->constants.CALL_FAILURE;
//         }
//         if (this->_vars.config.frequency_reference_source_select == RSA_API::FRS_EXTREF)
//         {
//             this->_config_get_external_reference_frequency_hz();
//             if (this->_vars.gp.api_status != RSA_API::noError)
//             {
//                 #ifdef DEBUG_MIN
//                     printf("\n\tfailure reading external reference frequency\n");
//                 #endif
//                 return this->constants.CALL_FAILURE;
//             }
//         }
//     }

//     return this->constants.CALL_SUCCESS;
// }


// ////~~~~


// /*
//     < 2 > private
// */
// CODEZ rsa306b_class::_config_set_reference_level_dbm()
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
//     if (this->vars.config.reference_level_dbm < this->constants.REFERENCE_LEVEL_MIN_DBM ||
//         this->vars.config.reference_level_dbm > this->constants.REFERENCE_LEVEL_MAX_DBM  )
//     {
//         #ifdef DEBUG_MIN
//             (void)snprintf(X_ddts, sizeof(X_ddts), "reference level { %lf }  ,  out of range [ %lf , %lf ]",
//                 this->vars.config.reference_level_dbm,
//                 this->constants.REFERENCE_LEVEL_MIN_DBM,
//                 this->constants.REFERENCE_LEVEL_MAX_DBM);
//             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
//             debug_record(true);
//         #endif
//         return this->constants.CALL_FAILURE;
//     }
//     this->device_stop();

//     this->_api_status =
//         RSA_API::CONFIG_SetReferenceLevel(this->vars.config.reference_level_dbm);
//     this->_report_api_status();
//     this->_config_get_reference_level_dbm();
//     return this->_gp_confirm_return();
// }


// ////~~~~


// /*
//     < 3 > private
// */
// CODEZ rsa306b_class::_config_set_center_frequency_hz()
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
//     if (this->vars.config.center_frequency_hz < this->_vars.config.min_center_frequency_hz ||
//         this->vars.config.center_frequency_hz > this->_vars.config.max_center_frequency_hz  )
//     {
//         #ifdef DEBUG_MIN
//             (void)snprintf(X_ddts, sizeof(X_ddts), "center frequency { %lf }  ,  out of range [ %lf , %lf ]",
//                 this->vars.config.center_frequency_hz,
//                 this->_vars.config.min_center_frequency_hz,
//                 this->_vars.config.max_center_frequency_hz);
//             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
//             debug_record(true);
//         #endif
//         return this->constants.CALL_FAILURE;
//     }
//     this->device_stop();

//     this->_api_status = 
//         RSA_API::CONFIG_SetCenterFreq(
//             this->vars.config.center_frequency_hz);
//     this->_report_api_status();
//     this->_config_get_center_frequency_hz();
//     return this->_gp_confirm_return();
// }


// ////~~~~


// /*
//     < 4 > private
// */
// CODEZ rsa306b_class::_config_set_external_reference_frequency_source_select()
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
//     if (this->vars.config.frequency_reference_source_select != RSA_API::FRS_EXTREF &&
//         this->vars.config.frequency_reference_source_select != RSA_API::FRS_INTERNAL)
//     {
//         #ifdef DEBUG_MIN
//             (void)snprintf(X_ddts, sizeof(X_ddts), "invalid frequency reference source:  %d",
//                 static_cast<int>(this->vars.config.frequency_reference_source_select));
//             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
//             debug_record(true);
//         #endif
//         return this->constants.CALL_FAILURE;
//     }
//     this->device_stop();

//     this->_api_status =
//         RSA_API::CONFIG_SetFrequencyReferenceSource(
//             this->vars.config.frequency_reference_source_select);
//     this->_report_api_status();
//     this->_config_get_frequency_reference_source_select();
//     return this->_gp_confirm_return();
// }


// ////////~~~~~~~~END>  rsa306b_config_set.cpp
