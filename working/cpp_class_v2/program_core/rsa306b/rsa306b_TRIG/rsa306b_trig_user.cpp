/*
    API group "TRIG", user functions

    public :
        < 1 >  trig_set_vars()
        < 2 >  trig_force()
    
    private :
        #  none

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    user updates "vars.trig.*" variables
    new values are set if they are valid
*/
void rsa306b_class::trig_set_vars()
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

    this->_vars.gp.call_status = this->_trig_set_vars();
    if (this->_vars.gp.call_status != this->_vars.constants.CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\terror setting trig parameters\n");
        #endif
        return;
    }
}


////~~~~


/*
    < 2 > private
    user calls "device_run()", 
    this fucntion forces the trigger when the device is running
    user should call "device_stop()" if work is complete
*/
void rsa306b_class::trig_force()
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
    /*
    if (this->_vars.device.is_running == false) // not needed, but could be nice
    {
        #ifdef DEBUG_MIN
            printf("\n\tthe device must be running to force the trigger\n");
        #endif
        return;
    }
    */
    this->_vars.gp.api_status = RSA_API::TRIG_ForceTrigger();
    this->_gp_confirm_api_status();
    #ifdef DEBUG_MAX
        printf("\n\ttrigger forced>>>  %s\n",
            this->_vars.device.error_string);
    #endif
}


////////~~~~~~~~END>  rsa306b_trig_user.cpp
