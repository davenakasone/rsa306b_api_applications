/*
    API group "IQSTREAM"

    public :
        < 1 >  iqstream_acquire_data()                   
        < 2 >  iqstream_make_csv()
        < 3 >  iqstream_clear_sticky()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    user should have configured with 
        "iqstream_set_vars()" before acquiring data
*/
void rsa306b_class::iqstream_acquire_data()
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

    this->device_run();
    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_Start();
    this->_gp_confirm_api_status();

    if (this->_vars.iqstream.destination_select == RSA_API::IQSOD_CLIENT)
    {
        switch (this->_vars.iqstream.datatype_select)
        {
        case (RSA_API::IQSODT_SINGLE) :
            this->_iqstream_acquire_data_direct_cplx32_v();
            break;
        case (RSA_API::IQSODT_SINGLE_SCALE_INT32) :
            this->_iqstream_acquire_data_direct_cplx32_v();
            break;
        case (RSA_API::IQSODT_INT16) :
            this->_iqstream_acquire_data_direct_cplxInt16_v();
            break;
        case (RSA_API::IQSODT_INT32) :
            this->_iqstream_acquire_data_direct_cplxInt32_v();
            break;
        default:
            #ifdef DEBUG_MIN
                snprintf(X_ddts, sizeof(X_ddts), "invalid IQSTREAM data output destination");
                snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(true);
            #endif
            break;
        }
    }
    else 
    {
        if (this->_vars.iqstream.destination_select == RSA_API::IQSOD_FILE_SIQ)
        {
            this->_iqstream_acquire_data_to_file();
        }
        else
        {
            #ifdef DEBUG_MIN
                snprintf(X_ddts, sizeof(X_ddts), "only use *.siq files");
                snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(true);
            #endif
        }
    }

    this->_vars.gp.api_status = 
        RSA_API::IQSTREAM_Stop();
    this->_gp_confirm_api_status();
    this->device_stop();
    this->_iqstream_get_enabled();
}


////~~~~


/*
    < 2 > public
    designed to be use immidiatley after acquiring data
*/
void rsa306b_class::iqstream_make_csv
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.iqstream.destination_select != RSA_API::IQSOD_CLIENT)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "no data was output direct to client");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (file_path_name == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "allocate output file-path-name");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->_vars.iqstream.cplx32_v.size() <= INIT_STL_LENGTH                      &&
        ( this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE             ||
          this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE_SCALE_INT32) )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "cplx32 vector has no data");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->_vars.iqstream.cplxInt32_v.size() <= INIT_STL_LENGTH  &&
        this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT32)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "cplxInt32 vector has no data");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    if (this->_vars.iqstream.cplxInt16_v.size() <= INIT_STL_LENGTH   &&
        this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT16 )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "cplxInt16 vector has no data");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    this->_fptr_write = fopen(file_path_name, "w");
    if (this->_fptr_write == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "failed to open:  %s", file_path_name);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    snprintf(this->_vars.gp.helper, BUF_E, "I,Q\n");
    fputs(this->_vars.gp.helper, this->_fptr_write);

    if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE            ||
        this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE_SCALE_INT32 )
    {
        for (std::size_t kk = 0; kk < this->_vars.iqstream.cplx32_v.size(); kk++)
        {
            if (kk == this->_vars.iqstream.cplx32_v.size()-1)
            {
                snprintf(this->_vars.gp.helper, BUF_E-1, "%0.9f,%0.9f",
                    this->_vars.iqstream.cplx32_v[kk].i,
                    this->_vars.iqstream.cplx32_v[kk].q);
            }
            else
            {
                snprintf(this->_vars.gp.helper, BUF_E-1, "%0.9f,%0.9f\n",
                    this->_vars.iqstream.cplx32_v[kk].i,
                    this->_vars.iqstream.cplx32_v[kk].q);
            }
            fputs(this->_vars.gp.helper, this->_fptr_write);
        }
    }
    else if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT32)
    {
        for (std::size_t kk = 0; kk < this->_vars.iqstream.cplxInt32_v.size(); kk++)
        {
            if (kk == this->_vars.iqstream.cplxInt32_v.size())
            {
                snprintf(this->_vars.gp.helper, BUF_E, "%d,%d",
                    this->_vars.iqstream.cplxInt32_v[kk].i,
                    this->_vars.iqstream.cplxInt32_v[kk].q);
            }
            else
            {
                snprintf(this->_vars.gp.helper, BUF_E-1, "%d,%d\n",
                    this->_vars.iqstream.cplxInt32_v[kk].i,
                    this->_vars.iqstream.cplxInt32_v[kk].q);
            }
            fputs(this->_vars.gp.helper, this->_fptr_write);
        }
    }
    else if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT16)
    {
        for (std::size_t kk = 0; kk < this->_vars.iqstream.cplxInt16_v.size(); kk++)
        {
            if (kk == this->_vars.iqstream.cplxInt16_v.size())
            {
                snprintf(this->_vars.gp.helper, BUF_E-1, "%d,%d",
                    this->_vars.iqstream.cplxInt16_v[kk].i,
                    this->_vars.iqstream.cplxInt16_v[kk].q);
            }
            else
            {
                snprintf(this->_vars.gp.helper, BUF_E-1, "%d,%d\n",
                    this->_vars.iqstream.cplxInt16_v[kk].i,
                    this->_vars.iqstream.cplxInt16_v[kk].q);
            }
            fputs(this->_vars.gp.helper, this->_fptr_write);
        }
    }
    else
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "logic error");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }
    fclose(this->_fptr_write);
    this->_fptr_write = NULL;
}


////~~~~


/*
    < 3 > public
*/
void rsa306b_class::iqstream_clear_sticky()
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
    
    RSA_API::IQSTREAM_ClearAcqStatus();    // implemented as void
    this->_iqstream_get_disk_fileinfo();   // assume file stream
    this->_vars.iqstream.info_type.acqStatus =
        this->_vars.iqstream.info_type.acqStatus  & 
        (
            RSA_API::IQSTRM_STATUS_OVERRANGE          |
            RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY |
            RSA_API::IQSTRM_STATUS_IBUFF75PCT         |
            RSA_API::IQSTRM_STATUS_IBUFFOVFLOW        |
            RSA_API::IQSTRM_STATUS_OBUFF75PCT         |
            RSA_API::IQSTRM_STATUS_OBUFFOVFLOW        );
    if (this->_vars.iqstream.destination_select == RSA_API::IQSOD_CLIENT)
    {
        this->_iqstream_bitcheck(
            this->_vars.iqstream.info_type.acqStatus);
    }
}


////////~~~~~~~~END>  rsa306b_iqstream_user.cpp
