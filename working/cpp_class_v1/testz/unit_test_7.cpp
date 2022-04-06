/*
    unit test # 7, "TRIG" section

    goals:
        - other sections continue to work
        - getters, setters, and blockers work
        - the trigger can be configured
        - test triggering operation with other groups or known signals
*/

#include "unit_tests.h"

//#define UT7_1 1    // getting
//#define UT7_2 2    // setter
#define UT7_3 3    // try tiggering and getting data

void unit_test_7 (void)
{
    printf("\n%s()  ,  testing the 'TRIG' section of the class\n", __func__);
    {
        rsa306b::trig_type trig_t;
        rsa306b rsa;
        rsa.device_connect();

        #ifdef UT7_1
            rsa.trig_print_all();
            rsa.trig_get_settings(&trig_t);
            printf("\ngot the settings, here is the percentage:  %0.3lf\n",
                trig_t.position_percent);
        #endif
        #ifdef UT7_2
            trig_t.if_power_level = 9e9;
            trig_t.mode_select = RSA_API::triggered;
            trig_t.position_percent = 2e3;
            trig_t.source_select = RSA_API::TriggerSourceTime;
            trig_t.transition_select = RSA_API::TriggerTransitionEither;
            rsa.trig_print_all();
            rsa.trig_prepare(&trig_t);
            rsa.trig_print_all();
            trig_t.if_power_level = -10;
            trig_t.mode_select = RSA_API::freeRun;
            trig_t.position_percent = 10;
            trig_t.source_select = RSA_API::TriggerSourceIFPowerLevel;
            trig_t.transition_select = RSA_API::TriggerTransitionEither;
            rsa.trig_prepare(&trig_t);
            rsa.trig_print_all();
        #endif
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_7.cpp
