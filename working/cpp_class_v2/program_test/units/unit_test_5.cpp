/*
    unit test # 5, API group "TRIG"

    this section is used to configure the trigger

    goals:
        - getters, setters, copiers working correctly
        - the trigger can be set
        - notice the trigger works, even if the device is not running
*/

#include "../testz.h"

//#define UT5_a 1    // basic test
#define UT5_b 2    // set trigger
//#define UT5_c 3    // a few forces


void unit_test_5 (void)
{
    printf("\n%s()  ,  API group 'TRIG'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();

        #ifdef UT5_a
            rsa.print_trig();
            rsa.get_everything();
            rsa.print_trig();
        #endif
        #ifdef UT5_b
            rsa.vars.trig.if_power_level = 6;
            rsa.vars.trig.mode_select = RSA_API::triggered;
            rsa.vars.trig.position_percent = 20.2222;
            rsa.vars.trig.transition_select = RSA_API::TriggerTransitionEither;
            rsa.trig_set_vars();
            rsa.print_trig();

            rsa.vars.config.reference_level_dbm = -35;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();

            rsa.vars.spectrum.settings_type.rbw = 1e3;
            rsa.vars.spectrum.settings_type.span = 1e6;
            rsa.spectrum_set_vars();

            for(int ii = 0; ii < 9; ii++)
            {
                rsa.trig_force();
                printf("%3d)  trigger forced\n", ii);
            }
            
        #endif
        #ifdef UT5_c
            //rsa.trig_force();
            //rsa.device_run();
            for(int ii = 0; ii < 9; ii++)
            {
                rsa.trig_force();
            }
            rsa.device_stop();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_5.cpp
