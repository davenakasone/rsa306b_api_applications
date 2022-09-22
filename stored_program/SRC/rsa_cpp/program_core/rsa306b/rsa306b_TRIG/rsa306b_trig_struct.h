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
    const double POSITION_PERCENT_MIN = 1;     // smallest trigger position percentage
    const double POSITION_PERCENT_MAX = 99;    // largest trigger position percentage

/*
    TRIG_ForceTrigger()
        device is forced to trigger when called
            if_power_level ; detection power level for the IF trigger source to detect a trigger even
*/


/*
    TRIG_GetIFPowerTriggerLevel(), TRIG_SetIFPowerTriggerLevel()
*/
    double       if_power_level;
    const double _IF_POWER_LEVEL = -11.1F;    // DEFAULT


    double position_percent;                         // how much data to store before and after trigger event
    
    RSA_API::TriggerMode mode_select;                // free-run or triggered
    RSA_API::TriggerSource source_select;            // where the source of the trigger is derived
    RSA_API::TriggerTransition transition_select;    // event that causes trigger activation

};
typedef struct rsa306b_trig_struct rsa306b_trig_struct;

// these are not in the manaul, but in the "RSA_API.h"...they look useful
        // RSA_API_DLL ReturnStatus TRIG_SetTriggerTime(time_t startTimeSec, uint64_t startTimeNsec, uint64_t repeatTimeNsec);
		// RSA_API_DLL ReturnStatus TRIG_GetTriggerTime(time_t* startTimeSec, uint64_t* startTimeNsec, uint64_t* repeatTimeNsec);

#endif


////////~~~~~~~~END>  rsa306b_trig_struct.h
