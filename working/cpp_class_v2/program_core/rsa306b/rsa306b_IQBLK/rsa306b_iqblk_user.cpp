/*
    API group "xxx"

    public :
        < 1 >  iqblk_acquire_data()
        < 2 >  iqblk_make_csv()
    
    private :
        < 1 >  _iqblk_get_iq_data()
        < 2 >  _iqblk_get_iq_data_cplx()
        < 3 >  _iqblk_get_iq_data_deinterleaved()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    all settings should have been set before calling
*/
void rsa306b_class::iqblk_acquire_data()
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
    switch (this->_vars.iqblk.getter)
    {
        case (IQBLK_GET_IQ_DATA) : 
            this->_iqblk_get_iq_data();               
            break;
        case (IQBLK_GET_IQ_DATA_CPLX) : 
            this->_iqblk_get_iq_data_cplx();          
            break;
        case (IQBLK_GET_IQ_DATA_DEINETERLEAVED) : 
            this->_iqblk_get_iq_data_deinterleaved(); 
            break;
        default : 
            #ifdef DEBUG_MIN
                printf("\n\terror in acquisition method\n");
            #endif
            return;
    }
    this->_iqblk_get_acq_info_type();
}


////~~~~


/*
    < 2 > public
*/
void rsa306b_class::iqblk_make_csv
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (file_path_name == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tprovide a file path and file name\n");
        #endif
        return;
    }
    this->_fptr_write = fopen(file_path_name, "w");
    snprintf(this->_vars.gp.helper, BUF_E, "I,Q,\n");
    fputs(this->_vars.gp.helper, this->_fptr_write);

    for (size_t ii = 0; ii < this->_vars.iqblk.cplx32_v.size(); ii++)
    {
        snprintf(this->_vars.gp.helper, BUF_E, "%f,%f,\n",
            this->_vars.iqblk.cplx32_v[ii].i,
            this->_vars.iqblk.cplx32_v[ii].q);
        fputs(this->_vars.gp.helper, this->_fptr_write);
    }
    fclose(this->_fptr_write);
    this->_fptr_write = NULL;
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_iqblk_get_iq_data()
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
    float* data_iq = NULL;
    int timeout_ms = 1;
    bool data_is_ready = false;

    this->_iqblk_get_record_length();
    data_iq = new float[2 * this->_vars.iqblk.record_length];
    if (data_iq == NULL) 
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocation failure\n");
        #endif
    }

    this->device_run();
    this->_vars.gp.api_status = RSA_API::IQBLK_AcquireIQData();
    this->_gp_confirm_api_status();

    while (data_is_ready == false)
    {
        this->_vars.gp.api_status = 
            RSA_API::IQBLK_WaitForIQDataReady(
                timeout_ms, 
                &data_is_ready);
        this->_gp_confirm_api_status();
    }

    this->_vars.gp.api_status = 
        RSA_API::IQBLK_GetIQData(
            data_iq,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length);
    this->_gp_confirm_api_status();
printf("\nrequested:  %d  ,  actual:  %d\n", this->_vars.iqblk.record_length, this->_vars.iqblk.actual_buffer_samples);
    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
    int idx = 0;
    while(idx < 2 * this->_vars.iqblk.actual_buffer_samples)
    {
        this->_vars.iqblk.cplx32_v[idx/2].i = data_iq[idx]; 
        idx++;
        this->_vars.iqblk.cplx32_v[idx/2].q = data_iq[idx]; 
        idx++;
printf("data_iq[%5d,%5d]= %0.7f,%0.7f  ...  cplx_v[%5d]i,q= [%0.7f,%0.7f]\n", 
idx-2, idx-1, data_iq[idx-1], data_iq[idx], 
(idx-1)/2, this->_vars.iqblk.cplx32_v[(idx-2)/2].i, this->_vars.iqblk.cplx32_v[(idx-1)/2].q);
    }

    this->device_stop();
    this->_iqblk_copy_cplx32_v();
    delete [] data_iq;
    data_iq = NULL;
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqblk_get_iq_data_cplx()
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
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_iqblk_get_iq_data_deinterleaved()
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
}


////////~~~~~~~~END>  rsa306b_iqblk_user.cpp
