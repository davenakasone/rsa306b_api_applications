/*
    unit test # 7, class [rsa_306b] API group 'TRIG'

    the undocumented API trigger time functions do not work
    you will have to use REFTIME and your custom timers to get the trigger

    goals:

        CODEZ trig_print   ();   
        CODEZ trig_set_vars();    
        CODEZ trig_force   ();   

        these don't work:
        RSA_API_DLL ReturnStatus TRIG_SetTriggerTime(time_t startTimeSec, uint64_t startTimeNsec, uint64_t repeatTimeNsec);
		RSA_API_DLL ReturnStatus TRIG_GetTriggerTime(time_t* startTimeSec, uint64_t* startTimeNsec, uint64_t* repeatTimeNsec);
 
*/

#include "../testz.h"

#ifdef UNIT_TESTING

constexpr double block_ut7 = 22.22;    // seconds to wait before breaking out of a loop
constexpr int bangz_ut7 = 3;


void unit_test_7 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'TRIG'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    X_rsa.device_connect();
    X_rsa.trig_print();

    X_rsa.vars.config.center_frequency_hz = 315.0e6;
    X_rsa.vars.config.reference_level_dbm = -1.99;
    X_rsa.vars.config.frequency_reference_source_select = RSA_API::FREQREF_SOURCE::FRS_INTERNAL;
    X_rsa.config_set_vars();

    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace1] = true; 
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace2] = false;
    X_rsa.vars.spectrum.is_enabled_trace[RSA_API::SpectrumTrace3] = false;
    X_rsa.vars.spectrum.detector_select[RSA_API::SpectrumTrace1] = RSA_API::SpectrumDetector_PosPeak;
    X_rsa.vars.spectrum.settings_type.enableVBW = false;
    X_rsa.vars.spectrum.settings_type.rbw = 10.0e3;
    X_rsa.vars.spectrum.settings_type.span = 10.0e6;
    X_rsa.vars.spectrum.settings_type.traceLength = 999;
    X_rsa.vars.spectrum.settings_type.verticalUnit = RSA_API::SpectrumVerticalUnit_dBm;
    X_rsa.vars.spectrum.settings_type.window = RSA_API::SpectrumWindow_Kaiser;
    X_rsa.vars.spectrum.is_enabled_measurement = true;
    (void)X_rsa.spectrum_set_vars();

    X_rsa.vars.device.event_id = static_cast<int>(RSA_API::DEVEVENT_TRIGGER);

    X_rsa.vars.trig.if_power_level = -31.2;
    X_rsa.vars.trig.mode_select = RSA_API::TriggerMode::triggered;
    X_rsa.vars.trig.position_percent = X_rsa.vars.trig.POSITION_PERCENT_MAX / 2;
    X_rsa.vars.trig.source_select = RSA_API::TriggerSource::TriggerSourceIFPowerLevel;
    X_rsa.vars.trig.transition_select = RSA_API::TriggerTransitionLH;
    X_rsa.trig_set_vars();

    X_rsa.trig_print();
    X_rsa.device_run();

    for (int ii = 0; ii < bangz_ut7; ii++)
    {
        X_rsa.cutil.timer_split_start();
        while (X_rsa.cutil.timer_get_split_wall() < block_ut7)
        {
            X_rsa.device_check_event();
            if (X_rsa.vars.device.event_occured == true)
            {
                printf("split:  %17.6lf  ,  trigger detected  %lu\n", 
                    X_rsa.cutil.timer_get_split_wall(),
                    X_rsa.vars.device.event_timestamp);
                X_rsa.spectrum_acquire_data(0);
                X_rsa.spectrum_find_peak_index(0);
                X_rsa.spectrum_make_frequency_v();
                printf("\tMHz=  %9.3lf  ,  dBm=  %9.3f\n", 
                    X_rsa.vars.spectrum.frequency_v[X_rsa.vars.spectrum.peak_index[0]],
                    X_rsa.vars.spectrum.trace_power_v[0][X_rsa.vars.spectrum.peak_index[0]]);
            }
        }
        #ifdef WAIT_ENTER_CLEAR
            if (ii < bangz_ut7-1)
            {
                printf("\nsession %2d of %2d complete, press any key for next repitition:",
                    ii+1,
                    bangz_ut7);
                wait_enter_clear();
            }
        #endif
    }
    X_rsa.vars.spectrum.is_enabled_measurement = false;
    X_rsa.spectrum_set_vars();
    X_rsa.vars.trig.mode_select = RSA_API::TriggerMode::freeRun;    // it is good to make the trigger free-run when done to avoid blocking
    X_rsa.trig_set_vars();
    X_rsa.device_disconnect();

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_7.cpp
