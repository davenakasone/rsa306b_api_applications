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


void unit_test_2 (void)
{
    printf("\n%s()  ,  API group 'DEVICE'\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;

        #ifdef UT2_a
            rsa.print_device();
            rsa.device_connect();
            rsa.print_device();
        #endif
        #ifdef UT2_b
            for (int ii = 0; ii < 21; ii++)
            {
                
                if (ii % 3)
                {
                    rsa.device_connect();
                }
                else
                {
                    rsa.device_disconnect();
                }
                rsa.device_check_run_state();
                printf("%d)  is connected:  %d\n", 
                    ii, rsa.vars.device.is_connected);
            }
        #endif
        #ifdef UT2_c
            rsa.device_connect();
            for (int ii = 0; ii < 34; ii++)
            {
                rsa.vars.device.event_id = ii % 2;
                if (ii % 3)
                {
                    rsa.device_run();
                }
                else
                {
                    rsa.device_stop();
                }
                rsa.device_check_event();
                rsa.device_check_run_state();
                rsa.device_check_temperature();
                printf("%d) running=  %d  ,  temperature=  %d\n",
                    ii, rsa.vars.device.is_running, rsa.vars.device.is_over_temperature);
                printf("\teventID:  %d  ,  eventOccured:  %d  ,  timestamp:  %ld\n",
                    rsa.vars.device.event_id, rsa.vars.device.event_occured, rsa.vars.device.event_timestamp);
            }
        #endif
        #ifdef UT2_d
            rsa.device_connect();
            rsa.device_prepare_for_run();
            rsa.print_device();
            rsa.device_start_frame_transfer();
            rsa.print_device();
        #endif
        #ifdef UT2_e
            rsa.device_connect();
            rsa.device_run();
            rsa.device_reset();
            /*
                avoid "device_reset" if possible:

                libusb: error [do_close] Device handle closed while transfer was still being processed, but the device is still connected as far as we know
                libusb: error [do_close] A cancellation hasn't even been scheduled on the transfer for which the device is closing
                terminate called without an active exception
                Aborted (core dumped)
            */
        #endif
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_2.cpp
