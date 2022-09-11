/*
    API group "IFSTREAM", getters

    public :
        #  none
    
    private :
        < 1 >  _ifstreamm_get_vars()
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
void rsa306b_class::_ifstream_get_vars()
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

    this->_ifstream_get_is_active();
    this->_ifstream_get_acq_parameters();
    this->_ifstream_get_buffer_size();
    this->_ifstream_get_eq_parameters();
    this->_ifstream_get_scaling_parameters();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_ifstream_get_is_active()
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

    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetActiveStatus(
            &this->_vars.ifstream.is_active);
    this->_gp_confirm_api_status();
    this->_ifstream_copy_is_active();
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_ifstream_get_acq_parameters()
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

    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetAcqParameters(
            &this->_vars.ifstream.if_bandwidth_hz,
            &this->_vars.ifstream.samples_per_second,
            &this->_vars.ifstream.if_center_frequency);
    this->_gp_confirm_api_status();
    this->_ifstream_copy_acq_parameters();
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_ifstream_get_buffer_size()
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

    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetIFDataBufferSize(
            &this->_vars.ifstream.buffer_size_bytes,
            &this->_vars.ifstream.number_of_samples);
    this->_gp_confirm_api_status();
    this->_ifstream_copy_buffer_size();
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_ifstream_get_eq_parameters()
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

    float* arr_freq;
    float* arr_ampl;
    float* arr_phase;
    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetEQParameters(
            &this->_vars.ifstream.points_in_equalization_buffer,
            &arr_freq,
            &arr_ampl,
            &arr_phase);
    this->_gp_confirm_api_status();
    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "error getting IFSTREAM EQ parameters");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->_vars.ifstream.points_in_equalization_buffer <= 0)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "empty IFSTREAM EQ parameters");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.ifstream.eq_frequency_v.resize(
        (size_t)this->_vars.ifstream.points_in_equalization_buffer);
    this->_vars.ifstream.eq_amplitude_v.resize(
        (size_t)this->_vars.ifstream.points_in_equalization_buffer);
    this->_vars.ifstream.eq_phase_v.resize(
        (size_t)this->_vars.ifstream.points_in_equalization_buffer);
    for (int ii = 0; ii < this->_vars.ifstream.points_in_equalization_buffer; ii++)
    {
        this->_vars.ifstream.eq_frequency_v[ii] = arr_freq[ii];
        this->_vars.ifstream.eq_amplitude_v[ii] = arr_ampl[ii];
        this->_vars.ifstream.eq_phase_v[ii] = arr_phase[ii];
    }
    this->_ifstream_copy_eq_parameters();
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_ifstream_get_scaling_parameters()
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

    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetScalingParameters(
            &this->_vars.ifstream.scale_factor,
            &this->_vars.ifstream.scale_frequency);
    this->_gp_confirm_api_status();
    this->_ifstream_copy_scaling_parameters();
}


////////~~~~~~~~END>  rsa306b_ifstream_get.cpp
