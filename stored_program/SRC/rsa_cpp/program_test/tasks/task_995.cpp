/*
    further evaluation of the trigger
    use the 315 MHz

    focus on the power-level trigger, the time trigger was never really developed by Tektronix
    the background is noisy in Las Vegas, set the trigger level above it (or it triggers on everything)

    this is the experimentation for builing special function "triggered_dump()"
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_995()
{
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_start(); 
#endif                   
//~
    (void)X_util.clear_data();
    X_rsa.device_connect();

    // DEVICE, ensure trigger event is set as query
    X_rsa.vars.device.event_id = static_cast<int>(RSA_API::DEVEVENT_TRIGGER);

    // CONFIG, always must set this
    X_rsa.vars.config.center_frequency_hz = 315.0e6;
    X_rsa.vars.config.reference_level_dbm = -1.99;
    X_rsa.vars.config.frequency_reference_source_select = RSA_API::FREQREF_SOURCE::FRS_INTERNAL;
    X_rsa.config_set_vars();

    // TRIG, specify the trigger
    X_rsa.vars.trig.if_power_level = -22.2;
    X_rsa.vars.trig.mode_select = RSA_API::TriggerMode::triggered;
    X_rsa.vars.trig.position_percent = X_rsa.vars.trig.POSITION_PERCENT_MAX / 2;
    X_rsa.vars.trig.source_select = RSA_API::TriggerSource::TriggerSourceIFPowerLevel;
    X_rsa.vars.trig.transition_select = RSA_API::TriggerTransitionEither;
    X_rsa.trig_set_vars();

    X_rsa.device_run();
    X_util.timer_split_start();
    while (X_util.timer_get_split_wall() < 10.0)
    {
        if(X_rsa.device_check_event() == true)
        {
            (void)X_rsa.reftime_get_vars();
            printf("trigger event detected: %lu\n", X_rsa.vars.reftime.current.timestamp);
        }
    }
    X_rsa.device_stop();

    X_rsa.device_disconnect();                  
//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


/////////~~~~~~~~END>  task_995.cpp
