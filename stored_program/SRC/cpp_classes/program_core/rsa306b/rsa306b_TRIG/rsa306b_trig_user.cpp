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
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    this->_vars.gp.call_status = this->_trig_set_vars();
    if (this->_vars.gp.call_status != this->constants.CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "error setting TRIG group");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
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
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "device not connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
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
        snprintf(X_ddts, sizeof(X_ddts), "trigger forced>>>  %s", this->_vars.device.error_string);
        snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(false);
    #endif
}


////////~~~~~~~~END>  rsa306b_trig_user.cpp
