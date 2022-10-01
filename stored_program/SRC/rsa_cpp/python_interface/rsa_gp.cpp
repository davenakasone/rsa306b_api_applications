/*
    source code for the python interface
    API group 'GP'

        < 1 >  int api_status()
        < 2 >  api_status_message()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
int api_status()
{
    return X_rsa.get_api_status_number();
}

// < 2 >
char* api_status_message()
{
    return X_rsa.get_api_status_string();
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_gp.cpp
