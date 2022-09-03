/*
    unit test # 7, "CONFIG"

    the configuration of the spectrum analyzer is very important

    goals:
        - getting, setting, copying, and gaurds work
        - valid configurations and changes are always passed to the device
*/

#include "../testz.h"
extern rsa306b_class X_rsa;


void unit_test_7 (void)
{
    printf("\n%s()  ,  API group 'CONFIG'\n", __func__);
    {
        cpu_timer_class cpu;
        X_rsa.device_disconnect();
        X_rsa.device_connect();
        
        X_rsa.print_config();
        
        X_rsa.vars.config.center_frequency_hz = 2.43e9;
        X_rsa.vars.config.reference_level_dbm = -25.987;
        X_rsa.config_set_vars();
        X_rsa.print_config();

        X_rsa.config_preset();
        X_rsa.print_config();
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_7.cpp
