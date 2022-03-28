/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API

        public:
            < 1 >  spectrum_get_limits_type()
            
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


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_get.cpp
