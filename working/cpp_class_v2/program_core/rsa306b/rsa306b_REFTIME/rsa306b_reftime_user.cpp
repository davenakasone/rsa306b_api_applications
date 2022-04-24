/*
    API group "REFTIME", user functions

    public :
        < 1 >  reftime_reset()
        < 2 >  reftime_get_vars()
        < 3 >  reftime_timestamp_2_time()
        < 4 >  reftime_time_2_timestamp()
        < 5 >  reftime_make_dts()
        < 6 >  reftime_split_begin()
        < 7 >  reftime_split_end()
    
    private :
        #  none

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::reftime_reset()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_vars.gp.api_status = 
        RSA_API::REFTIME_SetReferenceTime(0, 0, 0);
    this->_gp_confirm_api_status();
    this->_reftime_get_start();
}


////~~~~


/*
    < 2 > public
*/
void rsa306b_class::reftime_get_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->reftime_make_dts();
    this->_reftime_get_vars();
}


////~~~~


/*
    < 3 > public
*/
void rsa306b_class::reftime_timestamp_2_time()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_vars.gp.api_status =
        RSA_API::REFTIME_GetTimeFromTimestamp(
            this->_vars.reftime.helper.timestamp,
            &this->_vars.reftime.helper.seconds,
            &this->_vars.reftime.helper.nanos);
    this->_gp_confirm_api_status();
    this->_reftime_copy_helper();
}


////~~~~


/*
    < 4 > public
*/
void rsa306b_class::reftime_time_2_timestamp()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_vars.gp.api_status =
        RSA_API::REFTIME_GetTimestampFromTime(
            this->_vars.reftime.helper.seconds,
            this->_vars.reftime.helper.nanos,
            &this->_vars.reftime.helper.timestamp);
    this->_gp_confirm_api_status();
    this->_reftime_copy_helper();
}


////~~~~


/*
    < 5 > public
*/
void rsa306b_class::reftime_make_dts()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_reftime_get_current();
    memset(this->_vars.reftime.dts, '\0', BUF_C);
    struct tm * tm_ptr = NULL;
    tm_ptr = gmtime(&this->_vars.reftime.current.seconds);
    if (tm_ptr == NULL)
    {    
        #ifdef DEBUG_MIN
            printf("\n\terror in <time.h>\n");
        #endif
        return;
    }
    strftime(this->_vars.reftime.dts, BUF_C,
        "dts_%Y_%m_%d_%a_%H_%M_%S_%Z_nano_", tm_ptr);
    snprintf(this->_vars.gp.helper, BUF_E-1, "%ld", 
        this->_vars.reftime.current.nanos);
    strcat(this->_vars.reftime.dts, this->_vars.gp.helper);
    this->_reftime_copy_dts();
}


////~~~~


/*
    < 6 > public
*/
void rsa306b_class::reftime_split_begin()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_reftime_get_running_duration();
    this->_vars.reftime.split_trail = this->_vars.reftime.running_duration;
    this->_reftime_copy_split_trail();
}


////~~~~


/*
    < 7 > public
*/
void rsa306b_class::reftime_split_end()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MAX
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_reftime_get_running_duration();
    this->_vars.reftime.split_duration = 
        this->_vars.reftime.running_duration - this->_vars.reftime.split_trail;
    this->_reftime_copy_split_duration();
}
        

////////~~~~~~~~END>  rsa306b_reftime_user.cpp
