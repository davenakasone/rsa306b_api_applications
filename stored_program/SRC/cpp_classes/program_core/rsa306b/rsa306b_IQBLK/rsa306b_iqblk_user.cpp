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
CODEZ rsa306b_class::iqblk_acquire_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }

    if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA)
    {
        this->_iqblk_get_iq_data();  
    }
    else if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA_CPLX)
    {
        this->_iqblk_get_iq_data_cplx(); 
    }
    else if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA_DEINETERLEAVED)
    {
        this->_iqblk_get_iq_data_deinterleaved(); 
    }
    else
    {
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
CODEZ rsa306b_class::iqblk_make_csv
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (file_path_name == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tprovide a file path and file name\n");
        #endif
        return;
    }
    
    if (this->_fptr_write != NULL) 
    {
        fclose(this->_fptr_write);
    }
    this->_fptr_write = fopen(file_path_name, "w");
    if (this->_fptr_write == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tcould not open output path/file_name\n");
        #endif
        return;
    }


    snprintf(this->_vars.gp.helper, BUF_E, "I,Q\n");
    fputs(this->_vars.gp.helper, this->_fptr_write);

    for (std::size_t ii = 0; ii < this->_vars.iqblk.cplx32_v.size(); ii++)
    {
        if (ii == this->_vars.iqblk.cplx32_v.size()-1)
        {
            snprintf(this->_vars.gp.helper, BUF_E, "%f,%f",
                this->_vars.iqblk.cplx32_v[ii].i,
                this->_vars.iqblk.cplx32_v[ii].q);
        }
        else
        {
            snprintf(this->_vars.gp.helper, BUF_E, "%f,%f\n",
                this->_vars.iqblk.cplx32_v[ii].i,
                this->_vars.iqblk.cplx32_v[ii].q);
        }
        fputs(this->_vars.gp.helper, this->_fptr_write);
    }
    fclose(this->_fptr_write);
    this->_fptr_write = NULL;
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqblk_get_iq_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
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
    }
    this->_gp_confirm_api_status();

    this->_vars.gp.api_status = 
        RSA_API::IQBLK_GetIQData(
            data_iq,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length);
    this->_gp_confirm_api_status();

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
    int idx = 0;
    while(idx < 2 * this->_vars.iqblk.actual_buffer_samples)
    {
        this->_vars.iqblk.cplx32_v[idx/2].i = data_iq[idx]; 
        idx++;
        this->_vars.iqblk.cplx32_v[idx/2].q = data_iq[idx]; 
        idx++;
    }

    this->device_stop();
    this->_iqblk_copy_cplx32_v();
    this->_iqblk_copy_actual_buffer_samples();
    this->_iqblk_get_vars();
    delete [] data_iq;
    data_iq = NULL;
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_iqblk_get_iq_data_cplx()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    int timeout_ms = 1;
    bool data_is_ready = false;
    RSA_API::Cplx32* cplx32 = NULL;

    this->_iqblk_get_record_length();
    cplx32 = new RSA_API::Cplx32[this->_vars.iqblk.record_length];
    if (cplx32 == NULL) 
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
    }
    this->_gp_confirm_api_status();

    this->_vars.gp.api_status =
        RSA_API::IQBLK_GetIQDataCplx(
            cplx32,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length);
    this->_gp_confirm_api_status();

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
    for (int ii = 0; ii < this->_vars.iqblk.actual_buffer_samples; ii++)
    {
        this->_vars.iqblk.cplx32_v[ii].i = cplx32[ii].i;
        this->_vars.iqblk.cplx32_v[ii].q = cplx32[ii].q;
    }
    this->device_stop();
    this->_iqblk_copy_cplx32_v();
    this->_iqblk_copy_actual_buffer_samples();
    this->_iqblk_get_vars();
    delete [] cplx32;
    cplx32 = NULL;
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    int timeout_ms = 1;
    bool data_is_ready = false;
    float* data_i = NULL;
    float* data_q = NULL;

    this->_iqblk_get_record_length();
    data_i = new float[this->_vars.iqblk.record_length];
    if (data_i == NULL) 
    {
        #ifdef DEBUG_MIN
            (void)printf("\n\tallocation failure\n");
        #endif
    }
    data_q = new float[this->_vars.iqblk.record_length];
    if (data_q == NULL) 
    {
        #ifdef DEBUG_MIN
            (void)printf("\n\tallocation failure\n");
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
    }
    this->_gp_confirm_api_status();

    this->_vars.gp.api_status =
        RSA_API::IQBLK_GetIQDataDeinterleaved(
            data_i,
            data_q,
            &this->_vars.iqblk.actual_buffer_samples,
            this->_vars.iqblk.record_length);
    this->_gp_confirm_api_status();

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk.actual_buffer_samples);
    for (int ii = 0; ii < this->_vars.iqblk.actual_buffer_samples; ii++)
    {
        this->_vars.iqblk.cplx32_v[ii].i = data_i[ii];
        this->_vars.iqblk.cplx32_v[ii].q = data_q[ii];
    }
    this->device_stop();
    this->_iqblk_copy_cplx32_v();
    this->_iqblk_copy_actual_buffer_samples();
    this->_iqblk_get_vars();
    delete [] data_i;
    data_i = NULL;
    delete [] data_q;
    data_q = NULL;
}


////////~~~~~~~~END>  rsa306b_iqblk_user.cpp
