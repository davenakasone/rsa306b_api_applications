/*
    API group "TRIG"

    public :
        #  none
    
    private :
        < 1 >  _trig_set_vars()
        < 2 >  _trig_set_if_power_level()
        < 3 >  _trig_set_mode_select()
        < 4 >  _trig_set_position_percent()
        < 5 >  _trig_set_source_select()
        < 6 >  _trig_set_transition_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
int rsa306b_class::_trig_set_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->device_stop();

    // vars.gp.call_status
    if (this->vars.trig.if_power_level != this->_vars.trig.if_power_level)
    {
        if (this->_trig_set_if_power_level() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.trig.mode_select
    if (this->vars.trig.mode_select != this->_vars.trig.mode_select)
    {
        if (this->_trig_set_mode_select() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.trig.position_percent
    if (this->vars.trig.position_percent != this->_vars.trig.position_percent)
    {
        if (this->_trig_set_position_percent() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.trig.source_select
    if (this->vars.trig.source_select != this->_vars.trig.source_select)
    {
        if (this->_trig_set_source_select() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    // vars.trig.transition_select
    if (this->vars.trig.transition_select != this->_vars.trig.transition_select)
    {
        if (this->_trig_set_transition_select() != this->constants.CALL_SUCCESS)
        {
            return this->constants.CALL_FAILURE;
        }
    }
    
    return this->constants.CALL_SUCCESS;
}


////~~~~


/*
    < 2 > private
*/
int rsa306b_class::_trig_set_if_power_level()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.trig.if_power_level < this->constants.REFERENCE_LEVEL_MIN_DBM ||
        this->vars.trig.if_power_level > this->constants.REFERENCE_LEVEL_MAX_DBM  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "power level { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.trig.if_power_level,
                this->constants.REFERENCE_LEVEL_MIN_DBM,
                this->constants.REFERENCE_LEVEL_MIN_DBM);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_SetIFPowerTriggerLevel(this->vars.trig.if_power_level);
    this->_gp_confirm_api_status();
    this->_trig_get_if_power_level();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 3 > private
*/
int rsa306b_class::_trig_set_mode_select()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.trig.mode_select != RSA_API::freeRun  &&
        this->vars.trig.mode_select != RSA_API::triggered )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid trigger mode: %d", 
                static_cast<int>(this->vars.trig.mode_select));
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_SetTriggerMode(this->vars.trig.mode_select);
    this->_gp_confirm_api_status();
    this->_trig_get_mode_select();
    return this->_gp_confirm_return();
}



////~~~~


/*
    < 4 > private
*/
int rsa306b_class::_trig_set_position_percent()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.trig.position_percent < this->constants.POSITION_PERCENT_MIN ||
        this->vars.trig.position_percent > this->constants.POSITION_PERCENT_MAX  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "position percentage { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.trig.if_power_level,
                this->constants.POSITION_PERCENT_MIN,
                this->constants.POSITION_PERCENT_MAX);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_SetTriggerPositionPercent(this->vars.trig.position_percent);
    this->_gp_confirm_api_status();
    this->_trig_get_position_percent();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 5 > private
*/
int rsa306b_class::_trig_set_source_select()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.trig.source_select != RSA_API::TriggerSourceExternal     &&
        this->vars.trig.source_select != RSA_API::TriggerSourceIFPowerLevel &&
        this->vars.trig.source_select != RSA_API::TriggerSourceTime          )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid trigger source: %d",
                static_cast<int>(this->vars.trig.source_select));
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_SetTriggerSource(this->vars.trig.source_select);
    this->_gp_confirm_api_status();
    this->_trig_get_source_select();
    return this->_gp_confirm_return();
}


////~~~~


/*
    < 6 > private
*/
int rsa306b_class::_trig_set_transition_select()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    if (this->vars.trig.transition_select != RSA_API::TriggerTransitionLH   &&
        this->vars.trig.transition_select != RSA_API::TriggerTransitionHL   &&
        this->vars.trig.transition_select != RSA_API::TriggerTransitionEither)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid trigger transition: %d",
                static_cast<int>(this->vars.trig.transition_select));
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->constants.CALL_FAILURE;
    }
    this->_vars.gp.api_status = 
        RSA_API::TRIG_SetTriggerTransition(this->vars.trig.transition_select);
    this->_gp_confirm_api_status();
    this->_trig_get_transition_select();
    return this->_gp_confirm_return();
}


////////~~~~~~~~END>  rsa306b_trig_set.cpp
