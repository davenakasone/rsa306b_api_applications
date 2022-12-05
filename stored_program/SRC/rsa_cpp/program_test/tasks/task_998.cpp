/*
    special function "scan_dump()"

    mode 4 does not work beacause the API was never built with time-based trigger
    ...the functions are in the header, but they are inoperable

    mode 3 is not suitable for integration, develope it differently
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_998()
{
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_start(); 
#endif                   
//~
    int repz = 2;
    (void)X_util.clear_data();
    X_rsa.device_connect();

    for (int ii = 0; ii < repz; ii++)
    {
        
        printf("\nsmode 1\n\n");
        X_rsa.scan_dump
        (
            sMode::smode_1,
            10.0e6,
            1.0e9,
            -13.33,
            0,
            10.0e3,
            20.0e6,
            999,
            -55.55,
            20,
            X_rsa.cutil.helper
        );
        printf("%s\n", X_rsa.cutil.helper);

        printf("\nsmode 2\n\n");
        X_rsa.scan_dump
        (
            sMode::smode_2,
            20.0e6,
            3.0e9,
            -43.33,
            0,
            10.0e4,
            30.0e6,
            999,
            -55.55,
            20,
            X_rsa.cutil.helper
        );
        printf("%s\n", X_rsa.cutil.helper);

        // printf("\nsmode 3\n\n");
        // X_rsa.scan_dump
        // (
        //     sMode::smode_3,
        //     15.0e6,
        //     5.7e9,
        //     -13.33,
        //     0,
        //     10.0e5,
        //     35.0e6,
        //     999,
        //     -15.55,
        //     20,
        //     X_rsa.cutil.helper
        // );
        // printf("%s\n", X_rsa.cutil.helper);
    }

    X_rsa.device_disconnect();                  
//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


/////////~~~~~~~~END>  task_998.cpp
