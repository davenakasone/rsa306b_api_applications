/*
    API group "SPECTRUM", setters

    public :
        < 1 >  spectrum_set_vars()
    
    private :
        < 1 >  _spectrum_set_vars()
        < 2 >  _spectrum_set_is_enabled_measurement()
        < 3 >  _spectrum_set_settings_type()
        < 4 >  _spectrum_set_trace_type()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::spectrum_set_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    return this->_spectrum_set_vars();
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_spectrum_set_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    constexpr int callz = 5;
    int cc = 0;
    CODEZ caught_call[callz];

    caught_call[cc] = this->_spectrum_set_is_enabled_measurement(); cc++;
    caught_call[cc] = this->_spectrum_set_settings_type         (); cc++;

    for (std::size_t ii = 0; ii < TRACES_306B; ii++)
    {
        caught_call[cc] = this->_spectrum_set_trace_type(ii); cc++;
    }
    
    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_spectrum_set_is_enabled_measurement()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
        RSA_API::SPECTRUM_SetEnable
        (
            this->vars.spectrum.is_enabled_measurement
        );
    (void)this->_spectrum_get_is_enabled_measurement();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_spectrum_set_settings_type()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if ((this->vars.spectrum.settings_type.traceLength % 2) == 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "trace length { %d }  ,  must be an odd number",
                this->vars.spectrum.settings_type.traceLength);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.spectrum.settings_type.span < this->_vars.spectrum.limits_type.minSpan ||
        this->vars.spectrum.settings_type.span > this->_vars.spectrum.limits_type.maxSpan  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "span out of range { %lf }  ,  [ %lf : %lf ]",
                this->vars.spectrum.settings_type.span,
                this->_vars.spectrum.limits_type.minSpan,
                this->_vars.spectrum.limits_type.maxSpan);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.spectrum.settings_type.rbw < this->_vars.spectrum.limits_type.minRBW ||
        this->vars.spectrum.settings_type.rbw > this->_vars.spectrum.limits_type.maxRBW  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "RBW out of range { %lf }  ,  [ %lf : %lf ]",
                this->vars.spectrum.settings_type.rbw,
                this->_vars.spectrum.limits_type.minRBW,
                this->_vars.spectrum.limits_type.maxRBW);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.spectrum.settings_type.span < this->vars.spectrum.settings_type.rbw)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "span { %lf } < RBW  { %lf }  ,  illegal",
                this->vars.spectrum.settings_type.span,
                this->vars.spectrum.settings_type.rbw);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.spectrum.settings_type.vbw < this->_vars.spectrum.limits_type.minVBW ||
        this->vars.spectrum.settings_type.vbw > this->_vars.spectrum.limits_type.maxVBW  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "VBW out of range { %lf }  ,  [ %lf : %lf ]",
                this->vars.spectrum.settings_type.vbw,
                this->_vars.spectrum.limits_type.minVBW,
                this->_vars.spectrum.limits_type.maxVBW);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.spectrum.settings_type.traceLength < this->_vars.spectrum.limits_type.minTraceLength ||
        this->vars.spectrum.settings_type.traceLength > this->_vars.spectrum.limits_type.maxTraceLength  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "trace length out of range { %d }  ,  [ %d : %d ]",
                this->vars.spectrum.settings_type.traceLength,
                this->_vars.spectrum.limits_type.minTraceLength,
                this->_vars.spectrum.limits_type.maxTraceLength);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Kaiser         &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Mil6dB         &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_BlackmanHarris &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Rectangle      &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_FlatTop        &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Hann            )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid window selection:  %d",
                static_cast<int>(this->vars.spectrum.settings_type.window));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_dBm  &&
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_Watt &&  
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_Volt &&
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_Amp  &&
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_dBmV  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid vertical unit selection:  %d",
                static_cast<int>(this->vars.spectrum.settings_type.verticalUnit));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    (void)this->device_stop();

    RSA_API::ReturnStatus temp =  
        RSA_API::SPECTRUM_SetSettings
        (
            this->vars.spectrum.settings_type
        );
    (void)this->_spectrum_get_settings_type();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_spectrum_set_trace_type(std::size_t idx)
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    
    if (this->vars.spectrum.detector_select[idx] != RSA_API::SpectrumDetector_PosPeak     &&
        this->vars.spectrum.detector_select[idx] != RSA_API::SpectrumDetector_NegPeak     &&
        this->vars.spectrum.detector_select[idx] != RSA_API::SpectrumDetector_AverageVRMS &&
        this->vars.spectrum.detector_select[idx] != RSA_API::SpectrumDetector_Sample       )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid detector selection:  %d", 
                static_cast<int>(vars.spectrum.detector_select[idx]));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    (void)this->device_stop();

    RSA_API::ReturnStatus temp =  
        RSA_API::SPECTRUM_SetTraceType
        (
            this->vars.spectrum.trace_select[idx], 
            this->vars.spectrum.is_enabled_trace[idx], 
            this->vars.spectrum.detector_select[idx]
        );
    (void)this->_spectrum_get_trace_type(idx);
    this->_report_api_status();
    return this->set_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_spectrum_set.cpp
