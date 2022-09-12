/*
    API group "xxx"

    public :
        < 1 >  xxx()
    
    private :
        < 1 >  _xxx()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::get_everything()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::get_everything()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
//
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
//
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
//
#ifdef DEBUG_GETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
//
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "<your message> + extra");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        //
        #ifdef DEBUG_MAX
            snprintf(X_ddts, sizeof(X_ddts), "<your message> + extra");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(false);
        #endif
        //
        #ifdef DEBUG_CUSTOM
            snprintf(X_ddts, sizeof(X_ddts), "<your message> + extra");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_CUSTOM_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        
        return;
    }
}


////////~~~~~~~~END>  rsa306b_x.cpp
