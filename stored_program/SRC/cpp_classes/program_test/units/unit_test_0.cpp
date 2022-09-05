/*
    unit test # 0, "catch all"

    goals:
        - 
        - 
        - 
    
    this a just a place holder
    it is the basis for "unit_test_*" and "task_*" testing files
*/

#include "../testz.h"
extern rsa306b_class X_rsa;
extern r3f_manager_class X_r3f;
extern siq_manager_class X_siq;


void unit_test_0 (void)
{
    printf("\n%s()  ,  a test template\n", __func__);
    {
        cpu_timer_class cpu;
        X_rsa.device_disconnect();
        X_rsa.device_connect();
        
        printf("\n\ttest executes...\n");
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_0.cpp
