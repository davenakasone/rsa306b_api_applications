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


void unit_test_6 (void)
{
    printf("\n%s()  ,  API group 'REFTIME'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;

        #ifdef UT6_a
            rsa.print_reftime();
            rsa.device_connect();
            rsa.print_reftime();
        #endif
        #ifdef UT6_b
            rsa.device_connect();
            sleep(1);
            rsa.reftime_get_vars();
            rsa.print_reftime();
            rsa.vars.reftime.helper.timestamp = rsa.vars.reftime.current.timestamp;
            rsa.reftime_timestamp_2_time();
            rsa.print_reftime();
            
            wait_enter_clear();

            rsa.reftime_get_vars();
            rsa.print_reftime();
            rsa.vars.reftime.helper.seconds = rsa.vars.reftime.current.seconds;
            rsa.vars.reftime.helper.nanos = rsa.vars.reftime.current.nanos;
            rsa.reftime_time_2_timestamp();
            rsa.print_reftime();
        #endif
        #ifdef UT6_c
            rsa.device_connect();
            rsa.reftime_get_vars();
            printf("\n%s\n", rsa.vars.reftime.dts);
        #endif
        #ifdef UT6_d
            rsa.device_connect();
            rsa.print_reftime();
            sleep(1);
            rsa.reftime_reset();
            rsa.print_reftime();
        #endif
        #ifdef UT6_e
            rsa.device_connect();
            double lead = 0;
            double trail = 0;
            int waiting = 4; // change
            printf("\ncomparing a %d second sleep cylce...\n", waiting);

            cpu.time_split_start();
            rsa.reftime_get_vars();
            trail = (double)rsa.vars.reftime.current.seconds + (double)rsa.vars.reftime.current.nanos / 1.0e9;
            sleep(waiting);
            cpu.time_split_stop();
            rsa.reftime_get_vars();
            lead = (double)rsa.vars.reftime.current.seconds + (double)rsa.vars.reftime.current.nanos / 1.0e9;
            printf("rsa306 time split:  %0.12lf\n", lead - trail);
            cpu.print_time_split();
        #endif
        printf("\ndestructors....\n");
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_6.cpp
