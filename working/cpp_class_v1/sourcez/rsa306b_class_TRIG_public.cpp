/*
    implementation of the rsa306b_class
    using "TRIG" function group of the API
    public functions for user action 
    getters are combined in the struct "trig_type"

        public:
            < 1 >  trig_print_all() 
            < 2 >  trig_force_trigger() 
            < 3 >  trig_prepare()
            < 4 >  trig_get_settings()
            
        private:
            # none
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    call to print availible trigger information to stdout
*/
void rsa306b::trig_print_all()                       
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->trig_get_settings(&this->_trig_type);

    printf("\nTRIG information >>>\n");
    printf("\tIF power trigger level    :  %lf\n", this->_trig_type.if_power_level);
    printf("\ttrigger position percent  :  %lf\n", this->_trig_type.position_percent);
    printf("\tmode                      :  ");
    switch (this->_trig_type.mode_select)
    {
        case (RSA_API::freeRun)   : printf("free running\n"); break;
        case (RSA_API::triggered) : printf("triggered\n");    break;
        default                   : printf("unknown\n");      break;
    }
    printf("\tsource                    :  ");
    switch (this->_trig_type.source_select)
    {
        case (RSA_API::TriggerSourceExternal)     : printf("externally triggered\n");          break;
        case (RSA_API::TriggerSourceIFPowerLevel) : printf("IF power level causes trigger\n"); break;
        case (RSA_API::TriggerSourceTime)         : printf("time-based trigger\n");            break;
        default                                   : printf("unknown\n");                       break;
    }
    printf("\ttransition                :  ");
    switch (this->_trig_type.transition_select)
    {
        case(RSA_API::TriggerTransitionLH)     : printf("low to high\n");         break;
        case(RSA_API::TriggerTransitionHL)     : printf("high to low\n");         break;
        case(RSA_API::TriggerTransitionEither) : printf("either level change\n"); break;
        default                                : printf("unknown\n");             break;
    }
}


////~~~~


/*
    public < 2 >
    a trigger event is forced
    basic conditions are validated before API call
*/
void rsa306b::trig_force_trigger()                       
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->device_run();
    this->_api_return_status = RSA_API::TRIG_ForceTrigger();
    this->_api_error_check();
    if (this->_api_return_status == RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\ttrigger forced\n");
        #endif
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to force trigger\n");
        #endif
    }
}


////~~~~


/*
    public < 3 >
    user updates "trig_type" struct with desired settings
    settings are validated, and set if within ranges
    internal members are updated with the new settings
*/
void rsa306b::trig_prepare
(
    trig_type* trigger_settings
) 
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    if (trigger_settings == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate your struct\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_trig_set_if_power_trigger_level(trigger_settings->if_power_level);
    this->_gp_error_check();
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set the trigger\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_trig_set_trigger_mode(trigger_settings->mode_select);
    this->_gp_error_check();
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set the trigger\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_trig_set_trigger_position_percent(trigger_settings->position_percent);
    this->_gp_error_check();
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set the trigger\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_trig_set_trigger_source(trigger_settings->source_select);
    this->_gp_error_check();
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set the trigger\n");
        #endif
        return;
    }
    this->_gp_return_status = 
        this->_trig_set_trigger_transition(trigger_settings->transition_select);
    this->_gp_error_check();
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to set the trigger\n");
        #endif
        return;
    }
    this->trig_get_settings(&this->_trig_type);
}


////~~~~


/*
    public < 4 >
    user provides "trig_type" struct 
    current settings are overwritten into the struct
*/
void rsa306b::trig_get_settings
(
    trig_type* trigger_settings
) 
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    if (trigger_settings == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate your struct\n");
        #endif
        return;
    }
    this->_api_return_status = 
        RSA_API::TRIG_GetIFPowerTriggerLevel(&trigger_settings->if_power_level);
    this->_api_error_check();
    this->_api_return_status = 
        RSA_API::TRIG_GetTriggerMode(&trigger_settings->mode_select);
    this->_api_error_check();
    this->_api_return_status =
        RSA_API::TRIG_GetTriggerPositionPercent(&trigger_settings->position_percent);
    this->_api_error_check();
    this->_api_return_status =
        RSA_API::TRIG_GetTriggerSource(&trigger_settings->source_select);
    this->_api_error_check();
    this->_api_return_status =
        RSA_API::TRIG_GetTriggerTransition(&trigger_settings->transition_select);
    this->_api_error_check();
}


////////~~~~~~~~END>  rsa306b_class_TRIG_public.cpp
