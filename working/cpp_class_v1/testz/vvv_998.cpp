/*
    the time-split feature with "REFTIME" section seems off

    this test proved that the API is not using the system clock well
    going to drop in a few clock_t variables in there to get a good split
    something is probably wrong with sleep()
    hopefully the RSA-306B was made to produce time stamps correctly
    it should be alright
        taking all the sleep() out of the class is probably a good idea
*/

#include "unit_tests.h"

const long long WAIT_1 = 999999999;

struct cpu_timer
{
    clock_t lead;
    clock_t trail;
    double diff;
}; typedef struct cpu_timer cpu_timer;

void cpu_time_split(cpu_timer* stc);


void vvv_998()
{
    {
        double trackSplit;
        double trackRunning;
        cpu_timer cpu;
        int sleep_a = 2;
        int sleep_b = 3;
        double running;
        double splitTime;
        rsa306b rsa;             // constructor called
        rsa.device_connect();    // initialization and calibration
        //
        cpu.trail = clock();
        rsa.reftime_start_split();
        sleep(sleep_a);
        rsa.reftime_stop_split();
        cpu.lead = clock();
        cpu_time_split(&cpu);
        trackRunning = rsa.reftime_get_running_cpu();
        running = rsa.reftime_get_running();
        splitTime = rsa.reftime_get_split();
        trackSplit = rsa.reftime_get_split_cpu();
        printf("\nslept  %d  seconds\n", sleep_a);
        printf("\tclass time split, API  :  %lf  seconds\n", splitTime);
        printf("\tclass time split, CPU  :  %lf  seconds\n", trackSplit);
        printf("\tthread time split      :  %lf  seconds\n", cpu.diff);
        printf("\telapsed time, API      :  %lf  seconds\n", running);
        printf("\telapsed time, CPU      :  %lf  seconds\n", trackRunning);
        rsa.reftime_print_all();
        //
        cpu.trail = clock();
        rsa.reftime_start_split();
        sleep(sleep_b);
        rsa.reftime_stop_split();
        cpu.lead = clock();
        cpu_time_split(&cpu);
        trackRunning = rsa.reftime_get_running_cpu();
        running = rsa.reftime_get_running();
        splitTime = rsa.reftime_get_split();
        trackSplit = rsa.reftime_get_split_cpu();
        printf("\nslept  %d  seconds\n", sleep_b);
        printf("\tclass time split, API  :  %lf  seconds\n", splitTime);
        printf("\tclass time split, CPU  :  %lf  seconds\n", trackSplit);
        printf("\tthread time split      :  %lf  seconds\n", cpu.diff);
        printf("\telapsed time, API      :  %lf  seconds\n", running);
        printf("\telapsed time, CPU      :  %lf  seconds\n", trackRunning);
        rsa.reftime_print_all();
        //
        /*
        cpu.trail = clock();
        rsa.reftime_start_split();
        sleep(sleep_b);
        rsa.reftime_stop_split();
        cpu.lead = clock();
        cpu_time_split(&cpu);
        running = rsa.reftime_get_running();
        splitTime = rsa.reftime_get_split();
        printf("\nslept  %d  seconds\n", sleep_b);
        printf("\tclass time split  :  %lf  seconds\n", splitTime);
        printf("\tcpu time split    :  %lf  seconds\n", cpu.diff);
        printf("\telapsed time      :  %lf  seconds\n", running);
        rsa.reftime_print_all();
        */
        /*
        cpu.trail = clock();
        rsa.reftime_start_split();
        long long temp = 0;
        for (long long ii = 0; ii < WAIT_1; ii++)
        {
            temp = ii;
        }
        rsa.reftime_stop_split();
        cpu.lead = clock();
        cpu_time_split(&cpu);
        running = rsa.reftime_get_running();
        splitTime = rsa.reftime_get_split();
        printf("\nslept  for a task, counting from 0 to %lld\n", temp);
        printf("\tclass time split  :  %lf  seconds\n", splitTime);
        printf("\tcpu time split    :  %lf  seconds\n", cpu.diff);
        printf("\telapsed time      :  %lf  seconds\n", running);
        rsa.reftime_print_all();
        */
    }
}


////~~~~


void cpu_time_split(cpu_timer* stc)
{
    stc->diff = ( ((double)stc->lead) - ((double)stc->trail) ) / CLOCKS_PER_SEC;
}


/////////~~~~~~~~END>  vvv_998.cpp
