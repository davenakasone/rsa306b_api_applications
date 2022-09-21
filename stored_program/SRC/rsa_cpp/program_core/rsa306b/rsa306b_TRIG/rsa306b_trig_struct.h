/*
    variables needed for the API group "TRIG"
    TRIG_ForceTrigger()
    TRIG_GetIFPowerTriggerLevel()
    TRIG_GetTriggerMode()
    TRIG_GetTriggerPositionPercent()
    TRIG_GetTriggerSource()
    TRIG_GetTriggerTransition()
    TRIG_SetIFPowerTriggerLevel()
    TRIG_SetTriggerMode()
    TRIG_SetTriggerPositionPercent()
    TRIG_SetTriggerSource()
    TRIG_SetTriggerTransition()
*/

#ifndef H_rsa306b_trig_struct
#define H_rsa306b_trig_struct


#include "../../control/resourcez.h"

// NO constexpr helpers

struct rsa306b_trig_struct
{


// limiting constants

    double if_power_level;                           // power level of IF trigger occurs
    double position_percent;                         // how much data to store before and after trigger event
    
    RSA_API::TriggerMode mode_select;                // free-run or triggered
    RSA_API::TriggerSource source_select;            // where the source of the trigger is derived
    RSA_API::TriggerTransition transition_select;    // event that causes trigger activation

};
typedef struct rsa306b_trig_struct rsa306b_trig_struct;


#endif


////////~~~~~~~~END>  rsa306b_trig_struct.h
