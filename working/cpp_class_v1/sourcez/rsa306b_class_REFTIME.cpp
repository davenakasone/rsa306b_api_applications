/*
    implementation of the rsa306b_class
    using "REFTIME" function group of the API
        public:
            # print_time_begin()
            # print_time_info()
            # print_time_now()
            # print_time_running()
            # print_time_split()
        
        private:
            # record_date_time_stamp()
            # record_running_time()
            # record_start_time()
            # record_time_now()
            # record_time_split()
            # timestamp_2_time()
            # time_2_timestamp()
            # update_time_stamp_rate()

    "REFTIME" functions are ready when the device is successfully connected
*/

#include "../includez/rsa306b_class.h"

switch (this->_reftime_source_select)
{
    case (RSA_API::RTSRC_NONE) :
        printf("\treference time source:  none\n");
        break;
    case (RSA_API::RTSRC_SYSTEM) :
        printf("\treference time source:  system\n");
        break;
    case (RSA_API::RTSRC_GNSS) :
        printf("\treference time source:  GNSS\n");
        break;
    case (RSA_API::RTSRC_USER) :
        printf("\treference time source:  user\n");
        break;
    default :
        printf("\treference time source:  unknown\n");
        break;
}













////~~~~


/*
    private
    updates members "current_time_*"
    
*/
void rsa306b::record_time_now()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, can't record time now\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::REFTIME_GetCurrentTime(
        &this->current_time_seconds, 
        &this->current_time_nano_seconds, 
        &this->current_time_stamp);
    this->error_check();
}


////~~~~


/*
    private
    given a time stamp and timing data types, 
        updates timing data types to the time stamp
    the time stamp sample rate is updated because
        caller will likely need an accurate time stamp rate
*/
void rsa306b::timestamp_2_time
(
    uint64_t in_time_stamp, 
    time_t* out_seconds, 
    uint64_t* out_nanos
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no times to convert\n");
        #endif
        return;
    }
    this->update_time_stamp_rate();
    this->api_return_status = RSA_API::REFTIME_GetTimeFromTimestamp(
        in_time_stamp, out_seconds, out_nanos);
    this->error_check();
}


////~~~~


/*
    private
    given a time stamp and timing data types, 
        updates time stamp to the timing data types
    the time stamp sample rate is updated because
        caller will likely need an accurate time stamp rate
*/
void rsa306b::time_2_timestamp
(
    time_t in_seconds, 
    uint64_t in_nanos, 
    uint64_t* out_time_stamp
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no times to convert\n");
        #endif
        return;
    }
    this->update_time_stamp_rate();
    this->api_return_status = RSA_API::REFTIME_GetTimestampFromTime(
        in_seconds, in_nanos, out_time_stamp);
    this->error_check();
}




