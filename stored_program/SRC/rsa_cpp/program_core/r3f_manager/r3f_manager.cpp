/*
    "r3f_manager_class", public

        public:
            < 1 >  r3f_manager_class()
            < 2 >  ~r3f_manager_class()
            < 3 >  clear()

        private:
            #  none
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    only constructor of the class
*/
r3f_manager_class::r3f_manager_class()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)this->_init();
}


////~~~~


/*
    public < 2 >
    there can only be 1 destructor
*/
r3f_manager_class::~r3f_manager_class()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef DE_BUG
    debug_stop();
#endif
}


////~~~~


/*
    public < 3 >
    clears variables when user needsd it
*/
CODEZ r3f_manager_class::clear()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_init();
}


////////~~~~~~~~END>  r3f_manager.cpp
