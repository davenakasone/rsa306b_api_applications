/*
    API group "DEVICE", getters that use the API

    public :
        #  none
    
    private :
        < 1 >  _device_get_vars()
        < 2 >  _device_get_is_running()
        < 3 >  _device_get_error_string()
        < 4 >  _device_get_info_type()
        < 5 >  _device_get_is_over_temperature()
        < 6 >  _device_get_event()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    uses the API to get all 'DEVICE' variables
    updates the public struct
*/
CODEZ rsa306b_class::_device_get_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }

    this->_device_get_error_string();
    this->_device_get_event();
    this->_device_get_info_type();
    this->_device_get_is_over_temperature();
    this->_device_get_is_running();
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_device_get_is_running()
{
#ifdef DEBUG_GETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::DEVICE_GetEnable(&this->_vars.device.is_running);
    this->_gp_confirm_api_status();
    this->_device_copy_is_running();
}


////~~~~


/*
    private < 3 >
    updates "_vars.device.error_string" with API message as a string
    the API looks up the message based on the return status
    this is the only function the API that does not use return status
*/
CODEZ rsa306b_class::_device_get_error_string()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    
    (void)snprintf(this->_vars.device.api_status_string, BUF_E-1, 
        "error code:  %4d  ,  error message:  %s", 
        this->_vars.gp.api_status, 
        RSA_API::DEVICE_GetErrorString(this->_vars.gp.api_status));
    this->_device_copy_error_string();
}


////~~~~


/*
    < 4 > private
    the struct of strings is updated by the API
    values are copied into the public variable struct
*/
CODEZ rsa306b_class::_device_get_info_type()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::DEVICE_GetInfo(&this->_vars.device.info_type);
    this->_gp_confirm_api_status();
    this->_device_copy_info_type();
}


////~~~~


/*
    < 5 > private
    API is called to get the temperature status
    the public variable is updated
        true indicates that the device is too hot
        action should be taken to protect the device
*/
CODEZ rsa306b_class::_device_get_is_over_temperature()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::DEVICE_GetOverTemperatureStatus(&this->_vars.device.is_over_temperature);
    this->_gp_confirm_api_status();
    this->_device_copy_is_over_temperature();

    if (this->_vars.device.is_over_temperature == true)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "RSA-306B is too hot, shut it down now");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }
}


////~~~~


/*
    < 6 > private
    OVERRANGE: input signal to ADC exceeded allowable range
    TRIGGER: most recent sample, can force with API
    1PPS: only for RSA500+
    this query clears event history
    all events clear when going stop->run
    nothing is relevant unless the bool is true
    only valid if device is running
*/
CODEZ rsa306b_class::_device_get_event()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->_vars.device.is_running == false)
    {
        #ifdef DEBUG_MAX
            (void)printf("\n\tdevice is not running\n");
        #endif
        return;
    }

    this->_vars.gp.api_status = 
        RSA_API::DEVICE_GetEventStatus(
            this->_vars.device.event_id,
            &this->_vars.device.event_occured,
            &this->_vars.device.event_timestamp);
    this->_gp_confirm_api_status();
    this->_device_copy_event_occured();
    this->_device_copy_event_timestamp();
}


////////~~~~~~~~END>  rsa306b_device_get.cpp
