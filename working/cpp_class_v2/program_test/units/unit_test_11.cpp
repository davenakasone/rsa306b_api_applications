/*
    unit test # 11, API group "IQSTREAM"

    goals:
        -  the IQSTREAM variables, getters, setters, copiers are working
        -  validation procedures are enforced during program execution
        -  
*/

#define UT11a 1    // basic test of the group

#include "../testz.h"


void unit_test_11 (void)
{
    printf("\n%s()  ,  API group 'IQSTREAM'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();

        #ifdef UT11a
            rsa.print_iqstream();
            rsa.vars.iqstream.bandwidth = 11.222e6;
            rsa.vars.iqstream.record_time_ms = 3;
            rsa.iqstream_set_vars();
            rsa.print_iqstream();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_11.cpp
