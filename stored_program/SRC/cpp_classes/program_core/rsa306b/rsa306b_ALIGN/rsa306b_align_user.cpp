/*
    API group "ALIGN", functions for the user

    public :
        < 1 >  align_run()
        < 2 >  align_check_is_needed()
        < 3 >  align_check_is_warmed()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    the alignment process runs
*/
void rsa306b_class::align_run()
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
    
    this->_align_get_is_needed();
    if (this->_vars.align.is_needed == false)
    {
        return;
    }  
    this->_vars.gp.api_status = RSA_API::ALIGN_RunAlignment();
    this->_gp_confirm_api_status();
    this->_align_get_is_needed();
}


////~~~~


/*
    < 2 > public
    query if aligment is needed
*/
void rsa306b_class::align_check_is_needed()
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
    this->_align_get_is_needed();
}


////~~~~


/*
    < 3 > public
    query if device is warmed-up
*/
void rsa306b_class::align_check_is_warmed()
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
    this->_align_get_is_warmed();
}


////////~~~~~~~~END>  rsa306b_align_user.cpp
