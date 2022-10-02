/*
    API group "IQBLK"

    public :
        < 2 >  iqblk_make_write()
        < 3 >  iqblk_good_bitcheck
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::iqblk_write_csv
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
            (void)snprintf(X_ddts, sizeof(X_ddts), "%s", this->cutil.codez_messages(CODEZ::_25_pointer_is_null));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_25_pointer_is_null);
    }
    
    std::size_t v_size = this->_vars.iqblk.cplx32_v.size();

    if (v_size < 1LU)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "iqblk.cplx32_v.size() =  %lu", v_size);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    
    if (file_path_name[0] == '\0')    // using default output file_path_name
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_%lu_%s",
            DATA_DIRECTORY_PROCESSED,
            IQBLK_FILE_NAME_BASE,
            this->_vars.reftime.current.timestamp,
            DATA_OUTPUT_EXTENSTION);
        (void)sprintf(file_path_name, "%s", this->_helper);
    }
    else
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s", file_path_name);
    }

    this->_fp_write = fopen(this->_helper, "w");
    if (this->_fp_write == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_13_fopen_failed);
    }
    
    (void)sprintf(this->_helper, "%s,%s,%s\n",
        IQBLK_FIELD_1,
        IQBLK_FIELD_2,
        IQBLK_FIELD_3);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size; idx++)
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%0.12lf,%f,%f\n", 
            static_cast<double>(idx) / this->_vars.iqblk.sample_rate,
            this->_vars.iqblk.cplx32_v[idx].i,
            this->_vars.iqblk.cplx32_v[idx].q);
        (void)fputs(this->_helper, this->_fp_write);
    }

    (void)fclose(this->_fp_write);
    this->_fp_write = NULL;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 2 > public
*/
bool rsa306b_class::iqblk_good_bitcheck()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    CODEZ temp = 
    this->cutil.iqblk_acq_status
    (
        this->_vars.iqblk.acq_info_type.acqStatus, 
        this->_vars.iqblk.valid_bitmask,
        this->_vars.iqblk.acq_status_messages
    );
    (void)this->_ifstream_copy_acq_status_messages();

    if (temp == CODEZ::_0_no_errors)
    {
        return true;
    }
    else
    {
        return false;
    }
}


////////~~~~~~~~END>  rsa306b_iqblk_user.cpp
