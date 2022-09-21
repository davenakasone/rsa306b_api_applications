/*
    API group "IFSTREAM", user funcitons
    speed is sacrified for safety

    public :
        < 1 >  ifstream_acquire_adc_data()
    
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

*/
CODEZ rsa306b_class::ifstream_acquire_adc_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    int16_t* sample_getter = NULL;
    (void)this->_ifstream_get_buffer_size();
    if 
    (
        this->cutil.h_new_int16_d1
        (
            sample_getter,
            this->_vars.ifstream.buffer_samples
        ) != CODEZ::_0_no_errors
    )
    {
        return this->cutil.get_status_code();    // allocation failed
    }

    RSA_API::ReturnStatus temp = 
        RSA_API::IFSTREAM_GetIFData
        (
            sample_getter,
            &this->_vars.ifstream.if_data_length,
            &this->_vars.ifstream.data_info_type
        );
    
    (void)this->cutil.h_copy_int16_to_vector_d1(
        sample_getter, 
        this->_vars.ifstream.if_data_length, 
        this->_vars.ifstream.adc_data_v);

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
        (void)this->cutil.h_delete_int16_d1(sample_getter);
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }

    this->_vars.ifstream.adc_triggers_v.assign(this->vars.ifstream.adc_data_v.size(), false);
    for (int ii = 0; ii < this->_vars.ifstream.data_info_type.triggerCount; ii++)
    {
        if (this->_vars.ifstream.data_info_type.triggerIndices[ii] == true)
        {
            this->_vars.ifstream.adc_triggers_v
                [this->_vars.ifstream.data_info_type.triggerIndices[ii]] = true;
        }
    }
    this->_ifstream_copy_adc_data_v();
    this->_ifstream_copy_adc_tiggers_v();
    // check acqstatus


    #ifdef DEBUG_MAX
        (void)snprintf(X_ddts, sizeof(X_ddts), "vars.ifstream.adc_data_v loaded with %d samples",
            this->_vars.ifstream.if_data_length);
        (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(true);
    #endif

    return this->cutil.report_status_code(CODEZ::_0_no_errors);









   









    
            
    int16_t* data_getter = 
        new int16_t[this->_vars.ifstream.number_of_samples];
    if (!data_getter)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "dynamic allocation failed");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        this->vars.ifstream.is_enabled_adc = false;
        this->_ifstream_set_is_enabled_adc();
        this->device_stop();
        return;
    }
    this->_api_status = 
        RSA_API::IFSTREAM_GetIFData(
            data_getter, 
            &this->_vars.ifstream.if_data_length, 
            &this->_vars.ifstream.data_info_type);
    this->_report_api_status();

    this->_vars.ifstream.adc_data_v.resize(this->_vars.ifstream.if_data_length);
    for (int ii = 0; ii < this->_vars.ifstream.if_data_length; ii++)
    {
        this->_vars.ifstream.adc_data_v[ii] = data_getter[ii];
    }
    this->vars.ifstream.is_enabled_adc = false;
    this->_ifstream_set_is_enabled_adc();
    this->device_stop();
    this->_ifstream_copy_if_data();
    delete[] data_getter; data_getter = NULL;
}


////////~~~~~~~~END>  rsa306b_ifstream_user_acquire_adc_data.cpp
