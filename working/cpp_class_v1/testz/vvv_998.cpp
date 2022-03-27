/*
    the time-split feature with "REFTIME" section seems off
*/

#include "unit_tests.h"

const long long WAIT_1 = 999999999999;


void vvv_998()
{
    {
        int sleep_a = 2;
        int sleep_b = 3;

        double running;
        double splitTime;
        rsa306b rsa;             // constructor called
        rsa.device_connect();    // initialization and calibration

        rsa.reftime_start_split();
        sleep(sleep_a);
        rsa.reftime_stop_split();
        running = rsa.reftime_get_running();
        splitTime = rsa.reftime_get_split();
        printf("\nslept  %d  seconds\n", sleep_a);
        printf("\ttime split is:  %lf  seconds\n", splitTime);
        printf("\telapsed time:  %lf seconds\n", running);

        rsa.reftime_start_split();
        sleep(sleep_b);
        rsa.reftime_stop_split();
        splitTime = rsa.reftime_get_split();
        running = rsa.reftime_get_running();
        printf("\nslept  %d  seconds\n", sleep_b);
        printf("\ttime split is:  %lf  seconds\n", splitTime);
        printf("\telapsed time:  %lf seconds\n", running);

        rsa.reftime_start_split();
        long long temp = 0;
        for (long long ii = 0; ii < WAIT_1; ii++)
        {
            temp = ii;
        }
        temp = temp - 1;
        rsa.reftime_stop_split();
        splitTime = rsa.reftime_get_split();
        running = rsa.reftime_get_running();
        printf("\nslept  %d  seconds\n", sleep_b);
        printf("\ttime split is:  %lf  seconds\n", splitTime);
        printf("\telapsed time:  %lf seconds\n", running);

    }
}

/////////~~~~~~~~END>  vvv_998.cpp
