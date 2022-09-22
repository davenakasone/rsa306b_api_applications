/*
    API group "TRIG", user functions
    safety is removed for speed

    public :
        < 1 >  trig_force()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    there are no guards in this function
    this function is designed to be fast
    this fucntion forces the trigger when the device is running and triggering has been set
*/
CODEZ rsa306b_class::trig_force()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    (void)this->set_api_status(RSA_API::TRIG_ForceTrigger());

    #ifdef DEBUG_MAX
        (void)snprintf(X_ddts, sizeof(X_ddts), "trigger forced>>>  %s", this->get_api_status_string());
        (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(false);
    #endif

    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_trig_user.cpp
