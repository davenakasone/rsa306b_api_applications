/*
    API group "REFTIME"

    public :
        < 1 >  reftime_get_vars()
    
    private :
        < 1 >  _reftime_get_vars()
        < 2 >  _reftime_get_current()
        < 3 >  _reftime_get_start()
        < 4 >  _reftime_get_running_duration_seconds()
        < 5 >  _reftime_get_source_select()
        < 6 >  _reftime_get_timestamp_rate()
*/

#include "../rsa306b_class.h"



/*
    < 1 > public
*/
CODEZ rsa306b_class::reftime_get_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
    
    return this->_reftime_get_vars();
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_reftime_get_vars()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    constexpr int callz = 5;
    CODEZ caught_call[callz];

    caught_call[0] = this->_reftime_get_current                 ();
    caught_call[1] = this->_reftime_get_start                   ();
    caught_call[2] = this->_reftime_get_running_duration_seconds();
    caught_call[3] = this->_reftime_get_source_select           ();
    caught_call[4] = this->_reftime_get_timestamp_rate          ();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_reftime_get_current()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::REFTIME_GetCurrentTime
        (
            &this->_vars.reftime.current.seconds, 
            &this->_vars.reftime.current.nanos, 
            &this->_vars.reftime.current.timestamp
        );
    (void)this->_reftime_copy_current();
    return this->_report_api_status();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_reftime_get_start()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::REFTIME_GetReferenceTime
        (
            &this->_vars.reftime.start.seconds, 
            &this->_vars.reftime.start.nanos, 
            &this->_vars.reftime.start.timestamp
        );
    (void)this->_reftime_copy_start();
    return this->_report_api_status();
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_reftime_get_running_duration_seconds()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::REFTIME_GetIntervalSinceRefTimeSet
        (
            &this->_vars.reftime.running_duration_seconds
        );
    (void)this->_reftime_copy_running_duration_seconds();
    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_reftime_get_source_select()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::REFTIME_GetReferenceTimeSource
        (
            &this->_vars.reftime.source_select
        );
    (void)this->_reftime_copy_source_select();
    return this->_report_api_status();
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_reftime_get_timestamp_rate()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::REFTIME_GetTimestampRate
        (
            &this->_vars.reftime.timestamp_rate
        );
    (void)this->_reftime_copy_timestamp_rate();
    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_reftime_get.cpp
