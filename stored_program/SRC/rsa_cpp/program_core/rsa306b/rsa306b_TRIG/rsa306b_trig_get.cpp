/*
    API group "TRIG"

    public :
        #  none
    
    private :
        < 1 >  _trig_get_vars()
        < 2 >  _trig_get_if_power_level()
        < 3 >  _trig_get_mode_select()
        < 4 >  _trig_get_position_percent()
        < 5 >  _trig_get_source_select()
        < 6 >  _trig_get_transition_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_trig_get_vars()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 5;
    CODEZ caught_call[callz];

    caught_call[0] = this->_trig_get_if_power_level   ();
    caught_call[1] = this->_trig_get_mode_select      ();
    caught_call[2] = this->_trig_get_position_percent ();
    caught_call[3] = this->_trig_get_source_select    ();
    caught_call[4] = this->_trig_get_transition_select();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_trig_get_if_power_level()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::TRIG_GetIFPowerTriggerLevel(&this->_vars.trig.if_power_level);
    (void)this->_trig_copy_if_power_level();
    return this->_report_api_status();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_trig_get_mode_select()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::TRIG_GetTriggerMode(&this->_vars.trig.mode_select);
    (void)this->_trig_copy_mode_select();
    return this->_report_api_status();
}



////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_trig_get_position_percent()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::TRIG_GetTriggerPositionPercent(&this->_vars.trig.position_percent);
    (void)this->_trig_copy_position_percent();
    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_trig_get_source_select()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::TRIG_GetTriggerSource(&this->_vars.trig.source_select);
    this->_trig_copy_source_select();
    return this->_report_api_status();
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_trig_get_transition_select()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::TRIG_GetTriggerTransition(&this->_vars.trig.transition_select);
    (void)this->_trig_copy_transition_select();
    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_trig_get.cpp
