/*
    API group "REFTIME"

    public :
        #  none
    
    private :
        < 1 >  _reftime_copy_vars()
        < 2 >  _reftime_copy_current()
        < 3 >  _reftime_copy_start()
        < 4 >  _reftime_copy_helper()
        < 5 >  _reftime_copy_dts()
        < 6 >  _reftime_copy_running_duration_seconds()
        < 7 >  _reftime_copy_source_select()
        < 8 >  _reftime_copy_timestamp_rate()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_reftime_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 7;
    CODEZ caught_call[callz];

    caught_call[0] = this->_reftime_copy_current                 ();
    caught_call[1] = this->_reftime_copy_start                   ();
    caught_call[2] = this->_reftime_copy_helper                  ();
    caught_call[3] = this->_reftime_copy_dts                     ();
    caught_call[4] = this->_reftime_copy_running_duration_seconds();
    caught_call[5] = this->_reftime_copy_source_select           ();
    caught_call[6] = this->_reftime_copy_timestamp_rate          ();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_reftime_copy_current()
{  
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.current.nanos     = this->_vars.reftime.current.nanos;
    this->vars.reftime.current.seconds   = this->_vars.reftime.current.seconds;
    this->vars.reftime.current.timestamp = this->_vars.reftime.current.timestamp;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_reftime_copy_start()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.start.nanos     = this->_vars.reftime.start.nanos;
    this->vars.reftime.start.seconds   = this->_vars.reftime.start.seconds;
    this->vars.reftime.start.timestamp = this->_vars.reftime.start.timestamp;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_reftime_copy_helper()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.helper.nanos     = this->_vars.reftime.helper.nanos;
    this->vars.reftime.helper.seconds   = this->_vars.reftime.helper.seconds;
    this->vars.reftime.helper.timestamp = this->_vars.reftime.helper.timestamp;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_reftime_copy_dts()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)strcpy(this->vars.reftime.dts, this->_vars.reftime.dts);
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_reftime_copy_running_duration_seconds()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.running_duration_seconds = this->_vars.reftime.running_duration_seconds;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}
 

////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_reftime_copy_source_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.source_select = this->_vars.reftime.source_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_reftime_copy_timestamp_rate()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.timestamp_rate = this->_vars.reftime.timestamp_rate;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}
       

////////~~~~~~~~END>  rsa306b_reftime_copy.cpp
