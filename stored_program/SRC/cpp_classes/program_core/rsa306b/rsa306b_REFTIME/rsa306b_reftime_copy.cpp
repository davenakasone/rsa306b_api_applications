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
        < 6 >  _reftime_copy_running_duration()
        < 7 >  _reftime_copy_source_select()
        < 8 >  _reftime_copy_timestamp_rate()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_reftime_copy_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_reftime_copy_current();
    this->_reftime_copy_start();
    this->_reftime_copy_helper();
    this->_reftime_copy_dts();
    this->_reftime_copy_running_duration();
    this->_reftime_copy_source_select();
    this->_reftime_copy_timestamp_rate();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_reftime_copy_current()
{  
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.current.nanos     = this->_vars.reftime.current.nanos;
    this->vars.reftime.current.seconds   = this->_vars.reftime.current.seconds;
    this->vars.reftime.current.timestamp = this->_vars.reftime.current.timestamp;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_reftime_copy_start()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.start.nanos     = this->_vars.reftime.start.nanos;
    this->vars.reftime.start.seconds   = this->_vars.reftime.start.seconds;
    this->vars.reftime.start.timestamp = this->_vars.reftime.start.timestamp;
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_reftime_copy_helper()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.helper.nanos     = this->_vars.reftime.helper.nanos;
    this->vars.reftime.helper.seconds   = this->_vars.reftime.helper.seconds;
    this->vars.reftime.helper.timestamp = this->_vars.reftime.helper.timestamp;
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_reftime_copy_dts()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    strcpy(this->vars.reftime.dts, this->_vars.reftime.dts);
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_reftime_copy_running_duration()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.running_duration = this->_vars.reftime.running_duration;
}
 

////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_reftime_copy_source_select()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.source_select = this->_vars.reftime.source_select;
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_reftime_copy_timestamp_rate()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.reftime.timestamp_rate = this->_vars.reftime.timestamp_rate;
}
       

////////~~~~~~~~END>  rsa306b_reftime_copy.cpp
