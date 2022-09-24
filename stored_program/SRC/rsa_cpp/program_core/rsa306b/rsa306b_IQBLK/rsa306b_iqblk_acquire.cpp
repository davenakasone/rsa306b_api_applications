/*
    API group "IQBLK"
    user must run device and make sure settings are correct

    public :
        < 1 >  iqblk_acquire_data()
    
    private :
        < 1 >  _iqblk_get_iq_data()
        < 2 >  _iqblk_get_iq_data_cplx()
        < 3 >  _iqblk_get_iq_data_deinterleaved()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    all settings should have been set before calling
    device is running
*/
CODEZ rsa306b_class::iqblk_acquire_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    CODEZ catcher = CODEZ::_0_no_errors;
    switch(this->_vars.iqblk.getting_select)
    {
        
        case(iqblkGetData::interleaved)   : catcher = this->_iqblk_get_iq_data              (); break; 
        case(iqblkGetData::deinterleaved) : catcher = this->_iqblk_get_iq_data_deinterleaved(); break;
        case(iqblkGetData::complex)       : catcher = this->_iqblk_get_iq_data_cplx         (); break;
        default                           : catcher = this->_iqblk_get_iq_data_cplx         (); break;

    }

    (void)this->_iqblk_copy_cplx32_v();
    (void)this->_iqblk_copy_actual_buffer_samples();
    (void)this->_iqblk_get_acq_info_type();

#ifdef SAFETY_CHECKS
    (void)this->iqblk_good_bitcheck();
#endif

    return this->cutil.report_status_code(catcher);
}


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqblk_get_iq_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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

    float* data_iq     = NULL;
    bool data_is_ready = false;

    (void)this->_iqblk_get_record_length();
    
    (void)this->set_api_status(RSA_API::IQBLK_AcquireIQData());

    (void)this->cutil.h_new_float_d1
    (
        data_iq,
        static_cast<int>(2 * this->_vars.iqblk.record_length)
    );

#ifdef LOOP_TIMEOUT
    int timeout_ms     = this->_vars.iqblk.LOOP_LIMIT_MS;
    this->_api_status =
        RSA_API::IQBLK_WaitForIQDataReady
        (
            timeout_ms, 
            &data_is_ready
        );
#else
    int timeout_ms = 0;
    while(data_is_ready == false)
    {
        this->_api_status =
            RSA_API::IQBLK_WaitForIQDataReady
            (
                timeout_ms,
                &data_is_ready
            );
    }
#endif
    (void)this->_report_api_status();

    RSA_API::ReturnStatus temp = 
        RSA_API::IQBLK_GetIQData
        (
            data_iq,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length
        );

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
    std::size_t idx = 0LU;
    while
    (
        idx < 
        static_cast<std::size_t>(2* this->_vars.iqblk.actual_buffer_samples)
    )
    {
        this->_vars.iqblk.cplx32_v[idx/2].i = data_iq[idx]; 
        idx++;
        this->_vars.iqblk.cplx32_v[idx/2].q = data_iq[idx]; 
        idx++;
    }

    (void)this->cutil.h_delete_float_d1(data_iq);
    return this->set_api_status(temp);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_iqblk_get_iq_data_cplx()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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

    RSA_API::Cplx32* cplx32 = NULL;
    bool data_is_ready = false;

    (void)this->_iqblk_get_record_length();
    
    (void)this->set_api_status(RSA_API::IQBLK_AcquireIQData());

    cplx32 = new RSA_API::Cplx32[this->_vars.iqblk.record_length];
    if (cplx32 == NULL) 
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_22_dynamic_allocation_failed));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_22_dynamic_allocation_failed);
    }

#ifdef LOOP_TIMEOUT
    int timeout_ms    = this->_vars.iqblk.LOOP_LIMIT_MS;
    this->_api_status =
        RSA_API::IQBLK_WaitForIQDataReady
        (
            timeout_ms, 
            &data_is_ready
        );
#else
    int timeout_ms = 0;
    while(data_is_ready == false)
    {
        this->_api_status =
            RSA_API::IQBLK_WaitForIQDataReady
            (
                timeout_ms,
                &data_is_ready
            );
    }
#endif
    (void)this->_report_api_status();

    RSA_API::ReturnStatus temp = 
        RSA_API::IQBLK_GetIQDataCplx
        (
            cplx32,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length
        );

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
    std::size_t idx = 0LU;
    while
    (
        idx < 
        static_cast<std::size_t>(2* this->_vars.iqblk.actual_buffer_samples)
    )
    for (int kk = 0; kk < this->_vars.iqblk.actual_buffer_samples; kk++)
    {
        this->_vars.iqblk.cplx32_v[kk].i = cplx32[kk].i;
        this->_vars.iqblk.cplx32_v[kk].q = cplx32[kk].q;
    }

    delete [] cplx32;
    cplx32 = NULL;
    return this->set_api_status(temp);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_iqblk_get_iq_data_deinterleaved()
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

    bool data_is_ready = false;
    float* data_i = NULL;
    float* data_q = NULL;

    (void)this->_iqblk_get_record_length();
    
    (void)this->set_api_status(RSA_API::IQBLK_AcquireIQData());

    (void)this->cutil.h_new_float_d1
    (
        data_i,
        static_cast<int>(this->_vars.iqblk.record_length)
    );

    (void)this->cutil.h_new_float_d1
    (
        data_q,
        static_cast<int>(this->_vars.iqblk.record_length)
    );

#ifdef LOOP_TIMEOUT
    int timeout_ms    = this->_vars.iqblk.LOOP_LIMIT_MS;
    this->_api_status =
        RSA_API::IQBLK_WaitForIQDataReady
        (
            timeout_ms, 
            &data_is_ready
        );
#else
    int timeout_ms = 0;
    while(data_is_ready == false)
    {
        this->_api_status =
            RSA_API::IQBLK_WaitForIQDataReady
            (
                timeout_ms,
                &data_is_ready
            );
    }
#endif
    (void)this->_report_api_status();

    RSA_API::ReturnStatus temp =
        RSA_API::IQBLK_GetIQDataDeinterleaved
        (
            data_i,
            data_q,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length
        );

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
    for (int kk = 0; kk < this->_vars.iqblk.actual_buffer_samples; kk++)
    {
        this->_vars.iqblk.cplx32_v[kk].i = data_i[kk];
        this->_vars.iqblk.cplx32_v[kk].q = data_q[kk];
    }

    (void)this->cutil.h_delete_float_d1(data_i);
    (void)this->cutil.h_delete_float_d1(data_q);
    return this->set_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_iqblk_acquire.cpp
