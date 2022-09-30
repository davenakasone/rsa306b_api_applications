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

#ifdef UNIT_TESTING


void unit_test_0 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  a unit test template\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    (void)printf("\n\ta unit test executes...\n");    // test something

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_0.cpp
