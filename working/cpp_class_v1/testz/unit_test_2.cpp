/*
    unit test # 2, "DEVICE" section

    goals:
        - instance constructs and destructs properly
        - the "DEVICE" members variables are get and set correctly
        - the "DEVICE" member functions interact with the API correctly
        - every other section uses this, future tests follow
    
    note that reseting causes a USB disconnection,
        which produces a NULL status in -libcyusb_shared,
            then there is a core dump and the program crashes
        so, either remove reset from the class, or learn about it more
*/

#include "unit_tests.h"

//#define CAUSE_CORE_DUMP 666 // activate this to see how bad DEVICE_Rest() is

struct ut2
{
    bool connected;
    bool running;
    bool temperature;
    int d_id;
    RSA_API::DEVICE_INFO dev_info;
}; typedef struct ut2 ut2;

void ut2_print(ut2* stc);
void ut2_get(ut2* stc, rsa306b* RSA);


void unit_test_2 (void)
{
    printf("\n%s()  ,  testing the 'DEVICE' section of the class\n", __func__);
    {
        ut2 test;                   // holds variables needed for testing
        test.connected = true;
        test.running = true;
        test.temperature = true;    
        test.d_id = -11;
        rsa306b rsa;                // constructor is called

        //
        // not connected, should be rejected
        ut2_get(&test, &rsa);
        rsa.device_print_all();
        ut2_print(&test);
        //
        //
        rsa.device_connect();
        rsa.device_prepare_run();
        rsa.device_start_frame_transfer();
        ut2_get(&test, &rsa);
        ut2_print(&test);
        //
        #ifdef CAUSE_CORE_DUMP
            my_rsa.device_reset();  // try not to use this, maybe good to remove it from the class
        #endif
        //
        // observe stopped device, disconnected device
        rsa.device_stop();
        rsa.device_print_all();
        rsa.device_disconnect();
        rsa.device_print_all();
        //
        // connecte again and observe running device
        rsa.device_connect();
        rsa.device_run();
        rsa.device_print_all();
        //
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////~~~~


void ut2_print
(
    ut2* stc
)
{
    printf("\nget 'DEVICE' variables >>>\n");
    printf("\t_device_is_connected            :  %d\n", stc->connected);
    printf("\t_device_id                      :  %d\n", stc->d_id);
    printf("\t_device_is_running              :  %d\n", stc->running);
    printf("\t_device_is_over_temperature     :  %d\n", stc->temperature);
    printf("\t_device_info_type.apiVersion    :  %s\n", stc->dev_info.apiVersion);
    printf("\t_device_info_type.fpgaVersion   :  %s\n", stc->dev_info.fpgaVersion);
    printf("\t_device_info_type.fwVersion     :  %s\n", stc->dev_info.fwVersion);
    printf("\t_device_info_type.hwVersion     :  %s\n", stc->dev_info.hwVersion);
    printf("\t_device_info_type.nomenclature  :  %s\n", stc->dev_info.nomenclature);
    printf("\t_device_info_type.serialNum     :  %s\n", stc->dev_info.serialNum);
}


////~~~~


void ut2_get
(
    ut2* stc, 
    rsa306b* RSA
)
{
    stc->connected = RSA->device_get_is_connected();
    stc->running = RSA->device_get_is_running();
    stc->temperature = RSA->device_get_is_over_temperature();
    stc->d_id = RSA->device_get_id();
    RSA->device_get_info_type(&stc->dev_info);
}


////////~~~~~~~~END>  unit_test_2.cpp
