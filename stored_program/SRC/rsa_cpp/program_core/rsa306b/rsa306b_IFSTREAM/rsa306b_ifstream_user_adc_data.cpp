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
    - ifstream settings are correctly applied

    IFSTREAM_SetEnable() is only for files ?
*/
CODEZ rsa306b_class::ifstream_acquire_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    int16_t* sample_getter = NULL;                   // pointer to acquire the data
    (void)this->_ifstream_get_buffer_size();         // find out how much memory to allocate
    if 
    (
        this->cutil.h_new_int16_d1                   // allocate the memory, and verify the allocation
        (
            sample_getter,
            this->_vars.ifstream.buffer_samples    
        ) != CODEZ::_0_no_errors
    )
    {
        return this->cutil.get_status_code();        // allocation failed, acquisition is not possible
    }

    RSA_API::ReturnStatus temp = 
        RSA_API::IFSTREAM_GetIFData                  // acquire the data
        (
            sample_getter,
            &this->_vars.ifstream.if_data_length,
            &this->_vars.ifstream.data_info_type
        );
    
    (void)this->cutil.h_copy_int16_to_vector_d1      // copy the acquired data into std::vector for processing
    (
        sample_getter, 
        this->_vars.ifstream.if_data_length, 
        this->_vars.ifstream.adc_data_v
    );

    (void)this->cutil.h_delete_int16_d1              // deallocate the memory
    (
        sample_getter
    );

    (void)this->_ifstream_copy_adc_data_v();          // update the user's variables
    (void)this->_ifstream_copy_if_data_length();
    (void)this->_ifstream_copy_data_info_type();


#ifdef SAFETY_CHECKS
    if (this->_vars.ifstream.buffer_samples                    != 
        static_cast<int>(this->_vars.ifstream.adc_data_v.size()))
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "expected:  %d  ,  received:  %d",
                this->_vars.ifstream.buffer_samples,
                this->_vars.ifstream.if_data_length);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }

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

#endif
    
#ifdef DEBUG_MAX
    (void)snprintf(X_ddts, sizeof(X_ddts), "vars.ifstream.adc_data_v loaded with %lu of %dsamples",
        this->_vars.ifstream.adc_data_v.size(),
        this->_vars.ifstream.if_data_length);
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
    debug_record(true);
#endif

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
    (void)this->_ifstream_copy_acq_status_message();

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
    must have successfully called "ifstream_acquire_adc_data"
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
    
    if (file_path_name == NULL)
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

    if (this->cutil.exe_fopen(this->_helper, "w", this->_fp_write) != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }
    
    (void)sprintf(this->_helper, "%s,%s,\n",
        IFSTREAM_FIELD_1,
        IFSTREAM_FIELD_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t idx = 0; idx < v_size; idx++)
    {
        if (idx == v_size-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d\n", 
                idx,
                this->_vars.ifstream.adc_data_v[idx]);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d,\n", 
                idx,
                this->_vars.ifstream.adc_data_v[idx]);
        }
        (void)fputs(this->_helper, this->_fp_write);
    }

    return this->cutil.exe_fclose(this->_fp_write);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_acquire_adc_data.cpp
