/*
    variables needed for the API group "REFTIME" 
        REFTIME_GetReferenceTime()
        REFTIME_SetReferenceTime()
        REFTIME_GetCurrentTime()
        REFTIME_GetIntervalSinceRefTimeSet()
        REFTIME_GetReferenceTimeSource()
        REFTIME_GetTimeFromTimestamp(), REFTIME_GetTimestampFromTime()
        REFTIME_GetTimestampRate()
   
    active :
        rt_type              start
        rt_type              current
        double               running_duration_seconds
        RSA_API::REFTIME_SRC source_select
        rt_type              helper
        uint64_t             timestamp_rate 
        char                 dts[BUF_D]  

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"
*/

#ifndef H_rsa306b_reftime_struct
#define H_rsa306b_reftime_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rt_type
{
    time_t seconds;
    uint64_t nanos;
    uint64_t timestamp;
};
typedef struct rt_type rt_type;


////~~~~


struct rsa306b_reftime_struct
{


// NO limiting constants


/*
    REFTIME_SetReferenceTime()
        not necessary
        can be called (0, 0, 0) is applied
        this reinitializes the time system
        OS automatically coordinates the timestamp when connection is made
        state of device's internal timestamp counter at wall-clock time in "start"
*/


/*
    REFTIME_GetReferenceTime()
        gets the time association API is using, 
        time the device was connected or time was reset
        start.seconds   ; time elapsed since epoch (Jan 1, 1970, UTC [00:00:00])
        start.nanos     ; nano seconds elapsed, offset from seconds
        start.timestamp ; a counter value

*/
    rt_type        start;
    const time_t   _START_seconds   = 0;    // DEFAULT
    const uint64_t _START_nanos     = 0;    // DEFAULT
    const uint64_t _START_timestamp = 0;    // DEFAULT


/*
    REFTIME_GetCurrentTime()
        this is the API's best guess for current time
        RSA-306B can't use GPS clocks
        current.seconds   ; time elapsed since epoch (Jan 1, 1970, UTC [00:00:00])
        current.nanos     ; nano seconds elapsed, offset from seconds
        current.timestamp ; a counter value

*/
    rt_type        current;
    const time_t   _CURRENT_seconds   = 0;    // DEFAULT
    const uint64_t _CURRENT_nanos     = 0;    // DEFAULT
    const uint64_t _CURRENT_timestamp = 0;    // DEFAULT


/*
    REFTIME_GetIntervalSinceRefTimeSet()
        running_duration_seconds ; time since internal reference time to timestamp association was last set, in seconds
*/
    double running_duration_seconds;
    const double _RUNNING_DURATION_SECONDS = 0;    // DEFAULT

/*
     REFTIME_GetReferenceTimeSource()
        it always takes 'RTSRC_SYSTEM' when API connects
        this is as good as it gets for the RSA-306B
        'RTSRC_NONE'   , don't try it
		'RTSRC_SYSTEM' , use this
		'RTSRC_GNSS'   , not available on RSA-306B
		'RTSRC_USER'   , only try it if you know what you are doing
            source_select ; API enum, indicates timing source used
*/
    RSA_API::REFTIME_SRC       source_select;
    const RSA_API::REFTIME_SRC _SOURCE_SELECT = RSA_API::REFTIME_SRC::RTSRC_SYSTEM;    // DEFAULT

/*
    REFTIME_GetTimeFromTimestamp(), REFTIME_GetTimestampFromTime()
        given (seconds, nano seconds) --> updates (timestamp)
        given (timestamp)             --> updates (seconds, nano seconds)
        use the 'helper', it is always active and waiting for use
            helper.seconds   ; get or set the seconds here
            helper.nanos     ; get or set the nano seconds here
            helper.timestamp ; get or set the timestamp here
*/
    rt_type        helper;
    const time_t   _HELPER_seconds   = 0;    // DEFAULT
    const uint64_t _HELPER_nanos     = 0;    // DEFAULT
    const uint64_t _HELPER_timestamp = 0;    // DEFAULT

/*
    REFTIME_GetTimestampRate()
        clock rate of continously running timestamp counter
            timestamp_rate ; increments counter performs, per second
*/
    uint64_t timestamp_rate; 
    const uint64_t _TIMESTAMP_RATE = 0;


// holds the date-time-stamp
// for user's conveince
    char dts[BUF_D];                       
    const char* _DTS = INIT_CHARP;

};
typedef struct rsa306b_reftime_struct rsa306b_reftime_struct;


#endif


////////~~~~~~~~END>  rsa306b_reftime_struct.h
 