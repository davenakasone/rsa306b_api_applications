/*
    source code for the python interface
*/



#include "dummy.h"
extern rsa306b_class X_rsa;
extern r3f_manager_class X_r3f;
extern siq_manager_class X_siq;

#ifdef __cplusplus 
extern "C"      
{
#endif


int dummy_plus_plus_by_val(int input_int)
{
    input_int++;          // be very careful of who owns what memory space
    return input_int;     // to successfully interface with python, the memory must presist and be managed
}

void dcon()
{
    X_rsa.device_connect();
}

void print_d()
{
    X_rsa.print_device();
}

// void destructor()                  do not expose this to python
// {
//     X_rsa.~rsa306b_class();
// }

#ifdef __cplusplus      
}
#endif
////////~~~~~~~~END>  dummy.cpp
