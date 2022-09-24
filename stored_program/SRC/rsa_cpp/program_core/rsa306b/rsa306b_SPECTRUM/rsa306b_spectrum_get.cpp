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


/*
    < 1 > private
*/
CODEZ rsa306b_class::_spectrum_get_vars()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    constexpr int callz = 9;
    int cc = 0;
    CODEZ caught_call[callz];

    caught_call[cc] = this->_spectrum_get_is_enabled_measurement(); cc++;
    caught_call[cc] = this->_spectrum_get_limits_type           (); cc++;
    caught_call[cc] = this->_spectrum_get_settings_type         (); cc++;

    for (std::size_t ii = 0; ii < TRACES_306B; ii++)
    {
        caught_call[cc] = this->_spectrum_get_trace_info_type(ii); cc++;
        caught_call[cc] = this->_spectrum_get_trace_info_type(ii); cc++;
    }

    return this->cutil.codez_checker(caught_call, callz);
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

    this->_api_status = 
        RSA_API::SPECTRUM_GetEnable
        (
            &this->_vars.spectrum.is_enabled_measurement
        );
    (void)this->_spectrum_copy_is_enabled_measurement();
    return this->_report_api_status();
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

    this->_api_status = 
        RSA_API::SPECTRUM_GetLimits
        (
            &this->_vars.spectrum.limits_type
        );
    (void)this->_spectrum_copy_limits_type();
    return this->_report_api_status();
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

    this->_api_status = 
        RSA_API::SPECTRUM_GetSettings
        (
            &this->_vars.spectrum.settings_type
        );
    (void)this->_spectrum_copy_settings_type();
    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_spectrum_get_trace_info_type(std::size_t idx)
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::SPECTRUM_GetTraceInfo
        (
            &this->_vars.spectrum.trace_info_type[idx]
        );
    (void)this->_spectrum_copy_trace_info_type(idx);
    return this->_report_api_status();
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_spectrum_get_trace_type(std::size_t idx)
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
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

    this->_api_status = 
        RSA_API::SPECTRUM_GetTraceType
        (
            this->_vars.spectrum.trace_select[idx], 
            &this->_vars.spectrum.is_enabled_trace[idx], 
            &this->_vars.spectrum.detector_select[idx]
        );
    (void)this->_spectrum_copy_is_enabled_trace(idx);
    (void)this->_spectrum_copy_detector_select(idx);
    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_spectrum_get.cpp
