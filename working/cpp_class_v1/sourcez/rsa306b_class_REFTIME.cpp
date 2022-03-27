/*
    implementation of the rsa306b_class
    using "REFTIME" function group of the API
        public:
            < 1 >  reftime_start_split()
            < 2 >  reftime_stop_split()
            < 3 >  reftime_print_all()
            < 4 >  reftime_timestamp_2_time()
            < 5 >  reftime_time_2_timestamp()

        private:
            # none

    "REFTIME" functions are ready when the device is successfully connected
    do not try to change the time source unless you have GNSS (something better)
        the system time will be accurate enough for most use cases
            and CPU timing accuracy is only limited by <time.h>
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    updates members "_reftime_split_lead"
    called to mark the start of a time interval of interest
*/
void rsa306b::reftime_start_split()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice not connected, no timing availible\n");
        #endif
        return;
    }
    this->_reftime_set_split_trail();
    this->_reftime_cpu.trail = clock();
}


////~~~~


/*
    public < 2 >
    updates members "_reftime_split_trail"
    called to mark the end of a time interval of interest
    user calls reftime_get_split() to get the result
*/
void rsa306b::reftime_stop_split()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice not connected, no timing availible\n");
        #endif
        return;
    }
    
    this->_reftime_set_split_lead();
    this->_reftime_set_split();

    this->_reftime_cpu.lead = clock();
    this->_reftime_cpu.split = ( ((double)this->_reftime_cpu.lead) - 
        ((double)this->_reftime_cpu.trail) ) / CLOCKS_PER_SEC;
}


////~~~~


/*
    public < 3 >
    prints state of reftime members if connected
*/
void rsa306b::reftime_print_all()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice not connected, no timing availible\n");
        #endif
        return;
    }
    this->_reftime_set_date_timestamp();    // update

    printf("\nREFTIME information >>>\n");
    printf("\t_reftime_date_timestamp     :  %s\n", this->_reftime_date_timestamp);
    printf("\t_reftime_timestamp_rate     :  %lld\n", (long long)this->_reftime_timestamp_rate);
    printf("\t_reftime_running            :  %lf\n", this->_reftime_running);
    printf("\t_reftime_split_lead         :  %lf\n", this->_reftime_split_lead);
    printf("\t_reftime_split_trail        :  %lf\n", this->_reftime_split_trail);
    printf("\t_reftime_split              :  %lf\n", this->_reftime_split);
    printf("\t_reftime_source_select      :  ");
    switch (this->_reftime_source_select)
    {
        case (RSA_API::RTSRC_NONE)   : printf("none\n"); break;
        case (RSA_API::RTSRC_SYSTEM) : printf("system\n"); break;
        case (RSA_API::RTSRC_GNSS)   : printf("GNSS\n"); break;
        case (RSA_API::RTSRC_USER)   : printf("user\n");break;
        default                      : printf("unknown\n");break;
    }
    printf("\ttime start, seconds         :  %lld\n", (long long)this->_reftime_begin_type.seconds);
    printf("\ttime start, nano seconds    :  %lld\n", (long long)this->_reftime_begin_type.nanos);
    printf("\ttime start, stamp           :  %lld\n", (long long)this->_reftime_begin_type.stamp);
    printf("\ttime current, seconds       :  %lld\n", (long long)this->_reftime_current_type.seconds);
    printf("\ttime current, nano seconds  :  %lld\n", (long long)this->_reftime_current_type.nanos);
    printf("\ttime current, stamp         :  %lld\n", (long long)this->_reftime_begin_type.stamp);
}


////~~~~


/*
    public < 4 >
    given a defined "stamp" member of the "reftime_type"
        updates "seconds" and "nanos" members
    the time stamp sample rate is updated
*/
void rsa306b::reftime_timestamp_2_time
(
    reftime_type* r_t
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (r_t == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate struct before calling\n");
        #endif
        return;   
    }    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice not connected, no timing availible\n");
        #endif
        return;
    }
    this->_reftime_set_timestamp_rate();

    this->_api_return_status = RSA_API::REFTIME_GetTimeFromTimestamp(
        r_t->stamp, &r_t->seconds, &r_t->nanos);
    this->_api_error_check();
}




////~~~~


/*
    public < 5 >
    given a defined "seconds" and "nanos" members of the "reftime_type"
        updates "stamp" member
    the time stamp sample rate is updated
*/
void rsa306b::reftime_time_2_timestamp
(
    reftime_type* r_t
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (r_t == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate struct before calling\n");
        #endif
        return;   
    }    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice not connected, no timing availible\n");
        #endif
        return;
    }
    this->_reftime_set_timestamp_rate();

    this->_api_return_status = RSA_API::REFTIME_GetTimestampFromTime(
        r_t->seconds, r_t->nanos, &r_t->stamp);
    this->_api_error_check();
}


////////~~~~~~~~END>  rsa306b_class_REFTIME.cpp
