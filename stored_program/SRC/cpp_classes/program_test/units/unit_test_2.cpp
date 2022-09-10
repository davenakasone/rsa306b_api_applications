/*
    unit test # 2, API group "DEVICE"

    this section of the class is very important for all other sections

    goals:
        - copiers, getters, and setters operate correctly
        - functions using the API execute as intended
        - the spectrum analyzer can be controlled by the class
*/

#include "../testz.h"

//#define UT2_a 1    // basic connection
//#define UT2_b 2    // sporadic connect/disconnect
//#define UT2_c 3    // run, stop, checks    (need to configure before checking for events)
#define UT2_d 4    // prepare and aquire
//#define UT2_e 5    // just don't do it
// extern rsa306b_class X_rsa;
// extern timer_class X_timer;


void unit_test_2 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  API group 'DEVICE'\n", __func__);
X_timer.time_split_start();                      
#endif    
////~~~~
    
    #ifdef UT2_a
        X_rsa.print_device();
        X_rsa.device_connect();
        X_rsa.print_device();
    #endif
    #ifdef UT2_b
        for (int ii = 0; ii < 21; ii++)
        {
            
            if (ii % 3)
            {
                X_rsa.device_connect();
            }
            else
            {
                X_rsa.device_disconnect();
            }
            X_rsa.device_check_run_state();
            printf("%d)  is connected:  %d\n", 
                ii, X_rsa.vars.device.is_connected);
        }
    #endif
    #ifdef UT2_c
        X_rsa.device_connect();
        for (int ii = 0; ii < 34; ii++)
        {
            X_rsa.vars.device.event_id = ii % 2;
            if (ii % 3)
            {
                X_rsa.device_run();
            }
            else
            {
                X_rsa.device_stop();
            }
            X_rsa.device_check_event();
            X_rsa.device_check_run_state();
            X_rsa.device_check_temperature();
            printf("%d) running=  %d  ,  temperature=  %d\n",
                ii, X_rsa.vars.device.is_running, X_rsa.vars.device.is_over_temperature);
            printf("\teventID:  %d  ,  eventOccured:  %d  ,  timestamp:  %ld\n",
                X_rsa.vars.device.event_id, X_rsa.vars.device.event_occured, X_rsa.vars.device.event_timestamp);
        }
    #endif
    #ifdef UT2_d
        X_rsa.device_connect();
        X_rsa.device_prepare_for_run();
        X_rsa.print_device();
        X_rsa.device_start_frame_transfer();
        X_rsa.print_device();
    #endif
    #ifdef UT2_e
        X_rsa.device_connect();
        X_rsa.device_run();
        X_rsa.device_reset();
        /*
            avoid "device_reset" if possible:

            libusb: error [do_close] Device handle closed while transfer was still being processed, but the device is still connected as far as we know
            libusb: error [do_close] A cancellation hasn't even been scheduled on the transfer for which the device is closing
            terminate called without an active exception
            Aborted (core dumped)
        */
    #endif
    
////~~~~
#ifdef WAIT_ENTER_CLEAR
X_timer.time_split_stop();
X_timer.print_both();
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif    
}


////////~~~~~~~~END>  unit_test_2.cpp
