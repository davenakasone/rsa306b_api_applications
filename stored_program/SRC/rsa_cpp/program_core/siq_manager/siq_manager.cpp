/*
    common funtions of the 'siq_handler_class'

    public:
        < 1 >  siq_handler_class()
        < 2 >  ~siq_handler_class()
        < 3 >  clear()

    private:
        #  none
*/

#include "siq_manager_class.h"

/*
    < 1 > public
    constructor
*/
siq_manager_class::siq_manager_class()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)this->_init();
}


////~~~~


/*
    < 2 > public
    destructor
*/
siq_manager_class::~siq_manager_class()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef DE_BUG
    debug_stop();
#endif
}


//~~~~


/*
    < 3 > public
    clear the instance
*/
CODEZ siq_manager_class::clear()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif    

    return this->_init();
}


////////~~~~~~~~END>  siq_manager.cpp
