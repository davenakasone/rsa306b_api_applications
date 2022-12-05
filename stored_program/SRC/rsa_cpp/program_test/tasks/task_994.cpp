/*
    special function "triggered_dump()"
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_994()
{
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_start(); 
#endif                   
//~
    int repz = 3;
    (void)X_util.clear_data();
    X_rsa.device_connect();

    for (int ii = 0; ii < repz; ii++)
    {
        (void)printf("\n\n%d of %d, triggered_dump()\n\n", ii+1, repz);
        (void)X_rsa.triggered_dump
        (
            4,                                          // how many times to loiter on each bin
            30.0e6,                                     // stopping frequency (Hz)
            900.1e6,                                    // starting frequency (Hz)
            -1.1,                                       // configuration reference level (dBm)
            -33.33,                                     // trigger IF power level (dBm)
            RSA_API::SpectrumTraces::SpectrumTrace1,    // which trace
            1.0e4,                                      // resolution bandwidth (Hz)
            30.0e6,                                     // span (Hz)
            3333,                                       // points in a trace
            2,                                          // milli-seconds to record SIQ and R3F
            X_util.helper                               // directory where files will go                  
        );
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


/////////~~~~~~~~END>  task_994.cpp
