/*
    unit test # 4

    goals:
        - proper device and class operation
        - get and set "ALIGN" members
        - an alignment can be performed by the class
*/

#include "unit_tests.h"

void ut4_print_vars(bool needA, bool isW);


void unit_test_4 (void)
{
    printf("\n%s()  ,  testing the 'ALIGN' section of the class\n", __func__);
    {
        bool needAlign = false;
        bool isWarmed = false;
        rsa306b rsa;    // constructor is called

        // rejected, device not connected
        isWarmed = rsa.align_get_is_warmed();
        needAlign = rsa.align_get_need_alignment();
        rsa.align_execute_alignment();
        ut4_print_vars(needAlign, isWarmed);
        rsa.align_print_all();

        // should work, alginment automatic with connection
        rsa.device_connect();
        isWarmed = rsa.align_get_is_warmed();
        needAlign = rsa.align_get_need_alignment();
        ut4_print_vars(needAlign, isWarmed);
        rsa.align_print_all();
        rsa.device_disconnect();

        // try on running device
        rsa.device_connect();
        rsa.device_run();
        rsa.align_execute_alignment();
        isWarmed = rsa.align_get_is_warmed();
        needAlign = rsa.align_get_need_alignment();
        ut4_print_vars(needAlign, isWarmed);
        rsa.align_print_all();
    }
    // instance goes out of scope and destructor is called
    printf("\nwarm-up status is not very important, the device warms up fast\n");
    printf("\tisOverTemperature is much more important\n");
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////~~~~


void ut4_print_vars
(
    bool needA, 
    bool isW
)
{
    printf("\ngot 'ALIGN' variables:\n");
    printf("\tneed to align?  :  %d\n", needA);
    printf("\tis warmed up?   :  %d\n", isW);
}


////////~~~~~~~~END>  unit_test_4.cpp
