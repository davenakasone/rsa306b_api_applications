/*
    API group "SPECTRUM", initializing

    public :
        < 1 >  spectrum_default()
    
    private :
        < 1 >  _spectrum_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::spectrum_default()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    (void)this->device_stop();

    RSA_API::ReturnStatus temp = 
        RSA_API::SPECTRUM_SetDefault();
    //(void)this->get_everything();
    return this->set_api_status(temp);
}

////~~~~


/*
    < 1 > private
    don't need to touch "trace_info_type" or "limits_type"
*/
CODEZ rsa306b_class::_spectrum_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_vars.spectrum.is_enabled_measurement = this->_vars.spectrum._IS_ENABLED_MEASUREMENT;

    this->_vars.spectrum.limits_type.maxRBW         = this->_vars.spectrum._LIMITS_TYPE_maxRBW;
    this->_vars.spectrum.limits_type.minRBW         = this->_vars.spectrum._LIMITS_TYPE_minRBW;
    this->_vars.spectrum.limits_type.maxSpan        = this->_vars.spectrum._LIMITS_TYPE_maxSpan;
    this->_vars.spectrum.limits_type.minSpan        = this->_vars.spectrum._LIMITS_TYPE_minSpan;
    this->_vars.spectrum.limits_type.maxTraceLength = this->_vars.spectrum._LIMITS_TYPE_maxTraceLength;
    this->_vars.spectrum.limits_type.minTraceLength = this->_vars.spectrum._LIMITS_TYPE_minTraceLength;
    this->_vars.spectrum.limits_type.maxVBW         = this->_vars.spectrum._LIMITS_TYPE_maxVBW;
    this->_vars.spectrum.limits_type.minVBW         = this->_vars.spectrum._LIMITS_TYPE_minVBW;

    this->_vars.spectrum.settings_type.actualFreqStepSize = this->_vars.spectrum._SETTINGS_TYPE_actualFreqStepSize;
    this->_vars.spectrum.settings_type.actualNumIQSamples = this->_vars.spectrum._SETTINGS_TYPE_actualNumIQSamples;
    this->_vars.spectrum.settings_type.actualRBW          = this->_vars.spectrum._SETTINGS_TYPE_actualRBW;
    this->_vars.spectrum.settings_type.actualStartFreq    = this->_vars.spectrum._SETTINGS_TYPE_actualStartFreq;
    this->_vars.spectrum.settings_type.actualStopFreq     = this->_vars.spectrum._SETTINGS_TYPE_actualStopFreq;
    this->_vars.spectrum.settings_type.actualVBW          = this->_vars.spectrum._SETTINGS_TYPE_actualVBW;
    this->_vars.spectrum.settings_type.enableVBW          = this->_vars.spectrum._SETTINGS_TYPE_enableVBW;
    this->_vars.spectrum.settings_type.rbw                = this->_vars.spectrum._SETTINGS_TYPE_rbw;
    this->_vars.spectrum.settings_type.span               = this->_vars.spectrum._SETTINGS_TYPE_span;
    this->_vars.spectrum.settings_type.traceLength        = this->_vars.spectrum._SETTINGS_TYPE_traceLength;
    this->_vars.spectrum.settings_type.vbw                = this->_vars.spectrum._SETTINGS_TYPE_vbw;
    this->_vars.spectrum.settings_type.verticalUnit       = this->_vars.spectrum._SETTINGS_TYPE_verticalUint;
    this->_vars.spectrum.settings_type.window             = this->_vars.spectrum._SETTINGS_TYPE_WINDOW;

    this->_vars.spectrum.frequency_v.assign(this->_vars.spectrum._FREQUENCY_V_size, this->_vars.spectrum._FREQUENCY_V_element);
    
    for (std::size_t ii = 0; ii < TRACES_306B; ii++)
    {
        this->_vars.spectrum.trace_select[ii] = this->_vars.spectrum._TRACE_SELECT[ii];

        this->_vars.spectrum.trace_info_type[ii].acqDataStatus = this->_vars.spectrum._TRACE_INFO_TYPE_acqDataStatus;
        this->_vars.spectrum.trace_info_type[ii].timestamp     = this->_vars.spectrum._TRACE_INFO_TYPE_timestamp;

        this->_vars.spectrum.trace_power_v[ii].assign(
            this->_vars.spectrum._TRACE_POWER_V_size,
            this->_vars.spectrum._TRACE_POWER_V_element); 
        
        this->_vars.spectrum.is_enabled_trace[ii] = this->_vars.spectrum._IS_ENABLED_TRACE[ii];

        this->_vars.spectrum.detector_select[ii] = this->_vars.spectrum._DETECTOR_SELECT[ii];

        this->_vars.spectrum.peak_index[ii] = this->_vars.spectrum._PEAK_INDEX;

        this->_vars.spectrum.trace_points_acquired[ii] = this->_vars.spectrum._TRACE_POINTS_ACQURIED;
    }

    for (int ii = 0; ii < SPECTRUM_BITCHECKS; ii++)
    {
        //(void)strcpy(this->_vars.spectrum.acq_status_messages[ii], this->_vars.spectrum._ACQ_STATUS_MESSAGES);
        (void)strcpy(this->_vars.spectrum.acq_status_messages[ii], BITCHECK_SUCCESS_MESSAGE);
    }

    return this->_spectrum_copy_vars();
}


////////~~~~~~~~END>  rsa306b_spectrum_init_default.cpp
        