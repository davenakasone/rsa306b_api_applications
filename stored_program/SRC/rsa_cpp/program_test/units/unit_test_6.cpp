/*
    unit test # 6, class [rsa_306b] API group 'REFTIME'

    goals:
    
        CODEZ reftime_print           ();    // prints the "REFTIME" variables to stdout, using the private struct
        CODEZ reftime_reset           ();    // resets start time of the device
        CODEZ reftime_get_vars        ();    // gets all the "REFTIME" variables
        CODEZ reftime_timestamp_2_time();    // set "vars.reftime.helper.timestamp", then call, updates time_t and uint64_t
        CODEZ reftime_time_2_timestamp();    // set "vars.reftime.helper.seconds  and nanos", then call, updates timestamp
        char* reftime_make_dts        ();   
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut6 = 3;
static void ut6_basic();
static void ut6_convert();


void unit_test_6()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'REFTIME'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    X_rsa.device_connect();
    ut6_basic();
    ut6_convert();
    X_rsa.device_disconnect();

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut6_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic REFTIME methods\n", __func__);
#endif                   
//~ 
    
    X_rsa.reftime_get_vars();
    X_rsa.reftime_print();
    printf("\ndts:  %s\n", X_rsa.reftime_make_dts());

    printf("\nreseting...\n");
    X_rsa.reftime_reset();
    sleep(1);
    X_rsa.reftime_print();
    printf("\ndts:  %s\n", X_rsa.reftime_make_dts());

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut6_convert()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  conversion REFTIME methods\n", __func__);
#endif                   
//~ 
    
    for (int ii = 0; ii < bangz_ut6; ii++)
    {
        printf("\tsleep(%d)\n", ii+1);
        (void)sleep(ii+1);
        
        X_rsa.reftime_get_vars();
        X_rsa.vars.reftime.helper.timestamp = X_rsa.vars.reftime.current.timestamp;
        X_rsa.vars.reftime.helper.seconds = X_rsa.vars.reftime.current.seconds;
        X_rsa.vars.reftime.helper.nanos = X_rsa.vars.reftime.current.nanos;
        X_rsa.reftime_time_2_timestamp();
        X_rsa.reftime_timestamp_2_time();

        printf("\n%2d of %2d)  timestamp 2 time converted:  %lu  -->  %ld  %lu\n",
            ii+1,
            bangz_ut6,
            X_rsa.vars.reftime.helper.timestamp,
            X_rsa.vars.reftime.helper.seconds,
            X_rsa.vars.reftime.helper.nanos);
        printf("                                        %lu       %ld  %lu\n", 
            X_rsa.vars.reftime.current.timestamp,
            X_rsa.vars.reftime.current.seconds,
            X_rsa.vars.reftime.current.nanos);
    }
    
//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_6.cpp
