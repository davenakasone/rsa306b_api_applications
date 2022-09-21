/*
    API group "DEVICE", getters that use the API

    public :
        #  none
    
    private :
        < 1 >  _device_get_vars()
        < 2 >  _device_get_is_running()
        < 3 >  _device_get_api_status_message()
        < 4 >  _device_get_info_type()
        < 5 >  _device_get_is_over_temperature()
        < 6 >  device_get_event()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    uses the API to get all 'DEVICE' variables
    updates the public struct
*/
CODEZ rsa306b_class::_device_get_vars()
{
#ifdef DEBUG_GETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int calls = 5;
    CODEZ caught_call[calls];

    caught_call[0] = this->_device_get_is_running         ();
    caught_call[1] = this->_device_get_api_status_message ();
    caught_call[2] = this->_device_get_info_type          ();
    caught_call[3] = this->_device_get_is_over_temperature();
    caught_call[4] = this->_device_get_event              ();

    return this->cutil.codez_checker(caught_call, calls);
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

    this->_api_status = 
        RSA_API::DEVICE_GetEnable(&this->_vars.device.is_running);
    (void)this->_device_copy_is_running();
    return this->_report_api_status();
}


////~~~~


/*
    private < 3 >
    uses "_api_status" value to update "_vars.device.api_status_message"
    the API looks up the message based on the current value
    this is one of the few API functions that does not return "RSA_API::ReturnStatus"
*/
CODEZ rsa306b_class::_device_get_api_status_message()
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
    
    (void)snprintf(this->_vars.device.api_status_message, 
        sizeof(this->_vars.device.api_status_message), 
        "error code:  %4d  ,  error message:  %s", 
        static_cast<int>(this->_api_status), 
        RSA_API::DEVICE_GetErrorString(this->_api_status));
    return this->_device_copy_api_status_message();
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

    this->_api_status = 
        RSA_API::DEVICE_GetInfo(&this->_vars.device.info_type);
    (void) this->_device_copy_info_type();
    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
    API is called to get the temperature status
    the public variable is updated
        true indicates that the device is too hot
        action should be taken to protect the device (shut it down)
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

    this->_api_status = 
        RSA_API::DEVICE_GetOverTemperatureStatus(&this->_vars.device.is_over_temperature);
    (void)this->_device_copy_is_over_temperature();

    if (this->_vars.device.is_over_temperature == true)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "RSA-306B is too hot, shut it down now");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_26_rsa_too_hot);
    }
    return this->_report_api_status();
}


////~~~~


/*
    < 6 > public
    this is a "getter", that functions as a "setter"
    OVERRANGE: input signal to ADC exceeded allowable range
    TRIGGER  : most recent sample, can force with API
    1PPS     : only for RSA500+
    this query clears event history
    all events clear when going stop->run
    nothing is relevant unless the bool is true
    only valid if device is running
    user must set "vars.device.event_id" before calling:
        RSA_API::DEVEVENT_OVERRANGE
        RSA_API::DEVEVENT_TRIGGER
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

    if (this->vars.device.event_id != static_cast<int>(RSA_API::DEVEVENT_OVERRANGE) &&
        this->vars.device.event_id != static_cast<int>(RSA_API::DEVEVENT_TRIGGER)    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "bad event ID:  %d  ,  must be:  %d or %d",
                this->vars.device.event_id,
                static_cast<int>(RSA_API::DEVEVENT_OVERRANGE),
                static_cast<int>(RSA_API::DEVEVENT_TRIGGER));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->_vars.device.event_id = this->vars.device.event_id;

    this->_api_status = 
        RSA_API::DEVICE_GetEventStatus(
            this->_vars.device.event_id,
            &this->_vars.device.event_occured,
            &this->_vars.device.event_timestamp);
    (void)this->_device_copy_event_occured();
    (void)this->_device_copy_event_timestamp();
    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_device_get.cpp
