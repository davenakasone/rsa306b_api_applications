/*
    implementation of the rsa306b_class
    using "DEVICE" function group of the API
        # error_check()
        # rsa_connect()
        # print_device_temperature()
        # print_device_info()
        # rsa_reset()
        # rsa_run()
        # rsa_stop()
*/

#include "../includez/rsa306b_class.h"


/*
    public
    first searches for suitable device to connect to
        there must be only one deveice connected
    if the connection is successful, the device information is printed to stdout
        temperature and alignment are also verified
*/
void rsa306b::rsa_connect()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    int devices_found;
    int device_ids[RSA_API::DEVSRCH_MAX_NUM_DEVICES];
    char device_serials[RSA_API::DEVSRCH_MAX_NUM_DEVICES]
        [RSA_API::DEVSRCH_SERIAL_MAX_STRLEN];
    char device_types[RSA_API::DEVSRCH_MAX_NUM_DEVICES]
        [RSA_API::DEVSRCH_TYPE_MAX_STRLEN];

    this->api_return_status = RSA_API::DEVICE_Search(
        &devices_found, 
        device_ids, 
        device_serials, 
        device_types);
    this->error_check();

    if (devices_found == 1)
    {
        this->device_id = device_ids[0];
        this->api_return_status = RSA_API::DEVICE_GetInfo(
                &this->device_info_type);
        this->error_check();
        this->api_return_status = RSA_API::DEVICE_Connect(
                this->device_id);
        this->error_check();

        if (this->api_return_status != RSA_API::noError) 
        {
            #ifdef DEBUG_MIN
                printf("connection failure\n");
            #endif
            return;
        }
        #ifdef DEBUG_MIN
            printf("\t~ CONNECTED ~\n");
        #endif
        this->is_connected = true;
        this->record_start_time();
        this->rsa_align();
        this->print_device_info();
        this->print_device_temperature();
        this->print_alignment();
    }
    else if (devices_found > 1)
    {
        #ifdef DEBUG_MIN
            printf("too many devices, only connect one\n");
        #endif
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("no devices were found\n");
        #endif
    }
}


////~~~~


/*
    public
    checks the temperature of the device
    if the device is over temperature limit, operations should halt
*/
void rsa306b::print_device_temperature()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->api_return_status = RSA_API::DEVICE_GetOverTemperatureStatus(
            &this->is_over_temperature_limit);
    this->error_check();
    printf("\ndevice temperature status >>>\n");
    if (this->is_over_temperature_limit == false)
    {
            printf("\tunder the temperature limit, ready for use\n");
    }
    else
    {
            printf("\tOVER the temperature limit, shut down now\n");
    }
}


////~~~~


/*
    public
    call when device is connected, or no query is possible
    when called with a connected device
    basic info is printed to stdout
*/
void rsa306b::print_device_all()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("there is no device connected\n");
        #endif
        return;
    }
    printf("\ndevice information >>>\n");
    printf("\tAPI Version:        %s\n", this->_device_info_type.apiVersion);
    printf("\tDevice ID:          %d\n", this->_device_id);
    printf("\tFirm Ware Version:  %s\n", this->_device_info_type.fwVersion);
    printf("\tFPGA Version:       %s\n", this->_device_info_type.fpgaVersion);
    printf("\tHardware Version:   %s\n", this->_device_info_type.hwVersion);
    printf("\tNomenclature:       %s\n", this->_device_info_type.nomenclature);
    printf("\tSerial Number:      %s\n", this->_device_info_type.serialNum);
}


////~~~~


/*
    public
    resets the device, if needed
    blocks until reset is achieved
    halts running, if device is currently running
*/
void rsa306b::rsa_reset()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device can't reset, nothing is connected\n");
        #endif
        return;
    }
    this->rsa_stop();
    this->api_return_status = RSA_API::DEVICE_Reset(this->device_id);
    if (this->api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("reset FAILURE\n");
        #endif
        while (this->api_return_status != RSA_API::noError)
        {
            sleep(3);
            this->api_return_status = RSA_API::DEVICE_Reset(this->device_id);
        }
    }
    #ifdef DEBUG_MIN
        printf("device was reset\n");
    #endif
}


////~~~~


/*
    public
    allows the device to run, if connected
    sets "is_running"
*/
void rsa306b::rsa_run()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device can't run, nothing is connected\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::DEVICE_GetEnable(&this->is_running);
    this->error_check();
    if (is_running == true)
    {
        #ifdef DEBUG_MIN
            printf("device was already running\n");
        #endif
        return;
    }
    else
    {
        this->api_return_status = RSA_API::DEVICE_Run();
        this->error_check();
        is_running = true;
    }
    #ifdef DEBUG_MIN
        printf("device is running\n");
    #endif
}


////~~~~


/*
    public
    stops the device, if connected
    sets "is_running"
*/
void rsa306b::rsa_stop()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("device can't stop, nothing is connected\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::DEVICE_GetEnable(&this->is_running);
    this->error_check();
    if (is_running == false)
    {
        #ifdef DEBUG_MIN
            printf("device was already stopped\n");
        #endif
        return;
    }
    else
    {
        this->api_return_status = RSA_API::DEVICE_Stop();
        this->error_check();
        is_running = false;
    }
    #ifdef DEBUG_MIN
        printf("device stopped\n");
    #endif
}


////////~~~~~~~~END>  rsa306b_class_DEVICE.cpp
