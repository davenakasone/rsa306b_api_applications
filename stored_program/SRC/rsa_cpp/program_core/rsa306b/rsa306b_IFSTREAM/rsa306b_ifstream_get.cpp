/*
    API group "IFSTREAM", getters

    public :
        #  none
    
    private :
        < 1 >  _ifstream_get_vars()
        < 2 >  _ifstream_get_is_active()
        < 3 >  _ifstream_get_acq_parameters()
        < 4 >  _ifstream_get_buffer_size()
        < 5 >  _ifstream_get_eq_parameters()
        < 6 >  _ifstream_get_scaling_parameters()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_ifstream_get_vars()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    constexpr int callz = 5;
    CODEZ caught_call[callz];

    caught_call[0] = this->_ifstream_get_is_active();
    caught_call[1] = this->_ifstream_get_acq_parameters();
    caught_call[2] = this->_ifstream_get_buffer_size();
    caught_call[3] = this->_ifstream_get_eq_parameters();
    caught_call[4] = this->_ifstream_get_scaling_parameters();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_ifstream_get_is_active()
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

    this->_api_status = 
        RSA_API::IFSTREAM_GetActiveStatus(
            &this->_vars.ifstream.is_active);

    (void)this->_ifstream_copy_is_active();
    
    return this->_report_api_status();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_ifstream_get_acq_parameters()
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

    this->_api_status = 
        RSA_API::IFSTREAM_GetAcqParameters(
            &this->_vars.ifstream.if_bandwidth_hz,
            &this->_vars.ifstream.samples_per_second,
            &this->_vars.ifstream.if_center_frequency);

    (void)this->_ifstream_copy_if_bandwidth_hz();
    (void)this->_ifstream_copy_samples_per_second();
    (void)this->_ifstream_copy_if_center_frequency();

    return this->_report_api_status();
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_ifstream_get_buffer_size()
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

    this->_api_status = 
        RSA_API::IFSTREAM_GetIFDataBufferSize(
            &this->_vars.ifstream.buffer_size_bytes,
            &this->_vars.ifstream.buffer_samples);

    (void)this->_ifstream_copy_buffer_size_bytes();
    (void)this->_ifstream_copy_buffer_samples();

    return this->_report_api_status();
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_ifstream_get_eq_parameters()
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

    float* arr_freq = NULL;
    float* arr_ampl = NULL;
    float* arr_phase = NULL;
    this->_api_status = 
        RSA_API::IFSTREAM_GetEQParameters(
            &this->_vars.ifstream.points_in_equalization_buffer,
            &arr_freq,
            &arr_ampl,
            &arr_phase);
    
    if (this->_api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            this->_device_get_api_status_message();
            (void)snprintf(X_ddts, sizeof(X_ddts), "%s",
                this->_vars.device.api_status_message);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        arr_freq = NULL;
        arr_ampl = NULL;
        arr_phase = NULL;
        return this->_report_api_status();
    }
    if (this->_vars.ifstream.points_in_equalization_buffer <= 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "empty IFSTREAM EQ parameters");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        arr_freq = NULL;
        arr_ampl = NULL;
        arr_phase = NULL;
        return this->cutil.report_status_code(CODEZ::_21_rsa_api_task_failed);
    }

    this->_vars.ifstream.eq_frequency_v.assign(arr_freq, arr_freq + this->_vars.ifstream.points_in_equalization_buffer);
    this->_vars.ifstream.eq_amplitude_v.assign(arr_ampl, arr_ampl + this->_vars.ifstream.points_in_equalization_buffer);
    this->_vars.ifstream.eq_phase_v.assign(arr_phase, arr_phase + this->_vars.ifstream.points_in_equalization_buffer);

    (void)this->_ifstream_copy_eq_frequency_v();
    (void)this->_ifstream_copy_eq_amplitude_v();
    (void)this->_ifstream_copy_eq_phase_v();

    arr_freq = NULL;
    arr_ampl = NULL;
    arr_phase = NULL;

    return this->_report_api_status();
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_ifstream_get_scaling_parameters()
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

    this->_api_status = 
        RSA_API::IFSTREAM_GetScalingParameters(
            &this->_vars.ifstream.scale_factor,
            &this->_vars.ifstream.scale_frequency);

    (void)this->_ifstream_copy_scale_factor();
    (void)this->_ifstream_copy_scale_frequency();

    return this->_report_api_status();
}


////////~~~~~~~~END>  rsa306b_ifstream_get.cpp
