/*
    unit test # 8, "AUDIO" section

    goals:
        - other sections continue to work
        - getters, setters, and blockers work
        - the spectrum analyzer responds to audio settings
*/

#include "unit_tests.h"

//#define UT8_1 1    // a basic getting test
//#define UT8_2 2    // a basic setting test
#define UT8_3 3    // get some audio data, it is not picking up the radio


void unit_test_8 (void)
{
    printf("\n%s()  ,  testing the 'AUDIO' section of the class\n", __func__);
    {
        rsa306b::audio_type aud_t;
        rsa306b rsa;
        rsa.device_connect();

        #ifdef UT8_1
            rsa.audio_get_settings(&aud_t);
            printf("\ngot volume:  %f  ,  check rest with print...\n", aud_t.volume);
            rsa.audio_print_all();
        #endif
        #ifdef UT8_2
            rsa.audio_print_all();
            aud_t.center_frequency_offset_hz = 9e9;
            aud_t.is_demodulating = true; // user can't control this variable
            aud_t.data_length_received = 7777; // user can't control this variable
            aud_t.volume = 0.5;
            aud_t.is_mute = false;
            aud_t.demodulation_mode_select = RSA_API::ADM_FM_200KHZ;
            rsa.audio_prepare(&aud_t);
            rsa.audio_print_all();
            // rejected on condition, try agin
            aud_t.center_frequency_offset_hz = 1e6;
            aud_t.is_demodulating = true; // user can't control this variable
            aud_t.data_length_received = 666; // user can't control this variable
            aud_t.volume = 0.5;
            aud_t.is_mute = true;
            aud_t.demodulation_mode_select = RSA_API::ADM_FM_200KHZ;
            rsa.audio_prepare(&aud_t);
            rsa.audio_print_all();
        #endif
        #ifdef UT8_3
            RSA_API::Spectrum_Settings t_set;
            rsa306b::spectrum_3_traces_type t_3;
            double cf = 97.75e6;
            double rl = -30;
            rsa.spectrum_get_3_traces_type(&t_3);
            rsa.spectrum_get_settings_type(&t_set);
            t_set.span = 20.5e6;
            rsa.spectrum_prepare(cf, rl, &t_set, &t_3);

            aud_t.center_frequency_offset_hz = 1e6;
            aud_t.is_demodulating = true; // user can't control this variable
            aud_t.data_length_received = 666; // user can't control this variable
            aud_t.volume = 0.5;
            aud_t.is_mute = false;
            aud_t.demodulation_mode_select = RSA_API::ADM_FM_200KHZ;
            rsa.audio_prepare(&aud_t);
            rsa.audio_get_data(&aud_t);
            rsa.audio_print_all();
        #endif
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_8.cpp
