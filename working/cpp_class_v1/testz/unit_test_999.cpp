/*
    unit test # 999    ...use a "vvv_###.cpp" for something specific

    goals:
        - 
        - 
        - 
    
    this a just a place holder
    hopefully the object can be made in less than 1,000 unit tests
        if not, make this "9999" and continue
        Thomas Edison tried about 10,000 times to make a light bulb?
*/

#include "unit_tests.h"


void unit_test_999 (void)
{
    printf("\n%s()  ,  some data printing\n", __func__);
    {
        rsa306b rsa;
        rsa.device_connect();

        rsa.print_constants();
        rsa.print_variables();
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_999.cpp
