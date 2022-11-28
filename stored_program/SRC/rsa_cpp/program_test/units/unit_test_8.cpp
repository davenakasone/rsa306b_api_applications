/*
    unit test # 8, class [rsa_306b] API group 'AUDIO'

    goals:
    
        CODEZ audio_print                        ();    
        CODEZ audio_set_vars                     ();    
        CODEZ audio_acquire_data                 ();    
        CODEZ audio_start                        ();    
        CODEZ audio_stop                         ();    
        CODEZ audio_write_csv(char* file_path_name);   
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut8 = 4;
static void ut8_basic();
static void ut8_acquire();


void unit_test_8()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'AUDIO'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_PROCESSED);
    (void)X_util.delete_files_in_directory(DATA_DIRECTORY_RAW);
    X_rsa.device_connect();

    ut8_basic();
    ut8_acquire();
    
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


static void ut8_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic AUDIO methods\n", __func__);
#endif                   
//~

    X_rsa.audio_print();
    
    X_rsa.vars.audio.data_samples_requested = 1111;
    X_rsa.vars.audio.demodulation_select = RSA_API::ADM_FM_200KHZ;
    X_rsa.vars.audio.frequency_offset_hz = 200e3;
    X_rsa.vars.audio.is_mute = true;
    X_rsa.vars.audio.volume = 0.66;
    X_rsa.audio_set_vars();

    X_rsa.vars.spectrum.settings_type.span = 20e6;
    X_rsa.vars.spectrum.settings_type.rbw = 100e3;
    X_rsa.vars.spectrum.is_enabled_measurement = true;
    X_rsa.spectrum_set_vars();

    X_rsa.vars.config.center_frequency_hz = 102.7e6;
    X_rsa.vars.config.reference_level_dbm = -80.8;
    X_rsa.config_set_vars();

    X_rsa.audio_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut8_acquire()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  acquring adio data and demoudlating\n", __func__);
#endif                   
//~

    // X_rsa.device_run();
    // for (int ii = 0; ii < bangz_ut8; ii++)
    // {
    //     X_rsa.audio_start();
    //     printf("%d\n", X_rsa.vars.audio.is_demodulating);
    //     X_rsa.audio_acquire_data();
    //     if (X_rsa.vars.audio.data_samples_acquired > 0)
    //     {
    //         sprintf(X_rsa.cutil.helper, "%s%s_%2d_of%2d_.csv",
    //             DATA_DIRECTORY_PROCESSED,
    //             __func__,
    //             ii + 1,
    //             bangz_ut8);
    //         X_rsa.audio_write_csv(X_rsa.cutil.helper);
    //         printf("\n%s\n", X_rsa.cutil.helper);
    //     }
    //     X_rsa.audio_stop();
    // }

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_8.cpp
