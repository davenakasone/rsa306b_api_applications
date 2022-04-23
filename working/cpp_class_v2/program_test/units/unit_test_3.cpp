/*
    unit test # 3, API group "ALIGN"

    this is a small function group, but alignement is important

    goals:
        - alignment information is accessed correctly
        - the device self-alignment executes correctly
*/

#include "../testz.h"


void unit_test_3 (void)
{
    printf("\n%s()  ,  API group 'ALIGN'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;

        rsa.device_connect();
        rsa.print_align();
        rsa.align_check_is_needed();
        rsa.align_check_is_warmed();
        printf("needs alignment=  %d  ,  is warmed=  %d\n",
            rsa.vars.align.is_needed, rsa.vars.align.is_warmed);
        
        rsa.align_run();
        rsa.print_align();
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_3.cpp
