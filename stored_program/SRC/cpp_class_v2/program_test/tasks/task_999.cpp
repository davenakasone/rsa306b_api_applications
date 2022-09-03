/*
    temporary test bench
        don't keep anything permenant here
*/

#include "../testz.h"
extern rsa306b_class X_rsa;
extern r3f_manager_class X_r3f;
extern siq_manager_class X_siq;


void task_999()
{
    printf("\n%s()  ,  test bench\n", __func__);
    {
        cpu_timer_class cpu;
        printf("\n\tdo something\n");
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


/////////~~~~~~~~END>  task_999.cpp
