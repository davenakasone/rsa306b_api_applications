/*
    variables needed for the API group "REFTIME" 
    REFTIME_GetReferenceTime()
    REFTIME_GetCurrentTime()
    REFTIME_GetIntervalSinceRefTimeSet()
    REFTIME_GetReferenceTimeSource()
    REFTIME_GetTimeFromTimestamp()
    REFTIME_GetTimestampFromTime()
    REFTIME_GetTimestampRate()
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


// limiting constants


    rt_type current;                       // the current time since epoch
    rt_type start;                         // time the device was connected, or time was reset
    rt_type helper;                        // for utility, receives reftime_time_2_timesamp(), reftime_timestamp_2_time()

    char dts[BUF_C];                       // holds the date-time-stamp
    double running_duration;               // interval since a timestamp was set
    
    RSA_API::REFTIME_SRC source_select;    // indicates timing source
    uint64_t timestamp_rate;               // rate that timestamps are produced per second
};
typedef struct rsa306b_reftime_struct rsa306b_reftime_struct;


#endif


////////~~~~~~~~END>  rsa306b_reftime_struct.h
