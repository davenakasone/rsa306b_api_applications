/*
    loading task 2 of 2

    public:
        #  none
        
    private:
        < 1 >  _populate_data()
*/

#include "siq_manager_class.h"


/*
    < 2 > private
    parses an open *.siq file
    updates member variables with extracted information
    data block / samples only
*/
CODEZ siq_manager_class::_populate_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    if (this->_fp_read == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
    }
    if (fseek(this->_fp_read, 0L, SEEK_SET) != 0)
    {
        return this->cutil.report_status_code(CODEZ::_14_fseek_failed);
    }
    if 
    (
        fseek
        (
            this->_fp_read, 
            static_cast<long>(this->_vars.f0_header_size_in_bytes),
            SEEK_CUR
        ) != 0
    )
    {
        return this->cutil.report_status_code(CODEZ::_14_fseek_failed);
    }
    // on first data sample  -->

    std::size_t idx = 0;
    std::size_t idx_limit = 0;

    if (strcmp(this->_vars.f9_number_format, SIQ_NUMBER_FORMATS_STRING[siq_NUMBER_FORMAT_SINGLE]) == 0)
    {
        float temp = 0;
        this->_vars.data_block_cplx32_v.clear();
        this->_vars.data_block_cplx32_v.resize(static_cast<std::size_t>(this->_vars.f8_iq_sample_pairs));
        idx_limit = this->_vars.data_block_cplx32_v.size();
        if (idx_limit > static_cast<std::size_t>(0))
        {
             while(idx < idx_limit)
            {
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("\tbyte %15ld  ", ftell(this->_fp_read));
                #endif
                fread
                (
                    &temp,
                    sizeof(float),
                    1, 
                    this->_fp_read
                );
                this->_vars.data_block_cplx32_v[idx].i = temp;
                fread
                (
                    &temp, 
                    sizeof(float),
                    1, 
                    this->_fp_read
                );
                this->_vars.data_block_cplx32_v[idx].q = temp;
                idx++;
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("[%9ld  of  %9ld]  %14.7f, %14.7f\n",
                    idx,
                    idx_limit,
                    this->_vars.data_block_cplx32_v[idx-1].i,
                    this->_vars.data_block_cplx32_v[idx-1].q);
                #endif
            }
        }
        else
        {
            return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
        }
    }
    else if (strcmp(this->_vars.f9_number_format, SIQ_NUMBER_FORMATS_STRING[siq_NUMBER_FORMAT_INT32]) == 0)
    {
        int32_t temp = 0;
        this->_vars.data_block_cplxint32_v.clear();
        this->_vars.data_block_cplxint32_v.resize(static_cast<std::size_t>(this->_vars.f8_iq_sample_pairs));
        idx_limit = this->_vars.data_block_cplxint32_v.size();
        if (idx_limit > static_cast<std::size_t>(0))
        {
             while(idx < idx_limit)
            {
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("\tbyte %15ld  ", ftell(this->_fp_read));
                #endif
                fread
                (
                    &temp, 
                    sizeof(int32_t),
                    1, 
                    this->_fp_read
                );
                this->_vars.data_block_cplxint32_v[idx].i = temp;
                fread
                (
                    &temp, 
                    sizeof(int32_t),
                    1, 
                    this->_fp_read
                );
                this->_vars.data_block_cplxint32_v[idx].q = temp;
                idx++;
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("[%9ld  of  %9ld]  %15d, %15d\n",
                    idx,
                    idx_limit,
                    static_cast<int>(this->_vars.data_block_cplxint32_v[idx-1].i),
                    static_cast<int>(this->_vars.data_block_cplxint32_v[idx-1].q));
                #endif
            }
        }
        else
        {
            return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
        }
    }
    else if (strcmp(this->_vars.f9_number_format, SIQ_NUMBER_FORMATS_STRING[siq_NUMBER_FORMAT_INT16]) == 0)
    {
        int16_t temp = 0;
        this->_vars.data_block_cplxint16_v.resize(static_cast<std::size_t>(this->_vars.f8_iq_sample_pairs));
        idx_limit = this->_vars.data_block_cplxint16_v.size();
        if (idx_limit > static_cast<std::size_t>(0))
        {
             while(idx < idx_limit)
            {
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("\tbyte %15ld  ", ftell(this->_fp_read));
                #endif
                fread(
                    &temp, 
                    sizeof(int16_t),
                    1, 
                    this->_fp_read);
                this->_vars.data_block_cplxint16_v[idx].i = temp;
                fread(
                    &temp, 
                    sizeof(int16_t),
                    1, 
                    this->_fp_read);
                this->_vars.data_block_cplxint16_v[idx].q = temp;
                idx++;
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("[%9ld  of  %9ld]  %15d, %15d\n",
                    idx,
                    idx_limit,
                    static_cast<int>(this->_vars.data_block_cplxint16_v[idx-1].i),
                    static_cast<int>(this->_vars.data_block_cplxint16_v[idx-1].q));
                #endif
            }
        }
        else
        {
            return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
        }
    }
    else
    {
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  siq_populate_data.cpp
