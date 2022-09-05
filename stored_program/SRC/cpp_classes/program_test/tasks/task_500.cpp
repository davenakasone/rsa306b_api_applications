/*
    preparing global instances for use in the shared object
    "dynamically linked library"
    this is the first step in making the program interfacable with other languages

    C++ was chosen as the core language because of the speed, data structures, and control
    once compiled (and tested), this shared library can be applied generally
*/

#include "../testz.h"
extern rsa306b_class X_rsa;
extern r3f_manager_class X_r3f;
extern siq_manager_class X_siq;


void task_500()
{
    printf("\n%s()  ,  try the global variables\n", __func__);
    {
        X_rsa.device_connect();
        cpu_timer_class cpu;
    }
    printf("\n%s()  ,  test complete\n", __func__);
}


/////////~~~~~~~~END>  task_500.cpp
