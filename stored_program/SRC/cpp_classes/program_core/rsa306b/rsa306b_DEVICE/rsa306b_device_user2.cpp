/*
    API group "DEVICE", user functions 2 of 2

    public :
        < 1 >  device_check_run_state()
        < 2 >  device_check_temperature()
        < 3 >  device_check_event()
        < 4 >  device_prepare_for_run()
        < 5 >  device_start_frame_transfer()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    the public struct is updated, "vars.device.is_running"
*/
CODEZ rsa306b_class::device_check_run_state()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_device_get_is_running();
}


////~~~~


/*
    < 2 > public
    the public struct is updated, "vars.device.is_over_temperature"
    should be called every 15 minutes during operation
*/
CODEZ rsa306b_class::device_check_temperature()
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
CODEZ rsa306b_class::device_check_event()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    return this->_device_get_event();
}


////~~~~


/*
    < 4 > public
    useful to get application and hardware ready
    system is prepared, but data is not yet streamed
*/
CODEZ rsa306b_class::device_prepare_for_run()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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

    (void)this->device_stop();
    RSA_API::ReturnStatus temp = RSA_API::DEVICE_PrepareForRun();
    (void)this->_device_get_is_running();
    return this->_confirm_api_status(temp);
}


////~~~~


/*
    < 5 > public
    usually used as a trigger, after calling "device_prepare_for_run()"
    if system is stopped, it is placed into a run state
*/
CODEZ rsa306b_class::device_start_frame_transfer()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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

    RSA_API::ReturnStatus temp = RSA_API::DEVICE_StartFrameTransfer();
    (void)this->_device_get_is_running();
    return this->_confirm_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_device_user2.cpp
