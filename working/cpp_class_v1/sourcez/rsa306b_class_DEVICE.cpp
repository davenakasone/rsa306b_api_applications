/*
    implementation of the rsa306b_class
    using "DEVICE" function group of the API
        # error_check()
        # rsa_connect()
        # print_temperature()
        # print_device_info()
        # rsa_reset()
        # rsa_run()
        # rsa_stop()
*/

#include "../includez/rsa306b_class.h"


/*
    private
    matches current state of the ReturnStatus variable to the enum
    indicates if an error has occured, otherwise does nothing
    good practice to call after each API function is used, unless speed is needed
*/
void rsa306b::error_check()
{
    if (this->api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_ERR
            const char* temp;
            temp = RSA_API::DEVICE_GetErrorString(this->api_return_status);
            snprintf(this->device_error_string, BUF_D, "error code:  %d  ,  error message:  %s",
            this->api_return_status, temp);
            printf("\t!!! ERROR !!!  %s\n", this->device_error_string);
        #endif
        #ifdef DEBUG_MIN
            printf("\t!!! ERROR !!!\n");
        #endif
    }
}


////~~~~


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

    this->api_return_status = RSA_API::DEVICE_Search(
        &this->devices_found, this->device_ids, this->device_serials, this->device_types);
    this->error_check();
    if (this->devices_found == 1)
    {
        this->api_return_status = RSA_API::DEVICE_Connect(this->device_ids[0]);
        this->error_check();
        if (this->api_return_status == RSA_API::noError) 
        {
            this->is_connected = true;
        }
        else
        {
            #ifdef DEBUG_MIN
                printf("connection failure\n");
            #endif
            return;
        }
        #ifdef DEBUG_MIN
            printf("\t~ CONNECTED ~\n");
        #endif
        this->rsa_align();
        this->print_device_info();
        this->print_temperature();
        this->print_alignment();
    }
    else if (this->devices_found > 1)
    {
        #ifdef DEBUG_MIN
            printf("too many devices for the program, only connect on spectrum analyzer\n");
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
void rsa306b::print_temperature()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->api_return_status = RSA_API::DEVICE_GetOverTemperatureStatus(&this->is_over_temperature_limit);
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
void rsa306b::print_device_info()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("there is no device connected\n");
        #endif
        return;
    }

    this->api_return_status = RSA_API::DEVICE_GetAPIVersion(this->device_api_version);
    this->error_check();
    this->api_return_status = RSA_API::DEVICE_GetFWVersion(this->device_firm_ware_version);
    this->error_check();
    this->api_return_status = RSA_API::DEVICE_GetFPGAVersion(this->device_fpga_version);
    this->error_check();
    this->api_return_status = RSA_API::DEVICE_GetHWVersion(this->device_hardware_version);
    this->error_check();
    this->api_return_status = RSA_API::DEVICE_GetNomenclature(this->device_nomenclature);
    this->error_check();
    printf("\ndevice information >>>\n");
    printf("\tAPI Version:        %s\n", this->device_api_version);
    printf("\tDevice ID:          %d\n", this->device_ids[0]);
    printf("\tDevice Type:        %s\n", this->device_types[0]);
    printf("\tFirm Ware Version:  %s\n", this->device_firm_ware_version);
    printf("\tFPGA Version:       %s\n", this->device_fpga_version);
    printf("\tHardware Version:   %s\n", this->device_hardware_version);
    printf("\tNomenclature:       %s\n", this->device_nomenclature);
    printf("\tSerial Number:      %s\n", this->device_serials[0]);
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
    this->api_return_status = RSA_API::DEVICE_Reset(this->device_ids[0]);
    if (this->api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("reset FAILURE\n");
        #endif
        while (this->api_return_status != RSA_API::noError)
        {
            sleep(3);
            this->api_return_status = RSA_API::DEVICE_Reset(this->device_ids[0]);
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
