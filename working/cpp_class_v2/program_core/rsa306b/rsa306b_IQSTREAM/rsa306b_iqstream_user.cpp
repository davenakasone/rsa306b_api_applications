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
                printf("\n\terror in datatype selection\n");
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
                printf("\n\tonly '*.siq' files are available\n");
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
*/
void rsa306b_class::iqstream_make_csv
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.iqstream.destination_select != RSA_API::IQSOD_CLIENT)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno direct data availible to make CSV\n");
        #endif
        return;
    }
    if (file_path_name == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate 'file_path_name' before calling\n");
        #endif
        return;
    }
    if (this->_vars.iqstream.cplx32_v.size() <= this->constants.INIT_STL_LENGTH      &&
        ( this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE           ||
          this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE_SCALE_INT32) )
    {
        #ifdef DEBUG_MIN
            printf("\n\tCSV not possible, no data availible\n");
        #endif
        return;
    }
    if (this->_vars.iqstream.cplxInt32_v.size() <= this->constants.INIT_STL_LENGTH &&
        this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT32               )
    {
        #ifdef DEBUG_MIN
            printf("\n\tCSV not possible, no data availible\n");
        #endif
        return;
    }
    if (this->_vars.iqstream.cplxInt16_v.size() <= this->constants.INIT_STL_LENGTH &&
        this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT16               )
    {
        #ifdef DEBUG_MIN
            printf("\n\tCSV not possible, no data availible\n");
        #endif
        return;
    }

    this->_fptr_write = fopen(file_path_name, "w");
    if (this->_fptr_write == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tfailed to open CSV for writting\n");
        #endif
        return;
    }
    snprintf(this->_vars.gp.helper, BUF_E, "i,q,\n");
    fputs(this->_vars.gp.helper, this->_fptr_write);

    if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE            ||
        this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE_SCALE_INT32 )
    {
        for (std::size_t kk = 0; kk < this->_vars.iqstream.cplx32_v.size(); kk++)
        {
            snprintf(this->_vars.gp.helper, BUF_E, "%0.9f,%0.9f\n",
                this->_vars.iqstream.cplx32_v[kk].i,
                this->_vars.iqstream.cplx32_v[kk].q);
            fputs(this->_vars.gp.helper, this->_fptr_write);
        }
    }
    else if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT32)
    {
        for (std::size_t kk = 0; kk < this->_vars.iqstream.cplxInt32_v.size(); kk++)
        {
            snprintf(this->_vars.gp.helper, BUF_E, "%d,%d\n",
                this->_vars.iqstream.cplxInt32_v[kk].i,
                this->_vars.iqstream.cplxInt32_v[kk].q);
            fputs(this->_vars.gp.helper, this->_fptr_write);
        }
    }
    else if (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT16)
    {
        for (std::size_t kk = 0; kk < this->_vars.iqstream.cplxInt16_v.size(); kk++)
        {
            snprintf(this->_vars.gp.helper, BUF_E, "%d,%d\n",
                this->_vars.iqstream.cplxInt16_v[kk].i,
                this->_vars.iqstream.cplxInt16_v[kk].q);
            fputs(this->_vars.gp.helper, this->_fptr_write);
        }
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("\n\tlogice error, CSV failed\n");
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
