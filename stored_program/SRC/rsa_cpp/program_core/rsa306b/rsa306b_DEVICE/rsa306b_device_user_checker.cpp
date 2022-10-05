/*
    API group "DEVICE", user functions for checking

    public :
        < 1 >  device_check_run_state()
        < 2 >  device_check_temperature()
        < 3 >  device_check_event()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    the public struct is updated, "vars.device.is_running"
*/
bool rsa306b_class::device_check_run_state()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)this->_device_get_is_running();
    if (this->_vars.device.is_running == true)
    {
        return true;
    }
    return false;
}


////~~~~


/*
    < 2 > public
    the public struct is updated, "vars.device.is_over_temperature"
    should be called every 15 minutes during operation
*/
bool rsa306b_class::device_check_temperature()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    return this->_device_get_is_over_temperature();
}


////~~~~


/*
    < 3 > public
    the user sets "vars.device.event_id" before calling
    0 = ADC overflow
    1 = trigger occured
    events mean nothing unless "vars.device.event_occured" == true
    the device should be running, events are only updated when running
*/
bool rsa306b_class::device_check_event()
{
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif  

    return this->_device_get_event();
}


////////~~~~~~~~END>  rsa306b_device_user_checker.cpp
