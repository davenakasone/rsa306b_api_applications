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
void rsa306b_class::spectrum_set_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_spectrum_set_vars();
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_spectrum_set_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_spectrum_set_is_enabled_measurement();
    this->_spectrum_set_settings_type();
    this->_spectrum_set_trace_type();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_spectrum_set_is_enabled_measurement()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();
    this->_vars.gp.api_status = 
        RSA_API::SPECTRUM_SetEnable(
            this->vars.spectrum.is_enabled_measurement);
    this->_spectrum_get_is_enabled_measurement();
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_spectrum_set_settings_type()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if ((this->vars.spectrum.settings_type.traceLength % 2) == 0)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "trace length { %d }  ,  must be an odd number",
                this->vars.spectrum.settings_type.traceLength);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->vars.spectrum.settings_type.span < this->_vars.spectrum.limits_type.minSpan ||
        this->vars.spectrum.settings_type.span > this->_vars.spectrum.limits_type.maxSpan  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "span out of range { %lf }  ,  [ %lf : %lf ]",
                this->vars.spectrum.settings_type.span,
                this->_vars.spectrum.limits_type.minSpan,
                this->_vars.spectrum.limits_type.maxSpan);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->vars.spectrum.settings_type.rbw < this->_vars.spectrum.limits_type.minRBW ||
        this->vars.spectrum.settings_type.rbw > this->_vars.spectrum.limits_type.maxRBW  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "RBW out of range { %lf }  ,  [ %lf : %lf ]",
                this->vars.spectrum.settings_type.rbw,
                this->_vars.spectrum.limits_type.minRBW,
                this->_vars.spectrum.limits_type.maxRBW);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->vars.spectrum.settings_type.span < this->vars.spectrum.settings_type.rbw)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "span { %lf } < RBW  { %lf }  ,  illegal",
                this->vars.spectrum.settings_type.span,
                this->vars.spectrum.settings_type.rbw);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->vars.spectrum.settings_type.vbw < this->_vars.spectrum.limits_type.minVBW ||
        this->vars.spectrum.settings_type.vbw > this->_vars.spectrum.limits_type.maxVBW  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "VBW out of range { %lf }  ,  [ %lf : %lf ]",
                this->vars.spectrum.settings_type.vbw,
                this->_vars.spectrum.limits_type.minVBW,
                this->_vars.spectrum.limits_type.maxVBW);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->vars.spectrum.settings_type.traceLength < this->_vars.spectrum.limits_type.minTraceLength ||
        this->vars.spectrum.settings_type.traceLength > this->_vars.spectrum.limits_type.maxTraceLength  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "trace length out of range { %d }  ,  [ %d : %d ]",
                this->vars.spectrum.settings_type.traceLength,
                this->_vars.spectrum.limits_type.minTraceLength,
                this->_vars.spectrum.limits_type.maxTraceLength);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Kaiser         &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Mil6dB         &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_BlackmanHarris &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Rectangle      &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_FlatTop        &&
        this->vars.spectrum.settings_type.window != RSA_API::SpectrumWindow_Hann            )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid window selection:  %d",
                static_cast<int>(this->vars.spectrum.settings_type.window));
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_dBm  &&
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_Watt &&  
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_Volt &&
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_Amp  &&
        this->vars.spectrum.settings_type.verticalUnit != RSA_API::SpectrumVerticalUnit_dBmV  )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid vertical unit selection:  %d",
                static_cast<int>(this->vars.spectrum.settings_type.verticalUnit));
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->device_stop();

    this->_vars.gp.api_status = RSA_API::SPECTRUM_SetSettings(this->vars.spectrum.settings_type);
    this->_gp_confirm_api_status();
    this->_spectrum_get_settings_type();
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_spectrum_set_trace_type()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no device connected");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    
    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        _spectrum_copy_traces_select(ii); // enforce enum
        if (this->vars.spectrum.detectors_select[ii] != RSA_API::SpectrumDetector_PosPeak     &&
            this->vars.spectrum.detectors_select[ii] != RSA_API::SpectrumDetector_NegPeak     &&
            this->vars.spectrum.detectors_select[ii] != RSA_API::SpectrumDetector_AverageVRMS &&
            this->vars.spectrum.detectors_select[ii] != RSA_API::SpectrumDetector_Sample       )
        {
            #ifdef DEBUG_MIN
                snprintf(X_ddts, sizeof(X_ddts), "invalid detector selection:  %d", 
                    static_cast<int>(vars.spectrum.detectors_select[ii]));
                snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(true);
            #endif
            return;
        }
        this->_vars.gp.api_status = 
            RSA_API::SPECTRUM_SetTraceType(
                this->vars.spectrum.traces_select[ii], 
                this->vars.spectrum.is_enabled_trace[ii], 
                this->vars.spectrum.detectors_select[ii]);
        this->_gp_confirm_api_status();
        this->_spectrum_get_trace_type(ii);
    }
}


////////~~~~~~~~END>  rsa306b_spectrum_set.cpp
