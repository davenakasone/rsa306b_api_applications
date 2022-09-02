/*
    implementation of the rsa306b_class
    using "TRIG" function group of the API
    private functions are all setters

        public:
            # none 
            
        private:
            < 1 >  _trig_set_if_power_trigger_level()
            < 2 >  _trig_set_trigger_mode()
            < 3 >  _trig_set_trigger_position_percent()
            < 4 >  _trig_set_trigger_source
            < 5 >  _trig_set_trigger_transition
*/

#include "../includez/rsa306b_class.h"


/*
    private < 1 >
    power of IF level needed to trigger
    trigger occurs when signal power measure crosses this level
    the trigger power level is set
    new value is validated
    user is responsible for ensuring reference level of external source
*/
int rsa306b::_trig_set_if_power_trigger_level
(
    double level
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
        return CALL_FAILURE;
    }
    if (this->_trig_type.source_select == RSA_API::TriggerSourceIFPowerLevel ||
        this->_trig_type.source_select == RSA_API::TriggerSourceTime          )
    {
        if (level < this->REFERENCE_LEVEL_MIN_dbm ||
            level > this->REFERENCE_LEVEL_MAX_dbm  )
        {
            #ifdef DEBUG_MIN
                printf("\n\ttrigger level out of device range\n");
            #endif
            return CALL_FAILURE;
        }
    }
    this->device_stop();
    this->_api_return_status = RSA_API::TRIG_SetIFPowerTriggerLevel(level);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 2 >
    1 of 2 modes is validated
    free-run, data is continous
    triggered, data only aquired when triggered
*/
int rsa306b::_trig_set_trigger_mode
(
    RSA_API::TriggerMode mode
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
        return CALL_FAILURE;
    }
    if (mode != RSA_API::freeRun &&
        mode != RSA_API::triggered)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trigger mode\n");
        #endif
        return CALL_FAILURE;
    }
    this->device_stop();
    this->_api_return_status = RSA_API::TRIG_SetTriggerMode(mode);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 3 >
    range checked [1% : 99%]
    default 50%
    how much data is stored before and after triggering
    only effects IQ block and spectrum aquisitions
*/
int rsa306b::_trig_set_trigger_position_percent
(
    double percent
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
        return CALL_FAILURE;
    }
    if (percent < this->POSITION_PERCENT_MIN ||
        percent > this->POSITION_PERCENT_MAX  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tpercentage is out of range\n");
        #endif
        return CALL_FAILURE;
    }
    this->device_stop();
    this->_api_return_status = RSA_API::TRIG_SetTriggerPositionPercent(percent);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 4 >
    external source looks at external trigger as input
    must be valid source in the enum "TriggerSource"
*/
int rsa306b::_trig_set_trigger_source
(
    RSA_API::TriggerSource source
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
        return CALL_FAILURE;
    }
    if (source != RSA_API::TriggerSourceExternal     &&
        source != RSA_API::TriggerSourceIFPowerLevel &&
        source != RSA_API::TriggerSourceTime          )
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trigger source\n");
        #endif
        return CALL_FAILURE;
    }
    this->device_stop();
    this->_api_return_status = RSA_API::TRIG_SetTriggerSource(source);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 5 >
    high to low, low to high, or either
    when the trigger occurs
*/
int rsa306b::_trig_set_trigger_transition
(
    RSA_API::TriggerTransition transition
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
        return CALL_FAILURE;
    }
    if (transition != RSA_API::TriggerTransitionLH   &&
        transition != RSA_API::TriggerTransitionHL   &&
        transition != RSA_API::TriggerTransitionEither)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trigger transition\n");
        #endif
        return CALL_FAILURE;
    }
    this->device_stop();
    this->_api_return_status = RSA_API::TRIG_SetTriggerTransition(transition);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////////~~~~~~~~END>  rsa306b_class_TRIG_private.cpp
