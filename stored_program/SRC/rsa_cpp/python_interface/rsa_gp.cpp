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
    static int juicy;
    juicy = X_rsa.get_api_status_number();
    return juicy;
}

// < 2 >
char* api_status_message()
{
    static char juicy[BUF_E];
    memset(juicy, '\0', sizeof(juicy));
    (void)strcpy(juicy, X_rsa.get_api_status_string());
    return juicy;
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  rsa_gp.cpp
