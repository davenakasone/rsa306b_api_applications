/*
    unit test # 11, API group "IQSTREAM"

    goals:
        -  the IQSTREAM variables, getters, setters, copiers are working
        -  validation procedures are enforced during program execution
        -  
*/

#include "../testz.h"

#define ACQUISITIONS 10

//#define UT11a 1    // basic test of the group
#define UT11b 2    // get data to a file
//#define UT11c 3    // get data direct


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
            rsa.iqstream_clear_sticky();
            rsa.vars.iqstream.bandwidth = 1.2345e6;
            rsa.vars.iqstream.record_time_ms = 1;
            sprintf(rsa.vars.iqstream.filename_base, "./program_test/data/outputs_siq/potatoe");
            rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
            rsa.iqstream_set_vars();

            for (int ii = 0; ii < ACQUISITIONS; ii++)
            {
                rsa.iqstream_acquire_data();
                //printf("created:  file_%d\n", ii);
                //printf("created:  %s\n", rsa.vars.iqstream.name_of_file);
                //std::wcout << rsa.vars.iqstream.fileinfo_type.filenames[0] << std::endl;
                //wprintf(L"%ls\n", rsa.vars.iqstream.fileinfo_type.filenames[0]);
            }
        #endif
        #ifdef UT11c
            rsa.vars.config.reference_level_dbm = -33.3;
            rsa.vars.config.center_frequency_hz = 100e6;

            rsa.iqstream_clear_sticky();
            rsa.vars.iqstream.bandwidth = 5.2345e6;
            rsa.vars.iqstream.record_time_ms = 1;
            sprintf(rsa.vars.iqstream.filename_base, "./program_test/data/outputs_siq/potatoe");
            rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_1;
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
            rsa.iqstream_set_vars();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_11.cpp
