/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API
    the getters
    
        public:
            < 1 >  spectrum_get_limits_type()
            < 2 >  spectrum_get_measurement_enabled()
            < 3 >  spectrum_get_settings_type()
            < 4 >  spectrum_get_trace_info_type()
            < 5 >  spectrum_get_3_traces_type()

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


////~~~~


/*
    public < 3 >
    directly quiries provided struct for confirmation
    returned by reference
*/
void rsa306b::spectrum_get_settings_type
(
    RSA_API::Spectrum_Settings* settings
)
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
    if (settings == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\tallocate your struct before calling\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::SPECTRUM_GetSettings(settings);
    this->_api_error_check();
}


////~~~~


/*
    public < 4 >
    directly quiries provided struct for confirmation
    returned by reference
*/
void rsa306b::spectrum_get_trace_info_type
(
    RSA_API::Spectrum_TraceInfo* trace_info
)
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
    if (trace_info == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\tallocate your struct before calling\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::SPECTRUM_GetTraceInfo(trace_info);
    this->_api_error_check();
}


////~~~~


/*
    public < 5 >
    user is provided a "spectrum_3_traces_type" struct
    when called, the struct is updated, 
        giving information of the 3 trace types
    the order is enforced
*/
void rsa306b::spectrum_get_3_traces_type
(
    spectrum_3_traces_type* your_3_traces
)
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
    if (your_3_traces == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\tallocate your struct before calling\n");
        #endif
        return;
    }
   
    // enforced compliance
    your_3_traces->trace_select[0] = RSA_API::SpectrumTrace1;
    your_3_traces->trace_select[1] = RSA_API::SpectrumTrace2;
    your_3_traces->trace_select[2] = RSA_API::SpectrumTrace3;
    for (int ii = 0; ii < 3; ii++)
    {
        this->_api_return_status = RSA_API::SPECTRUM_GetTraceType(
            your_3_traces->trace_select[ii], 
            &your_3_traces->trace_enabled[ii],
            &your_3_traces->detector_select[ii]);
        this->_api_error_check();
    }
}


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_get.cpp
