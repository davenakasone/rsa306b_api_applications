/*
    unit test # 3, API group "ALIGN"

    this is a small function group, but alignement is important

    goals:
        - alignment information is accessed correctly
        - the device self-alignment executes correctly
*/

#include "../testz.h"
extern rsa306b_class X_rsa;


void unit_test_3 (void)
{
    printf("\n%s()  ,  API group 'ALIGN'\n", __func__);
    {
        cpu_timer_class cpu;

        X_rsa.device_connect();
        X_rsa.print_align();
        X_rsa.align_check_is_needed();
        X_rsa.align_check_is_warmed();
        printf("needs alignment=  %d  ,  is warmed=  %d\n",
            X_rsa.vars.align.is_needed, X_rsa.vars.align.is_warmed);
        
        X_rsa.align_run();
        X_rsa.print_align();
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_3.cpp
