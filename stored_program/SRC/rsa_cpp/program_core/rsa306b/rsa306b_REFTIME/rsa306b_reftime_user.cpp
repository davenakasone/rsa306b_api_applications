/*
    API group "REFTIME", user functions

    public :
        < 1 >  reftime_reset()
        < 2 >  reftime_timestamp_2_time()
        < 3 >  reftime_time_2_timestamp()
        < 4 >  reftime_make_dts()

    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    user should not have to use this
*/
CODEZ rsa306b_class::reftime_reset()
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

    RSA_API::ReturnStatus temp = RSA_API::REFTIME_SetReferenceTime(0, 0, 0);
    (void)this->_reftime_get_vars();
    return this->set_api_status(temp);
}


////~~~~



/*
    < 2 > public
    user sets:
        'vars.reftime.helper.timestamp'
    updates occur in:
        'vars.reftime.helper.seconds'
        'vars.reftime.helper.nanos'
*/
CODEZ rsa306b_class::reftime_timestamp_2_time()
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

    this->_vars.reftime.helper.timestamp = this->vars.reftime.helper.timestamp;
    this->_api_status =
        RSA_API::REFTIME_GetTimeFromTimestamp
        (
            this->_vars.reftime.helper.timestamp,
            &this->_vars.reftime.helper.seconds,
            &this->_vars.reftime.helper.nanos
        );
    (void)this->_reftime_copy_helper();
    return this->_report_api_status();
}


////~~~~


/*
    < 3 > public
    user sets :
        'vars.reftime.helper.seconds'
        'vars.reftime.helper.nanos'
    updates occur in:
        'vars.reftime.helper.timestamp'
        
*/
CODEZ rsa306b_class::reftime_time_2_timestamp()
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

    this->_vars.reftime.helper.seconds = this->vars.reftime.helper.seconds;
    this->_vars.reftime.helper.nanos = this->vars.reftime.helper.nanos;
    this->_api_status =
        RSA_API::REFTIME_GetTimestampFromTime
        (
            this->_vars.reftime.helper.seconds,
            this->_vars.reftime.helper.nanos,
            &this->_vars.reftime.helper.timestamp
        );
    (void)this->_reftime_copy_helper();
    return this->_report_api_status();
}


////~~~~


/*
    < 4 > public
    call and use "reftime.dts"
    it will update the char* with the current time
*/
char* rsa306b_class::reftime_make_dts()
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
        return NULL;
    }
#endif
    
    if(this->_reftime_get_current() != CODEZ::_0_no_errors)
    {
        return NULL;
    }

    if
    (
        this->cutil.make_date_timestamp
        (
            &this->_vars.reftime.current.seconds,
            this->_vars.reftime.current.nanos,
            this->_vars.reftime.dts
        ) != CODEZ::_0_no_errors
    )
    {
        (void)strcpy(this->_vars.reftime.dts, INIT_CHARP);
        (void)this->_reftime_copy_dts();
        return NULL;
    }

    (void)this->_reftime_copy_dts();
    return this->vars.reftime.dts;
}


////////~~~~~~~~END>  rsa306b_reftime_user.cpp
