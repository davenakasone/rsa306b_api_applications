/*
    unit test # 9, class [rsa_306b] API group 'SPECTRUM'

    goals:
    
        CODEZ spectrum_print                                          ()
        CODEZ spectrum_set_vars                                       ()
        CODEZ spectrum_default                                        ()
        CODEZ spectrum_acquire_data                   (int trace_number)
        CODEZ spectrum_find_peak_index                (int trace_number)
        CODEZ spectrum_make_frequency_v                               ()
        CODEZ spectrum_write_csv(char* file_path_name, int trace_number)
        bool  spectrum_good_bitcheck                  (int trace_number)
        CODEZ spectrum_scanner
        (
            const int    trace_number,
            const double fstart, 
            const double fstop, 
            const double threshold, 
            const int    loitering,
            char*        file_path_name,
            const double reflevel,
            const double rbw,
            const double span,
            const int    tlen
        )
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr double block_ut9 = 11.11;    // seconds to wait before breaking out of a loop
constexpr int bangz_ut9 = 3;
static void ut9_basic();
static void ut9_untrig_acq();
static void ut9_trig_acq();
static void ut9_auto_scan();


void unit_test_9()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'SPECTRUM'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);
    X_rsa.device_connect();

    ut9_basic();
    ut9_untrig_acq();
    ut9_trig_acq();
    ut9_auto_scan();

    X_rsa.device_disconnect();
//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut9_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic SPECTRUM methods\n", __func__);
#endif                   
//~

    X_rsa.spectrum_print();

    X_rsa.vars.config.center_frequency_hz = 315.002e6;
    X_rsa.vars.config.reference_level_dbm = -11.8;
    X_rsa.config_set_vars();

    X_rsa.vars.spectrum.settings_type.span = 13.3e6;
    X_rsa.vars.spectrum.settings_type.rbw = 20e3;
    X_rsa.vars.spectrum.settings_type.traceLength = 5555;
    X_rsa.vars.spectrum.is_enabled_measurement = true;
    X_rsa.vars.spectrum.is_enabled_trace[0] = true;
    X_rsa.vars.spectrum.detector_select[0] = RSA_API::SpectrumDetector_PosPeak;
    X_rsa.spectrum_set_vars();

    X_rsa.spectrum_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut9_untrig_acq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  SPECTRUM acquisition, untriggered\n", __func__);
#endif                   
//~
    X_rsa.vars.trig.mode_select = RSA_API::TriggerMode::freeRun;
    X_rsa.trig_set_vars();
    X_rsa.device_run();

    for (int ii = 0; ii < bangz_ut9; ii++)
    {
        (void)sprintf(X_rsa.cutil.helper, "%s%s_t0__%d_of_%d.csv",
            DATA_DIRECTORY_PROCESSED,
            __func__,
            ii+1,
            bangz_ut9);
        if (X_rsa.spectrum_acquire_data(0) == CODEZ::_0_no_errors)
        {
            (void)X_util.report_status_code(X_rsa.spectrum_make_frequency_v());
            (void)X_util.report_status_code(X_rsa.spectrum_find_peak_index(0));
            (void)X_util.report_status_code(X_rsa.spectrum_write_csv(X_rsa.cutil.helper, 0));
            printf("\n%2d of %2d  peaks)  MHz=  %15.5lf  ,  dBm=  %15.5f  ,  bitcheck:  %d {1 means good}\n",
                ii+1,
                bangz_ut9,
                X_rsa.vars.spectrum.frequency_v[X_rsa.vars.spectrum.peak_index[0]] / 1e6,
                X_rsa.vars.spectrum.trace_power_v[0][X_rsa.vars.spectrum.peak_index[0]],
                X_rsa.spectrum_good_bitcheck(0));
            printf("\t%s\n", X_rsa.cutil.helper);
        }
    }

    X_rsa.vars.spectrum.is_enabled_measurement = false;
    X_rsa.spectrum_set_vars();
    X_rsa.device_stop();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}



////~~~~


static void ut9_trig_acq()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  SPECTRUM acquisition, triggered\n", __func__);
#endif                   
//~

    X_rsa.vars.device.event_id = static_cast<int>(RSA_API::DEVEVENT_TRIGGER);

    X_rsa.vars.spectrum.is_enabled_measurement = true;
    X_rsa.spectrum_set_vars();

    X_rsa.vars.trig.mode_select = RSA_API::TriggerMode::triggered;
    X_rsa.vars.trig.position_percent = X_rsa.vars.trig.POSITION_PERCENT_MAX / 2;
    X_rsa.vars.trig.source_select = RSA_API::TriggerSource::TriggerSourceIFPowerLevel;
    X_rsa.vars.trig.transition_select = RSA_API::TriggerTransitionLH;
    X_rsa.trig_set_vars();

    X_rsa.device_run();

    for (int ii = 0; ii < bangz_ut9; ii++)
    {
        X_util.timer_split_start();
        printf("\nwaiting for trigger, repetition:  %d of %d\n", ii+1, bangz_ut9);
        while (X_util.timer_get_split_wall() < block_ut9)
        {
            X_rsa.device_check_event();
            if (X_rsa.vars.device.event_occured == true)
            {
                if (X_rsa.spectrum_acquire_data(0) == CODEZ::_0_no_errors)
                {   
                    X_rsa.cutil.helper[0] = '\0';
                    (void)X_util.report_status_code(X_rsa.spectrum_make_frequency_v());
                    (void)X_util.report_status_code(X_rsa.spectrum_find_peak_index(0));
                    (void)X_util.report_status_code(X_rsa.spectrum_write_csv(X_rsa.cutil.helper, 0));
                    printf("\n%2d of %2d  peaks)  MHz=  %15.5lf  ,  dBm=  %15.5f  ,  bitcheck:  %d {1 means good}\n",
                        ii+1,
                        bangz_ut9,
                        X_rsa.vars.spectrum.frequency_v[X_rsa.vars.spectrum.peak_index[0]] / 1e6,
                        X_rsa.vars.spectrum.trace_power_v[0][X_rsa.vars.spectrum.peak_index[0]],
                        X_rsa.spectrum_good_bitcheck(0));
                    printf("\t%s\n", X_rsa.cutil.helper);
                }
            }
        }
        if (ii<bangz_ut9-1){printf("\twaiting for next trigger...\n");}
    }

    X_rsa.vars.spectrum.is_enabled_measurement = false;
    X_rsa.spectrum_set_vars();
    X_rsa.device_stop();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}



////~~~~


static void ut9_auto_scan()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  SPECTRUM automatic scan over range\n", __func__);
#endif                   
//~

    for (int ii = 0; ii < bangz_ut9; ii++)
    {
        printf("\nauto scan %d of %d\n\n", ii+1, bangz_ut9);
        (void)sprintf(X_rsa.cutil.helper, "%s%s_t0__%d_of_%d.csv",
            DATA_DIRECTORY_PROCESSED,
            __func__,
            ii+1,
            bangz_ut9);
        (void)X_rsa.spectrum_scanner
        (
            static_cast<int>(RSA_API::SpectrumTraces::SpectrumTrace1),   // trace # [0, 1, 2]
            10e6,                                                        // start frequency (Hz)
            500e6,                                                       // stop frequency (Hz)
            -65.5,                                                       // threshold (dBm) that iniates further processing
            4,                                                           // repititions to loiter on a center frequency
            X_rsa.cutil.helper,                                          // output file-path-name
            -1.11,                                                       // reference level (dBm)
            10e3,                                                        // resolution bandwidth (Hz)
            10e6,                                                        // frequency span (Hz)
            999                                                          // pairs [frequency (Hz), power (dBm)] acquired per trace
        );
    }

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_9.cpp
