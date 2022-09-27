/*
    API group "IFSTREAM", user funcitons

    public :
        < 1 >  ifstream_write_csv_equalization()

    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    write a csv file after getting the equalization parameters
    the equalization parameters are populated automatically, call "get_everything()" to be sure
    file_path_name must be allocated, even if it is on NULL
        that is how the output file is tracked
        output file either uses provided name, or default (if NULL)
    
    these can be used to smooth acquired data
*/
CODEZ rsa306b_class::ifstream_write_csv_equalization
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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

    std::size_t v_size_freq  = this->_vars.ifstream.eq_frequency_v.size();
    std::size_t v_size_ampl  = this->_vars.ifstream.eq_amplitude_v.size();
    std::size_t v_size_phase = this->_vars.ifstream.eq_phase_v.size();

    if 
    ( 
        ((v_size_freq < 1LU) | (v_size_ampl < 1LU) | (v_size_phase < 1LU)) ||
        (v_size_freq != v_size_ampl)                                       ||
        (v_size_freq != v_size_phase)   
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "ifstream.eq_*_v.size() =  %lu  %lu  %lu", 
            v_size_freq,
            v_size_ampl,
            v_size_phase);
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
            IFSTREAM_FILE_NAME_BASE,
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
    
    (void)sprintf(this->_helper, "frequency, amplitude, phase\n");
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size_freq; idx++)
    {
        if (idx == v_size_freq-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%f,%f,%f\n", 
                this->_vars.ifstream.eq_frequency_v[idx],
                this->_vars.ifstream.eq_amplitude_v[idx],
                this->_vars.ifstream.eq_phase_v[idx]);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%f,%f,%f,\n", 
                this->_vars.ifstream.eq_frequency_v[idx],
                this->_vars.ifstream.eq_amplitude_v[idx],
                this->_vars.ifstream.eq_phase_v[idx]);
        }
        (void)fputs(this->_helper, this->_fp_write);
    }

    (void)fclose(this->_fp_write);
    this->_fp_write = NULL;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_write_csv_equalization.cpp
