/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >  _iqstream_acquire_data_to_file()
        < 2 >  _iqstream_acquire_data_direct()
    
    user should have configured with "iqstream_set_vars()" before acquiring data
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    connection check already occured
    not possible to use getter because of that wchar_t
        get private, bitcheck, get public
*/
void rsa306b_class::_iqstream_acquire_data_to_file()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    bool is_complete = false;
    bool is_writing = false;
    bool is_ready = false;

    this->device_run();
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_Start();
    this->_gp_confirm_api_status();

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
            this->_gp_confirm_api_status();
        }
    }
    else    // triggered mode
    {
        this->_vars.gp.api_status =
            RSA_API::IQSTREAM_WaitForIQDataReady
            (
                this->constants.IQSTREAM_TIMEOUT_MS, 
                &is_ready
            );
        this->_gp_confirm_api_status();
        if (is_ready == false)
        {
            #ifdef DEBUG_MIN
                printf("\n\t%d ms elapsed, no trigger detected, no data acquired\n",
                    this->constants.IQSTREAM_TIMEOUT_MS);
            #endif
            this->_vars.gp.api_status = 
                RSA_API::IQSTREAM_GetDiskFileInfo
                (
                    &this->_vars.iqstream.fileinfo_type
                );
            this->_gp_confirm_api_status();
            this->_iqstream_copy_fileinfo_type();
            return;    // file aborted
        }
        this->_vars.gp.api_status =
            RSA_API::IQSTREAM_GetDiskFileWriteStatus
            (
                &is_complete,
                &is_writing
            );
        this->_gp_confirm_api_status();
        if (is_complete != true &&
            is_writing != true   )
        {
            #ifdef DEBUG_MIN
                printf("\n\tfailed to record IQ data to file\n");
            #endif
            this->_vars.gp.api_status = 
                RSA_API::IQSTREAM_GetDiskFileInfo
                (
                    &this->_vars.iqstream.fileinfo_type
                );
            this->_gp_confirm_api_status();
            this->_iqstream_copy_fileinfo_type();
            return;  // file aborted
        }
    }
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_Stop();
    this->_gp_confirm_api_status();

    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_GetDiskFileInfo
        (
            &this->_vars.iqstream.fileinfo_type
        );
    this->_gp_confirm_api_status();
    this->_iqstream_bitcheck(this->_vars.iqstream.fileinfo_type.acqStatus);
    std::wstring filenames_0w(this->_vars.iqstream.fileinfo_type.filenames[0]);
    std::wstring filenames_1w(this->_vars.iqstream.fileinfo_type.filenames[1]);
    std::string filenames0s (filenames_0w.begin(), filenames_0w.end());
    std::string filenames1s (filenames_1w.begin(), filenames_1w.end());
    strncpy(this->_vars.iqstream.fileinfo_type.filenames_0, filenames0s.c_str(), BUF_E);
    strncpy(this->_vars.iqstream.fileinfo_type.filenames_1, filenames1s.c_str(), BUF_E);
    strncpy(this->vars.iqstream.fileinfo_type.filenames_0, this->_vars.iqstream.fileinfo_type.filenames_0, BUF_E);
    strncpy(this->vars.iqstream.fileinfo_type.filenames_1, this->_vars.iqstream.fileinfo_type.filenames_0, BUF_E);

    this->device_stop();
    this->_iqstream_get_enabled();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqstream_acquire_data_direct()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }

    bool is_ready = false;
    if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT16)    // data to td::vector<CplxInt16>
    {
        this->_iqstream_get_iq_data_buffer_size();
        this->device_run();
        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Start();
        this->_gp_confirm_api_status();
        
        if (this->_vars.trig.mode_select == RSA_API::freeRun)
        {
            while (is_ready == false)
            {
                this->_vars.gp.api_status =
                    RSA_API::IQSTREAM_WaitForIQDataReady
                    (
                        0, 
                        &is_ready
                    );
                this->_gp_confirm_api_status();
            }
        }
        else    // triggered
        {
            this->_vars.gp.api_status =
                RSA_API::IQSTREAM_WaitForIQDataReady
                (
                    this->constants.IQSTREAM_TIMEOUT_MS,
                    &is_ready
                );
            this->_gp_confirm_api_status();
            if (is_ready == false)
            {
                #ifdef DEBUG_MIN
                    printf("\n\t%d ms elapsed, no trigger detected, no data acquired\n",
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

        }
       
        RSA_API::CplxInt16* p_cplxInt16 = new RSA_API::CplxInt16[this->_vars.iqstream.pairs_max];       
        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_GetIQData
            (
                p_cplxInt16,
                &this->_vars.iqstream.pairs_copied,
                &this->_vars.iqstream.info_type
            );
        this->_gp_confirm_api_status();
        
        this->_vars.iqstream.cplxInt16_v.resize(this->_vars.iqstream.pairs_copied);
        for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
        {
            this->_vars.iqstream.cplxInt16_v[kk].i = p_cplxInt16[kk].i;
            this->_vars.iqstream.cplxInt16_v[kk].q = p_cplxInt16[kk].q;
        }
        delete [] p_cplxInt16; p_cplxInt16 = NULL;
        this->_iqstream_copy_pairs_copied();
        this->_iqstream_copy_info_type();
        this->_iqstream_copy_cplxInt16_v();
        this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);

        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Stop();
        this->_gp_confirm_api_status();
        this->device_stop();
        this->_iqstream_get_enabled();
    }
    else if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT32)    // data to std::vector<CplxInt32>
    {
        this->_iqstream_get_iq_data_buffer_size();
        this->device_run();
        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Start();
        this->_gp_confirm_api_status();
        
        if (this->_vars.trig.mode_select == RSA_API::freeRun)
        {
            while (is_ready == false)
            {
                this->_vars.gp.api_status =
                    RSA_API::IQSTREAM_WaitForIQDataReady
                    (
                        0, 
                        &is_ready
                    );
                this->_gp_confirm_api_status();
            }
        }
        else    // triggered
        {
            this->_vars.gp.api_status =
                RSA_API::IQSTREAM_WaitForIQDataReady
                (
                    this->constants.IQSTREAM_TIMEOUT_MS,
                    &is_ready
                );
            this->_gp_confirm_api_status();
            if (is_ready == false)
            {
                #ifdef DEBUG_MIN
                    printf("\n\t%d ms elapsed, no trigger detected, no data acquired\n",
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

        }
       
        RSA_API::CplxInt32* p_cplxInt32 = new RSA_API::CplxInt32[this->_vars.iqstream.pairs_max];       
        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_GetIQData
            (
                p_cplxInt32,
                &this->_vars.iqstream.pairs_copied,
                &this->_vars.iqstream.info_type
            );
        this->_gp_confirm_api_status();
        
        this->_vars.iqstream.cplxInt32_v.resize(this->_vars.iqstream.pairs_copied);
        for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
        {
            this->_vars.iqstream.cplxInt32_v[kk].i = p_cplxInt32[kk].i;
            this->_vars.iqstream.cplxInt32_v[kk].q = p_cplxInt32[kk].q;
        }
        delete [] p_cplxInt32; p_cplxInt32 = NULL;
        this->_iqstream_copy_pairs_copied();
        this->_iqstream_copy_info_type();
        this->_iqstream_copy_cplxInt32_v();
        this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);

        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Stop();
        this->_gp_confirm_api_status();
        this->device_stop();
        this->_iqstream_get_enabled();
    }
    else    // data to std::vector<Cplx32> 
    {
        this->_iqstream_get_iq_data_buffer_size();
        this->device_run();
        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Start();
        this->_gp_confirm_api_status();
        
        if (this->_vars.trig.mode_select == RSA_API::freeRun)
        {
            while (is_ready == false)
            {
                this->_vars.gp.api_status =
                    RSA_API::IQSTREAM_WaitForIQDataReady
                    (
                        0, 
                        &is_ready
                    );
                this->_gp_confirm_api_status();
            }
        }
        else    // triggered
        {
            this->_vars.gp.api_status =
                RSA_API::IQSTREAM_WaitForIQDataReady
                (
                    this->constants.IQSTREAM_TIMEOUT_MS,
                    &is_ready
                );
            this->_gp_confirm_api_status();
            if (is_ready == false)
            {
                #ifdef DEBUG_MIN
                    printf("\n\t%d ms elapsed, no trigger detected, no data acquired\n",
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

        }
       
        RSA_API::Cplx32* p_cplx32 = new RSA_API::Cplx32[this->_vars.iqstream.pairs_max];       
        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_GetIQData
            (
                p_cplx32,
                &this->_vars.iqstream.pairs_copied,
                &this->_vars.iqstream.info_type
            );
        this->_gp_confirm_api_status();
        
        this->_vars.iqstream.cplx32_v.resize(this->_vars.iqstream.pairs_copied);
        for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
        {
            this->_vars.iqstream.cplx32_v[kk].i = p_cplx32[kk].i;
            this->_vars.iqstream.cplx32_v[kk].q = p_cplx32[kk].q;
        }
        delete [] p_cplx32; p_cplx32 = NULL;
        this->_iqstream_copy_pairs_copied();
        this->_iqstream_copy_info_type();
        this->_iqstream_copy_cplx32_v();
        this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);

        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Stop();
        this->_gp_confirm_api_status();
        this->device_stop();
        this->_iqstream_get_enabled();
    }
}


////////~~~~~~~~END>  rsa306b_iqstream_acquire.cpp
