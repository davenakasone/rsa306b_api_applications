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


/*
    public
*/
void rsa306b::print_time_begin()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no timing data to print\n");
        #endif
        return;
    }
    printf("\nbegin time >>>\n");
    printf("\tseconds:        %ld\n",
        this->reference_time_seconds);
    printf("\tnano seconds:  %ld\n", 
        this->reference_time_nano_seconds);
    printf("\tcounter:        %ld\n", 
        this->reference_time_stamp);
    this->record_date_time_stamp(
        this->reference_time_seconds, 
        this->reference_time_nano_seconds);
    printf("\t%s\n", this->date_time_stamp);
}


////~~~~


/*
    public
*/
void rsa306b::print_time_info()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no timing data to print\n");
        #endif
        return;
    }
    printf("\ntiming info >>>\n");  
    this->api_return_status = RSA_API::REFTIME_GetReferenceTimeSource(
        &this->reference_time_source_select);
    this->error_check();
    switch (this->reference_time_source_select)
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
    this->update_time_stamp_rate();
    printf("\ttime-stamp rate:  %ld\n", 
        this->time_stamp_sampling_rate);
    this->print_time_begin();
    this->print_time_now();
    this->print_time_running();
    this->print_time_split();
}


////~~~~


/*
    public
*/
void rsa306b::print_time_now()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no timing data to print\n");
        #endif
        return;
    }
    this->record_time_now();
    printf("\nnow time >>>\n");
    printf("\tseconds:        %ld\n",
        this->current_time_seconds);
    printf("\tnano seconds:  %ld\n", 
        this->current_time_nano_seconds);
    printf("\tcounter:        %ld\n", 
        this->current_time_stamp);
    this->record_date_time_stamp(
        this->current_time_seconds, 
        this->current_time_nano_seconds);
    printf("\t%s\n", this->date_time_stamp);
}


////~~~~


/*
    public
*/
void rsa306b::print_time_running()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no timing data to print\n");
        #endif
        return;
    }
    this->record_running_time();
    printf("\ntotal running time>>>\n");
    printf("\t%lf  seconds\n", 
        this->seconds_since_reference_time_set);
}


////~~~~


/*
    public
*/
void rsa306b::print_time_split()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no timing data to print\n");
        #endif
        return;
    }
    this->record_time_split();
    printf("\ntime split >>>\n");
    printf("\t%lf  seconds\n", 
        this->time_split);
}

////~~~~


/*
    private
    creates a date time stamp in member "date_time_stamp" string
    dts_YYYY_MM_DD_dayOfWeek_HH_MM_SS_timeZone_nano_NSEC
*/
void rsa306b::record_date_time_stamp
(
    time_t time_in, 
    uint64_t nano_in
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, can't make a date time stamp\n");
        #endif
        return;
    }
    memset(this->date_time_stamp, '\0', BUF_B);
    struct tm * tm_ptr = NULL;
    tm_ptr = gmtime(&time_in);
    if (tm_ptr == NULL)
    {    
        #ifdef DEBUG_MIN
            printf("error in <time.h>\n");
        #endif
        return;
    }
    strftime(this->date_time_stamp, BUF_B,
        "dts_%Y_%m_%d_%a_%H_%M_%S_%Z_nano_", tm_ptr);
    snprintf(this->helper_string, BUF_E-1, "%ld", nano_in);
    strcat(this->date_time_stamp, this->helper_string);
}


////~~~~


/*
    private
    updates member "seconds_since_reference_time_set"
*/
void rsa306b::record_running_time()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, no running time\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::REFTIME_GetIntervalSinceRefTimeSet(
        &this->seconds_since_reference_time_set);
    this->error_check();
}


////~~~~


/*
    private
    called from constructor
    should be the only call this function once
    "reference_time_*" members are set for the life of the object
    the time split is prepared
    time stamp sampling rate is received
*/
void rsa306b::record_start_time()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, can't record start time\n");
        #endif
        return;
    }
    this->record_time_split();
    this->api_return_status = RSA_API::REFTIME_GetReferenceTime(
        &this->reference_time_seconds, 
        &this->reference_time_nano_seconds, 
        &this->reference_time_stamp);
    this->error_check();
    this->update_time_stamp_rate();
    
}


////~~~~


/*
    private
    updates members "current_time_*"
    call before operation requiring the current time
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
    updates member "time_split"
    updates member "time_split_trail", to follow a new interval
*/
void rsa306b::record_time_split()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, can't make a time split\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::REFTIME_GetIntervalSinceRefTimeSet(&this->time_split_lead);
    this->error_check();
    this->time_split = this->time_split_lead - this->time_split_trail;

    this->api_return_status = RSA_API::REFTIME_GetIntervalSinceRefTimeSet(&this->time_split_trail);
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


////~~~~


/*
    private
    called to set time stamp sampling rate
    good to call occasionally in case any temperature changes occur
*/
void rsa306b::update_time_stamp_rate()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device not connected, can't update time stamp rate\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::REFTIME_GetTimestampRate(
        &this->time_stamp_sampling_rate);
    this->error_check();
}


////////~~~~~~~~END>  rsa306b_class_REFTIME.cpp
