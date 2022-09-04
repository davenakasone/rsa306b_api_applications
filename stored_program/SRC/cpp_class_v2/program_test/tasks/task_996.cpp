/*
    begin Fall 2022 semester
*/

#include "../testz.h"


void task_996()
{
    printf("\n%s()  ,  EE498\n", __func__);
    {
        cpu_timer_class cpu;
        task_998();
        task_991();

        unit_test_5();
        unit_test_6();
        unit_test_7();
        unit_test_8();
        unit_test_9();
        unit_test_10();
        unit_test_11();

        task_997();
        task_995();
    }
    printf("\n%s()  ,  demonstration complete\n", __func__);
    // #ifdef WAIT_ENTER_CLEAR
    //     wait_enter_clear();
    // #endif
}


/////////~~~~~~~~END>  task_996.cpp
