/*
    API group "IFSTREAM", user funcitons
    speed can be sacrificed for safety by disabling "SAFETY_CHECKS"

    public :
        < 1 >  ifstream_acquire_data()
        < 2 >  ifstream_bitcheck()
        < 3 >  ifstream_write_csv_data()

    private :
        #  none
*/

#include "../rsa306b_class.h"

/*
    < 1 > public
    populates "vars.ifstream.adc_data_v", std::vector
    user can make a csv when done or conduct what ever processing is desired
    equalization and scaling parameters are already available if procedure was followed

    0) user updated the public "vars.ifstream.*", ensuring "vars.ifstream.output_destination_select == RSA_API::IFSOD_CLIENT"
    1) user called "ifstream_set_vars()"  // successfully 
    2) user called "device_run()"         // must be called for first iteration
    3) user calls this function for as many acquisitions as desired (the vector is over-wrtiten every call)
    4) user calls "device_stop()" when done, unless another type of acquisition is desired

    all the guards are ommitted, at a minimum:
    - the device is connected
    - the device is running
    - ifstream settings are correctly applied (IFSTREAM was enabled)

    IFSTREAM_SetEnable() is only for files ?
*/
CODEZ rsa306b_class::ifstream_acquire_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    (void)this->_ifstream_get_buffer_size();
    this->vars.ifstream.is_enabled = true;
    (void)this->_ifstream_set_is_enabled();

    int16_t* sample_getter = NULL;
    try
    {
        sample_getter = new int16_t[this->_vars.ifstream.buffer_samples];
    }
    catch(...)
    {
        return this->cutil.report_status_code(CODEZ::_22_dynamic_allocation_failed);
    }

    RSA_API::ReturnStatus temp = 
        RSA_API::IFSTREAM_GetIFData                  // acquire the data
        (
            sample_getter,
            &this->_vars.ifstream.if_data_length,
            &this->_vars.ifstream.data_info_type
        );
    
    this->_vars.ifstream.adc_data_v.assign(sample_getter, sample_getter + this->_vars.ifstream.if_data_length);
    delete [] sample_getter;
    sample_getter = NULL;

    if 
    (
        this->_vars.ifstream.buffer_samples                  != 
        static_cast<int>(this->_vars.ifstream.adc_data_v.size())
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "expected:  %d  ,  received:  %d",
                this->_vars.ifstream.buffer_samples,
                this->_vars.ifstream.if_data_length);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        this->vars.ifstream.is_enabled = false;
        (void)this->_ifstream_set_is_enabled();
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    (void)this->_ifstream_copy_adc_data_v();          // update the user's variables
    (void)this->_ifstream_copy_if_data_length();
    (void)this->_ifstream_copy_data_info_type();
    this->vars.ifstream.is_enabled = false;
    (void)this->_ifstream_set_is_enabled();
    (void)this->ifstream_good_bitcheck();
    this->_vars.ifstream.adc_triggers_v.assign(this->vars.ifstream.adc_data_v.size(), false);
    for (int ii = 0; ii < this->_vars.ifstream.data_info_type.triggerCount; ii++)
    {
        this->_vars.ifstream.adc_triggers_v
        [
            static_cast<std::size_t>
            (
                this->_vars.ifstream.data_info_type.triggerIndices[ii]
            )
        ] = true;
    }
    this->_ifstream_copy_adc_tiggers_v();

    return this->set_api_status(temp);    // good acquisition, but see bitcheck result
}


////~~~~


/*
    < 2 > public
    updates 'vars.ifstream.acq_status_message'
    checks 'vars.data.ifstream.data_info_type.acqStatus'
    good to call after every acquisition if there is time
*/
bool rsa306b_class::ifstream_good_bitcheck()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    CODEZ temp = 
        this->cutil.ifstream_acq_status
        (
            this->_vars.ifstream.data_info_type.acqStatus, 
            this->_vars.ifstream.valid_bitmask,
            this->_vars.ifstream.acq_status_messages
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


////~~~~


/*
    < 3 > public
    write a csv file after standard acquisition
    can't write framed acquisition
    must have successfully called "ifstream_acquire_data()"
    be sure the file_path_name is allocated, even if it is on NULL
        that is how the output file is tracked
        output file either uses provided name, or default (if NULL)
*/
CODEZ rsa306b_class::ifstream_write_csv_data
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

    std::size_t v_size = this->_vars.ifstream.adc_data_v.size();

    if (v_size < 1LU)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "ifstream.adc_data_v.size() =  %lu", v_size);
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
    
    (void)sprintf(this->_helper, "%s,%s\n",
        IFSTREAM_FIELD_1,
        IFSTREAM_FIELD_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size; idx++)
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%0.9lf,%d\n", 
            static_cast<double>(idx) / this->_vars.ifstream.samples_per_second,
            this->_vars.ifstream.adc_data_v[idx]);
        (void)fputs(this->_helper, this->_fp_write);
    }

    (void)fclose(this->_fp_write);
    this->_fp_write = NULL;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_acquire_adc_data.cpp
