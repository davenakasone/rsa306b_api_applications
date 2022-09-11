/*
    API group "REFTIME"

    public :
        #  none
    
    private :
        < 1 >  _reftime_get_vars()
        < 2 >  _reftime_get_current()
        < 3 >  _reftime_get_start()
        < 4 >  _reftime_get_running_duration()
        < 5 >  _reftime_get_source_select()
        < 6 >  _reftime_get_timestamp_rate()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_reftime_get_vars()
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
    this->_reftime_make_dts();    // calls _reftime_get_current
    this->_reftime_get_start();
    this->_reftime_get_running_duration();
    this->_reftime_get_source_select();
    this->_reftime_get_timestamp_rate();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_reftime_get_current()
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
    this->_vars.gp.api_status = 
        RSA_API::REFTIME_GetCurrentTime(
            &this->_vars.reftime.current.seconds, 
            &this->_vars.reftime.current.nanos, 
            &this->_vars.reftime.current.timestamp);
    this->_gp_confirm_api_status();
    this->_reftime_copy_current();
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_reftime_get_start()
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
    this->_vars.gp.api_status = 
        RSA_API::REFTIME_GetReferenceTime(
            &this->_vars.reftime.start.seconds, 
            &this->_vars.reftime.start.nanos, 
            &this->_vars.reftime.start.timestamp);
    this->_gp_confirm_api_status();
    this->_reftime_copy_start();
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_reftime_get_running_duration()
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
    this->_vars.gp.api_status = 
        RSA_API::REFTIME_GetIntervalSinceRefTimeSet(
            &this->_vars.reftime.running_duration);
    this->_reftime_copy_running_duration();
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_reftime_get_source_select()
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
    this->_vars.gp.api_status = 
        RSA_API::REFTIME_GetReferenceTimeSource(
            &this->_vars.reftime.source_select);
    this->_reftime_copy_source_select();
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_reftime_get_timestamp_rate()
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
    this->_vars.gp.api_status = 
        RSA_API::REFTIME_GetTimestampRate(
            &this->_vars.reftime.timestamp_rate);
    this->_reftime_copy_timestamp_rate();
}

////////~~~~~~~~END>  rsa306b_reftime_get.cpp
