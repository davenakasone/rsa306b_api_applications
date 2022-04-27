/*
    unit test # 8, "SPECTRUM"

    this group is fundametal to correct spectrum analysis

    goals:
        - getting, setting, copying, and gaurds work
        - valid configurations and changes are always passed to the device
*/

#include "../testz.h"

#define UT8_a 1 // basic use


void unit_test_8 (void)
{
    printf("\n%s()  ,  API group 'SPECTRUM'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();
        
        #ifdef UT8_a
            rsa.print_spectrum();
        #endif
        #ifdef UT8_b
            
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_8.cpp
