/*
    unit test # 10, API group "IQBLK"

    this section directly streams the IQ block
    useful if processing is needed without the "*.sig" file

    goals:
        - getters, setters, copiers working correctly
        - IQBLK can be streamed, acquired, and processed
*/

#include "../testz.h"

#define UT10_a 1    // basic test, get, set, print
 

void unit_test_10 (void)
{
    printf("\n%s()  ,  API group 'IQBLK'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();

        #ifdef UT10_a
            rsa.print_iqblk();

            rsa.vars.iqblk.getter = IQBLK_GET_IQ_DATA_CPLX;
            rsa.vars.iqblk.record_length = 4444;
            rsa.vars.iqblk.bandwidth_hz = 1234.5678;
            rsa.iqblk_set_vars();

            rsa.print_iqblk();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_10.cpp
