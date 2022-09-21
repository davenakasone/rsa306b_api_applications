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
CODEZ rsa306b_class::align_run()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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
    
    (void)this->_align_get_is_needed();
    if (this->_vars.align.is_needed == false)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);
    }  
    (void)this->device_stop();
    
    (void)this->set_api_status(RSA_API::ALIGN_RunAlignment());
    (void)this->_align_get_is_needed();
    if (this->_vars.align.is_needed == false)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);
    } 
    else
    {
        return this->cutil.report_status_code(CODEZ::_21_rsa_api_task_failed);
    } 
}


////~~~~


/*
    < 2 > public
    query if aligment is needed
*/
CODEZ rsa306b_class::align_check_is_needed()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_align_get_is_needed();
}


////~~~~


/*
    < 3 > public
    query if device is warmed-up
*/
CODEZ rsa306b_class::align_check_is_warmed()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_align_get_is_warmed();
}


////////~~~~~~~~END>  rsa306b_align_user.cpp
