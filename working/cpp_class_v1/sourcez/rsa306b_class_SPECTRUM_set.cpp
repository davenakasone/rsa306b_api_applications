/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API

        public:
            # none
            
        private:
            < 1 > _spectrum_set_limits_type()
            < 2 > _spectrum_set_measurement_enabled()
        
*/

#include "../includez/rsa306b_class.h"


/*
    private < 1 >
    gets the spectrum limits using the API
    these values are used to enforce limits
    should be called when device is connected
*/
void rsa306b::_spectrum_set_limits_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    } 
    this->_api_return_status = RSA_API::SPECTRUM_GetLimits(
        &this->_spectrum_limits_type);
    this->_api_error_check();
}


////~~~~


/*
    private < 2 >
    the device must be connected
    setting value must be different than current
    a running device is stopped
    new measurement state is sent
    status of measurement state is updated to member
*/
void rsa306b::_spectrum_set_measurement_enabled
(
    bool new_value
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    } 
    if (new_value == false                        && 
        this->_spectrum_measurement_enabled == false)
    {
        #ifdef DEBUG_MIN
            printf("\nmeasurement already disabled\n");
        #endif
        return;
    }
    if (new_value == true                       && 
        this->_spectrum_measurement_enabled == true)
    {
        #ifdef DEBUG_MIN
            printf("\nmeasurement already enabled\n");
        #endif
        return;
    }
    this->device_stop();
    this->_api_error_check();
    this->_api_return_status = RSA_API::SPECTRUM_SetEnable(new_value);
    this->_api_error_check();
    this->_api_return_status = RSA_API::SPECTRUM_GetEnable(
        &this->_spectrum_measurement_enabled);
    this->_api_error_check();
}


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_set.cpp
