/*
    implementation of the rsa306b_class
    using "REFTIME" function group of the API
    getters and setters for member variables

        public:
            < 1 >  reftime_get_date_timestamp()
            < 2 >  reftime_get_running()
            < 3 >  reftime_get_split()
            < 4 >  reftime_get_source()
            < 5 >  reftime_get_timestamp_rate()
            < 6 >  reftime_get_begin_type()
            < 7 >  reftime_get_current_type()
            < 8 >  reftime_get_split_cpu()
            < 9 >  rectime_get_running_cpu()

        private:
            # none
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    provides date-time-stamp as a string if device is connected
    ensure char* dts is at least BUF_C in size before calling
*/
void rsa306b::reftime_get_date_timestamp
(
    char* dts
)
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
    if (dts == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdate-time-stamp string not allocated\n");
        #endif
        return;
    }
    this->_reftime_set_date_timestamp();
    strcpy(dts, this->_reftime_date_timestamp);
}


////~~~~


/*
    public < 2 >
    updates the running time, then returns value
*/
double rsa306b::reftime_get_running()
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
    }
    this->_reftime_set_running();
    return this->_reftime_running;
}


////~~~~


/*
    public < 3 >
    returns the time split, but call:
        start_split
        stop_split
    returns value of the time split in seconds
*/
double rsa306b::reftime_get_split()
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
    }
    return this->_reftime_split;
}


////~~~~


/*
    public < 4 >
    returns enum value, indicating source of the time
    with the RSA-306B, it will almost always be internal
*/
RSA_API::REFTIME_SRC  rsa306b::reftime_get_source_select()
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
    }
    this->_reftime_set_source_select();
    return this->_reftime_source_select;
}


////~~~~


/*
    public < 5 >
    ensures caller gets updated time-stamp sample rate
*/
uint64_t rsa306b::reftime_get_timestamp_rate()
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
    }
    this->_reftime_set_timestamp_rate();
    return this->_reftime_timestamp_rate;
}


////~~~~


/*
    public < 6 >
    caller recieves beginning time
*/
void rsa306b::reftime_get_begin_type
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
            printf("\n\tno device connected, no timing availible\n");
        #endif
        return;
    }
    r_t->seconds = this->_reftime_begin_type.seconds;
    r_t->nanos = this->_reftime_begin_type.nanos;
    r_t->stamp = this->_reftime_begin_type.stamp;
}


////~~~~


/*
    public < 7 >
    caller receives updated time
*/
void rsa306b::reftime_get_current_type
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
            printf("\n\tno device connected, no timing availible\n");
        #endif
        return;
    }
    this->_reftime_set_current_type();
    r_t->seconds = this->_reftime_current_type.seconds;
    r_t->nanos = this->_reftime_current_type.nanos;
    r_t->stamp = this->_reftime_current_type.stamp;
}


////~~~~


/*
    public < 8 >
    returns the time split, but call:
        start_split
        stop_split
    returns value of the time split in seconds, 
        using CPU clock
*/
double rsa306b::reftime_get_split_cpu()
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
    }
    return this->_reftime_cpu.split;
}


////~~~~


/*
    public < 9 >
    updates the running time, then returns value
        uses CPU clock
*/
double rsa306b::reftime_get_running_cpu()
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
    }
    clock_t temp = clock();
    this->_reftime_cpu.running = ( ((double)temp) - 
        ((double)this->_reftime_cpu.begin) ) / CLOCKS_PER_SEC;
    return this->_reftime_cpu.running;
}

////////~~~~~~~~END>  rsa306b_class_REFTIME_get.cpp
