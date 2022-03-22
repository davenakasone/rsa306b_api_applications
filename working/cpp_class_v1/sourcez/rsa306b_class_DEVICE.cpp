/*
    implementation of the rsa306b_class
    using "DEVICE" function group of the API
        # error_check()
        # rsa_connect()
        # rsa_device_info()
        # rsa_check_temperature()
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
        printf("\t!!! ERROR !!!  %s\n", this->device_error_string);
    }
}


////~~~~


/*
    public
    first searches for suitable device to connect to
        there must be only one deveice connected
    if the connection is successful, the device information is printed to stdout
*/
void rsa306b::rsa_connect()
{
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
            printf("<%d> %s/%s()  ,  connection failure\n",
                __LINE__, __FILE__, __func__);
            return;
        }
        printf("\n\tCONNECTED >>>\n");
        this->rsa_device_info();
    }
    else if (this->devices_found > 1)
    {
        printf("too many devices for the program, only connect on spectrum analyzer\n");
    }
    else
    {
        printf("no devices were found\n");
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
    if (this->is_connected == false)
    {
        printf("there is no device connected\n");
        return;
    }

    this->api_return_status = RSA_API::DEVICE_GetAPIVersion(this->device_api_version);
    this->error_check();
    printf("\t\tAPI Version:        %s\n", this->device_api_version);
    printf("\t\tDevice ID:          %d\n", this->device_ids[0]);
    printf("\t\tDevice Type:        %s\n", this->device_types[0]);
    this->api_return_status = RSA_API::DEVICE_GetFWVersion(this->device_firm_ware_version);
    this->error_check();
    printf("\t\tFirm Ware Version:  %s\n", this->device_firm_ware_version);
    this->api_return_status = RSA_API::DEVICE_GetFPGAVersion(this->device_fpga_version);
    this->error_check();
    printf("\t\tFPGA Version:       %s\n", this->device_fpga_version);
    this->api_return_status = RSA_API::DEVICE_GetHWVersion(this->device_hardware_version);
    this->error_check();
    printf("\t\tHardware Version:   %s\n", this->device_hardware_version);
    this->api_return_status = RSA_API::DEVICE_GetNomenclature(this->device_nomenclature);
    this->error_check();
    printf("\t\tNomenclature:       %s\n", this->device_nomenclature);
    printf("\t\tSerial Number:      %s\n", this->device_serials[0]);
}


/*
    public
    checks the temperature of the device
    if the device is over temperature limit, operations should halt
*/
void rsa306b::rsa_check_temperature()
{
    this->api_return_status = RSA_API::DEVICE_GetOverTemperatureStatus(&this->is_over_temperature_limit);
    this->error_check();
    if (this->is_over_temperature_limit == false)
    {
        printf("the device is under the temperature limit, it is ready for use\n");
    }
    else
    {
        printf("the device is OVER the temperature limit, shut it down now\n");
    }
}

////////~~~~~~~~END>  rsa306b_class_DEVICE.cpp
