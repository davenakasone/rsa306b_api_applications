/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >  _iqstream_acquire_data_to_file()
        < 2 >  _iqstream_acquire_data_direct_cplx32_v()
        < 3 >  _iqstream_acquire_data_direct_cplxInt16_v()
        < 4 >  _iqstream_acquire_data_direct_cplxInt32_v()
    
    user should have configured with "iqstream_set_vars()" before acquiring data
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    data goes to a "*.siq" file
    make other files types if people need it
*/
CODEZ rsa306b_class::_iqstream_acquire_data_to_file()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    bool is_complete = false;
    bool is_writing = false;
    if (this->_vars.trig.mode_select == RSA_API::freeRun)
    {
        while (is_complete == false)
        {
            this->_vars.gp.api_status =
                RSA_API::IQSTREAM_GetDiskFileWriteStatus
                (
                    &is_complete,
                    &is_writing
                );
        }
        this->_gp_confirm_api_status();
    }
    else    // triggered mode
    {
        std::chrono::time_point<std::chrono::steady_clock> start_time;
        start_time = std::chrono::steady_clock::now();
        std::chrono::time_point<std::chrono::steady_clock> current_time;
        int elapsed_ms = 0;

        while 
        (
            elapsed_ms < this->constants.IQSTREAM_TIMEOUT_MS &&
            is_complete == false
        )
        {
            this->_vars.gp.api_status =
                RSA_API::IQSTREAM_GetDiskFileWriteStatus
                (
                    &is_complete,
                    &is_writing
                );
            this->_gp_confirm_api_status();

            current_time = std::chrono::steady_clock::now();
            elapsed_ms = static_cast<int>(
                std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count());
        }
        if (is_complete == false)
        {
            #ifdef DEBUG_MIN
                printf("\n\ttrigger event never occured...aborting output file\n");
            #endif
            this->_iqstream_get_disk_fileinfo();
            this->_iqstream_bitcheck(this->_vars.iqstream.fileinfo_type.acqStatus);
            std::wstring filenames_0w(this->_vars.iqstream.fileinfo_type.filenames[0]);
            std::wstring filenames_1w(this->_vars.iqstream.fileinfo_type.filenames[1]);
            std::string filenames0s (filenames_0w.begin(), filenames_0w.end());
            std::string filenames1s (filenames_1w.begin(), filenames_1w.end());
            (void)strncpy(this->_vars.iqstream.fileinfo_type.filenames_0, filenames0s.c_str(), BUF_E);
            (void)strncpy(this->_vars.iqstream.fileinfo_type.filenames_1, filenames1s.c_str(), BUF_E);
            (void)strncpy(this->vars.iqstream.fileinfo_type.filenames_0, this->_vars.iqstream.fileinfo_type.filenames_0, BUF_E);
            (void)strncpy(this->vars.iqstream.fileinfo_type.filenames_1, this->_vars.iqstream.fileinfo_type.filenames_0, BUF_E);
            
            this->_vars.gp.call_status = remove(this->_vars.iqstream.fileinfo_type.filenames_0);
            if (this->_vars.gp.call_status != 0)
            {
                #ifdef DEBUG_MIN
                    (void)printf("\n\terror removing: %s  ,  %d\n", 
                        this->_vars.iqstream.fileinfo_type.filenames_0,
                        this->_vars.gp.call_status);
                #endif
            }
            else
            {
                (void)printf("timed out, deleted  '%s'\n",
                    this->_vars.iqstream.fileinfo_type.filenames_0);
            }
            this->_vars.iqstream.fileinfo_type.numberSamples = 0;
            this->vars.iqstream.fileinfo_type.numberSamples = this->_vars.iqstream.fileinfo_type.numberSamples;
            return;
        }
    }

    this->_iqstream_get_disk_fileinfo();
    this->_iqstream_bitcheck(this->_vars.iqstream.fileinfo_type.acqStatus);
    std::wstring filenames_0w(this->_vars.iqstream.fileinfo_type.filenames[0]);
    std::wstring filenames_1w(this->_vars.iqstream.fileinfo_type.filenames[1]);
    std::string filenames0s (filenames_0w.begin(), filenames_0w.end());
    std::string filenames1s (filenames_1w.begin(), filenames_1w.end());
    (void)strncpy(this->_vars.iqstream.fileinfo_type.filenames_0, filenames0s.c_str(), BUF_E);
    (void)strncpy(this->_vars.iqstream.fileinfo_type.filenames_1, filenames1s.c_str(), BUF_E);
    (void)strncpy(this->vars.iqstream.fileinfo_type.filenames_0, this->_vars.iqstream.fileinfo_type.filenames_0, BUF_E);
    (void)strncpy(this->vars.iqstream.fileinfo_type.filenames_1, this->_vars.iqstream.fileinfo_type.filenames_0, BUF_E);
}


////~~~~


/*
    < 2 > private
    data to std::vector<Cplx32> 
    trigger timeout is handled by the delay
*/
CODEZ rsa306b_class::_iqstream_acquire_data_direct_cplx32_v()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    bool is_ready = false;
    this->_iqstream_get_iq_data_buffer_size();
    while (is_ready == false)
    {
        this->_vars.gp.api_status =
            RSA_API::IQSTREAM_WaitForIQDataReady
            (
                0, 
                &is_ready
            );// need a breakout timer
    }
    this->_gp_confirm_api_status();
    if (is_ready == false)
    {
        #ifdef DEBUG_MIN
            (void)printf("\n\t%d ms elapsed, no trigger detected, no data acquired\n",
                this->constants.IQSTREAM_TIMEOUT_MS);
        #endif
        this->_vars.iqstream.cplx32_v.clear();
        this->_vars.iqstream.cplx32_v.resize(this->constants.INIT_STL_LENGTH);
        this->_iqstream_copy_cplx32_v();
        this->_vars.iqstream.pairs_copied = this->constants.INIT_INT;
        this->_iqstream_copy_pairs_copied();
        this->_vars.iqstream.info_type.acqStatus = this->constants.INIT_UINT;
        this->_vars.iqstream.info_type.scaleFactor = this->constants.INIT_DOUBLE;
        this->_vars.iqstream.info_type.timestamp = this->constants.INIT_UINT;
        this->_iqstream_copy_info_type();
        this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);
        return;    // data transfer aborted
    }

    RSA_API::Cplx32* p_cplx32 = NULL;
    try
    {
        p_cplx32 = new RSA_API::Cplx32[this->_vars.iqstream.pairs_max];
    }
    catch(const std::exception& allocation_status)
    {
        std::cout << "allocation failure:  " << allocation_status.what() << std::endl;
    }
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_GetIQData
        (
            p_cplx32,
            &this->_vars.iqstream.pairs_copied,
            &this->_vars.iqstream.info_type
        );
    this->_gp_confirm_api_status();

    this->_vars.iqstream.cplx32_v.
        resize(static_cast<std::size_t>(this->_vars.iqstream.pairs_copied));
    for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
    {
        this->_vars.iqstream.cplx32_v[kk].i = p_cplx32[kk].i;
        this->_vars.iqstream.cplx32_v[kk].q = p_cplx32[kk].q;
    }
    delete [] p_cplx32; 
    p_cplx32 = NULL;

    this->_iqstream_copy_pairs_copied();
    this->_iqstream_copy_info_type();
    this->_iqstream_copy_cplx32_v();
    this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);
}


////~~~~


/*
    < 3 > private
    data to std::vector<CplxInt16> 
    trigger timeout is handled by the delay
*/
CODEZ rsa306b_class::_iqstream_acquire_data_direct_cplxInt16_v()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    bool is_ready = false;
    this->_iqstream_get_iq_data_buffer_size();
    while (is_ready == false)
    {
        this->_vars.gp.api_status =
            RSA_API::IQSTREAM_WaitForIQDataReady
            (
                0, 
                &is_ready
            );
    }
    this->_gp_confirm_api_status();
    if (is_ready == false)
    {
        #ifdef DEBUG_MIN
            (void)printf("\n\t%d ms elapsed, no trigger detected, no data acquired\n",
                this->constants.IQSTREAM_TIMEOUT_MS);
        #endif
        this->_vars.iqstream.cplxInt16_v.clear();
        this->_vars.iqstream.cplxInt16_v.resize(this->constants.INIT_STL_LENGTH);
        this->_iqstream_copy_cplxInt16_v();
        this->_vars.iqstream.pairs_copied = this->constants.INIT_INT;
        this->_iqstream_copy_pairs_copied();
        this->_vars.iqstream.info_type.acqStatus = this->constants.INIT_UINT;
        this->_vars.iqstream.info_type.scaleFactor = this->constants.INIT_DOUBLE;
        this->_vars.iqstream.info_type.timestamp = this->constants.INIT_UINT;
        this->_iqstream_copy_info_type();
        this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);
        return;    // data transfer aborted
    }

    RSA_API::CplxInt16* p_cplxInt16 = NULL;
    try
    {
        p_cplxInt16 = new RSA_API::CplxInt16[this->_vars.iqstream.pairs_max];
    }
    catch(const std::exception& allocation_status)
    {
        std::cout << "allocation failure:  " << allocation_status.what() << std::endl;
    }
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_GetIQData
        (
            p_cplxInt16,
            &this->_vars.iqstream.pairs_copied,
            &this->_vars.iqstream.info_type
        );
    this->_gp_confirm_api_status();

    this->_vars.iqstream.cplxInt16_v.
        resize(static_cast<std::size_t>(this->_vars.iqstream.pairs_copied));
    for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
    {
        this->_vars.iqstream.cplxInt16_v[kk].i = p_cplxInt16[kk].i;
        this->_vars.iqstream.cplxInt16_v[kk].q = p_cplxInt16[kk].q;
    }
    delete [] p_cplxInt16; 
    p_cplxInt16 = NULL;

    this->_iqstream_copy_pairs_copied();
    this->_iqstream_copy_info_type();
    this->_iqstream_copy_cplxInt16_v();
    this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);
}


////~~~~


/*
    < 4 > private
    data to std::vector<CplxInt32> 
    trigger timeout is handled by the delay
*/
CODEZ rsa306b_class::_iqstream_acquire_data_direct_cplxInt32_v()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    bool is_ready = false;
    this->_iqstream_get_iq_data_buffer_size();
    while (is_ready == false)
    {
        this->_vars.gp.api_status =
            RSA_API::IQSTREAM_WaitForIQDataReady
            (
                0, 
                &is_ready
            );
    }
    this->_gp_confirm_api_status();
    if (is_ready == false)
    {
        #ifdef DEBUG_MIN
            (void)printf("\n\t%d ms elapsed, no trigger detected, no data acquired\n",
                this->constants.IQSTREAM_TIMEOUT_MS);
        #endif
        this->_vars.iqstream.cplxInt32_v.clear();
        this->_vars.iqstream.cplxInt32_v.resize(this->constants.INIT_STL_LENGTH);
        this->_iqstream_copy_cplxInt32_v();
        this->_vars.iqstream.pairs_copied = this->constants.INIT_INT;
        this->_iqstream_copy_pairs_copied();
        this->_vars.iqstream.info_type.acqStatus = this->constants.INIT_UINT;
        this->_vars.iqstream.info_type.scaleFactor = this->constants.INIT_DOUBLE;
        this->_vars.iqstream.info_type.timestamp = this->constants.INIT_UINT;
        this->_iqstream_copy_info_type();
        this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);
        return;    // data transfer aborted
    }

    RSA_API::CplxInt32* p_cplxInt32 = NULL;
    try
    {
        p_cplxInt32 = new RSA_API::CplxInt32[this->_vars.iqstream.pairs_max];
    }
    catch(const std::exception& allocation_status)
    {
        std::cout << "allocation failure:  " << allocation_status.what() << std::endl;
    }
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_GetIQData
        (
            p_cplxInt32,
            &this->_vars.iqstream.pairs_copied,
            &this->_vars.iqstream.info_type
        );
    this->_gp_confirm_api_status();

    this->_vars.iqstream.cplxInt32_v.
        resize(static_cast<std::size_t>(this->_vars.iqstream.pairs_copied));
    for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
    {
        this->_vars.iqstream.cplxInt32_v[kk].i = p_cplxInt32[kk].i;
        this->_vars.iqstream.cplxInt32_v[kk].q = p_cplxInt32[kk].q;
    }
    delete [] p_cplxInt32; 
    p_cplxInt32 = NULL;

    this->_iqstream_copy_pairs_copied();
    this->_iqstream_copy_info_type();
    this->_iqstream_copy_cplxInt32_v();
    this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);
}

             
////////~~~~~~~~END>  rsa306b_iqstream_acquire.cpp
