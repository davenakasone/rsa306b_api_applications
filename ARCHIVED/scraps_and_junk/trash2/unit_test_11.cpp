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

#ifdef UNIT_TESTINGG

#define UT11_a 1    // basic test of the group
#define UT11_b 2    // calls through to task_990(), handles all client and file stream cases
#define UT11_c 3    // parse some "*.siq files", calls through task_989()


void unit_test_11 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  API group 'IQSTREAM'\n", __func__);
//X_timer.time_split_start();                      
#endif    
////~~~~

    X_rsa.device_disconnect();
    X_rsa.device_connect();

    #ifdef UT11_a

        X_rsa.print_iqstream();
        sprintf(X_rsa.vars.iqstream.filename_base, "potatoe");
        X_rsa.vars.iqstream.bandwidth          = 1.222e6;
        X_rsa.vars.iqstream.record_time_ms     = 3;
        X_rsa.vars.iqstream.suffix_control     = RSA_API::IQSSDFN_SUFFIX_TIMESTAMP;
        X_rsa.vars.iqstream.buffer_multiplier  = X_rsa.constants.IQSTREAM_BUFFER_X_3;
        X_rsa.vars.iqstream.datatype_select    = RSA_API::IQSODT_SINGLE_SCALE_INT32;
        X_rsa.vars.iqstream.destination_select = RSA_API::IQSOD_FILE_MIDAS;
        X_rsa.iqstream_set_vars();
        X_rsa.print_iqstream();

    #endif
    #if ((defined (UT11_b) || defined (UT11_c)) && (defined (WAIT_ENTER_CLEAR)))   
        wait_enter_clear();     
    #endif
    #ifdef UT11_b
        task_993();
    #if ((defined (UT11_c)) && (defined (WAIT_ENTER_CLEAR)))   
        wait_enter_clear();     
    #endif
    #endif
    #ifdef UT11_c
        task_992();
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


////////~~~~~~~~END>  unit_test_11.cpp
