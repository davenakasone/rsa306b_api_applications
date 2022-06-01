/*
    unit test # 10, API group "IQBLK"

    this section directly streams the IQ block
    useful if processing is needed without the "*.sig" file

    goals:
        - getters, setters, copiers working correctly
        - IQBLK can be streamed, acquired, and processed
*/

#include "../testz.h"

#define CYCLEZ 1    // files of each acquisition method to write

//#define UT10_a 1    // basic test, get, set, print
#define UT10_b 2    // testing 3 data acquisition methods

void unit_test_10 (void)
{
    printf("\n%s()  ,  API group 'IQBLK'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();

        #ifdef UT10_a
            rsa.print_iqblk();

            rsa.vars.iqblk.getter = IQBLK_GET_IQ_DATA_CPLX;
            rsa.vars.iqblk.record_length = 4444;
            rsa.vars.iqblk.bandwidth_hz = 1234.5678;
            rsa.iqblk_set_vars();

            rsa.print_iqblk();

            rsa.vars.iqblk.getter = IQBLK_GET_IQ_DATA;
            rsa.vars.iqblk.record_length = 3333;
            rsa.vars.iqblk.bandwidth_hz = 1e6;
            rsa.iqblk_set_vars();

            rsa.print_iqblk();
        #endif
        #ifdef UT10_b
            strcpy(rsa.vars.gp.helper, "./program_test/data/outputs_txt/");

            rsa.vars.config.center_frequency_hz = 99.5e6;
            rsa.vars.config.reference_level_dbm = -35.2;
            rsa.config_set_vars();

            rsa.vars.spectrum.settings_type.span = 1e6;
            rsa.vars.spectrum.settings_type.rbw = 1e3;
            rsa.spectrum_set_vars();
            
            rsa.vars.iqblk.record_length = 3333;
            rsa.vars.iqblk.bandwidth_hz = 2e6;
            rsa.iqblk_set_vars();

            printf("\n");
            for (int ii = 0; ii < CYCLEZ; ii ++)
            {
                rsa.vars.iqblk.getter = IQBLK_GET_IQ_DATA;
                rsa.iqblk_set_vars();
                snprintf(rsa.vars.gp.holder, BUF_F, "%sgetIQdata%d.csv",
                    rsa.vars.gp.helper,
                    ii);
                rsa.iqblk_acquire_data();
                rsa.iqblk_make_csv(rsa.vars.gp.holder);
                printf(">>>%s\n", rsa.vars.gp.holder);
            }
            printf("\n");

            rsa.print_iqblk();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_10.cpp
