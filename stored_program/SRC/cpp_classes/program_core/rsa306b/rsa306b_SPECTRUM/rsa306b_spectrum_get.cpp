/*
    API group "SPECTRUM", getters

    public :
        #  none
    
    private :
        < 1 >  _spectrum_get_vars()
        < 2 >  _spectrum_get_is_enabled_measurement()
        < 3 >  _spectrum_get_limits_type()
        < 4 >  _spectrum_get_settings_type()
        < 5 >  _spectrum_get_trace_info_type()
        < 6 >  _spectrum_get_trace_type()
*/

#include "../rsa306b_class.h"





////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_spectrum_get_vars()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_spectrum_get_is_enabled_measurement();
    this->_spectrum_get_limits_type();
    this->_spectrum_get_settings_type();
    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->_spectrum_get_trace_info_type(ii);
        this->_spectrum_get_trace_type(ii);
    }
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_spectrum_get_is_enabled_measurement()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::SPECTRUM_GetEnable(
            &this->_vars.spectrum.is_enabled_measurement);
    this->_gp_confirm_api_status();
    this->_spectrum_copy_is_enabled_measurement();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_spectrum_get_limits_type()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::SPECTRUM_GetLimits(
            &this->_vars.spectrum.limits_type);
    this->_gp_confirm_api_status();
    this->_spectrum_copy_limits_type();
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_spectrum_get_settings_type()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::SPECTRUM_GetSettings(
            &this->_vars.spectrum.settings_type);
    this->_gp_confirm_api_status();
    this->_spectrum_copy_settings_type();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_spectrum_get_trace_info_type(int trace_index)
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_vars.gp.api_status = 
        RSA_API::SPECTRUM_GetTraceInfo(
            &this->_vars.spectrum.trace_info_type[trace_index]);
    this->_gp_confirm_api_status();
    this->_spectrum_copy_trace_info_type(trace_index);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_spectrum_get_trace_type(int trace_index)
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    for (int ii = 0; ii < TRACES_AVAILABLE; ii++)
    {
        this->_vars.gp.api_status = 
            RSA_API::SPECTRUM_GetTraceType(
                this->_vars.spectrum.traces_select[ii], 
                &this->_vars.spectrum.is_enabled_trace[ii], 
                &this->_vars.spectrum.detectors_select[ii]);
        this->_gp_confirm_api_status();
    }
    this->_spectrum_copy_is_enabled_trace(trace_index);
    this->_spectrum_copy_detectors_select(trace_index);
}


////////~~~~~~~~END>  rsa306b_spectrum_get.cpp
