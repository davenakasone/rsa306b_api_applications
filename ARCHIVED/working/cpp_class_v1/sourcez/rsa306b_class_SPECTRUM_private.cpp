/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API
    private functions for internal use

        public:
            # none
            
        private:
            < 1 > _spectrum_init()
            < 2 > _spectrum_create_frequency_array()
            < 3 > _spectrum_trace_number_2_index()
            < 4 > _spectrum_find_peak_index(RSA_API::SpectrumTraces trace_number)
        
*/

#include "../includez/rsa306b_class.h"


/*
    private < 1 >
    called after a connection
    prepares spectrum for use:
        (a) measurement is disabled
        (b) default applied 
        (c) traces are assigned and disabled, all 3
        (d) limits are updated, _spectrum_limits_type
        (e) settings updated, _spectrum_settings_type
        (f) settings updated, _spectrum_trace_info_type
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
    // (a)
    this->_spectrum_measurement_enabled = false;
    this->_gp_return_status = this->_spectrum_set_measurement_enabled(
        this->_spectrum_measurement_enabled);  
    this->_gp_error_check();

    // (b)
    this->_api_return_status = RSA_API::SPECTRUM_SetDefault();
    this->_api_error_check();

    // (c)
    this->spectrum_get_3_traces_type(&this->_spectrum_3_traces_type);
    this->_gp_return_status = this->_spectrum_set_3_traces_type(&this->_spectrum_3_traces_type);
    this->_gp_error_check();

    // (d)
    this->_gp_return_status = this->_spectrum_set_limits_type();
    this->_gp_error_check();

    // (e)
    this->spectrum_get_settings_type(&this->_spectrum_settings_type);
    this->_gp_return_status = this->_spectrum_set_settings_type(
        &this->_spectrum_settings_type);
    this->_gp_error_check();

    // (f)
    this->_spectrum_set_trace_info_type();
}


////~~~~


/*
    private < 2 >
    called at end of "spectrum_prepare()"
    if built-in checks are good,
    this functions prepares the frequency array
    "_spectrum_frequency_array" is valid for all 3 traces
*/
void rsa306b::_spectrum_create_frequency_array()
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
    if (this->_spectrum_frequency_array == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfrequency array not allocated\n");
        #endif
        return;
    }
	for (int ii = 0; ii < this->_spectrum_settings_type.traceLength; ii++)
	{
		this->_spectrum_frequency_array[ii] = 
            this->_spectrum_settings_type.actualStartFreq + 
            this->_spectrum_settings_type.actualFreqStepSize * ii;
	}
}


////~~~~


/*
    private < 3 >
    given a trace number, enum in converted to an index 
    avoids casting
    returns INIT_INT if invalid request
*/
int rsa306b::_spectrum_trace_number_2_index
(
    RSA_API::SpectrumTraces trace_number
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    int casted = this->INIT_INT;
    if (trace_number != RSA_API::SpectrumTrace1 &&
        trace_number != RSA_API::SpectrumTrace2 &&
        trace_number != RSA_API::SpectrumTrace3  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trace selection:  %d\n", (int)trace_number);
        #endif
        return casted;
    }
    switch (trace_number)
    {
        case (RSA_API::SpectrumTrace1) : casted = 0; break;
        case (RSA_API::SpectrumTrace2) : casted = 1; break;
        case (RSA_API::SpectrumTrace3) : casted = 2; break;
        default           : casted = this->INIT_INT; break;
    }
    return casted;
}


////~~~~


/*
    private < 4 >
    returns index of highest measurement,
    if aquisition occured
*/
int rsa306b::_spectrum_find_peak_index
(
    RSA_API::SpectrumTraces trace_number
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    int peak = this->INIT_INT;
    int idx = this->_spectrum_trace_number_2_index(trace_number);
    if (idx == this->INIT_INT)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trace requested:  %d\n", (int)trace_number);
        #endif
        return peak;
    }
    peak = 0;
    for (int ii = 0; ii < this->_spectrum_settings_type.traceLength; ii++)
    {
        if (this->_spectrum_trace_data[idx][ii]  > 
            this->_spectrum_trace_data[idx][peak])
        {
            peak = ii;
        }
    }
    return peak;
}


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_private.cpp
