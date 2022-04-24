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
//#define UT6_d 4    // test wall clock and cpu timers   ...it is a split since last timestamp was made
#define UT6_e 5    // reset


void unit_test_6 (void)
{
    printf("\n%s()  ,  API group 'TRIG'\n", __func__);
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

            rsa.vars.reftime.helper.seconds = 0;
            rsa.vars.reftime.helper.nanos = 0;
            rsa.print_reftime();
            rsa.reftime_get_vars();
            rsa.print_reftime();
            rsa.vars.reftime.helper.seconds = rsa.vars.reftime.current.seconds;
            rsa.vars.reftime.helper.nanos = rsa.vars.reftime.current.nanos;
            rsa.reftime_time_2_timestamp();
            rsa.print_reftime();
        #endif
        #ifdef UT6_c
            rsa.device_connect();
            rsa.reftime_make_dts();
            printf("\n%s\n", rsa.vars.reftime.dts);
        #endif
        #ifdef UT6_d
            int discard;
            rsa.device_connect();
            cpu.time_split_start();
            rsa.reftime_split_begin();
            sleep(3);
            rsa.reftime_split_end();
            cpu.time_split_stop();
            printf("\nwall clock :  %12lf  ,  started:  %0.12lf\n", 
                rsa.vars.reftime.split_duration, rsa.vars.reftime.split_trail);
            printf("\ncpu clock  :  %12lf\n", cpu.get_running_time());
        #endif
        #ifdef UT6_e
            rsa.device_connect();
            rsa.print_reftime();
            rsa.reftime_reset();
            rsa.print_reftime();
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_6.cpp
/*
reftime_reset()
reftime_get_vars()
reftime_timestamp_2_time()
reftime_time_2_timestamp()
reftime_make_dts()
reftime_split_begin()
reftime_split_end()
*/