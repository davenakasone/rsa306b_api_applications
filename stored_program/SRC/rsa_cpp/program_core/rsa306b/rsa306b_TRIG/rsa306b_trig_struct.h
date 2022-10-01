/*
    variables needed for the API group "TRIG"
        TRIG_ForceTrigger()
        TRIG_GetIFPowerTriggerLevel()   , TRIG_SetIFPowerTriggerLevel()
        TRIG_GetTriggerMode()           , TRIG_SetTriggerMode()
        TRIG_GetTriggerPositionPercent(), TRIG_SetTriggerPositionPercent()
        TRIG_GetTriggerSource()         , TRIG_SetTriggerSource()
        TRIG_GetTriggerTransition()     , TRIG_SetTriggerTransition()
        // TRIG_GetTriggerTime()           , TRIG_SetTriggerTime()

    active :
        double if_power_level
        RSA_API::TriggerMode mode_select
        double position_percent
        RSA_API::TriggerSource source_select
        RSA_API::TriggerTransition transition_select
        // time_t start_time_seconds
        // uint64_t start_time_nano_seconds
        // uint64_t repeat_time_nano_seconds

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"
*/


#ifndef H_rsa306b_trig_struct
#define H_rsa306b_trig_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_trig_struct
{


// limiting constants
    const double POSITION_PERCENT_MIN = 1.0F;     // smallest trigger position percentage
    const double POSITION_PERCENT_MAX = 99.0F;    // largest trigger position percentage

/*
    TRIG_ForceTrigger()
        device is forced to trigger when called
        good for breaking out of poll loops or randomly initiating an acquisition
*/


/*
    TRIG_GetIFPowerTriggerLevel(), TRIG_SetIFPowerTriggerLevel()
        requires :
            mode_select   == freeRun
            source_select == TriggerSourceIFPowerLevel
        detection threshold, measured in units of power, for the IF trigger source
            if_power_level ; value of detection, best used in dBm
*/
    double       if_power_level;
    const double _IF_POWER_LEVEL = -12.3F;    // DEFAULT

/*
    TRIG_GetTriggerMode(), TRIG_SetTriggerMode()
        uses the enum to identify the triggered or untriggered
        'freeRun'    // trigger allows the device to continually update
        'triggered'  // the device only updates if a triggering event occurs
            mode_select ; API enum to specifiy tigger mode
*/

    RSA_API::TriggerMode       mode_select;
    const RSA_API::TriggerMode _MODE_SELECT = RSA_API::TriggerMode::freeRun;    // DEFAULT

/*
    TRIG_GetTriggerPositionPercent(), TRIG_SetTriggerPositionPercent()
        only effects IQBLK and SPECTRUM calls
            position_percent ; how much data to keep before and after trigger event
        limited by :
            POSITION_PERCENT_MIN
            POSITION_PERCENT_MAX
*/
    double       position_percent;
    const double _POSITION_PERCENT = 0.5F;    // DEFAULT

/*
    TRIG_GetTriggerSource(), TRIG_SetTriggerSource()
        identifies what is used as the trigger source "where the source of the trigger is derived from"
        'TriggerSourceExternal'        // external trigger causes the trigger
		'TriggerSourceIFPowerLevel'    //  IF power level...signal causes the trigger
		'TriggerSourceTime'            //  time-based setting causes the trigger
            source_select ; API enum used to designate the trigger source
*/
    RSA_API::TriggerSource       source_select;
    const RSA_API::TriggerSource _SOURCE_SELECT = RSA_API::TriggerSource::TriggerSourceIFPowerLevel;    // DEFAULT


/*
    TRIG_GetTriggerTransition(), TRIG_SetTriggerTransition()
        condition of signal that will cause the trigger event
        'TriggerTransitionLH'        //  Low to High transition		
		'TriggerTransitionHL'	     //  High to Low transition
		'TriggerTransitionEither'    //  either Low to High or High to Low transition
            transition_select ; API enum to specify the signal behavior for triggering
*/
    RSA_API::TriggerTransition       transition_select;
    const RSA_API::TriggerTransition _TRANSITION_SELECT = RSA_API::TriggerTransitionLH;    // DEFAULT


/*
    TRIG_GetTriggerTime(), TRIG_SetTriggerTime()
        these are in the "RSA_API.h", but there is no description in the manual
        they look useful, but further assement is needed ...looks like they would work with REFTIME
            start_time_seconds       ; appears to be the time to start triggering, in seconds
            start_time_nano_seconds  ; appears to be the time to start triggering, in nano seconds
            repeat_time_nano_seconds ; appears to be the time to repeat trigger, in nano seconds
*/
    time_t       start_time_seconds;
    const time_t _START_TIME_SECONDS = 0;            // DEFAULT

    uint64_t       start_time_nano_seconds;
    const uint64_t _START_TIME_NANO_SECONDS = 0;     // DEFAULT

    uint64_t       repeat_time_nano_seconds;
    const uint64_t _REPEAT_TIME_NANO_SECONDS = 0;    // DEFAULT


};
typedef struct rsa306b_trig_struct rsa306b_trig_struct;


#endif


////////~~~~~~~~END>  rsa306b_trig_struct.h
