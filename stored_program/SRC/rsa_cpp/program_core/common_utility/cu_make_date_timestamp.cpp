/*
    common_utility, class

    public :
        < 1 >  make_date_timestamp()
    
    private :
        #  none
        
*/

#include "common_utility.h"


/*
    < 1 > public
    call with time of interest and allocated char*
    the char* comes back formated to the time provided
    if using current time, call with seconds==0 and nanos==0, they will not matter

    make_date_timestamp(0,0, dts)              use current time
    make_date_timestamp(seconds,nanos, dts)    use your time

    be sure to stay with CLOCK_MONOTONIC
*/
CODEZ common_utility::make_date_timestamp
(
    const time_t* seconds, 
    const uint64_t nanos, 
    char* dts_string
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (dts_string == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "the char* is empty");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }
    
    char temp[BUF_C];
    memset(temp, '\0', sizeof(temp));

    struct tm * tm_ptr = NULL;
    if ((seconds==0) && (nanos==0))
    {
        this->_timer_set_running_wall();
        tm_ptr = localtime(&this->_lead_wall.tv_sec);
    }
    else
    {
        tm_ptr = localtime(seconds);    // or gmtime()
    }
    

    if (tm_ptr == NULL)
    {    
        // error in <time.h>
        return this->report_status_code(this->_status_code = CODEZ::_9_function_call_failed);
    }

    (void)strftime(temp, sizeof(temp)-1,
        "_%Y_%m_%d_%a__%Z_%H_%M_%S_", tm_ptr);    // _YYYY_MM_DD_day__ZONE_hh_mm_ss_
    
    if ((seconds==0) && (nanos==0))
    {
        (void)sprintf(dts_string,"%s%ld_", temp, this->_lead_wall.tv_nsec);    // _YYYY_MM_DD_day__ZONE_hh_mm_ss_nano_
    }
    {
        (void)sprintf(dts_string,"%s%lu_", temp, nanos);    // _YYYY_MM_DD_day__ZONE_hh_mm_ss_nano_
    }

    return this->report_status_code(this->_status_code = CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  cu_make_date_timestamp.cpp
