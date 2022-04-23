/*
    unit test # 0, "catch all"

    goals:
        - 
        - 
        - 
    
    this a just a place holder
    it is the basis for "unit_test_*" and "task_*" testing files
*/

#include "testz.h"


void unit_test_0 (void)
{
    printf("\n%s()  ,  a test template\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        
        printf("\n\ttest executes...\n");
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_0.cpp
