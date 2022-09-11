/*
    API group "CONFIG"

    public :
        < 1 >  config_preset()
        < 2 >  config_set_vars()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::config_preset()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = RSA_API::CONFIG_Preset();    // effects other API groups
    this->_gp_confirm_api_status();
    this->get_everything();                                  // "get" to ensure preset values    
}


////~~~~


/*
    < 2 > public
*/
void rsa306b_class::config_set_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_config_set_vars();
}



////////~~~~~~~~END>  rsa306b_config_user.cpp
