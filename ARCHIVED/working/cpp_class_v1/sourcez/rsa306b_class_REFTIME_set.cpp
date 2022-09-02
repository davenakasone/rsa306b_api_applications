/*
    implementation of the rsa306b_class
    using "REFTIME" function group of the API
    getters and setters for member variables

        public:
            # none

        private:
            < 1 >  _reftime_set_date_timestamp()
            < 2 >  _reftime_set_running()
            < 3 >  _reftime_set_split()
            < 4 >  _reftime_set_split_lead()
            < 5 >  _reftime_set_split_trail()
            < 6 >  _reftime_set_source_select();
            < 7 >  _reftime_set_timestamp_rate()
            < 8 >  _reftime_set_begin_type()
            < 9 >  _reftime_set_current_type()
*/

#include "../includez/rsa306b_class.h"


/*
    private < 1 >
    creates a date time stamp in provided string, given reftime_type
    dts_YYYY_MM_DD_dayOfWeek_HH_MM_SS_timeZone_nano_NSEC
    automatically sets current time
*/
void rsa306b::_reftime_set_date_timestamp()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, can't make a date time stamp\n");
        #endif
        return;
    }
    this->_reftime_set_current_type();
    memset(this->_reftime_date_timestamp, '\0', BUF_C);
    struct tm * tm_ptr = NULL;
    tm_ptr = gmtime(&this->_reftime_current_type.seconds);
    if (tm_ptr == NULL)
    {    
        #ifdef DEBUG_MIN
            printf("\n\terror in <time.h>\n");
        #endif
        return;
    }
    strftime(this->_reftime_date_timestamp, BUF_C,
        "dts_%Y_%m_%d_%a_%H_%M_%S_%Z_nano_", tm_ptr);
    snprintf(this->_helper_string, BUF_E-1, "%ld", 
        this->_reftime_current_type.nanos);
    strcat(this->_reftime_date_timestamp, this->_helper_string);
}


////~~~~


/*
    private < 2 >
    updates member to reflect
        "seconds since reference time set"
*/
void rsa306b::_reftime_set_running()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no running time\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::REFTIME_GetIntervalSinceRefTimeSet(
        &this->_reftime_running);
    this->_api_error_check();
}


////~~~~


/*
    private < 3 >
    the time split is lead - trail, in seconds
    caller should have set:
        trail, at beginning of interval
        lead, at end of interval
*/
void rsa306b::_reftime_set_split()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no split availible\n");
        #endif
        return;
    }
    this->_reftime_split = this->_reftime_split_lead - this->_reftime_split_trail;
}


////~~~~


/*
    private < 4 >
    marks total running time
        should call after setting trail
*/
void rsa306b::_reftime_set_split_lead()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no split availible\n");
        #endif
        return;
    }
    this->_reftime_set_running();
    this->_reftime_split_lead = this->_reftime_running;
}


////~~~~


/*
    private < 5 >
    marks total running time
        should call before setting lead
*/
void rsa306b::_reftime_set_split_trail()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no split availible\n");
        #endif
        return;
    }
    this->_reftime_set_running();
    this->_reftime_split_trail = this->_reftime_running;
}


////~~~~


/*
    private < 6 >
    
*/
void rsa306b::_reftime_set_source_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no source availible\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::REFTIME_GetReferenceTimeSource(
        &this->_reftime_source_select);
    this->_api_error_check();
}


////~~~~


/*
    private < 7 >
    called to set time stamp sampling rate
    good to call occasionally in case any temperature changes occur
*/
void rsa306b::_reftime_set_timestamp_rate()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no rate availible\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::REFTIME_GetTimestampRate(
        &this->_reftime_timestamp_rate);
    this->_api_error_check();
}


////~~~~


/*
    private < 8 >
    called when device is connected, records initial time
    only need to call once 
        members are set for the life of the object
    uses initialization point to set _reftime_* members
*/
void rsa306b::_reftime_set_begin_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no timing availible\n");
        #endif
        return;
    }
    this->_reftime_cpu.begin = clock();
    this->_reftime_set_split_lead();
    this->_reftime_set_split_trail();
    this->_reftime_set_source_select();
    this->_reftime_set_timestamp_rate();

    this->_api_return_status = RSA_API::REFTIME_GetReferenceTime(
        &this->_reftime_begin_type.seconds,
        &this->_reftime_begin_type.nanos,
        &this->_reftime_begin_type.stamp);
    this->_api_error_check();

    this->_reftime_set_date_timestamp(); // calls _reftime_set_current_type()
    this->_reftime_set_running();
    this->_reftime_set_split();
}


////~~~~


/*
    private < 9 >
    call before operation requiring the current time
    automatic update of timestamp sampling rate
    automatic update of running time
    called from "_reftime_set_date_timestamp()", don't make circular
*/
void rsa306b::_reftime_set_current_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, no timing availible\n");
        #endif
        return;
    }
    this->_reftime_set_timestamp_rate();    // update
    this->_reftime_set_running();           // update

    this->_api_return_status = RSA_API::REFTIME_GetCurrentTime(
        &this->_reftime_current_type.seconds,
        &this->_reftime_current_type.nanos,
        &this->_reftime_current_type.stamp);
    this->_api_error_check();
}


////////~~~~~~~~END>  rsa306b_class_REFTIME_set.cpp
