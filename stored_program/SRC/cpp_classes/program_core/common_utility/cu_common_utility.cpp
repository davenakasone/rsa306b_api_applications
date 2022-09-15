/*
    common_utility, class 

    public :
        < 1 >  common_utility()
        < 2 >  ~common_utility()
        
    private :
        #  none
*/

#include "common_utility.h"
/*
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
//
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 
//
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
//
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
//
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
//
#ifdef DEBUG_MIN
    (void)snprintf(X_ddts, sizeof(X_ddts), "<your message> + extra");
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
    debug_record(true);
#endif
//
#ifdef DEBUG_MAX
    (void)snprintf(X_ddts, sizeof(X_ddts), "<your message> + extra");
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
    debug_record(false);
#endif
//
#ifdef DEBUG_CUSTOM
    (void)snprintf(X_ddts, sizeof(X_ddts), "<your message> + extra");
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CUSTOM_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
    debug_record(true);
#endif
*/


/*
    < 1 > public
*/
common_utility::common_utility()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)this->_timer_init();
}


////~~~~


/*
    < 2 > public
*/
common_utility::~common_utility()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef DEBUGS_WILL_PRINT
    (void)this->timer_print_both(1,2);
#endif

#ifdef DE_BUG
    debug_stop();
#endif
}


////////~~~~~~~~END>  cu_common_utility.cpp
