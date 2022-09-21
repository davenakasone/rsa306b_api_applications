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
    print "AUDIO" group variables to stdout
    ...must allocate the string, it will have the return path
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

    std::size_t v_size = this->_vars.audio.data_v.size();

    if (v_size < 1)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "audio.data_v.size() =  %lu", v_size);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    
    if (file_path_name == NULL)
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_%lu_%s",
            DATA_DIRECTORY_PROCESSED,
            AUDIO_FILE_NAME_BASE,
            this->_vars.reftime.current.timestamp,
            AUDIO_OUTPUT_EXTENSTION);
        (void)sprintf(file_path_name, "%s", this->_helper);
    }
    else
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s", file_path_name);
    }

    if (this->cutil.exe_fopen(this->_helper, "w", this->_fp_write) != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }
    
    (void)sprintf(this->_helper, "audio,\n");
    (void)fputs(this->_helper, this->_fp_write);

    for (size_t idx = 0; idx < v_size; idx++)
    {
        if (idx == v_size-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%d\n", this->_vars.audio.data_v[idx]);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%d,\n", this->_vars.audio.data_v[idx]);
        }
        (void)fputs(this->_helper, this->_fp_write);
    }

    return this->cutil.exe_fclose(this->_fp_write);
}


////////~~~~~~~~END>  rsa306b_write_csv.cpp    
