/*
    unit test # 11, API group "IQSTREAM"

    goals:
        -  the IQSTREAM variables, getters, setters, copiers are working
        -  validation procedures are enforced during program execution
        -  client stream success, both triggered and untriggered, simple CSV as output
        -  file stream success, both triggered and untriggered, taking "*.siq" only
        -  ...the file handler class goes with it
*/

#include "../testz.h"

#define UT11a 1    // basic test of the group
#define UT11b 2    // calls through to task_990(), handles all client and file stream cases
#define UT11c 3    // parse some "*.siq files", calls through task_989()
extern rsa306b_class X_rsa;


void unit_test_11 (void)
{
    printf("\n%s()  ,  API group 'IQSTREAM'\n", __func__);
    {
        cpu_timer_class cpu;
        X_rsa.device_disconnect();
        X_rsa.device_connect();

        #ifdef UT11a
        
            X_rsa.print_iqstream();
            X_rsa.vars.iqstream.bandwidth = 1.222e6;
            X_rsa.vars.iqstream.record_time_ms = 3;
            sprintf(X_rsa.vars.iqstream.filename_base, "potatoe");
            X_rsa.vars.iqstream.suffix_control = RSA_API::IQSSDFN_SUFFIX_TIMESTAMP;
            X_rsa.vars.iqstream.buffer_multiplier = X_rsa.constants.IQSTREAM_BUFFER_X_3;
            X_rsa.vars.iqstream.datatype_select = RSA_API::IQSODT_SINGLE_SCALE_INT32;
            X_rsa.vars.iqstream.destination_select = RSA_API::IQSOD_FILE_MIDAS;
            X_rsa.iqstream_set_vars();
            X_rsa.print_iqstream();

            #if defined (UT11b) || (UT11c)
                #ifdef WAIT_ENTER_CLEAR
                    wait_enter_clear();
                #endif
            #endif
        #endif
        
        #ifdef UT11b
            task_990();
            #ifdef UT11c
                #ifdef WAIT_ENTER_CLEAR
                    wait_enter_clear();
                #endif
            #endif
        #endif

        #ifdef UT11c
            task_989();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_11.cpp
