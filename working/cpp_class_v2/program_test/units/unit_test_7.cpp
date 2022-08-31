/*
    unit test # 7, "CONFIG"

    the configuration of the spectrum analyzer is very important

    goals:
        - getting, setting, copying, and gaurds work
        - valid configurations and changes are always passed to the device
*/

#include "../testz.h"

//#define UT7_a 1 // basic use
#define UT7_b 2 // check preseter


void unit_test_7 (void)
{
    printf("\n%s()  ,  API group 'CONFIG'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();
        
        #ifdef UT7_a
            rsa.print_config();
            rsa.vars.config.center_frequency_hz = 20;
            rsa.config_set_vars();

            rsa.vars.config.center_frequency_hz = 2.43e9;
            rsa.vars.config.reference_level_dbm = -25.987;
            rsa.config_set_vars();
            rsa.print_config();
        #endif
        #ifdef UT7_b
            rsa.vars.config.reference_level_dbm = 0.69;
            rsa.vars.config.center_frequency_hz = 23.567e4;
            rsa.config_set_vars();
            rsa.print_config();

            rsa.config_preset();
            rsa.print_config();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_7.cpp
