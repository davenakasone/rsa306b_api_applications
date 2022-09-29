/*
    temporary test bench
        don't keep anything permenant here
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_999()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  a unit test template\n", __func__);
X_util.timer_split_start(); 
#endif                   
////~~~~

    
    (void)printf("\n\ttest bench executes\n");


////~~~~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif

/////////~~~~~~~~END>  task_999.cpp
