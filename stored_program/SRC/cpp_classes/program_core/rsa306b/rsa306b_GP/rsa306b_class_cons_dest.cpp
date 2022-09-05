/*
    the class constructor and destructor
*/

#include "../rsa306b_class.h"


rsa306b_class::rsa306b_class()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  constructor\n",
        __LINE__, __FILE__, __func__);
#endif
#ifdef DEBUG_MIN
    printf("\n\tinstance constructed\n");
#endif

    this->_init_everything();
}


////~~~~


rsa306b_class::~rsa306b_class()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  destructor\n",
        __LINE__, __FILE__, __func__);
#endif
#ifdef DEBUG_MIN
    printf("\n\tinstance destroyed\n");
#endif

    this->device_disconnect();
}


////////~~~~~~~~END>  rsa306b_constructor.cpp
