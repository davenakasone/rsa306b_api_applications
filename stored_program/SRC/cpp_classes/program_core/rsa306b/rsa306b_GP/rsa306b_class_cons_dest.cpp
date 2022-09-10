/*
    the class constructor and destructor
*/

#include "../rsa306b_class.h"


rsa306b_class::rsa306b_class()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    snprintf(X_dstr, DEBUG_WIDTH-1, DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record();
#endif

    this->_init_everything();
}


////~~~~


rsa306b_class::~rsa306b_class()
{
#ifdef DEBUG_CLI
    if (X_dfp != NULL)
    {
        snprintf(X_dstr, DEBUG_WIDTH-1, DEBUG_CLI_FORMAT, 
            __LINE__, __FILE__, __func__);
        debug_record();
    }
#endif

    this->device_disconnect();

#ifdef DE_BUG
    debug_stop();
#endif
}


////////~~~~~~~~END>  rsa306b_constructor.cpp
