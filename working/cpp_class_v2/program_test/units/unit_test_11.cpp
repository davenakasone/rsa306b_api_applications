/*
    unit test # 11, API group "IQSTREAM"

    goals:
        -  the IQSTREAM variables, getters, setters, copiers are working
        -  validation procedures are enforced during program execution
        -  
*/

#include "../testz.h"

//#define UT11a 1    // basic test of the group
#define UT11b 2    // get data to a file


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
            rsa.vars.iqstream.bandwidth = 1.222e6;
            rsa.vars.iqstream.record_time_ms = 3;
            sprintf(rsa.vars.iqstream.filename_base, "potatoe");
            rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_TIMESTAMP;
            rsa.vars.iqstream.buffer_multiplier = rsa.constants.IQSTREAM_BUFFER_X_3;
            rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE_SCALE_INT32;
            rsa.vars.iqstream.destination_select = RSA_API::IQSOD_FILE_MIDAS;
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_11.cpp
