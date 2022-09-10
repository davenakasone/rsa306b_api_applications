/*
    unit test # 10, API group "IQBLK"

    this section directly streams the IQ block
    useful if processing is needed without the "*.sig" file

    goals:
        - getters, setters, copiers working correctly
        - IQBLK can be streamed, acquired, and processed
*/

#include "../testz.h"

#define CYCLEZ 9        // files of each acquisition method to write
#define TEST_INDEX 5    // arbitrary index to observe the IQBLK std::vector<float>

#define UT10_a 1    // basic test, get, set, print
#define UT10_b 2    // testing 3 data acquisition methods
// extern rsa306b_class X_rsa;
// extern timer_class X_timer;


void unit_test_10 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  API group 'IQBLK'\n", __func__);                     
#endif    
////~~~~

        X_rsa.device_disconnect();
        X_rsa.device_connect();

        #ifdef UT10_a

            X_rsa.print_iqblk();
            X_rsa.vars.iqblk.record_length = 4444;
            X_rsa.vars.iqblk.getter        = X_rsa.constants.IQBLK_GET_IQ_DATA_CPLX;
            X_rsa.vars.iqblk.bandwidth_hz  = 1234.5678;
            X_rsa.iqblk_set_vars();
            X_rsa.print_iqblk();

            X_rsa.vars.iqblk.getter        = X_rsa.constants.IQBLK_GET_IQ_DATA;
            X_rsa.vars.iqblk.record_length = 3333;
            X_rsa.vars.iqblk.bandwidth_hz  = 1e6;
            X_rsa.iqblk_set_vars();
            X_rsa.print_iqblk();

        #if ((defined (UT10_b)) && (defined (WAIT_ENTER_CLEAR)))
            wait_enter_clear();
        #endif
        #endif
        #ifdef UT10_b

            strcpy(X_rsa.vars.gp.helper, X_rsa.constants.DATA_DIRECTORY_PROCESSED);
            X_rsa.vars.config.center_frequency_hz = 99.5e6;
            X_rsa.vars.config.reference_level_dbm = -35.2;
            X_rsa.config_set_vars();

            X_rsa.vars.spectrum.settings_type.span = 1e6;
            X_rsa.vars.spectrum.settings_type.rbw  = 1e3;
            X_rsa.spectrum_set_vars();
            
            X_rsa.vars.iqblk.record_length = 3333;
            X_rsa.vars.iqblk.bandwidth_hz  = 2e6;
            X_rsa.iqblk_set_vars();

            printf("\n");
            X_timer.time_split_start(); 
            for (int ii = 0; ii < CYCLEZ; ii ++)
            {
                X_rsa.vars.iqblk.getter = X_rsa.constants.IQBLK_GET_IQ_DATA;
                X_rsa.iqblk_set_vars();
                snprintf(X_rsa.vars.gp.holder, BUF_F, "%sgetIQdata_%d.csv",
                    X_rsa.vars.gp.helper,
                    ii);
                X_rsa.iqblk_acquire_data();
                X_rsa.iqblk_make_csv(X_rsa.vars.gp.holder);

                printf(">>>%d  %s\n", ii, X_rsa.vars.gp.holder);
                printf("\t\trequested:  %d  ,  actual:  %d\n", 
                    X_rsa.vars.iqblk.record_length, 
                    X_rsa.vars.iqblk.actual_buffer_samples);
                printf("\t\tstd::vector,  cplx_v[%d].i=  %0.7f  ,  cplx_v[%d].q=  %0.7f\n", 
                    TEST_INDEX, 
                    X_rsa.vars.iqblk.cplx32_v[TEST_INDEX].i,
                    TEST_INDEX, 
                    X_rsa.vars.iqblk.cplx32_v[TEST_INDEX].q);
            }
            X_timer.time_split_stop();
            X_timer.print_time_split(true);
            printf("\n");
            X_timer.time_split_start(); 
            for (int ii = 0; ii < CYCLEZ; ii ++)
            {
                X_rsa.vars.iqblk.getter = X_rsa.constants.IQBLK_GET_IQ_DATA_CPLX;
                X_rsa.iqblk_set_vars();
                snprintf(X_rsa.vars.gp.holder, BUF_F, "%sgetIQdataCplx_%d.csv",
                    X_rsa.vars.gp.helper,
                    ii);
                X_rsa.iqblk_acquire_data();
                X_rsa.iqblk_make_csv(X_rsa.vars.gp.holder);

                printf(">>>%d  %s\n", ii, X_rsa.vars.gp.holder);
                printf("\t\trequested:  %d  ,  actual:  %d\n", 
                    X_rsa.vars.iqblk.record_length, 
                    X_rsa.vars.iqblk.actual_buffer_samples);
                printf("\t\tstd::vector,  cplx_v[%d].i=  %0.7f  ,  cplx_v[%d].q=  %0.7f\n", 
                    TEST_INDEX, 
                    X_rsa.vars.iqblk.cplx32_v[TEST_INDEX].i,
                    TEST_INDEX, 
                    X_rsa.vars.iqblk.cplx32_v[TEST_INDEX].q);
            }
            X_timer.time_split_stop();
            X_timer.print_time_split(true);
            printf("\n");
            X_timer.time_split_start(); 
            for (int ii = 0; ii < CYCLEZ; ii ++)
            {
                X_rsa.vars.iqblk.getter = X_rsa.constants.IQBLK_GET_IQ_DATA_DEINETERLEAVED;
                X_rsa.iqblk_set_vars();
                snprintf(X_rsa.vars.gp.holder, BUF_F, "%sgetIQdataDeinterleaved_%d.csv",
                    X_rsa.vars.gp.helper,
                    ii);
                X_rsa.iqblk_acquire_data();
                X_rsa.iqblk_make_csv(X_rsa.vars.gp.holder);

                printf(">>>%d  %s\n", ii, X_rsa.vars.gp.holder);
                printf("\t\trequested:  %d  ,  actual:  %d\n", 
                    X_rsa.vars.iqblk.record_length, 
                    X_rsa.vars.iqblk.actual_buffer_samples);
                printf("\t\tstd::vector,  cplx_v[%d].i=  %0.7f  ,  cplx_v[%d].q=  %0.7f\n", 
                    TEST_INDEX, 
                    X_rsa.vars.iqblk.cplx32_v[TEST_INDEX].i,
                    TEST_INDEX, 
                    X_rsa.vars.iqblk.cplx32_v[TEST_INDEX].q);
            }
            X_timer.time_split_stop();
            X_timer.print_time_split(true);
            printf("\n");
        #endif

////~~~~
#ifdef WAIT_ENTER_CLEAR
X_timer.print_running_time(true);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////////~~~~~~~~END>  unit_test_10.cpp
