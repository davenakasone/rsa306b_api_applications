/*
    unit test # 4, API group "AUDIO"

    this section is used to demodulate data

    goals:
        - getters, setters, copiers working correctly
        - the audio demodulator can be controlled
*/

#include "../testz.h"

//#define UT4_a 1    // basic test
#define UT4_b 2    // test getting audio data


void unit_test_4 (void)
{
    printf("\n%s()  ,  API group 'AUDIO'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;

        #ifdef UT4_a
            rsa.print_audio();
            rsa.device_connect();
            rsa.print_audio();
        #endif
        #ifdef UT4_b
            rsa.device_connect();
            
            rsa.vars.audio.data_samples_requested = 100;
            rsa.vars.audio.demodulation_select = RSA_API::ADM_FM_75KHZ;
            rsa.vars.audio.frequency_offset_hz = 8e3;
            rsa.vars.audio.volume = 0.6;
            rsa.vars.audio.is_mute = false;
            rsa.audio_set_vars();

            rsa.audio_acquire_data();
            rsa.print_audio();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_4.cpp
