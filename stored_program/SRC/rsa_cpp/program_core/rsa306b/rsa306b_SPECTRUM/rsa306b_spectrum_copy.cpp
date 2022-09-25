/*
    API group "SPECTRUM", copiers

    public :
        #  none
    
    private :
        < 1 >   _spectrum_copy_vars()
        < 2 >   _spectrum_copy_is_enabled_measurement()
        < 3 >   _spectrum_copy_limits_type()
        < 4 >   _spectrum_copy_settings_type()
        < 5 >   _spectrum_copy_trace_select()
        < 6 >   _spectrum_copy_trace_power_v()
        < 7 >   _spectrum_copy_trace_info_type()
        < 8 >   _spectrum_copy_acq_status_messages()
        < 9 >   _spectrum_copy_is_enabled_trace()
        < 10 >  _spectrum_copy_detector_select()
        < 11 >  _spectrum_copy_frequency_v()
        < 12 >  _spectrum_copy_peak_index()
        < 13 >  _spectrum_copy_trace_points_acquired()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_spectrum_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef DEBUG_FUNC
    printf("\n%s()\n", __func__);
#endif

    constexpr int callz = 26;
    int cc = 0;
    CODEZ caught_call[callz];

        caught_call[cc] = this->_spectrum_copy_is_enabled_measurement(); cc++;
        caught_call[cc] = this->_spectrum_copy_limits_type           (); cc++;
        caught_call[cc] = this->_spectrum_copy_settings_type         (); cc++;
        caught_call[cc] = this->_spectrum_copy_acq_status_messages   (); cc++;
        caught_call[cc] = this->_spectrum_copy_frequency_v           (); cc++;

        for (std::size_t ii = 0; ii < TRACES_306B; ii++)
        {
            caught_call[cc] = this->_spectrum_copy_trace_select         (ii); cc++;
            caught_call[cc] = this->_spectrum_copy_trace_info_type      (ii); cc++;
            caught_call[cc] = this->_spectrum_copy_is_enabled_trace     (ii); cc++;
            caught_call[cc] = this->_spectrum_copy_detector_select      (ii); cc++;
            caught_call[cc] = this->_spectrum_copy_peak_index           (ii); cc++;
            caught_call[cc] = this->_spectrum_copy_trace_points_acquired(ii); cc++;
            caught_call[cc] = this->_spectrum_copy_trace_power_v        (ii); cc++;
        }

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_spectrum_copy_is_enabled_measurement()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.is_enabled_measurement = this->_vars.spectrum.is_enabled_measurement;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_spectrum_copy_limits_type()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.limits_type.maxRBW         = this->_vars.spectrum.limits_type.maxRBW;
    this->vars.spectrum.limits_type.maxSpan        = this->_vars.spectrum.limits_type.maxSpan;
    this->vars.spectrum.limits_type.maxTraceLength = this->_vars.spectrum.limits_type.maxTraceLength;
    this->vars.spectrum.limits_type.maxVBW         = this->_vars.spectrum.limits_type.maxVBW;
    this->vars.spectrum.limits_type.minRBW         = this->_vars.spectrum.limits_type.minRBW;
    this->vars.spectrum.limits_type.minSpan        = this->_vars.spectrum.limits_type.minSpan;
    this->vars.spectrum.limits_type.minTraceLength = this->_vars.spectrum.limits_type.minTraceLength;
    this->vars.spectrum.limits_type.minVBW         = this->_vars.spectrum.limits_type.minVBW;

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_spectrum_copy_settings_type()
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.settings_type.actualFreqStepSize = this->_vars.spectrum.settings_type.actualFreqStepSize;
    this->vars.spectrum.settings_type.actualNumIQSamples = this->_vars.spectrum.settings_type.actualNumIQSamples;
    this->vars.spectrum.settings_type.actualRBW          = this->_vars.spectrum.settings_type.actualRBW;
    this->vars.spectrum.settings_type.actualStartFreq    = this->_vars.spectrum.settings_type.actualStartFreq;
    this->vars.spectrum.settings_type.actualStopFreq     = this->_vars.spectrum.settings_type.actualStopFreq;
    this->vars.spectrum.settings_type.actualVBW          = this->_vars.spectrum.settings_type.actualVBW;
    this->vars.spectrum.settings_type.enableVBW          = this->_vars.spectrum.settings_type.enableVBW;
    this->vars.spectrum.settings_type.rbw                = this->_vars.spectrum.settings_type.rbw;
    this->vars.spectrum.settings_type.span               = this->_vars.spectrum.settings_type.span;
    this->vars.spectrum.settings_type.traceLength        = this->_vars.spectrum.settings_type.traceLength;
    this->vars.spectrum.settings_type.vbw                = this->_vars.spectrum.settings_type.vbw;
    this->vars.spectrum.settings_type.verticalUnit       = this->_vars.spectrum.settings_type.verticalUnit;
    this->vars.spectrum.settings_type.window             = this->_vars.spectrum.settings_type.window;

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_spectrum_copy_trace_select(std::size_t idx)
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.trace_select[idx] = this->_vars.spectrum.trace_select[idx];
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_spectrum_copy_trace_power_v(std::size_t idx)
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.trace_power_v[idx].resize(
        this->_vars.spectrum.trace_power_v[idx].size());

    for (std::size_t ii = 0; ii < this->_vars.spectrum.trace_power_v[idx].size(); ii++)
    {
        this->vars.spectrum.trace_power_v[idx][ii] = this->_vars.spectrum.trace_power_v[idx][ii];
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_spectrum_copy_trace_info_type(std::size_t idx)
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.trace_info_type[idx] = this->_vars.spectrum.trace_info_type[idx];
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_spectrum_copy_acq_status_messages()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    for (int ii = 0; ii < SPECTRUM_BITCHECKS; ii++)
    {
        strcpy(this->vars.spectrum.acq_status_messages[ii], this->_vars.spectrum.acq_status_messages[ii]);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 9 > private
*/
CODEZ rsa306b_class::_spectrum_copy_is_enabled_trace(std::size_t idx)
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.is_enabled_trace[idx] = this->_vars.spectrum.is_enabled_trace[idx];
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 10 > private
*/
CODEZ rsa306b_class::_spectrum_copy_detector_select(std::size_t idx)
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.detector_select[idx] = this->_vars.spectrum.detector_select[idx];
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 11 > private
*/
CODEZ rsa306b_class::_spectrum_copy_frequency_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.frequency_v.clear();
    this->vars.spectrum.frequency_v.resize(
        this->_vars.spectrum.frequency_v.size());
    this->vars.spectrum.frequency_v = this->_vars.spectrum.frequency_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 12 > private
*/
CODEZ rsa306b_class::_spectrum_copy_peak_index(std::size_t idx)
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.peak_index[idx] = this->_vars.spectrum.peak_index[idx];
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 13 > private
*/
CODEZ rsa306b_class::_spectrum_copy_trace_points_acquired(std::size_t idx)
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.spectrum.trace_points_acquired[idx] = this->_vars.spectrum.trace_points_acquired[idx];
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_spectrum_copy.cpp
