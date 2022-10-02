/*
    common_utility, class 

    public :
        < 1 >  common_utility()
        < 2 >  ~common_utility()
        < 3 >  clear()

    private :
        #  none
*/

#include "common_utility.h"


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

    (void)this->clear();    // any higher-level classes can count on this composed class being initialized
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

#ifdef DE_BUG
    debug_stop();
#endif
}


////~~~~


/*
    < 3 > public
*/
CODEZ common_utility::clear()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)memset(this->helper, '\0', sizeof(this->helper));
    (void)memset(this->holder, '\0', sizeof(this->holder));
    (void)memset(this->_worker, '\0', sizeof(this->_worker));
    this->filez_in.clear();
    this->filez_out.clear();
    return this->_timer_init();
}


////////~~~~~~~~END>  cu_common_utility.cpp
