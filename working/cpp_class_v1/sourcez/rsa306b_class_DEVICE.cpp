/*
    implementation of the rsa306b_class
    using "DEVICE" function group of the API
        # error_check()
        # rsa_connect()
        # rsa_check_temperature()
        # rsa_device_info()
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
        const char* temp;
        temp = RSA_API::DEVICE_GetErrorString(this->api_return_status);
        snprintf(this->device_error_string, BUF_D-1, "%s", temp);
        snprintf(this->device_error_string, BUF_D, "error code:  %d  ,  error message:  %s",
        this->api_return_status, temp);
        #ifdef DEBUG_CLI
            printf("\t!!! ERROR !!!  %s\n", this->device_error_string);
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
            #ifdef DEBUG_CLI
                printf("\t<%d> %s/%s()  ,  connection failure\n",
                    __LINE__, __FILE__, __func__);
            #endif
            return;
        }
        #ifdef DEBUG_CLI
            printf("\n\tCONNECTED >>>\n");
        #endif
        this->rsa_device_info();
        this->rsa_check_temperature();
        this->rsa_alignment();
    }
    else if (this->devices_found > 1)
    {
        #ifdef DEBUG_CLI
            printf("too many devices for the program, only connect on spectrum analyzer\n");
        #endif
    }
    else
    {
        #ifdef DEBUG_CLI
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
void rsa306b::rsa_check_temperature()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->api_return_status = RSA_API::DEVICE_GetOverTemperatureStatus(&this->is_over_temperature_limit);
    this->error_check();
    if (this->is_over_temperature_limit == false)
    {
        #ifdef DEBUG_CLI
            printf("the device is under the temperature limit, it is ready for use\n");
        #endif
    }
    else
    {
        #ifdef DEBUG_CLI
            printf("the device is OVER the temperature limit, shut it down now\n");
        #endif
    }
}


////~~~~


/*
    public
    call when device is connected, or no query is possible
    when called with a connected device:
        basic info is printed to stdout
        indicates if temperature is under the limit
*/
void rsa306b::rsa_device_info()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_CLI
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

    #ifdef DEBUG_CLI
        printf("\t\tAPI Version:        %s\n", this->device_api_version);
        printf("\t\tDevice ID:          %d\n", this->device_ids[0]);
        printf("\t\tDevice Type:        %s\n", this->device_types[0]);
        printf("\t\tFirm Ware Version:  %s\n", this->device_firm_ware_version);
        printf("\t\tFPGA Version:       %s\n", this->device_fpga_version);
        printf("\t\tHardware Version:   %s\n", this->device_hardware_version);
        printf("\t\tNomenclature:       %s\n", this->device_nomenclature);
        printf("\t\tSerial Number:      %s\n", this->device_serials[0]);
    #endif
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
        #ifdef DEBUG_CLI
            printf("device can't reset, nothing is connected\n");
        #endif
        return;
    }
    this->rsa_stop();
    this->api_return_status = RSA_API::DEVICE_Reset(this->device_ids[0]);
    if (this->api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_CLI
            printf("reset FAILURE\n");
        #endif
        while (this->api_return_status != RSA_API::noError)
        {
            this->api_return_status = RSA_API::DEVICE_Reset(this->device_ids[0]);
            sleep(1);
        }
    }
    #ifdef DEBUG_CLI
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
        #ifdef DEBUG_CLI
            printf("device can't run, nothing is connected\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::DEVICE_GetEnable(&this->is_running);
    this->error_check();
    if (is_running == true)
    {
        #ifdef DEBUG_CLI
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
    #ifdef DEBUG_CLI
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
        #ifdef DEBUG_CLI
            printf("device can't stop, nothing is connected\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::DEVICE_GetEnable(&this->is_running);
    this->error_check();
    if (is_running == false)
    {
        #ifdef DEBUG_CLI
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
    #ifdef DEBUG_CLI
        printf("device stopped\n");
    #endif
}


////////~~~~~~~~END>  rsa306b_class_DEVICE.cpp
