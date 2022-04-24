/*
    the constructor and destructor of the constant class are inert
    they could be used for future development
*/

#include "rsa306b_constants_class.h"


rsa306b_constants_class::rsa306b_constants_class()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()  ,  constructor\n",
        __LINE__, __FILE__, __func__);
#endif
#ifdef DEBUG_MAX
    printf("\n\tinstance constructed\n");
#endif

}


////~~~~


rsa306b_constants_class::~rsa306b_constants_class()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()  ,  destructor\n",
        __LINE__, __FILE__, __func__);
#endif
#ifdef DEBUG_MAX
    printf("\n\tinstance destroyed\n");
#endif

}


////////~~~~~~~~END>  rsa306b_constants_constructor.cpp
