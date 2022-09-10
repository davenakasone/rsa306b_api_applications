/*
    unit test # 0, "catch all"

    goals:
        - 
        - 
        - 
    
    this a just a place holder
    it is the basis for "unit_test_*" and "task_*" testing files

    1) information about what test or task is executing, timer split begins
    2) test or task executes
    3) program may be suspended to view output, timer split ends
*/

#include "../testz.h"
// extern rsa306b_class X_rsa;
// extern r3f_manager_class X_r3f;
// extern siq_manager_class X_siq;
// extern timer_class X_timer;


void unit_test_0 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  a test template\n", __func__);
X_timer.time_split_start();                      
#endif    
////~~~~

    printf("\n\ttest executes...\n");    // test something

////~~~~
#ifdef WAIT_ENTER_CLEAR
X_timer.time_split_stop();
X_timer.print_both();
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////////~~~~~~~~END>  unit_test_0.cpp
