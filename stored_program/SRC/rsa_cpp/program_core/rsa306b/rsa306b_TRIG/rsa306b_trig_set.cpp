/*
    API group "TRIG"

    public :
        < 1 >  trig_set_vars()
    
    private :
        < 1 >  _trig_set_vars()
        < 2 >  _trig_set_if_power_level()
        < 3 >  _trig_set_mode_select()
        < 4 >  _trig_set_position_percent()
        < 5 >  _trig_set_source_select()
        < 6 >  _trig_set_transition_select()
        // < 7 >  _trig_set_time()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    user updates "vars.trig.*" variables
    new values are set if they are valid
*/
CODEZ rsa306b_class::trig_set_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_trig_set_vars();
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_trig_set_vars()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 5;
    CODEZ caught_call[callz];

    caught_call[0] = this->_trig_set_if_power_level   ();
    caught_call[1] = this->_trig_set_mode_select      ();
    caught_call[2] = this->_trig_set_position_percent ();
    caught_call[3] = this->_trig_set_source_select    ();
    caught_call[4] = this->_trig_set_transition_select();
    // caught_call[5] = this->_trig_set_time             ();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_trig_set_if_power_level()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->vars.trig.if_power_level < this->_vars.config.REFERENCE_LEVEL_MIN_DBM ||
        this->vars.trig.if_power_level > this->_vars.config.REFERENCE_LEVEL_MAX_DBM  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "power level { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.trig.if_power_level,
                this->_vars.config.REFERENCE_LEVEL_MIN_DBM,
                this->_vars.config.REFERENCE_LEVEL_MAX_DBM);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->device_stop();

    RSA_API::ReturnStatus temp = 
        RSA_API::TRIG_SetIFPowerTriggerLevel
        (
            this->vars.trig.if_power_level
        );
    (void)this->_trig_get_if_power_level();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_trig_set_mode_select()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->vars.trig.mode_select != RSA_API::freeRun  &&
        this->vars.trig.mode_select != RSA_API::triggered )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid trigger mode: %d", 
                static_cast<int>(this->vars.trig.mode_select));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->device_stop();

    RSA_API::ReturnStatus temp = 
        RSA_API::TRIG_SetTriggerMode
        (
            this->vars.trig.mode_select
        );
    (void)this->_trig_get_mode_select();
    return this->set_api_status(temp);
}



////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_trig_set_position_percent()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->vars.trig.position_percent < this->_vars.trig.POSITION_PERCENT_MIN ||
        this->vars.trig.position_percent > this->_vars.trig.POSITION_PERCENT_MAX  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "position percentage { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.trig.if_power_level,
                this->_vars.trig.POSITION_PERCENT_MIN,
                this->_vars.trig.POSITION_PERCENT_MAX);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->device_stop();

    RSA_API::ReturnStatus temp = 
        RSA_API::TRIG_SetTriggerPositionPercent
        (
            this->vars.trig.position_percent
        );
    (void)this->_trig_get_position_percent();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_trig_set_source_select()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->vars.trig.source_select != RSA_API::TriggerSourceExternal     &&
        this->vars.trig.source_select != RSA_API::TriggerSourceIFPowerLevel &&
        this->vars.trig.source_select != RSA_API::TriggerSourceTime          )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid trigger source: %d",
                static_cast<int>(this->vars.trig.source_select));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->device_stop();

    RSA_API::ReturnStatus temp = 
        RSA_API::TRIG_SetTriggerSource
        (
            this->vars.trig.source_select
        );
    (void)this->_trig_get_source_select();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_trig_set_transition_select()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->vars.trig.transition_select != RSA_API::TriggerTransitionLH   &&
        this->vars.trig.transition_select != RSA_API::TriggerTransitionHL   &&
        this->vars.trig.transition_select != RSA_API::TriggerTransitionEither)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid trigger transition: %d",
                static_cast<int>(this->vars.trig.transition_select));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->device_stop();

    RSA_API::ReturnStatus temp = 
        RSA_API::TRIG_SetTriggerTransition
        (
            this->vars.trig.transition_select
        );
    (void)this->_trig_get_transition_select();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 7 > private
*/
// CODEZ rsa306b_class::_trig_set_time()
// {
// #ifdef DEBUG_SETS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif
// #ifdef SAFETY_CHECKS
//     if (this->_vars.device.is_connected == false)
//     {
//         #ifdef DEBUG_MIN
//             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
//                 this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
//             debug_record(true);
//         #endif
//         return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
//     }
// #endif
//     this->device_stop();

//     RSA_API::ReturnStatus temp = 
//         RSA_API::TRIG_SetTriggerTime
//         (
//             this->vars.trig.start_time_seconds,
//             this->vars.trig.start_time_nano_seconds,
//             this->vars.trig.repeat_time_nano_seconds
//         );
//     (void)this->_trig_get_time();
//     return this->set_api_status(temp);
// }


////////~~~~~~~~END>  rsa306b_trig_set.cpp
