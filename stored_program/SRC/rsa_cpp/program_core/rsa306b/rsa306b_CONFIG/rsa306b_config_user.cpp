/*
    API group "CONFIG"

    public :
        < 1 >  config_preset()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::config_preset()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    (void)this->device_stop();

    RSA_API::ReturnStatus temp = RSA_API::CONFIG_Preset();    // effects other API groups
    (void)this->get_everything();                             // to ensure member variables are updated
    return this->set_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_config_user.cpp
