/*
    unit test # 4, API group "AUDIO"

    this section is used to demodulate data

    goals:
        - getters, setters, copiers working correctly
        - the audio demodulator can be controlled
*/

#include "../testz.h"

#ifdef UNIT_TESTINGG

#define UT4_a 1    // basic test


void unit_test_4 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  API group 'AUDIO'\n", __func__);
//X_timer.time_split_start();                      
#endif    
////~~~~

    #ifdef UT4_a
        X_rsa.device_connect();
        X_rsa.print_audio();
        
        X_rsa.vars.audio.data_samples_requested = 100;
        X_rsa.vars.audio.demodulation_select    = RSA_API::ADM_FM_75KHZ;
        X_rsa.vars.audio.frequency_offset_hz    = 8e3;
        X_rsa.vars.audio.volume                 = 0.6;
        X_rsa.vars.audio.is_mute                = false;
        X_rsa.audio_set_vars();

        X_rsa.audio_acquire_data();
        X_rsa.print_audio();
    #endif

////~~~~
#ifdef WAIT_ENTER_CLEAR
// X_timer.time_split_stop();
// X_timer.print_both();
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif


////////~~~~~~~~END>  unit_test_4.cpp
