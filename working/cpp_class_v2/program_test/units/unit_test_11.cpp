/*
    unit test # 11, API group "IQSTREAM"

    goals:
        -  the IQSTREAM variables, getters, setters, copiers are working
        -  validation procedures are enforced during program execution
        -  
*/

#include "../testz.h"

#define ACQUISITIONS 9

//#define UT11a 1    // basic test of the group
//#define UT11b 2    // get data to a file, freerun and triggered
#define UT11c 3    // get data direct, cplx32 format, freerun and triggered --> CSV
#define UT11d 4    // get data direct, cplxInt32 format, freerun and triggered --> CSV
#define UT11e 5    // get data direct, cplxInt16 format, freerun and triggered --> CSV
#define UT11f 6    // get data direct, cplx32 format, freerun and triggered --> CSV


void unit_test_11 (void)
{
    printf("\n%s()  ,  API group 'IQSTREAM'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        rsa.device_connect();

        #ifdef UT11a
            rsa.print_iqstream();
            rsa.vars.iqstream.bandwidth = 1.222e6;
            rsa.vars.iqstream.record_time_ms = 3;
            sprintf(rsa.vars.iqstream.filename_base, "potatoe");
            rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_TIMESTAMP;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_3;
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE_SCALE_INT32;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_FILE_MIDAS;
            rsa.iqstream_set_vars();
            rsa.print_iqstream();
        #endif
        #ifdef UT11b
            rsa.vars.config.reference_level_dbm = -33.3;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.vars.trig.mode_select = RSA_API::freeRun;
            rsa.trig_set_vars();
            rsa.iqstream_clear_sticky();
            rsa.vars.iqstream.bandwidth = 1.2345e6;
            rsa.vars.iqstream.record_time_ms = 1;
            sprintf(rsa.vars.iqstream.filename_base, "./program_test/data/outputs_siq/potatoe");
            rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
            rsa.iqstream_set_vars();
            printf("\n");
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                printf("%4d)  file:  %s  ,  header:  %s\n", 
                    ii, 
                    rsa.vars.iqstream.fileinfo_type.filenames_0,
                    rsa.vars.iqstream.fileinfo_type.filenames_1);
            }
            rsa.vars.trig.mode_select = RSA_API::triggered;
            rsa.trig_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
            }
        #endif
        #ifdef UT11c
            rsa.device_stop();
            rsa.vars.trig.mode_select = RSA_API::freeRun;
            rsa.trig_set_vars();
            rsa.vars.config.reference_level_dbm = -33.3;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.iqstream_clear_sticky();
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_CLIENT;
            rsa.vars.iqstream.bandwidth = 5.2345e6;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;
            rsa.iqstream_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                
                rsa.iqstream_acquire_data();
                printf("%4d)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[0].i =  %f  ,  cplx32_v[0].q = %f\n",
                    ii,
                    rsa.vars.iqstream.pairs_copied,
                    rsa.vars.iqstream.cplx32_v.size(),
                    rsa.vars.iqstream.cplx32_v[0].i,
                    rsa.vars.iqstream.cplx32_v[0].q);
                snprintf(rsa.vars.gp.helper, BUF_E, "./program_test/data/outputs_txt/cplx32_%d.csv", ii);
                rsa.iqstream_make_csv(rsa.vars.gp.helper);
                printf("%s\n\n", rsa.vars.gp.helper);
            }
            rsa.vars.trig.mode_select = RSA_API::triggered;
            rsa.trig_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                if (rsa.vars.iqstream.pairs_copied != rsa.constants.INIT_INT)
                {
                    printf("%4d)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[0].i =  %f  ,  cplx32_v[0].q = %f\n",
                        ii,
                        rsa.vars.iqstream.pairs_copied,
                        rsa.vars.iqstream.cplx32_v.size(),
                        rsa.vars.iqstream.cplx32_v[0].i,
                        rsa.vars.iqstream.cplx32_v[0].q);
                }
            }
        #endif
        #ifdef UT11d
            rsa.vars.trig.mode_select = RSA_API::freeRun;
            rsa.trig_set_vars();
            rsa.vars.config.reference_level_dbm = -33.3;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.iqstream_clear_sticky();
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_INT32;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_CLIENT;
            rsa.vars.iqstream.bandwidth = 5.2345e6;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;
            rsa.iqstream_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                printf("%4d)  pairs copied:  %d  ,  cplxInt32_v.size() = %ld  ,  cplxInt32_v[0].i =  %d  ,  cplxInt32_v[0].q = %d\n",
                    ii,
                    rsa.vars.iqstream.pairs_copied,
                    rsa.vars.iqstream.cplxInt32_v.size(),
                    rsa.vars.iqstream.cplxInt32_v[0].i,
                    rsa.vars.iqstream.cplxInt32_v[0].q);
                snprintf(rsa.vars.gp.helper, BUF_E, "./program_test/data/outputs_txt/cplxInt32_%d.csv", ii);
                rsa.iqstream_make_csv(rsa.vars.gp.helper);
                printf("%s\n\n", rsa.vars.gp.helper);
            }
            rsa.vars.trig.mode_select = RSA_API::triggered;
            rsa.trig_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                if (rsa.vars.iqstream.pairs_copied != rsa.constants.INIT_INT)
                {
                    printf("%4d)  pairs copied:  %d  ,  cplxInt32_v.size() = %ld  ,  cplxInt32_v[0].i =  %d  ,  cplxInt32_v[0].q = %d\n",
                        ii,
                        rsa.vars.iqstream.pairs_copied,
                        rsa.vars.iqstream.cplxInt32_v.size(),
                        rsa.vars.iqstream.cplxInt32_v[0].i,
                        rsa.vars.iqstream.cplxInt32_v[0].q);
                }
            }
        #endif
         #ifdef UT11e
            rsa.vars.trig.mode_select = RSA_API::freeRun;
            rsa.trig_set_vars();
            rsa.vars.config.reference_level_dbm = -33.3;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.iqstream_clear_sticky();
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_INT16;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_CLIENT;
            rsa.vars.iqstream.bandwidth = 5.2345e6;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;
            rsa.iqstream_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                printf("%4d)  pairs copied:  %d  ,  cplxInt16_v.size() = %ld  ,  cplxInt16_v[0].i =  %d  ,  cplxInt16_v[0].q = %d\n",
                    ii,
                    rsa.vars.iqstream.pairs_copied,
                    rsa.vars.iqstream.cplxInt16_v.size(),
                    rsa.vars.iqstream.cplxInt16_v[0].i,
                    rsa.vars.iqstream.cplxInt16_v[0].q);
                snprintf(rsa.vars.gp.helper, BUF_E, "./program_test/data/outputs_txt/cplxInt16_%d.csv", ii);
                rsa.iqstream_make_csv(rsa.vars.gp.helper);
                printf("%s\n\n", rsa.vars.gp.helper);
            }
            rsa.vars.trig.mode_select = RSA_API::triggered;
            rsa.trig_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                if (rsa.vars.iqstream.pairs_copied != rsa.constants.INIT_INT)
                {
                    printf("%4d)  pairs copied:  %d  ,  cplxInt16_v.size() = %ld  ,  cplxInt16_v[0].i =  %d  ,  cplxInt16_v[0].q = %d\n",
                        ii,
                        rsa.vars.iqstream.pairs_copied,
                        rsa.vars.iqstream.cplxInt16_v.size(),
                        rsa.vars.iqstream.cplxInt16_v[0].i,
                        rsa.vars.iqstream.cplxInt16_v[0].q);
                }
            }
        #endif
        #ifdef UT11f
            rsa.vars.trig.mode_select = RSA_API::freeRun;
            rsa.trig_set_vars();
            rsa.vars.config.reference_level_dbm = -33.3;
            rsa.vars.config.center_frequency_hz = 100e6;
            rsa.config_set_vars();
            rsa.iqstream_clear_sticky();
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE_SCALE_INT32;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_CLIENT;
            rsa.vars.iqstream.bandwidth = 5.2345e6;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;
            rsa.iqstream_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                printf("%4d)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[0].i =  %f  ,  cplx32_v[0].q = %f\n",
                    ii,
                    rsa.vars.iqstream.pairs_copied,
                    rsa.vars.iqstream.cplx32_v.size(),
                    rsa.vars.iqstream.cplx32_v[0].i,
                    rsa.vars.iqstream.cplx32_v[0].q);
                snprintf(rsa.vars.gp.helper, BUF_E, "./program_test/data/outputs_txt/cplx32s_%d.csv", ii);
                rsa.iqstream_make_csv(rsa.vars.gp.helper);
                printf("%s\n\n", rsa.vars.gp.helper);
            }
            rsa.vars.trig.mode_select = RSA_API::triggered;
            rsa.trig_set_vars();
            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                if (rsa.vars.iqstream.pairs_copied != rsa.constants.INIT_INT)
                {
                    printf("%4d)  pairs copied:  %d  ,  cplx32_v.size() = %ld  ,  cplx32_v[0].i =  %f  ,  cplx32_v[0].q = %f\n",
                        ii,
                        rsa.vars.iqstream.pairs_copied,
                        rsa.vars.iqstream.cplx32_v.size(),
                        rsa.vars.iqstream.cplx32_v[0].i,
                        rsa.vars.iqstream.cplx32_v[0].q);
                }
            }
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_11.cpp
