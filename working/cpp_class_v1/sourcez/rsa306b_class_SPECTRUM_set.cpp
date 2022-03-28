/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API

        public:
            # none
            
        private:
            < 1 > _spectrum_set_limits_type()
        
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


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_set.cpp
