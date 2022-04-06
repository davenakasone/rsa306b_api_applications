/*
    unit test # 999    ...use a "vvv_###.cpp" for something specific

    goals:
        - 
        - 
        - 
*/

#include "unit_tests.h"


void unit_test_999 (void)
{
    printf("\n%s()  ,  some data printing\n", __func__);

    rsa306b rsa;
    rsa.device_connect();

    rsa.print_all_const();

    rsa.device_print_all();

    rsa.align_print_all();

    rsa.reftime_print_all();

    rsa.config_print_all();

    rsa.spectrum_print_all();

    rsa.trig_print_all();

    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_999.cpp
