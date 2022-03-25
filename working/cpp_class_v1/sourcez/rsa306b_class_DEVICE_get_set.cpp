/*
    implementation of the rsa306b_class
    using "DEVICE" function group of the API
    getters and setters for member variables

        public:
            # device_get_id()
            # device_get_info_type()
            # device_get_is_connected()
            # device_get_is_over_temperature()
            # device_get_is_running()
        
        private:
            # _device_set_id
            # _device_set_info_type()
            # _device_set_is_connected()
            # _device_set_is_over_temperature()
            # _device_set_is_running()
*/

#include "../includez/rsa306b_class.h"


/*
    public
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
    public
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
    strcpy(devInfo->apiVersion, this->_device_info_type.apiVersion);
    strcpy(devInfo->fpgaVersion, this->_device_info_type.fpgaVersion);
    strcpy(devInfo->fwVersion, this->_device_info_type.fwVersion);
    strcpy(devInfo->hwVersion, this->_device_info_type.hwVersion);
    strcpy(devInfo->nomenclature, this->_device_info_type.nomenclature);
    strcpy(devInfo->serialNum, this->_device_info_type.serialNum);
}


////~~~~


/*
    public
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
    public
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
    return this->_device_is_over_temperature;
}


////~~~~


/*
    public
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
    return this->_device_is_running;
}


////~~~~


/*
    private
    sets "_device_id" to provided value
*/
int rsa306b::_device_set_id(int new_value)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_device_id = new_value;
    return CALL_SUCCESS;
}


////~~~~


/*
    private
    sets "_device_info_type" when connected
*/
int rsa306b::_device_set_info_type()
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
        return CALL_FAILURE;
    }
    this->_api_return_status = RSA_API::DEVICE_GetInfo(&this->_device_info_type);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////~~~~


/*
    private
    sets "_device_is_connected" to provided value
*/
int rsa306b::_device_set_is_connected(bool new_value)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_device_is_connected = new_value;
    return CALL_SUCCESS;
}


////~~~~


/*
    private
    sets "_device_is_over_temperature" to provided value, when connected
*/
int rsa306b::_device_set_is_over_temperature(bool new_value)
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
        return CALL_FAILURE;
    }
    this->_device_is_over_temperature = new_value;
    return CALL_SUCCESS;
}


////~~~~


/*
    private
    sets "_device_is_running" to provided value, when connected
*/
int rsa306b::_device_set_is_running(bool new_value)
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
        return CALL_FAILURE;
    }
    this->_device_is_running = new_value;
    return CALL_SUCCESS;
}


////////~~~~~~~~END>  rsa306b_class_DEVICE_get_set.cpp
