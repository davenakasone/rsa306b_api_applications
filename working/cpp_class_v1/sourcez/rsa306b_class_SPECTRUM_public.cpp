/*
    implementation of the rsa306b_class
    using "SPECTRUM" function group of the API
    public functions for user action

        public:
            < 1 >  spectrum_prepare()
            < 2 >  spectrum_acquire_trace()
            < 3 >  spectrum_index_of_peak_measurement()
            < 4 >  spectrum_collect_data(spectrum_data_collector* data_getter, int index)
            < 5 >  spectrum_print_all()
            
        private:
            # none
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    caller provides:
        center frequency
        reference level
        settings
        settings of 3 traces
    if validation is successful, device is configured
    returns otherwise
    this eliminates need for "config_update_cf_rl()"
    a successful call make the spectrum analyzer ready to get traces
        _measurement_enabled is activated automatically
*/
void rsa306b::spectrum_prepare
(
    double cf_Hz, 
    double rl_dBm,        
    RSA_API::Spectrum_Settings* settings,                     
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
        return;
    }
    this->_gp_return_status = this->config_update_cf_rl(cf_Hz, rl_dBm);
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailure in center frequency, reference level\n");
        #endif
        return;
    }
    this->_gp_return_status = this->_spectrum_set_measurement_enabled(true);
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tmeasurement enable activation has failed\n");
        #endif
        return;
    } 
    this->_gp_return_status = this->_spectrum_set_settings_type(settings);
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailure in configuring settings\n");
        #endif
        return;
    } 
    this->_gp_return_status = this->_spectrum_set_3_traces_type(traces3);
    if (this->_gp_return_status != CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailure in configuring the 3 traces\n");
        #endif
        return;
    } 
    #ifdef DEBUG_MIN
        printf("\n\tspectrum settings were successfully applied, measurement is enabled\n");
    #endif
    this->_spectrum_create_frequency_array();
}


////~~~~


/*
    public < 2 >
    the 'trace_number' argument specifies the trace number
    the selected trace number will aquire the specified trace
    the device is checked for proper configuration before proceeding
    think about dynamic memory if static is not suitable
    this function blocks until it gets the trace
*/
void rsa306b::spectrum_acquire_trace
(
    RSA_API::SpectrumTraces trace_number
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
    if (this->_spectrum_measurement_enabled == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tcall 'spectrum_prepare()' first\n");
        #endif
        return;
    }
    int traceIdx = this->_spectrum_trace_number_2_index(trace_number);
    if (traceIdx == this->INIT_INT)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinvalid trace selection\n");
        #endif
        return;
    }
    if (trace_number == RSA_API::SpectrumTrace1              &&
        this->_spectrum_3_traces_type.trace_enabled[0] == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\ttrace1 is not enabled, aquistion not possible\n");
        #endif
        return;
    }
    if (trace_number == RSA_API::SpectrumTrace2              &&
        this->_spectrum_3_traces_type.trace_enabled[1] == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\ttrace2 is not enabled, aquistion not possible\n");
        #endif
        return;
    }
    if (trace_number == RSA_API::SpectrumTrace3              &&
        this->_spectrum_3_traces_type.trace_enabled[2] == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\ttrace3 is not enabled, aquistion not possible\n");
        #endif
        return;
    }
    if (this->_spectrum_settings_type.traceLength > SPECTRUM_DATA_LENGTH)
    {
        #ifdef DEBUG_MIN
            printf("\n\tneed more memory, allocated  %d  ,  required  %d\n", 
                SPECTRUM_DATA_LENGTH, this->_spectrum_settings_type.traceLength);
        #endif
        return;
    }

    bool trace_is_ready = false;
	int timeout_ms = 0;
	
	this->device_run();
	this->_api_return_status = RSA_API::SPECTRUM_AcquireTrace();
    this->_api_error_check();
	while (trace_is_ready == false)
	{
		RSA_API::SPECTRUM_WaitForTraceReady(timeout_ms, &trace_is_ready);  // ignoring return value, blocking
	}
	this->_api_return_status = RSA_API::SPECTRUM_GetTrace(
        trace_number, 
        this->_spectrum_settings_type.traceLength, 
        this->_spectrum_trace_data[traceIdx], 
        &this->_spectrum_valid_trace_points);
    this->_api_error_check();
    this->device_stop();
    if (this->_spectrum_valid_trace_points !=
        this->_spectrum_settings_type.traceLength)
    {
        #ifdef DEBUG_MIN
            printf("\n\tmismatched data aquisition\n");
        #endif
    }
	this->_spectrum_set_trace_info_type();
}


////~~~~


/*
    public < 3 >
    attemps to find value of peak index when called
*/
int rsa306b::spectrum_index_of_peak_measurement
(
    RSA_API::SpectrumTraces trace_number
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
        return this->INIT_INT;
    }
    return this->_spectrum_find_peak_index(trace_number);
}


////~~~~


/*
    public < 4 >
    populates the struct at given index,
    if data is availible
    trace order is enforced
*/
void rsa306b::spectrum_collect_data
(
    spectrum_data_collector* data_getter, 
    int index
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
    if (data_getter == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate your struct\n");
        #endif
        return;
    }
    if (index > this->_spectrum_settings_type.traceLength ||
        index < 0                                          )
    {
        #ifdef DEBUG_MIN
            printf("\n\tindex out of range\n");
        #endif
        return;
    }
    data_getter->trace_number[0] = RSA_API::SpectrumTrace1;
    data_getter->trace_number[1] = RSA_API::SpectrumTrace2;
    data_getter->trace_number[2] = RSA_API::SpectrumTrace3;
    for (int ii = 0; ii < 3; ii++)
    {
        if (this->_spectrum_3_traces_type.trace_enabled[ii] == true)
        {
            data_getter->y_measurement[ii] = 
                this->_spectrum_trace_data[ii][index];
        }
    }
    data_getter->x_frequency = this->_spectrum_frequency_array[index];
}


////~~~~


/*
    public < 5 >
    prints all "SPECTRUM" member data
*/
void rsa306b::spectrum_print_all()
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

    this->_spectrum_set_limits_type();
    printf("\nSPECTRUM limits >>>\n");
    printf("\tmaximum span                  :  %lf\n", this->_spectrum_limits_type.maxSpan);
    printf("\tminimum span                  :  %lf\n", this->_spectrum_limits_type.minSpan);
    printf("\tmaximum resolution bandwidth  :  %lf\n", this->_spectrum_limits_type.maxRBW);
    printf("\tminimum resolution bandwidth  :  %lf\n", this->_spectrum_limits_type.minRBW);
    printf("\tmaximum video bandwidth       :  %lf\n", this->_spectrum_limits_type.maxVBW);
    printf("\tminimum video bandwidth       :  %lf\n", this->_spectrum_limits_type.minVBW);
    printf("\tmaximum trace length          :  %d\n", this->_spectrum_limits_type.maxTraceLength);
    printf("\tminimum trace length          :  %d\n", this->_spectrum_limits_type.minTraceLength);
    
    this->spectrum_get_settings_type(&this->_spectrum_settings_type);
    printf("\nSPECTRUM settings, actual >>>\n");
    printf("\tactual number of IQ samples  :  %d\n", this->_spectrum_settings_type.actualNumIQSamples);
    printf("\tactual starting frequency    :  %lf\n", this->_spectrum_settings_type.actualStartFreq);
    printf("\tactual stopping frequency    :  %lf\n", this->_spectrum_settings_type.actualStopFreq);
    printf("\tactual frequency step size   :  %lf\n", this->_spectrum_settings_type.actualFreqStepSize);
    printf("\tactual resolution bandwidth  :  %lf\n", this->_spectrum_settings_type.actualRBW);
    printf("\tactual video bandwidth       :  %lf\n", this->_spectrum_settings_type.actualVBW);
    
    printf("\nSPECTRUM settings, configured >>>\n");
    printf("\tmeasurement is enabled   :  %d\n", this->_spectrum_measurement_enabled);
    printf("\tspan                     :  %lf\n", this->_spectrum_settings_type.span);
    printf("\tresolution bandwidth     :  %lf\n", this->_spectrum_settings_type.rbw);
    printf("\tvideo bandwidth enabled  :  %d\n", this->_spectrum_settings_type.enableVBW);
    printf("\ttrace length             :  %d\n", this->_spectrum_settings_type.traceLength);
    printf("\twindow                   :  ");
    switch (this->_spectrum_settings_type.window)
    {
        case (RSA_API::SpectrumWindow_Kaiser) :
            printf("Kaiser\n");
            break;
        case (RSA_API::SpectrumWindow_Mil6dB) :
            printf("Mil6dB\n");
            break;
        case (RSA_API::SpectrumWindow_BlackmanHarris) :
            printf("Blackman-Harris\n");
            break;
        case (RSA_API::SpectrumWindow_Rectangle) :
            printf("Rectangle\n");
            break;
        case (RSA_API::SpectrumWindow_FlatTop) :
            printf("Flat-top\n");
            break;
        case (RSA_API::SpectrumWindow_Hann) :
            printf("Hann\n");
            break;
        default :
            printf("UNKNOWN\n");
            break;
    }
    printf("\tvertical units           :  ");
    switch (this->_spectrum_settings_type.verticalUnit)
    {
        case (RSA_API::SpectrumVerticalUnit_dBm) :
            printf("dBm\n");
            break;
        case (RSA_API::SpectrumVerticalUnit_Watt) :
            printf("watt\n");
            break;
        case (RSA_API::SpectrumVerticalUnit_Volt) :
            printf("volt\n");
            break;
        case (RSA_API::SpectrumVerticalUnit_Amp) :
            printf("amp\n");
            break;
        case (RSA_API::SpectrumVerticalUnit_dBmV) :
            printf("dBmV\n");
            break;
        default :
            printf("UNKOWN\n");
    }

    this->spectrum_get_trace_info_type(&this->_spectrum_trace_info_type);
    int temp_aqStat = (int)this->_spectrum_trace_info_type.acqDataStatus; 
    int temp_0x1 = (int)RSA_API::AcqDataStatus_ADC_OVERRANGE;
    int temp_0x2 = (int)RSA_API::AcqDataStatus_REF_OSC_UNLOCK;
    int temp_0x10 = (int)RSA_API::AcqDataStatus_LOW_SUPPLY_VOLTAGE;
    int temp_0x20 = (int)RSA_API::AcqDataStatus_ADC_DATA_LOST;
    int temp_mask = (int)RSA_API::AcqDataStatus_VALID_BITS_MASK;
    this->_spectrum_good_aquisition = !(temp_aqStat && temp_mask);
    printf("\nSPECTRUM trace information >>>\n");
    printf("\ttimestamp                :  %ld\n", this->_spectrum_trace_info_type.timestamp);
    printf("\tdata aquisition status   :  %d  {no active bits is good}\n", this->_spectrum_trace_info_type.acqDataStatus);
    printf("\tdata aquisition is good  :  %d\n", this->_spectrum_good_aquisition);
    printf("\t\t{\n");
    if (temp_aqStat && temp_0x1)  {printf("\t\t  input to ADC was outside operating range\n");}
    if (temp_aqStat && temp_0x2)  {printf("\t\t  loss of locked status on the reference oscillator\n");}
    if (temp_aqStat && temp_0x10) {printf("\t\t  power supply below 5 V detected\n");}
    if (temp_aqStat && temp_0x20) {printf("\t\t  ADC data frame samples were dropped\n");}
    if (this->_spectrum_good_aquisition) {printf("\t\t  aquisition success\n");}
    printf("\t\t}\n");

    this->spectrum_get_3_traces_type(&this->_spectrum_3_traces_type);
    printf("\nSPECTRUM, 3 traces >>>\n");
    for (int ii = 0; ii < 3; ii++)
    {
        printf("\tspectrum trace number :  %d  ,  ", this->_spectrum_3_traces_type.trace_select[ii]);
        switch (this->_spectrum_3_traces_type.trace_select[ii])
        {
            case (RSA_API::SpectrumTrace1) : printf("SpectrumTrace1  ,  "); break;
            case (RSA_API::SpectrumTrace2) : printf("SpectrumTrace2  ,  "); break;
            case (RSA_API::SpectrumTrace3) : printf("SpectrumTrace3  ,  "); break;
            default                        : printf("UNKNOWN  ,  ");        break;
        }
        if (this->_spectrum_3_traces_type.trace_enabled[ii] == true) 
        {
            printf("%d  {trace IS enabled}      ,  ", this->_spectrum_3_traces_type.trace_enabled[ii]);
        }
        else
        {
            printf("%d  {trace is NOT enabled}  ,  ", this->_spectrum_3_traces_type.trace_enabled[ii]);
        }
        printf("detector = %d  ,  ", this->_spectrum_3_traces_type.detector_select[ii]);
        switch (this->_spectrum_3_traces_type.detector_select[ii])
        {
            case (RSA_API::SpectrumDetector_PosPeak)     : printf("positive peak\n");        break;
            case (RSA_API::SpectrumDetector_NegPeak)     : printf("negative peak\n");        break;
            case (RSA_API::SpectrumDetector_AverageVRMS) : printf("average voltage, RMS\n"); break;
            case (RSA_API::SpectrumDetector_Sample)      : printf("sampled\n");              break;
            default                                      : printf("UNKNOWN\n");              break;
        }
    }
}


////////~~~~~~~~END>  rsa306b_class_SPECTRUM_public.cpp
