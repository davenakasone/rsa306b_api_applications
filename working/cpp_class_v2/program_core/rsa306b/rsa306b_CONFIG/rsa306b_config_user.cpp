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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = RSA_API::CONFIG_Preset();
    this->_gp_confirm_api_status();
    this->get_everything();    // it effects other API groups
}


////~~~~


/*
    < 2 > public
*/
void rsa306b_class::config_set_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_config_set_vars();
}



////////~~~~~~~~END>  rsa306b_config_user.cpp
