/*
    unit test # 6, API group "REFTIME"

    this section uses the availible API timing features

    goals:
        - getters, setters, copiers working correctly
        - timestamp conversions work
        - dts works
        - timers are functioning
*/

#include "../testz.h"

//#define UT6_a 1    // basic test
//#define UT6_b 2    // timestamp conversions
//#define UT6_c 3    // dts
//#define UT6_d 4    // reset
#define UT6_e 5 // compare time splits ... it is unresponsive to sleep?
extern rsa306b_class X_rsa;


void unit_test_6 (void)
{
    printf("\n%s()  ,  API group 'REFTIME'\n", __func__);
    {
        cpu_timer_class cpu;
        X_rsa.device_disconnect();
        X_rsa.device_connect();
        
        #ifdef UT6_a
            X_rsa.print_reftime();
            X_rsa.device_connect();
            X_rsa.print_reftime();
        #endif
        #ifdef UT6_b
            X_rsa.device_connect();
            sleep(1);
            X_rsa.reftime_get_vars();
            X_rsa.print_reftime();
            X_rsa.vars.reftime.helper.timestamp = X_rsa.vars.reftime.current.timestamp;
            X_rsa.reftime_timestamp_2_time();
            X_rsa.print_reftime();
            
            #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif

            X_rsa.reftime_get_vars();
            X_rsa.print_reftime();
            X_rsa.vars.reftime.helper.seconds = X_rsa.vars.reftime.current.seconds;
            X_rsa.vars.reftime.helper.nanos = X_rsa.vars.reftime.current.nanos;
            X_rsa.reftime_time_2_timestamp();
            X_rsa.print_reftime();
        #endif
        #ifdef UT6_c
            X_rsa.device_connect();
            X_rsa.reftime_get_vars();
            printf("\n%s\n", X_rsa.vars.reftime.dts);
        #endif
        #ifdef UT6_d
            X_rsa.device_connect();
            X_rsa.print_reftime();
            sleep(1);
            X_rsa.reftime_reset();
            X_rsa.print_reftime();
        #endif
        #ifdef UT6_e
           
            double lead = 0;
            double trail = 0;
            int waiting = 4; // change
            printf("\ncomparing a %d second sleep cylce...\n", waiting);

            cpu.time_split_start();
            X_rsa.reftime_get_vars();
            trail = (double)X_rsa.vars.reftime.current.seconds + (double)X_rsa.vars.reftime.current.nanos / 1.0e9;
            sleep(waiting);
            cpu.time_split_stop();
            X_rsa.reftime_get_vars();
            lead = (double)X_rsa.vars.reftime.current.seconds + (double)X_rsa.vars.reftime.current.nanos / 1.0e9;
            printf("rsa306 time split:  %0.12lf\n", lead - trail);
            cpu.print_time_split();
            X_rsa.print_reftime();

        #endif
        printf("\ndestructors....\n");
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_6.cpp
