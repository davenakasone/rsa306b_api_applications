/*
    implementation of the rsa306b_class
    using "DEVICE" function group of the API
    getters and setters for member variables

        public:
            < 1 >  device_get_id()
            < 2 >  device_get_info_type()
            < 3 >  device_get_is_connected()
            < 4 >  device_get_is_over_temperature()
            < 5 >  device_get_is_running()
        
        private:
            < 1 >  _device_set_id
            < 2 >  _device_set_info_type()
            < 3 >  _device_set_is_connected()
            < 4 >  _device_set_is_over_temperature()
            < 5 >  _device_set_is_running()
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    returns current value of "_device_id"
*/
int rsa306b::device_get_id()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
    }
    return this->_device_id;
}


////~~~~


/*
    public < 2 >
    populates current values of "DEVICE_INFO" struct, 6 strings
*/
void rsa306b::device_get_info_type(RSA_API::DEVICE_INFO* devInfo)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
    }

    this->_device_set_info_type();
    strcpy(devInfo->apiVersion, this->_device_info_type.apiVersion);
    strcpy(devInfo->fpgaVersion, this->_device_info_type.fpgaVersion);
    strcpy(devInfo->fwVersion, this->_device_info_type.fwVersion);
    strcpy(devInfo->hwVersion, this->_device_info_type.hwVersion);
    strcpy(devInfo->nomenclature, this->_device_info_type.nomenclature);
    strcpy(devInfo->serialNum, this->_device_info_type.serialNum);
}


////~~~~


/*
    public < 3 >
    returns current value of "_device_is_connected"
*/
bool rsa306b::device_get_is_connected()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    return this->_device_is_connected;
}


////~~~~


/*
    public < 4 >
    returns current value of "_device_is_over_temperature"
*/
bool rsa306b::device_get_is_over_temperature()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
    }
    else
    {
        this->_device_set_is_over_temperature();
    }
    return this->_device_is_over_temperature;
}


////~~~~


/*
    public < 5 >
    returns current value of "_device_is_running"
*/
bool rsa306b::device_get_is_running()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, values as initialized\n");
        #endif
    }
    this->_device_set_is_running();
    return this->_device_is_running;
}


////~~~~


/*
    private < 1 >
    sets "_device_id" to provided value
    should only be set while connecting
*/
void rsa306b::_device_set_id(int new_value)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_device_id = new_value;
}


////~~~~


/*
    private < 2 >
    sets "_device_info_type" when connected
*/
void rsa306b::_device_set_info_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, not possible to set values\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::DEVICE_GetInfo(&this->_device_info_type);
    this->_api_error_check();
}


////~~~~


/*
    private < 3 >
    sets "_device_is_connected" to provided value
    should only be set when connecting or disconnecting
*/
void rsa306b::_device_set_is_connected(bool new_value)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_device_is_connected = new_value;
}


////~~~~


/*
    private < 4 >
    sets "_device_is_over_temperature", if connected
*/
void rsa306b::_device_set_is_over_temperature()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, not possible to set values\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::DEVICE_GetOverTemperatureStatus(
            &this->_device_is_over_temperature);
    this->_api_error_check();
}


////~~~~


/*
    private < 5 >
    sets "_device_is_running" to provided value, if connected
*/
void rsa306b::_device_set_is_running()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, not possible to set values\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::DEVICE_GetEnable(
        &this->_device_is_running);
    this->_api_error_check();
}


////////~~~~~~~~END>  rsa306b_class_DEVICE_get_set.cpp
