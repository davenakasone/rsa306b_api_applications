/*
    API group "CONFIG", getters

    public :
        #  none
    
    private :
        < 1 >  _config_get_vars()
        < 2 >  _config_get_reference_level_dbm()
        < 3 >  _config_get_center_frequency_hz()
        < 4 >  _config_get_min_center_frequency_hz()
        < 5 >  _config_get_max_center_frequency_hz()
        < 6 >  _config_get_external_reference_frequency_hz()
        < 7 >  _config_get_frequency_reference_source_select()
*/

#include "../rsa306b_class.h"



/*
    < 1 > private
*/
void rsa306b_class::_config_get_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_config_get_reference_level_dbm();
    this->_config_get_center_frequency_hz();
    this->_config_get_min_center_frequency_hz();
    this->_config_get_max_center_frequency_hz();
    this->_config_get_external_reference_frequency_hz();
    this->_config_get_frequency_reference_source_select();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_config_get_reference_level_dbm()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::CONFIG_GetReferenceLevel(
            &this->_vars.config.reference_level_dbm);
    this->_gp_confirm_api_status();
    this->_config_copy_reference_level_dbm();
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_config_get_center_frequency_hz()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::CONFIG_GetCenterFreq(
            &this->_vars.config.center_frequency_hz);
    this->_gp_confirm_api_status();
    this->_config_copy_center_frequency_hz();
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_config_get_min_center_frequency_hz()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::CONFIG_GetMinCenterFreq(
            &this->_vars.config.min_center_frequency_hz);
    this->_gp_confirm_api_status();
    this->_config_copy_min_center_frequency_hz();
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_config_get_max_center_frequency_hz()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::CONFIG_GetMaxCenterFreq(
            &this->_vars.config.max_center_frequency_hz);
    this->_gp_confirm_api_status();
    this->_config_copy_max_center_frequency_hz();
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_config_get_external_reference_frequency_hz()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::CONFIG_GetExternalRefFrequency(
            &this->_vars.config.external_reference_frequency_hz);
    this->_gp_confirm_api_status();
    this->_config_copy_external_reference_frequency_hz();
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_config_get_frequency_reference_source_select()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::CONFIG_GetFrequencyReferenceSource(
            &this->_vars.config.frequency_reference_source_select);
    this->_gp_confirm_api_status();
    this->_config_copy_frequency_reference_source_select();
}


////////~~~~~~~~END>  rsa306b_config_get.cpp
