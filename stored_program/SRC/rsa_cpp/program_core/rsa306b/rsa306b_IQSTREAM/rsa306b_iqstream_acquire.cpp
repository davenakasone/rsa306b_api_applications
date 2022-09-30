/*
    API group "IQSTREAM"

    public :
        < 1 >  iqstream_acquire()
    
    private :
        < 1 >  _iqstream_acquire_data_direct_cplx32_v()
        < 2 >  _iqstream_acquire_data_direct_cplxInt16_v()
        < 3 >  _iqstream_acquire_data_direct_cplxInt32_v()
    
    user should have configured with "iqstream_set_vars()" before acquiring data
*/

#include "../rsa306b_class.h"

/*
    < 1 > public
    user should have configured with 
        "iqstream_set_vars()" before acquiring data
        "device_run()" was called at lease for first acquisition
        "iqstream_start()" was called at least for first acquisition
        ...get data
        "iqstream_stop()" is called when done
        "device_stop()" is called last

        data and files will presist, but a new operation will overwrite the std::vectors
        so process or dump the data before subsequent acquisitons
*/
CODEZ rsa306b_class::iqstream_acquire_data
(
    const int timeout_ms
)
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
    if (this->_vars.iqstream.destination_select != RSA_API::IQSOD_CLIENT)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "only can use direct-to-client streaming");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
#endif

int ms_timeout = timeout_ms;

#ifdef TIMEOUT_MS
    if (ms_timeout > TIMEOUT_MS)
    {
        ms_timeout = TIMEOUT_MS;
    }
    if (ms_timeout < 0)
    {
        ms_timeout = 1;
    }
#endif

    // settings applied
    // device_run()
    // iqstream_start()

    bool is_ready = false;
    (void)this->_iqstream_get_iq_data_buffer_size();

#ifdef TIMEOUT_MS
    this->_api_status =
        RSA_API::IQSTREAM_WaitForIQDataReady
        (
            timeout_ms, 
            &is_ready
        );
#else
    while (is_ready == false)    // this could block forever
    {
        this->_api_status =
            RSA_API::IQSTREAM_WaitForIQDataReady
            (
                timeout_ms, 
                &is_ready
            );
    }
#endif
    this->_report_api_status();

    if (is_ready == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "trigger event never occured...no data acquired");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif

        this->_vars.iqstream.cplx32_v.clear();
        this->_vars.iqstream.cplx32_v.resize(this->_vars.iqstream._CPLX_V_size);
        (void)this->_iqstream_copy_cplx32_v();
        
        this->_vars.iqstream.pairs_copied = this->_vars.iqstream._PAIRS_COPIED;
        (void)this->_iqstream_copy_pairs_copied();

        return this->cutil.report_status_code(CODEZ::_30_trigger_event_never_occured);
    }

    switch (this->_vars.iqstream.datatype_select)
    {
        case (RSA_API::IQSODT_SINGLE)             : return this->_iqstream_acquire_data_direct_cplx32_v   ();
        case (RSA_API::IQSODT_SINGLE_SCALE_INT32) : return this->_iqstream_acquire_data_direct_cplx32_v   ();
        case (RSA_API::IQSODT_INT16)              : return this->_iqstream_acquire_data_direct_cplxInt16_v();
        case (RSA_API::IQSODT_INT32)              : return this->_iqstream_acquire_data_direct_cplxInt32_v();
        default : return this->cutil.report_status_code(CODEZ::_2_error_in_logic);
    }
    // iqstream_stop()
    // device_stop()
    // bitchecks
}


////~~~~


/*
    < 1 > private
    data to std::vector<Cplx32> 
    trigger timeout is handled by the delay
*/
CODEZ rsa306b_class::_iqstream_acquire_data_direct_cplx32_v()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    RSA_API::Cplx32* p_cplx32 = NULL;
    try
    {
        p_cplx32 = new RSA_API::Cplx32[this->_vars.iqstream.pairs_max];
    }
    catch(const std::exception& allocation_status)
    {
        std::cout << "allocation failure:  " << allocation_status.what() << std::endl;
    }

    RSA_API::ReturnStatus temp = 
        RSA_API::IQSTREAM_GetIQData
        (
            p_cplx32,
            &this->_vars.iqstream.pairs_copied,
            &this->_vars.iqstream.info_type
        );

    this->_vars.iqstream.cplx32_v.
        resize(static_cast<std::size_t>(this->_vars.iqstream.pairs_copied));
    for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
    {
        this->_vars.iqstream.cplx32_v[kk].i = p_cplx32[kk].i;
        this->_vars.iqstream.cplx32_v[kk].q = p_cplx32[kk].q;
    }
    delete [] p_cplx32; 
    p_cplx32 = NULL;

    (void)this->_iqstream_copy_pairs_copied();
    (void)this->_iqstream_copy_info_type();
    (void)this->_iqstream_copy_cplx32_v();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 2 > private
    data to std::vector<CplxInt16> 
    trigger timeout is handled by the delay
*/
CODEZ rsa306b_class::_iqstream_acquire_data_direct_cplxInt16_v()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    RSA_API::CplxInt16* p_cplxInt16 = NULL;
    try
    {
        p_cplxInt16 = new RSA_API::CplxInt16[this->_vars.iqstream.pairs_max];
    }
    catch(const std::exception& allocation_status)
    {
        std::cout << "allocation failure:  " << allocation_status.what() << std::endl;
    }

    RSA_API::ReturnStatus temp =
        RSA_API::IQSTREAM_GetIQData
        (
            p_cplxInt16,
            &this->_vars.iqstream.pairs_copied,
            &this->_vars.iqstream.info_type
        );

    this->_vars.iqstream.cplxInt16_v.
        resize(static_cast<std::size_t>(this->_vars.iqstream.pairs_copied));
    for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
    {
        this->_vars.iqstream.cplxInt16_v[kk].i = p_cplxInt16[kk].i;
        this->_vars.iqstream.cplxInt16_v[kk].q = p_cplxInt16[kk].q;
    }
    delete [] p_cplxInt16; 
    p_cplxInt16 = NULL;

    (void)this->_iqstream_copy_pairs_copied();
    (void)this->_iqstream_copy_info_type();
    (void)this->_iqstream_copy_cplxInt16_v();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 3 > private
    data to std::vector<CplxInt32> 
    trigger timeout is handled by the delay
*/
CODEZ rsa306b_class::_iqstream_acquire_data_direct_cplxInt32_v()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    RSA_API::CplxInt32* p_cplxInt32 = NULL;
    try
    {
        p_cplxInt32 = new RSA_API::CplxInt32[this->_vars.iqstream.pairs_max];
    }
    catch(const std::exception& allocation_status)
    {
        std::cout << "allocation failure:  " << allocation_status.what() << std::endl;
    }
    
    RSA_API::ReturnStatus temp =
        RSA_API::IQSTREAM_GetIQData
        (
            p_cplxInt32,
            &this->_vars.iqstream.pairs_copied,
            &this->_vars.iqstream.info_type
        );

    this->_vars.iqstream.cplxInt32_v.
        resize(static_cast<std::size_t>(this->_vars.iqstream.pairs_copied));
    for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
    {
        this->_vars.iqstream.cplxInt32_v[kk].i = p_cplxInt32[kk].i;
        this->_vars.iqstream.cplxInt32_v[kk].q = p_cplxInt32[kk].q;
    }
    delete [] p_cplxInt32; 
    p_cplxInt32 = NULL;

    (void)this->_iqstream_copy_pairs_copied();
    (void)this->_iqstream_copy_info_type();
    (void)this->_iqstream_copy_cplxInt32_v();
    return this->set_api_status(temp);
}

             
////////~~~~~~~~END>  rsa306b_iqstream_acquire.cpp
