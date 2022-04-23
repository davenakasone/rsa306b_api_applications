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
void rsa306b_class::_device_get_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

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
void rsa306b_class::_device_get_is_running()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
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
void rsa306b_class::_device_get_error_string()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    const char* temp = NULL;
    temp = RSA_API::DEVICE_GetErrorString(this->_vars.gp.api_status);
    snprintf(this->_vars.device.error_string, BUF_D-1, 
        "error code:  %d  ,  error message:  %s", 
        this->_vars.gp.api_status, temp);
    temp = NULL;
    this->_device_copy_error_string();
}


////~~~~


/*
    < 4 > private
    the struct of strings is updated by the API
    values are copied into the public variable struct
*/
void rsa306b_class::_device_get_info_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
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
void rsa306b_class::_device_get_is_over_temperature()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_vars.gp.api_status = 
        RSA_API::DEVICE_GetOverTemperatureStatus(&this->_vars.device.is_over_temperature);
    this->_gp_confirm_api_status();
    this->_device_copy_is_over_temperature();

    if (this->_vars.device.is_over_temperature == true)
    {
        #ifdef DEBUG_MIN
            printf("\n\tthe device is too hot, shut it down now\n");
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
void rsa306b_class::_device_get_event()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    if (this->_vars.device.is_running == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice is not running\n");
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
