/*
    API group "DEVICE", user functions 1 of 2

    public :
        < 1 >  device_connect()
        < 2 >  device_disconnect()
        < 3 >  device_run()
        < 4 >  device_stop()
        < 5 >  device_reset()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    user must call this function to use the spectrum analyzer
    the API can only mange one connected device per computer
    device search begins, device must succesfully connect
    information is taken fromt he device after connection
*/
CODEZ rsa306b_class::device_connect()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == true)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);
    }

    int  devices_found;
    int  device_ids    [RSA_API::DEVSRCH_MAX_NUM_DEVICES];
    char device_serials[RSA_API::DEVSRCH_MAX_NUM_DEVICES][RSA_API::DEVSRCH_SERIAL_MAX_STRLEN];
    char device_types  [RSA_API::DEVSRCH_MAX_NUM_DEVICES][RSA_API::DEVSRCH_TYPE_MAX_STRLEN];
    this->_api_status = 
        RSA_API::DEVICE_Search
        (
            &devices_found, 
            device_ids, 
            device_serials, 
            device_types
        );

    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "search for devices failed");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_api_status();
    }
    if (devices_found > 1)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "too many devices are connected");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    if (devices_found < 1)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "no devices were found");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }

    this->_vars.device.id = device_ids[0];
    this->_device_copy_id();
    this->_api_status = 
        RSA_API::DEVICE_Connect(this->_vars.device.id);
    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "failed to connect, deviceID:  %d", this->_vars.device.id);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_api_status();
    }

    this->_vars.device.is_connected = true;    // this is very important
    (void)this->_device_copy_is_connected();

    #ifdef DEBUG_MIN
        (void)snprintf(X_ddts, sizeof(X_ddts), "CONNECTED");
        (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(true);
    #endif
    
    constexpr int calls = 10;
    CODEZ caught_call[calls];

    caught_call[0] = this->device_stop();
    caught_call[1] = this->align_run();
    caught_call[2] = this->config_preset();    
    caught_call[3] = this->spectrum_default();
    caught_call[4] = this->get_everything();
    sleep(1);    // toggle
    caught_call[5] = this->device_run();
    sleep(1);    // toggle
    caught_call[6] = this->device_stop();
    sleep(1);    // toggle
    caught_call[7] = this->device_run();
    sleep(1);    // toggle
    caught_call[8] = this->device_stop();
    sleep(1);    // toggle
    caught_call[9] = this->get_everything();

    // INSERT
    return this->cutil.codez_checker(caught_call, calls);
}


////~~~~


/*
    < 2 > public
    the device is disconnected, iff it is connected
    member variables are initialzied
*/
CODEZ rsa306b_class::device_disconnect()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        return this->clear();
    }
    this->_vars.device.is_connected = false;    // this is very important
    (void)this->_device_copy_is_connected();

    (void)this->cutil.report_status_code(this->device_stop());

    this->_api_status = RSA_API::DEVICE_Disconnect();
    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "failed to disconnect device");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_api_status();
    }

    return this->clear();
}


////~~~~


/*
    < 3 > public
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }

    (void)this->_device_get_is_running();    // DEVICE_GetEnable()
    if (this->_vars.device.is_running == true)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);
    }

    this->_api_status = RSA_API::DEVICE_Run();
    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "failed to run device");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_api_status();
    }
    return this->_device_get_is_running();  // DEVICE_GetEnable()
}


////~~~~


/*
    < 4 > public
    the run state is deactivated, if device is connected and running
    errors stopping the device force a return
*/
CODEZ rsa306b_class::device_stop()
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

    (void)this->_device_get_is_running();    // DEVICE_GetEnable()
    if (this->_vars.device.is_running == false)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);
    }

    this->_api_status = RSA_API::DEVICE_Stop();
    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_1_rsa_api_error));
            debug_record(true);
        #endif
        return this->_report_api_status();
    }
    return this->_device_get_is_running();    // DEVICE_GetEnable()
}


////~~~~


/*
    < 5 > public
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


////////~~~~~~~~END>  rsa306b_device_user1.cpp
