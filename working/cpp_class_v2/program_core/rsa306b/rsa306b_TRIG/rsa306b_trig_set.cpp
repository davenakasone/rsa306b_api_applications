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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.call_status = this->_trig_set_if_power_level();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_trig_set_mode_select();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_trig_set_position_percent();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_trig_set_source_select();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    this->_vars.gp.call_status = this->_trig_set_transition_select();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        return this->_vars.constants.CALL_FAILURE;
    }
    return this->_vars.constants.CALL_SUCCESS;
}


////~~~~


/*
    < 2 > private
*/
int rsa306b_class::_trig_set_if_power_level()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->vars.trig.if_power_level == this->_vars.trig.if_power_level)
    {
        #ifdef DEBUG_MAX
            printf("\n\ttrig IF power level already set\n");
        #endif
        return this->_vars.constants.CALL_SUCCESS;
    }
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.trig.if_power_level < this->_vars.constants.REFERENCE_LEVEL_MIN_dbm ||
        this->vars.trig.if_power_level > this->_vars.constants.REFERENCE_LEVEL_MAX_dbm  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tpower level{ %lf }  ,  out of range [ %lf , %lf ]\n",
                this->vars.trig.if_power_level,
                this->_vars.constants.REFERENCE_LEVEL_MIN_dbm,
                this->_vars.constants.REFERENCE_LEVEL_MIN_dbm);
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

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
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->vars.trig.mode_select == this->_vars.trig.mode_select)
    {
        #ifdef DEBUG_MAX
            printf("\n\ttrig mode already set\n");
        #endif
        return this->_vars.constants.CALL_SUCCESS;
    }
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.trig.mode_select != RSA_API::freeRun  &&
        this->vars.trig.mode_select != RSA_API::triggered )
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trigger mode selected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

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
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->vars.trig.position_percent == this->_vars.trig.position_percent)
    {
        #ifdef DEBUG_MAX
            printf("\n\ttrig position percent already set\n");
        #endif
        return this->_vars.constants.CALL_SUCCESS;
    }
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.trig.position_percent < this->_vars.constants.POSITION_PERCENT_MIN ||
        this->vars.trig.position_percent > this->_vars.constants.POSITION_PERCENT_MAX  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tposition percentage { %lf }  ,  out of range [ %lf , %lf ]\n",
                this->vars.trig.if_power_level,
                this->_vars.constants.POSITION_PERCENT_MIN,
                this->_vars.constants.POSITION_PERCENT_MAX);
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

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
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->vars.trig.source_select== this->_vars.trig.source_select)
    {
        #ifdef DEBUG_MAX
            printf("\n\ttrig source select already set\n");
        #endif
        return this->_vars.constants.CALL_SUCCESS;
    }
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.trig.source_select != RSA_API::TriggerSourceExternal     &&
        this->vars.trig.source_select != RSA_API::TriggerSourceIFPowerLevel &&
        this->vars.trig.source_select != RSA_API::TriggerSourceTime          )
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trigger source selected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

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
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->vars.trig.transition_select == this->_vars.trig.transition_select)
    {
        #ifdef DEBUG_MAX
            printf("\n\ttrig transition select already set\n");
        #endif
        return this->_vars.constants.CALL_SUCCESS;
    }
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    if (this->vars.trig.transition_select != RSA_API::TriggerTransitionLH   &&
        this->vars.trig.transition_select != RSA_API::TriggerTransitionHL   &&
        this->vars.trig.transition_select != RSA_API::TriggerTransitionEither)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trigger transition selected\n");
        #endif
        return this->_vars.constants.CALL_FAILURE;
    }
    this->device_stop();

    this->_vars.gp.api_status = 
        RSA_API::TRIG_SetTriggerTransition(this->vars.trig.transition_select);
    this->_gp_confirm_api_status();
    this->_trig_get_transition_select();
    return this->_gp_confirm_return();
}


////////~~~~~~~~END>  rsa306b_trig_set.cpp
