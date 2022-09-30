/*
    unit test # 3, API group "ALIGN"

    this is a small function group, but alignement is important

    goals:
        - alignment information is accessed correctly
        - the device self-alignment executes correctly
*/

#include "../testz.h"

#ifdef UNIT_TESTINGG


void unit_test_3 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  API group 'ALIGN'\n", __func__);
//X_timer.time_split_start();                      
#endif    
////~~~~

    X_rsa.device_connect();
    X_rsa.print_align();
    X_rsa.align_check_is_needed();
    X_rsa.align_check_is_warmed();
    printf("needs alignment=  %d  ,  is warmed=  %d\n",
        X_rsa.vars.align.is_needed, X_rsa.vars.align.is_warmed);
    
    X_rsa.align_run();
    X_rsa.print_align();

////~~~~
#ifdef WAIT_ENTER_CLEAR
// X_timer.time_split_stop();
// X_timer.print_both();
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif


////////~~~~~~~~END>  unit_test_3.cpp
