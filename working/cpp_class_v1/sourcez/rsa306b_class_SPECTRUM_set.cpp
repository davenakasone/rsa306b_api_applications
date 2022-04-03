/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API
    the setters

        public:
            # none
            
        private:
            < 1 > _spectrum_set_limits_type()
            < 2 > _spectrum_set_measurement_enabled()
            < 3 > _spectrum_set_settings_type()
            < 4 > _spectrum_set_trace_info_type()
            < 5 > _spectrum_set_3_traces_type()
        
*/

#include "../includez/rsa306b_class.h"


/*
    private < 1 >
    gets the spectrum limits using the API
    these values are used to enforce limits
    should be called when device is connected
    returning a failure should be used to halt operations
    returning a success should be used to continue operations
*/
int rsa306b::_spectrum_set_limits_type()
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
        return CALL_FAILURE;
    } 
    this->_api_return_status = RSA_API::SPECTRUM_GetLimits(
        &this->_spectrum_limits_type);
    this->_api_error_check();
    if (this->_api_return_status != RSA_API::noError)
    {
        return CALL_FAILURE;
    }
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 2 >
    the device must be connected
    setting value must be different than current
    a running device is stopped
    new measurement state is sent
    status of measurement state is updated to member
    returning a failure should be used to halt operations
    returning a success should be used to continue operations
*/
int rsa306b::_spectrum_set_measurement_enabled
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
        return CALL_FAILURE;
    } 
    if (new_value == false                        && 
        this->_spectrum_measurement_enabled == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tmeasurement already disabled\n");
        #endif
        return CALL_SUCCESS;
    }
    if (new_value == true                       && 
        this->_spectrum_measurement_enabled == true)
    {
        #ifdef DEBUG_MIN
            printf("\n\tmeasurement already enabled\n");
        #endif
        return CALL_SUCCESS;
    }
    this->device_stop();
    this->_api_error_check();
    this->_api_return_status = RSA_API::SPECTRUM_SetEnable(new_value);
    this->_api_error_check();
    if (this->_api_return_status != RSA_API::noError)
    {
        return CALL_FAILURE;
    }
    this->_api_return_status = RSA_API::SPECTRUM_GetEnable(
        &this->_spectrum_measurement_enabled);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 3 >
    user provides desired settings
    device is stopped, if needed
    new settings(s) are range-validated to device limits
    _spectrum_settings_type member is passed to API to set
    returning a failure should be used to halt operations
    returning a success should be used to continue operations
    
*/
int rsa306b::_spectrum_set_settings_type
(
    RSA_API::Spectrum_Settings* new_settings
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
        return CALL_FAILURE;
    } 
    this->device_stop();
    this->_spectrum_set_limits_type();

    if (new_settings->span > this->_spectrum_limits_type.maxSpan ||
        new_settings->span < this->_spectrum_limits_type.minSpan  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tspan is out of range:  %0.3lf  !!!  [  %0.3lf  ,  %0.3lf ]\n",
                new_settings->span,
                this->_spectrum_limits_type.minSpan,
                this->_spectrum_limits_type.maxSpan);
        #endif
        return CALL_FAILURE;
    }
    if (new_settings->rbw > this->_spectrum_limits_type.maxRBW ||
        new_settings->rbw < this->_spectrum_limits_type.minRBW  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tRBW is out of range:  %0.3lf  !!!  [  %0.3lf  ,  %0.3lf ]\n",
                new_settings->rbw,
                this->_spectrum_limits_type.minRBW,
                this->_spectrum_limits_type.maxRBW);
        #endif
        return CALL_FAILURE;
    }
    if (new_settings->vbw > this->_spectrum_limits_type.maxVBW ||
        new_settings->vbw < this->_spectrum_limits_type.minVBW  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tVBW is out of range:  %0.3lf  !!!  [  %0.3lf  ,  %0.3lf ]\n",
                new_settings->vbw,
                this->_spectrum_limits_type.minVBW,
                this->_spectrum_limits_type.maxVBW);
        #endif
        return CALL_FAILURE;
    }
    if (new_settings->traceLength > this->_spectrum_limits_type.maxTraceLength ||
        new_settings->traceLength < this->_spectrum_limits_type.minTraceLength  )
    {
        #ifdef DEBUG_MIN
            printf("\n\ttrace length is out of range:  %d  !!!  [  %d ,  %d ]\n",
                new_settings->traceLength,
                this->_spectrum_limits_type.minTraceLength,
                this->_spectrum_limits_type.maxTraceLength);
        #endif
        return CALL_FAILURE;
    }
    if (new_settings->traceLength % 2 == 0)
    {
        #ifdef DEBUG_MIN
            printf("\n\ttraceLength =  %d  ,  must be an odd number\n",
                new_settings->traceLength);
        #endif
        return CALL_FAILURE;
    }
    if (new_settings->window != RSA_API::SpectrumWindow_Kaiser         &&
        new_settings->window != RSA_API::SpectrumWindow_Mil6dB         &&
        new_settings->window != RSA_API::SpectrumWindow_BlackmanHarris &&
        new_settings->window != RSA_API::SpectrumWindow_Rectangle      &&
        new_settings->window != RSA_API::SpectrumWindow_FlatTop        &&
        new_settings->window != RSA_API::SpectrumWindow_Hann            )
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid window selection:  %d\n",
                new_settings->window);
        #endif
        return CALL_FAILURE;
    }
    if (new_settings->verticalUnit != RSA_API::SpectrumVerticalUnit_dBm  &&
        new_settings->verticalUnit != RSA_API::SpectrumVerticalUnit_Watt &&  
        new_settings->verticalUnit != RSA_API::SpectrumVerticalUnit_Volt &&
        new_settings->verticalUnit != RSA_API::SpectrumVerticalUnit_Amp  &&
        new_settings->verticalUnit != RSA_API::SpectrumVerticalUnit_dBmV  )
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid vertical unit selection:  %d\n",
                new_settings->verticalUnit);
        #endif
        return CALL_FAILURE;
    }
    this->_api_return_status = RSA_API::SPECTRUM_SetSettings(
        this->_spectrum_settings_type);
    this->_api_error_check();
    if (this->_api_return_status != RSA_API::noError)
    {
        return CALL_FAILURE;
    }
    this->_api_return_status = RSA_API::SPECTRUM_GetSettings(
        &this->_spectrum_settings_type);
    this->_api_error_check();
    return CALL_SUCCESS;
}


////~~~~


/*
    private < 4 >
    "_specrum_trace_info_type" is quiried
    the aquisition status is validated,
        updating "_spectrum_good_aquisition"
*/
void rsa306b::_spectrum_set_trace_info_type()
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
    this->_api_return_status = RSA_API::SPECTRUM_GetTraceInfo(
        &this->_spectrum_trace_info_type); 
    this->_api_error_check();
    int temp_aqStat = (int)this->_spectrum_trace_info_type.acqDataStatus; 
    int temp_0x1 = (int)RSA_API::AcqDataStatus_ADC_OVERRANGE;
    int temp_0x2 = (int)RSA_API::AcqDataStatus_REF_OSC_UNLOCK;
    int temp_0x10 = (int)RSA_API::AcqDataStatus_LOW_SUPPLY_VOLTAGE;
    int temp_0x20 = (int)RSA_API::AcqDataStatus_ADC_DATA_LOST;
    int temp_mask = (int)RSA_API::AcqDataStatus_VALID_BITS_MASK;
    this->_spectrum_good_aquisition = !(temp_aqStat && temp_mask);
    if (temp_aqStat && temp_0x1)
    {
        #ifdef DEBUG_MIN
            printf("\tinput to ADC was outside operating range\n");
        #endif
        this->_spectrum_good_aquisition = false;
    }
    if (temp_aqStat && temp_0x2)
    {
        #ifdef DEBUG_MIN
            printf("\tloss of locked status on the reference oscillator\n");
        #endif
        this->_spectrum_good_aquisition = false;
    }
    if (temp_aqStat && temp_0x10)
    {
        #ifdef DEBUG_MIN
            printf("\tpower supply below 5 V detected\n");
        #endif
        this->_spectrum_good_aquisition = false;
    }
    if (temp_aqStat && temp_0x20)
    {
        #ifdef DEBUG_MIN
            printf("\tADC data frame samples were dropped\n");
        #endif
        this->_spectrum_good_aquisition = false;
    }
}


////~~~~


/*
    private < 5 >
    updates information on all 3 traces
    new settings are validated
    caller must comply with trace order
*/
int rsa306b::_spectrum_set_3_traces_type
(
    spectrum_3_traces_type* traces3
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
        return CALL_FAILURE;
    } 
    if (traces3 == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate your struct\n");
        #endif
        return CALL_FAILURE;
    }

    // enforced compliance
    traces3->trace_select[0] = RSA_API::SpectrumTrace1;
    traces3->trace_select[1] = RSA_API::SpectrumTrace2;
    traces3->trace_select[2] = RSA_API::SpectrumTrace3;
    for (int ii = 0; ii < 3; ii++)
    {
        if (traces3->detector_select[ii] != RSA_API::SpectrumDetector_PosPeak     &&
            traces3->detector_select[ii] != RSA_API::SpectrumDetector_NegPeak     &&
            traces3->detector_select[ii] != RSA_API::SpectrumDetector_AverageVRMS &&
            traces3->detector_select[ii] != RSA_API::SpectrumDetector_Sample       )
        {
            return CALL_FAILURE;
        }
    }
    for (int ii = 0; ii < 3; ii++)
    {
        this->_api_return_status = RSA_API::SPECTRUM_SetTraceType(
            traces3->trace_select[ii], 
            traces3->trace_enabled[ii],
            traces3->detector_select[ii]);
        this->_api_error_check();
        if (this->_api_return_status != RSA_API::noError)
        {
            return CALL_FAILURE;
        }
    }
    this->spectrum_get_3_traces_type(&this->_spectrum_3_traces_type);
    return CALL_SUCCESS;
}


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_set.cpp
