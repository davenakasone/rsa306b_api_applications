/*
    unit test # 5, API group "TRIG"

    this section is used to configure the trigger

    goals:
        - getters, setters, copiers working correctly
        - the trigger can be set
        - notice the trigger works, even if the device is not running
*/

#include "../testz.h"

#define UT5_a 1    // basic test
#define UT5_b 2    // set trigger


void unit_test_5 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  API group 'TRIG'\n", __func__);
//X_timer.time_split_start();                      
#endif    
////~~~~

    X_rsa.device_disconnect();
    X_rsa.device_connect();

    #ifdef UT5_a
        X_rsa.get_everything();
        X_rsa.print_trig();

        X_rsa.vars.trig.if_power_level    = 6;
        X_rsa.vars.trig.mode_select       = RSA_API::triggered;
        X_rsa.vars.trig.position_percent  = 20.2222;
        X_rsa.vars.trig.transition_select = RSA_API::TriggerTransitionEither;
        X_rsa.trig_set_vars();
        X_rsa.print_trig();

        X_rsa.vars.config.reference_level_dbm = -35;
        X_rsa.vars.config.center_frequency_hz = 100e6;
        X_rsa.config_set_vars();

        X_rsa.vars.spectrum.settings_type.rbw  = 1e3;
        X_rsa.vars.spectrum.settings_type.span = 1e6;
        X_rsa.spectrum_set_vars();

        for(int ii = 0; ii < 9; ii++)
        {
            X_rsa.trig_force();
            printf("%3d)  trigger forced\n", ii);
        }
        X_rsa.print_trig();
    #endif

////~~~~
#ifdef WAIT_ENTER_CLEAR
// X_timer.time_split_stop();
// X_timer.print_both();
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////////~~~~~~~~END>  unit_test_5.cpp
