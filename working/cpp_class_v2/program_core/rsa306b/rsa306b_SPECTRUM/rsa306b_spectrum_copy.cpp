/*
    API group "SPECTRUM", copiers

    public :
        #  none
    
    private :
        < 1 >   _spectrum_copy_vars()
        < 2 >   _spectrum_copy_is_enabled_measurement()
        < 3 >   _spectrum_copy_settings_type()
        < 4 >   _spectrum_copy_limits_type()
        < 5 >   _spectrum_copy_trace_points_aquired()
        < 6 >   _spectrum_copy_array_frequency()
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
    this->_spectrum_copy_trace_points_aquired();
    this->_spectrum_copy_array_frequency();
    this->_spectrum_copy_is_enabled_trace();
    this->_spectrum_copy_traces_select();
    this->_spectrum_copy_detectors_select();
    this->_spectrum_copy_trace_info_type();
    this->_spectrum_copy_array_power();
    this->_spectrum_copy_peak_index();
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

    // fill here
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
void rsa306b_class::_spectrum_copy_trace_points_aquired()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.trace_points_acquired = this->_vars.spectrum.trace_points_acquired;
}


////~~~~


/*
    < 6 > private
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
    < 7 > private
*/
void rsa306b_class::_spectrum_copy_is_enabled_trace()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif 

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->vars.spectrum.is_enabled_trace[ii] = this->_vars.spectrum.is_enabled_trace[ii];
    }
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_spectrum_copy_traces_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->vars.spectrum.traces_select[ii] = this->_vars.spectrum.traces_select[ii];
    }
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_spectrum_copy_detectors_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->vars.spectrum.detectors_select[ii] = this->_vars.spectrum.detectors_select[ii];
    }
}


////~~~~


/*
    < 10 > private
*/
void rsa306b_class::_spectrum_copy_trace_info_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.spectrum.trace_info_type->acqDataStatus = this->_vars.spectrum.trace_info_type->acqDataStatus;
    this->vars.spectrum.trace_info_type->timestamp = this->_vars.spectrum.trace_info_type->timestamp;
}


////~~~~


/*
    < 11 > private
*/
void rsa306b_class::_spectrum_copy_array_power()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        for (int jj = 0; jj < SPECTRUM_DATA_LENGTH; jj++)
        {
            this->_vars.spectrum.array_power[ii][jj] = this->_vars.spectrum.array_power[ii][jj];
        }
    }
}
    

////~~~~


/*
    < 12 > private
*/
void rsa306b_class::_spectrum_copy_peak_index()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->vars.spectrum.peak_index[ii] = this->_vars.spectrum.peak_index[ii];
    }
}


////////~~~~~~~~END>  rsa306b_spectrum_copy.cpp
