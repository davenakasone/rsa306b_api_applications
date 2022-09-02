/*
    unit test # 3, "REFTIME" section

    goals:
        - general purpouse and REFTIME section continues to work
        - REFTIME getters and setters operate correctly
        - REFTIME functions are accurate
    
    note that the rsa306b class has a public struct "reftime_type"
    use this struct for any timing needs
    it is ready to interface with all REFTIME capabilities of the API
*/

#include "unit_tests.h"

struct ut3
{
    char dts[BUF_C];                   
    double running;                        
    double split;                          
    RSA_API::REFTIME_SRC source;    
    uint64_t rate;              
    rsa306b::reftime_type begin;      // internal public struct, good for timing analysis           
    rsa306b::reftime_type current;    // internal public struct, good for timing analysis
}; typedef struct ut3 ut3;

void ut3_print(ut3* stc);
void ut3_get(ut3* stc, rsa306b* RSA);
void ut3_print_times(rsa306b::reftime_type* dest, rsa306b::reftime_type* src);


void unit_test_3 (void)
{
    printf("\n%s()  ,  testing the 'REFTIME' section of the class\n", __func__);
    {
        rsa306b::reftime_type* fail_me = NULL;    // checks guards
        char start_dts[BUF_C];                    // extra date-time-stamp holder
        ut3 test;                                 // holds variables needed for testing
        rsa306b rsa;                              // constructor is called

        // should all get rejected, no connection yet
        ut3_get(&test, &rsa);
        ut3_print(&test);

        // getters should work now, device connected
        rsa.device_connect();
        sleep(3);
        ut3_get(&test, &rsa);
        ut3_print(&test);

        // try a time split
        rsa.reftime_start_split();
        sleep(2);
        rsa.reftime_stop_split();
        test.split = rsa.reftime_get_split();
        printf("\ntime split:  %lf seconds\n", test.split);

        // disconnect, recconnect, run, and get time stamp
        rsa.device_disconnect();
        rsa.device_connect();
        rsa.reftime_get_current_type(fail_me);
        rsa.reftime_get_begin_type(fail_me);
        rsa.reftime_get_date_timestamp(start_dts);
        rsa.device_run();
        sleep(2);
        rsa.reftime_get_date_timestamp(test.dts);
        printf("\ntime stamps:\n");
        printf("\tbegin:  %s\n", start_dts);
        printf("\tend  :  %s\n", test.dts);
        rsa.reftime_print_all();

        // use the time2timestap and timestamp2time tools
        rsa.reftime_time_2_timestamp(fail_me);
        rsa.reftime_timestamp_2_time(fail_me);
        fail_me = (rsa306b::reftime_type*)malloc(sizeof(rsa306b::reftime_type));
        printf("\nmatching time print-outs indicate tools convert properly:\n");
        rsa.reftime_get_begin_type(fail_me);
        rsa.reftime_get_begin_type(&test.begin);
        ut3_print_times(fail_me, &test.begin);
        rsa.reftime_timestamp_2_time(fail_me);
        ut3_print_times(fail_me, &test.begin);
        sleep(2);
        rsa.reftime_get_current_type(fail_me);
        rsa.reftime_get_current_type(&test.current);
        ut3_print_times(fail_me, &test.current);
        rsa.reftime_time_2_timestamp(fail_me);
        ut3_print_times(fail_me, &test.current);

        rsa.device_stop();
        rsa.device_disconnect();
        if (fail_me != NULL)
        {
            free(fail_me);
            fail_me = NULL;
        }
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////~~~~


void ut3_print
(
    ut3* stc
)
{
    printf("\nget 'REFTIME' information:\n");
    printf("\t_reftime_date_timestamp     :  %s\n", stc->dts);
    printf("\t_reftime_timestamp_rate     :  %lld\n", (long long)stc->rate);
    printf("\t_reftime_running            :  %lf\n", stc->running);
    printf("\t_reftime_split              :  %lf\n", stc->split);
    printf("\t_reftime_source_select      :  ");
    switch (stc->source)
    {
        case (RSA_API::RTSRC_NONE)   : printf("none\n"); break;
        case (RSA_API::RTSRC_SYSTEM) : printf("system\n"); break;
        case (RSA_API::RTSRC_GNSS)   : printf("GNSS\n"); break;
        case (RSA_API::RTSRC_USER)   : printf("user\n");break;
        default                      : printf("unknown\n");break;
    }
    printf("\ttime start, seconds         :  %lld\n", (long long)stc->begin.seconds);
    printf("\ttime start, nano seconds    :  %lld\n", (long long)stc->begin.nanos);
    printf("\ttime start, stamp           :  %lld\n", (long long)stc->begin.stamp);
    printf("\ttime current, seconds       :  %lld\n", (long long)stc->current.seconds);
    printf("\ttime current, nano seconds  :  %lld\n", (long long)stc->current.nanos);
    printf("\ttime current, stamp         :  %lld\n", (long long)stc->current.stamp);
}


////~~~~


void ut3_get
(
    ut3* stc, rsa306b* RSA
)
{
    RSA->reftime_get_date_timestamp(stc->dts);
    stc->running = RSA->reftime_get_running();
    stc->source = RSA->reftime_get_source_select();
    stc->rate = RSA->reftime_get_timestamp_rate();
    RSA->reftime_get_begin_type(&stc->begin);
    RSA->reftime_get_current_type(&stc->current);
    RSA->reftime_start_split();
    sleep(1);    // to produce a noticable time split
    RSA->reftime_stop_split();
    stc->split = RSA->reftime_get_split();
}


////~~~~


void ut3_print_times
(
    rsa306b::reftime_type* dest, 
    rsa306b::reftime_type* src
)
{
    printf("\ntimes copied:\n");
    printf("\tdest seconds:  %lld\n", (long long)dest->seconds);
    printf("\tsrc seconds :  %lld\n", (long long)src->seconds);
    printf("\tdest nanos  :  %lld\n", (long long)dest->nanos);
    printf("\tsrc nanos   :  %lld\n", (long long)src->nanos);
    printf("\tdest stamp  :  %lld\n", (long long)dest->stamp);
    printf("\tsrc stamp   :  %lld\n", (long long)src->stamp);
}


////////~~~~~~~~END>  unit_test_3.cpp
