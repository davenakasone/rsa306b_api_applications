/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API
    private functions for internal use
        public:
            # none
            
        private:
            < 1 > _spectrum_init()
        
*/

#include "../includez/rsa306b_class.h"


/*
    private < 1 >
    called after a connection
    prepares spectrum for use:
        measurement is disabled
        traces are assigned
        traces are disabled

        default applied
        limits are updated
        settings updated
        all 3 traces are updated
        measurement enable is updated

*/
void rsa306b::_spectrum_init()
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
    this->_spectrum_set_measurement_enabled(false);  // also stops running device
    this->_spectrum_traces_select[0] = RSA_API::SpectrumTrace1;
    this->_spectrum_trace_enabled[0] = false;
    this->_spectrum_traces_select[1] = RSA_API::SpectrumTrace2;
    this->_spectrum_trace_enabled[1] = false;
    this->_spectrum_traces_select[2] = RSA_API::SpectrumTrace3;
    this->_spectrum_trace_enabled[2] = false;
    this->_api_return_status = RSA_API::SPECTRUM_SetDefault();

    this->_spectrum_set_limits_type();

    // GetTraceType(), 0, 1, 2
    // 

}


////~~~~



////////~~~~~~~~END>  rsa306b_class_SPECTRUM_private.cpp
