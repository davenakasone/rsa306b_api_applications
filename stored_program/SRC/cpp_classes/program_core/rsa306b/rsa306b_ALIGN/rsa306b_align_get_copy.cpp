/*
    API group "ALIGN", getters and copiers

    public :
        #  none
    
    private :
        < 1 >  _align_get_vars()       
        < 2 >  _align_get_is_needed()
        < 3 >  _align_get_is_warmed()
        < 4 >  _align_copy_vars()
        < 5 >  _align_copy_is_needed()
        < 6 >  _align_copy_is_warmed()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_align_get_vars()
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
    this->device_stop();
    this->_align_get_is_needed();
    this->_align_get_is_warmed();
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_align_get_is_needed()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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
    this->device_stop();
    this->_vars.gp.api_status = 
        RSA_API::ALIGN_GetAlignmentNeeded(&this->_vars.align.is_needed);
    this->_gp_confirm_api_status();
    this->_align_copy_is_needed();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_align_get_is_warmed()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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
    this->device_stop();
    this->_vars.gp.api_status = 
        RSA_API::ALIGN_GetWarmupStatus(&this->_vars.align.is_warmed);
    this->_gp_confirm_api_status();
    this->_align_copy_is_warmed();
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_align_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_align_copy_is_needed();
    this->_align_copy_is_warmed();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_align_copy_is_needed()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.align.is_needed = this->_vars.align.is_needed;
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_align_copy_is_warmed()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.align.is_warmed = this->_vars.align.is_warmed;
}

////////~~~~~~~~END>  rsa306b_align_get_copy.cpp
