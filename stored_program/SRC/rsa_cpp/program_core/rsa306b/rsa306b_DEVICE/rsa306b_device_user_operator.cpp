/*
    API group "DEVICE", user functions for operation

    public :
        < 1 >  device_run()
        < 2 >  device_stop()
        < 3 >  device_reset()
        < 4 >  device_prepare_for_run()
        < 5 >  device_start_frame_transfer()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    device is put into the run state, if connected
    if error occurs, run state is never activated
    running initiates data transfer
*/
CODEZ rsa306b_class::device_run()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    (void)this->_device_get_is_running();    // DEVICE_GetEnable()
    if (this->_vars.device.is_running == true)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);    // device was already running
    }

    this->_api_status = RSA_API::DEVICE_Run();
    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            this->_device_get_api_status_message();
            (void)snprintf(X_ddts, sizeof(X_ddts), "%s",
                this->_vars.device.api_status_message);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_api_status();
    }
    return this->_device_get_is_running();  // DEVICE_GetEnable()
}


////~~~~


/*
    < 2 > public
    the run state is deactivated, if device is connected and running
    errors stopping the device force a return
*/
CODEZ rsa306b_class::device_stop()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    (void)this->_device_get_is_running();    // DEVICE_GetEnable()
    if (this->_vars.device.is_running == false)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);    // device was already stopped
    }

    this->_api_status = RSA_API::DEVICE_Stop();
    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            this->_device_get_api_status_message();
            (void)snprintf(X_ddts, sizeof(X_ddts), "%s",
                this->_vars.device.api_status_message);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_api_status();
    }
    return this->_device_get_is_running();    // DEVICE_GetEnable()
}


////~~~~


/*
    < 3 > public
    use sparingly, resets device
    most likely will crash program if resources are not released
    might want to rethink the prompt
*/
CODEZ rsa306b_class::device_reset()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    (void)this->device_stop();

    try
    {
        (void)printf("\n\t\t-witness\n\n");
        this->_api_status = RSA_API::DEVICE_Reset(this->_vars.device.id);
    }
    catch(...)
    {
        (void)printf("\nyou did not make it to vahallah\n");
        (void)sleep(10);
        this->clear();
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
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
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    (void)this->device_stop();
    RSA_API::ReturnStatus temp = RSA_API::DEVICE_PrepareForRun();
    (void)this->_device_get_is_running();
    return this->set_api_status(temp);
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
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif

    RSA_API::ReturnStatus temp = RSA_API::DEVICE_StartFrameTransfer();
    (void)this->_device_get_is_running();
    return this->set_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_device_user1.cpp
