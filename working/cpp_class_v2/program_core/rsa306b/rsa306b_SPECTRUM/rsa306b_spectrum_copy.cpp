/*
    API group "SPECTRUM", copiers

    public :
        #  none
    
    private :
        < 1 >   _spectrum_copy_vars()
        < 2 >   _spectrum_copy_is_enabled_measurement()
        < 3 >   _spectrum_copy_settings_type()
        < 4 >   _spectrum_copy_limits_type()
        < 5 >   _spectrum_copy_array_frequency()
        < 6 >   _spectrum_copy_trace_points_aquired()
        < 7 >   _spectrum_copy_is_enabled_trace()
        < 8 >   _spectrum_copy_traces_select()
        < 9 >   _spectrum_copy_detectors_select()
        < 10 >  _spectrum_copy_trace_info_type()
        < 11 >  _spectrum_copy_array_power()
        < 12 >  _spectrum_copy_peak_index()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_spectrum_copy_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_spectrum_copy_is_enabled_measurement();
    this->_spectrum_copy_settings_type();
    this->_spectrum_copy_limits_type();
    this->_spectrum_copy_array_frequency();
    
    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->_spectrum_copy_trace_points_aquired(ii);
        this->_spectrum_copy_traces_select(ii);
        this->_spectrum_copy_trace_info_type(ii);
        this->_spectrum_copy_is_enabled_trace(ii);
        this->_spectrum_copy_detectors_select(ii);
        this->_spectrum_copy_array_power(ii);
        this->_spectrum_copy_peak_index(ii);
    }
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_spectrum_copy_is_enabled_measurement()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.is_enabled_measurement = this->_vars.spectrum.is_enabled_measurement;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_spectrum_copy_settings_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.settings_type.actualFreqStepSize = this->_vars.spectrum.settings_type.actualFreqStepSize;
    this->vars.spectrum.settings_type.actualNumIQSamples = this->_vars.spectrum.settings_type.actualNumIQSamples;
    this->vars.spectrum.settings_type.actualRBW = this->_vars.spectrum.settings_type.actualRBW;
    this->vars.spectrum.settings_type.actualStartFreq = this->_vars.spectrum.settings_type.actualStartFreq;
    this->vars.spectrum.settings_type.actualStopFreq = this->_vars.spectrum.settings_type.actualStopFreq;
    this->vars.spectrum.settings_type.actualVBW = this->_vars.spectrum.settings_type.actualVBW;
    this->vars.spectrum.settings_type.enableVBW = this->_vars.spectrum.settings_type.enableVBW;
    this->vars.spectrum.settings_type.rbw = this->_vars.spectrum.settings_type.rbw;
    this->vars.spectrum.settings_type.span = this->_vars.spectrum.settings_type.span;
    this->vars.spectrum.settings_type.traceLength = this->_vars.spectrum.settings_type.traceLength;
    this->vars.spectrum.settings_type.vbw = this->_vars.spectrum.settings_type.vbw;
    this->vars.spectrum.settings_type.verticalUnit = this->_vars.spectrum.settings_type.verticalUnit;
    this->vars.spectrum.settings_type.window = this->_vars.spectrum.settings_type.window;
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_spectrum_copy_limits_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.limits_type.maxRBW = this->_vars.spectrum.limits_type.maxRBW;
    this->vars.spectrum.limits_type.maxSpan = this->_vars.spectrum.limits_type.maxSpan;
    this->vars.spectrum.limits_type.maxTraceLength = this->_vars.spectrum.limits_type.maxTraceLength;
    this->vars.spectrum.limits_type.maxVBW = this->_vars.spectrum.limits_type.maxVBW;
    this->vars.spectrum.limits_type.minRBW = this->_vars.spectrum.limits_type.minRBW;
    this->vars.spectrum.limits_type.minSpan = this->_vars.spectrum.limits_type.minSpan;
    this->vars.spectrum.limits_type.minTraceLength = this->_vars.spectrum.limits_type.minTraceLength;
    this->vars.spectrum.limits_type.minVBW = this->_vars.spectrum.limits_type.minVBW;
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_spectrum_copy_array_frequency()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < SPECTRUM_DATA_LENGTH; ii++)
    {
        this->vars.spectrum.array_frequency[ii] = this->_vars.spectrum.array_frequency[ii];
    }
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_spectrum_copy_trace_points_aquired(int trace_index)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.trace_points_acquired[trace_index] = this->_vars.spectrum.trace_points_acquired[trace_index];
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_spectrum_copy_is_enabled_trace(int trace_index)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif 

    this->vars.spectrum.is_enabled_trace[trace_index] = this->_vars.spectrum.is_enabled_trace[trace_index];
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_spectrum_copy_traces_select(int trace_index)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.traces_select[trace_index] = this->_vars.spectrum.traces_select[trace_index];
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_spectrum_copy_detectors_select(int trace_index)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.detectors_select[trace_index] = this->_vars.spectrum.detectors_select[trace_index];
}


////~~~~


/*
    < 10 > private
*/
void rsa306b_class::_spectrum_copy_trace_info_type(int trace_index)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.trace_info_type[trace_index].acqDataStatus = this->_vars.spectrum.trace_info_type[trace_index].acqDataStatus;
    this->vars.spectrum.trace_info_type[trace_index].timestamp = this->_vars.spectrum.trace_info_type[trace_index].timestamp;
}


////~~~~


/*
    < 11 > private
*/
void rsa306b_class::_spectrum_copy_array_power(int trace_index)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < SPECTRUM_DATA_LENGTH; ii++)
    {
       this->vars.spectrum.array_power[trace_index][ii] = this->_vars.spectrum.array_power[trace_index][ii];
    }
}
    

////~~~~


/*
    < 12 > private
*/
void rsa306b_class::_spectrum_copy_peak_index(int trace_index)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.peak_index[trace_index] = this->_vars.spectrum.peak_index[trace_index];
}


////////~~~~~~~~END>  rsa306b_spectrum_copy.cpp
