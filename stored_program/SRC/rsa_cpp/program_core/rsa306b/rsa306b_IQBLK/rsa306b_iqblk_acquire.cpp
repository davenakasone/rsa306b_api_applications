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

    CODEZ catcher = CODEZ::_0_no_errors;
    (void)this->_iqblk_get_record_length();
    (void)this->set_api_status(RSA_API::IQBLK_AcquireIQData());
    bool is_ready = false;
    
#ifdef BLOCKING_TIMEOUT
    (void)this->cutil.timer_split_start();
    while 
    (
        this->cutil.timer_get_split_wall() < TIMEOUT_LIMIT_S &&
        is_ready == false
    )
    {
        this->_api_status =
            RSA_API::IQBLK_WaitForIQDataReady
            (
                0,
                &is_ready
            );
    }
#else
    while (is_ready == false)    // will block until data is ready
    {
        this->_api_status =
            RSA_API::IQBLK_WaitForIQDataReady
            (
                0,
                &is_ready
            );
    }
#endif
    (void)this->_report_api_status();
    if (is_ready == false)
    {
        return this->cutil.report_status_code(CODEZ::_27_loop_timed_out);
    }

    switch(this->_vars.iqblk.getting_select)
    {
        
        case(iqblkGetData::interleaved)   : catcher = this->_iqblk_get_iq_data              (); break; 
        case(iqblkGetData::deinterleaved) : catcher = this->_iqblk_get_iq_data_deinterleaved(); break;
        case(iqblkGetData::complex)       : catcher = this->_iqblk_get_iq_data_cplx         (); break;
        default                           : return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    if (catcher == CODEZ::_0_no_errors)
    {
        (void)this->_iqblk_copy_cplx32_v();
        (void)this->_iqblk_copy_actual_buffer_samples();
        (void)this->_iqblk_get_acq_info_type();
        #ifdef SAFETY_CHECKS
            (void)this->iqblk_good_bitcheck();
        #endif
        this->set_api_status(RSA_API::IQBLK_FinishedIQData());    // ?
    }

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

    float* data_iq     = NULL;
    try
    {
        data_iq = new float[2 * this->_vars.iqblk.record_length];
    }
    catch(...)
    {
        return this->cutil.report_status_code(CODEZ::_22_dynamic_allocation_failed);
    }

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

    delete [] data_iq;
    data_iq = NULL;
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

    RSA_API::Cplx32* cplx32 = NULL;
    try
    {
        cplx32 = new RSA_API::Cplx32[this->_vars.iqblk.record_length];
    }
    catch(...)
    {
        return this->cutil.report_status_code(CODEZ::_22_dynamic_allocation_failed);
    }

    RSA_API::ReturnStatus temp = 
        RSA_API::IQBLK_GetIQDataCplx
        (
            cplx32,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length
        );

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
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

    float* data_i = NULL;
    float* data_q = NULL;
    try
    {
        data_i = new float[this->_vars.iqblk.record_length];
        data_q = new float[this->_vars.iqblk.record_length];
    }
    catch(...)
    {
        return this->cutil.report_status_code(CODEZ::_22_dynamic_allocation_failed);
    }

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

    delete [] data_i;
    data_i = NULL;
    delete [] data_q;
    data_q = NULL;
    return this->set_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_iqblk_acquire.cpp
