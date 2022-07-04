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
*/
void rsa306b_class::_iqstream_acquire_data_to_file()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    bool is_complete = false;
    bool is_writing = false;

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
        while (is_complete == true && 
               is_writing == true   )
        {
            // timeout required, see p73 ....sleep + counter?
        }
        printf("\n\tTODO\n");
    }

    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_Stop();
    this->_gp_confirm_api_status();
    RSA_API::IQSTREAM_GetDiskFileInfo(&this->_vars.iqstream.fileinfo_type);
    this->_iqstream_get_disk_fileinfo();    // bit check is handeled

    std::wstring filenames_0w(this->_vars.iqstream.fileinfo_type.filenames[0]);
    std::wstring filenames_1w(this->_vars.iqstream.fileinfo_type.filenames[1]);
    std::string filenames0s (filenames_0w.begin(), filenames_0w.end());
    std::string filenames1s (filenames_1w.begin(), filenames_1w.end());
    strncpy(this->_vars.iqstream.name_of_file, filenames0s.c_str(), BUF_C);
    printf("%s  ,  %s\n", this->_vars.iqstream.name_of_file, this->_vars.iqstream.n);

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

    if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT16)    // data to td::vector<CplxInt16>
    {

    }
    else if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT32)    // data to std::vector<CplxInt32>
    {

    }
    else    // data to std::vector<Cplx32>
    {
        this->_iqstream_get_iq_data_buffer_size();
        RSA_API::Cplx32* p_cplx32 = new RSA_API::Cplx32[this->_vars.iqstream.pairs_max];
            this->device_run();
        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Start();
        this->_gp_confirm_api_status();
        
        RSA_API::IQSTREAM_GetIQData
        (
            p_cplx32,
            &this->_vars.iqstream.pairs_copied,
            &this->_vars.iqstream.info_type
        );

        this->_vars.iqstream.cplx32_v.resize(this->_vars.iqstream.pairs_copied);
        for (int kk = 0; kk < this->_vars.iqstream.pairs_copied; kk++)
        {
            this->_vars.iqstream.cplx32_v[kk].i = p_cplx32[kk].i;
            this->_vars.iqstream.cplx32_v[kk].q = p_cplx32[kk].q;
        }
        delete [] p_cplx32; p_cplx32 = NULL;

        this->_vars.gp.api_status = 
            RSA_API::IQSTREAM_Stop();
        this->_gp_confirm_api_status();
        //this->_iqstream_
        this->device_stop();
    }
}


////////~~~~~~~~END>  rsa306b_iqstream_acquire.cpp
