/*
    special function "spectrum_scanner()"

    this one appears to drop out over large ranges
    tune it to be more robust
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_996()
{
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_start(); 
#endif                   
//~
    (void)X_util.clear_data();
    X_rsa.device_connect();

    int repz = 3;

    for (int ii = 0; ii < repz; ii++)
    {
        (void)sprintf(X_rsa.cutil.helper, "%s%s_t0%s__%d_of_%d.csv",
            DATA_DIRECTORY_PROCESSED,
            __func__,
            GET_NAME(ii),
            ii+1,
            repz);
        (void)X_rsa.spectrum_scanner
        (
            static_cast<int>(RSA_API::SpectrumTraces::SpectrumTrace1),   // trace # [0, 1, 2]
            10e6,                                                        // start frequency (Hz)
            500e6,                                                       // stop frequency (Hz)
            -65.5,                                                       // threshold (dBm) that iniates further processing
            4,                                                           // repititions to loiter on a center frequency
            X_rsa.cutil.helper,                                          // output file-path-name
            -1.11,                                                       // reference level (dBm)
            10e3,                                                        // resolution bandwidth (Hz)
            10e6,                                                        // frequency span (Hz)
            999                                                          // pairs [frequency (Hz), power (dBm)] acquired per trace
        );
        printf("%s\n", X_rsa.cutil.helper);
    }
    for (int jj = 0; jj < repz; jj++)
    {
        (void)sprintf(X_rsa.cutil.helper, "%s%s_t0%s__%d_of_%d.csv",
            DATA_DIRECTORY_PROCESSED,
            __func__,
            GET_NAME(jj),
            jj+1,
            repz);
        (void)X_rsa.spectrum_scanner
        (
            static_cast<int>(RSA_API::SpectrumTraces::SpectrumTrace1),   // trace # [0, 1, 2]
            20e6,                                                        // start frequency (Hz)
            1.0e9,                                                       // stop frequency (Hz)
            -35.5,                                                       // threshold (dBm) that iniates further processing
            3,                                                           // repititions to loiter on a center frequency
            X_rsa.cutil.helper,                                          // output file-path-name
            -22.11,                                                      // reference level (dBm)
            10e4,                                                        // resolution bandwidth (Hz)
            20e6,                                                        // frequency span (Hz)
            999                                                          // pairs [frequency (Hz), power (dBm)] acquired per trace
        );
        printf("%s\n", X_rsa.cutil.helper);
    }
    for (int kk = 0; kk < repz; kk++)
    {
        (void)sprintf(X_rsa.cutil.helper, "%s%s_t0%s__%d_of_%d.csv",
            DATA_DIRECTORY_PROCESSED,
            __func__,
            GET_NAME(kk),
            kk+1,
            repz);
        (void)X_rsa.spectrum_scanner
        (
            static_cast<int>(RSA_API::SpectrumTraces::SpectrumTrace1),   // trace # [0, 1, 2]
            25e6,                                                        // start frequency (Hz)
            1.0e9,                                                       // stop frequency (Hz)
            -45.5,                                                       // threshold (dBm) that iniates further processing
            2,                                                           // repititions to loiter on a center frequency
            X_rsa.cutil.helper,                                          // output file-path-name
            -32.11,                                                      // reference level (dBm)
            10e5,                                                        // resolution bandwidth (Hz)
            30e6,                                                        // frequency span (Hz)
            999                                                          // pairs [frequency (Hz), power (dBm)] acquired per trace
        );
        printf("%s\n", X_rsa.cutil.helper);
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


/////////~~~~~~~~END>  task_996.cpp
