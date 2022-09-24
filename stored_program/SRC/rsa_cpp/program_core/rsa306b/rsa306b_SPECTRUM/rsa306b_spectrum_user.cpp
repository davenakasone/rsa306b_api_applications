/*
    API group "SPECTRUM"

    public :
        < 1 >  spectrum_aquire_data()
        < 2 >  spectrum_write_csv()

*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    user has already:
        connected the device
        called 'device_run()'
        called 'spectrum_set_vars()
            - is_enabled_measurement == true, trace at 'trace_number' is enabled
            - settings are as desired (center frequency, reference level, ect)
    
    call as many times as desired, 'trace_power_v' is overwritten each call
    so find peak index, write the csv, and process before the next call

    made to quickly get trace[trace_number]
    keep trace numbers {0, 1, 2}
    good to call after:
        spectrum_make_frequency_v ()
        spectrum_find_peak_index  (file_path_name, trace_number)
        spectrum_write_csv        (trace_number)
*/
CODEZ rsa306b_class::spectrum_acquire_data
(
    int trace_number
)
{
// no safety, no checking, but enforce if needed

    (void)this->set_api_status(RSA_API::SPECTRUM_AcquireTrace());     // notify device to start acquisition

    float* data    = NULL;
    bool is_ready  = false;
    int timeout_ms = 0;

    (void)this->cutil.h_new_float_d1(data, this->_vars.spectrum.settings_type.traceLength);    // allocate data getter
    
    while (is_ready == false)
    {
        (void)RSA_API::SPECTRUM_WaitForTraceReady(timeout_ms, &is_ready);    // block until data is ready for acquisition
    }

    RSA_API::ReturnStatus temp = 
        RSA_API::SPECTRUM_GetTrace    // data is acquired
        (
            this->_vars.spectrum.trace_select[trace_number], 
            this->_vars.spectrum.settings_type.traceLength, 
            data, 
            &this->_vars.spectrum.trace_points_acquired[0]
        );

    (void)this->cutil.h_copy_float_to_vector_d1
        (
            data, 
            this->_vars.spectrum.trace_points_acquired[trace_number], 
            this->_vars.spectrum.trace_power_v[trace_number]
        );
    (void)this->cutil.h_delete_float_d1(data);
    (void)this->_spectrum_copy_trace_power_v(trace_number);
    (void)this->_spectrum_copy_trace_points_acquired(trace_number);
    (void)this->_spectrum_get_trace_info_type(trace_number);    // user should do a bitcheck on this result
    
    return this->set_api_status(temp);
}


////~~~~


/*
    < 2 > public
    does not nead a connected device, 
    just writes arrays to file as is
    might want to allow user to select a file-path-name and trace?
*/
CODEZ rsa306b_class::spectrum_write_csv
(
    char* file_path_name,
    int trace_number
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

    std::size_t v_size_frequency = this->_vars.spectrum.frequency_v.size();
    std::size_t v_size_power     = this->_vars.spectrum.trace_power_v[trace_number].size();
    if 
    (
        (v_size_frequency < 1LU) ||
        (v_size_power < 1LU)     ||
        (v_size_frequency != v_size_power)
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "freq_v.size() =  %lu  ,  pow_v.size() =  %lu", 
            v_size_frequency,
            v_size_power);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    
    if (file_path_name[0] == '\0')    // using default output file_path_name
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_%d__%lu_%s",
            DATA_DIRECTORY_PROCESSED,
            SPECTRUM_FILE_NAME_BASE,
            trace_number,
            this->_vars.reftime.current.timestamp,
            DATA_OUTPUT_EXTENSTION);
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
    
    (void)sprintf(this->_helper, "%s,%s,\n",
        SPECTRUM_FIELD_1,
        SPECTRUM_FIELD_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size_frequency; idx++)
    {
        if (idx == v_size_frequency-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lf,%f\n",
                this->_vars.spectrum.frequency_v[idx],
                this->_vars.spectrum.trace_power_v[trace_number][idx]);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lf,%f,\n",
                this->_vars.spectrum.frequency_v[idx],
                this->_vars.spectrum.trace_power_v[trace_number][idx]);
        }
        (void)fputs(this->_helper, this->_fp_write);
    }

    return this->cutil.exe_fclose(this->_fp_write);
}


////////~~~~~~~~END>  rsa306b_spectrum_user.cpp
