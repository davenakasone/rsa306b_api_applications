/*
    special function "scan_dump()"
*/

#include "../testz.h"

#ifdef UNIT_TESTING

const double t998_fstart   = 10.0e6;
const double t998_fstop    = 1.0e9;
const double t998_reflvl   = -13.33;
const int    t998_traceNum = 0;
const double t998_rbw      = 10.0e3;
const double t998_span     = 20.0e6;
const int    t998_tlen     = 999;
const double t998_thresh   = -55.55;
const int    t998_recms    = 20;


void task_998()
{
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_start(); 
#endif                   
//~

    X_rsa.device_connect();
    printf("\nsmode 1\n\n");
    X_rsa.scan_dump
    (
        sMode::smode_1,
        t998_fstart,
        t998_fstop,
        t998_reflvl,
        t998_traceNum,
        t998_rbw,
        t998_span,
        t998_tlen,
        t998_thresh,
        t998_recms,
        X_rsa.cutil.helper
    );
    printf("\nsmode 2\n\n");
    X_rsa.scan_dump
    (
        sMode::smode_2,
        t998_fstart,
        t998_fstop,
        t998_reflvl,
        t998_traceNum,
        t998_rbw,
        t998_span,
        t998_tlen,
        t998_thresh,
        t998_recms,
        X_rsa.cutil.helper
    );
    printf("\nsmode 3\n\n");
    X_rsa.scan_dump
    (
        sMode::smode_3,
        t998_fstart,
        t998_fstop,
        t998_reflvl,
        t998_traceNum,
        t998_rbw,
        t998_span,
        t998_tlen,
        t998_thresh,
        t998_recms,
        X_rsa.cutil.helper
    );
    printf("\nsmode 4\n\n");
    X_rsa.scan_dump
    (
        sMode::smode_4,
        t998_fstart,
        t998_fstop,
        t998_reflvl,
        t998_traceNum,
        t998_rbw,
        t998_span,
        t998_tlen,
        t998_thresh,
        t998_recms,
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
