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
void rsa306b_class::_trig_get_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_trig_get_if_power_level();
    this->_trig_get_mode_select();
    this->_trig_get_position_percent();
    this->_trig_get_source_select();
    this->_trig_get_transition_select();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_trig_get_if_power_level()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_GetIFPowerTriggerLevel(&this->_vars.trig.if_power_level);
    this->_gp_confirm_api_status();
    this->_trig_copy_if_power_level();
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_trig_get_mode_select()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_GetTriggerMode(&this->_vars.trig.mode_select);
    this->_gp_confirm_api_status();
    this->_trig_copy_mode_select();
}



////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_trig_get_position_percent()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_GetTriggerPositionPercent(&this->_vars.trig.position_percent);
    this->_gp_confirm_api_status();
    this->_trig_copy_position_percent();
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_trig_get_source_select()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_GetTriggerSource(&this->_vars.trig.source_select);
    this->_gp_confirm_api_status();
    this->_trig_copy_source_select();
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_trig_get_transition_select()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_GetTriggerTransition(&this->_vars.trig.transition_select);
    this->_gp_confirm_api_status();
    this->_trig_copy_transition_select();
}


////////~~~~~~~~END>  rsa306b_trig_get.cpp
