/*
    API group "TRIG"

    public :
        #  none
    
    private :
        < 1 >  _trig_copy_vars()
        < 2 >  _trig_copy_if_power_level()
        < 3 >  _trig_copy_mode_select()
        < 4 >  _trig_copy_position_percent()
        < 5 >  _trig_copy_source_select()
        < 6 >  _trig_copy_transition_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_trig_copy_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT,  __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 5;
    CODEZ caught_call[callz];

    caught_call[0] = this->_trig_copy_if_power_level   ();
    caught_call[1] = this->_trig_copy_mode_select      ();
    caught_call[2] = this->_trig_copy_position_percent ();
    caught_call[3] = this->_trig_copy_source_select    ();
    caught_call[4] = this->_trig_copy_transition_select();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_trig_copy_if_power_level()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.trig.if_power_level = this->_vars.trig.if_power_level;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_trig_copy_mode_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.trig.mode_select = this->_vars.trig.mode_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}



////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_trig_copy_position_percent()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.trig.position_percent = this->_vars.trig.position_percent;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_trig_copy_source_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.trig.source_select = this->_vars.trig.source_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_trig_copy_transition_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.trig.transition_select = this->_vars.trig.transition_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_trig_copy.cpp
