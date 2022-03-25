/*
    unit test # 2

    goals:
        - instance constructs and destructs properly
        - the "DEVICE" members variables are get and set correctly
        - the "DEVICE" member functions interact with the API correctly
    
    note that reseting causes a USB disconnection,
        which produces a NULL status in -libcyusb_shared,
            then there is a core dump and the program crashes
        so, either remove reset from the class, or learn about it more
*/

#include "unit_tests.h"

//#define CAUSE_CORE_DUMP 666 // activate this to see how bad DEVICE_Rest() is


void unit_test_2 (void)
{
    printf("\n%s()  ,  testing the 'DEVICE' section of the class\n", __func__);
    {
        bool connected = true;
        bool running = true;
        bool temperature = true;
        int d_id = -11;
        RSA_API::DEVICE_INFO dev_info;
        rsa306b my_rsa;    // constructor is called

        connected = my_rsa.device_get_is_connected();
        running = my_rsa.device_get_is_running();
        temperature = my_rsa.device_get_is_over_temperature();
        d_id = my_rsa.device_get_id();
        my_rsa.device_get_info_type(&dev_info);
        my_rsa.device_print_all();
        printf("\nget 'DEVICE' variables >>>\n");
        printf("\t_device_is_connected            :  %d\n", connected);
        printf("\t_device_id                      :  %d\n", d_id);
        printf("\t_device_is_running              :  %d\n", running);
        printf("\t_device_is_over_temperature     :  %d\n", temperature);
        printf("\t_device_info_type.apiVersion    :  %s\n", dev_info.apiVersion);
        printf("\t_device_info_type.fpgaVersion   :  %s\n", dev_info.fpgaVersion);
        printf("\t_device_info_type.fwVersion     :  %s\n", dev_info.fwVersion);
        printf("\t_device_info_type.hwVersion     :  %s\n", dev_info.hwVersion);
        printf("\t_device_info_type.nomenclature  :  %s\n", dev_info.nomenclature);
        printf("\t_device_info_type.serialNum     :  %s\n", dev_info.serialNum);

        my_rsa.device_connect();
        my_rsa.device_prepare_run();
        my_rsa.device_start_frame_transfer();

        connected = my_rsa.device_get_is_connected();
        running = my_rsa.device_get_is_running();
        temperature = my_rsa.device_get_is_over_temperature();
        d_id = my_rsa.device_get_id();
        my_rsa.device_get_info_type(&dev_info);
        printf("\nget 'DEVICE' variables >>>\n");
        printf("\t_device_is_connected            :  %d\n", connected);
        printf("\t_device_id                      :  %d\n", d_id);
        printf("\t_device_is_running              :  %d\n", running);
        printf("\t_device_is_over_temperature     :  %d\n", temperature);
        printf("\t_device_info_type.apiVersion    :  %s\n", dev_info.apiVersion);
        printf("\t_device_info_type.fpgaVersion   :  %s\n", dev_info.fpgaVersion);
        printf("\t_device_info_type.fwVersion     :  %s\n", dev_info.fwVersion);
        printf("\t_device_info_type.hwVersion     :  %s\n", dev_info.hwVersion);
        printf("\t_device_info_type.nomenclature  :  %s\n", dev_info.nomenclature);
        printf("\t_device_info_type.serialNum     :  %s\n", dev_info.serialNum);

        #ifdef CAUSE_CORE_DUMP
            my_rsa.device_reset();  // try not to use this, or remove it from the class
        #endif
        my_rsa.device_stop();
        my_rsa.device_print_all();
        my_rsa.device_disconnect();
        my_rsa.device_print_all();

        my_rsa.device_connect();
        my_rsa.device_run();
        my_rsa.device_print_all();
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_2.cpp
