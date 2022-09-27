/*
    API group "AUDIO"

    public :
        < 1 >  audio_write_csv()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    write a csv file after audio acquisition
    must have successfully called "audio_acquire_data()"
    be sure the file_path_name is allocated, even if it is on NULL
        that is how the output file is tracked
        output file either uses provided name, or default (if NULL)
*/
CODEZ rsa306b_class::audio_write_csv
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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
    
    std::size_t v_size = this->_vars.audio.data_v.size();

    if (v_size < 1LU)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "audio.data_v.size() =  %lu", v_size);
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
            AUDIO_FILE_NAME_BASE,
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
    
    (void)sprintf(this->_helper, "%s,%s,\n",
        AUDIO_FIELD_1,
        AUDIO_FIELD_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size; idx++)
    {
        if (idx == v_size-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d\n", 
                idx,
                this->_vars.audio.data_v[idx]);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d,\n", 
                idx,
                this->_vars.audio.data_v[idx]);
        }
        (void)fputs(this->_helper, this->_fp_write);
    }

    fclose(this->_fp_write);
    this->_fp_write = NULL;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_write_csv.cpp    
