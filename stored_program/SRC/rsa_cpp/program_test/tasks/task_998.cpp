/*
    special function "scan_dump()"
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_998()
{
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_start(); 
#endif                   
//~

    X_rsa.device_connect();

    X_rsa.scan_dump
    (
        10.0e6,
        1.0e9,
        -13.33,
        0,
        10.0e3,
        20.0e6,
        999,
        -55.55,
        X_rsa.cutil.helper
    );

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
