/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API

        public:
            < 1 >  spectrum_get_limits_type()
            < 2 >  spectrum_get_measurement_enabled()
        private:
            # none
        
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    directly uses the API to get device limits
*/
void rsa306b::spectrum_get_limits_type(RSA_API::Spectrum_Limits* limits)
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
    if (limits == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\tallocate the struct\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::SPECTRUM_GetLimits(limits);
    this->_api_error_check();
}


////~~~~


/*
    public < 2 >
    measurement state is queried and returned
*/
bool rsa306b::spectrum_get_measurement_enabled()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, passing initialized value\n");
        #endif
    } 
    this->_api_return_status = RSA_API::SPECTRUM_GetEnable(
        &this->_spectrum_measurement_enabled);
    this->_api_error_check();
    return this->_spectrum_measurement_enabled;
}


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_get.cpp
