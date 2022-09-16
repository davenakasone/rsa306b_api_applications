/*
    API group "IFSTREAM", user funcitons

    public :
        < 1 >  ifstream_set_vars()
        < 2 >  ifstream_record_file()
        < 3 >  ifstream_acquire_adc_data()
        < 4 >  ifstream_acquire_adc_frames()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::ifstream_set_vars()
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
    this->_ifstream_set_vars();
}


////~~~~


/*
    < 2 > public
    produces "*.r3f" file
    user already set correct settings (or is using default)
*/
CODEZ rsa306b_class::ifstream_record_file()
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
    if (this->_vars.ifstream.output_configuration_select != 
        RSA_API::IFSOD_FILE_R3F                           )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "must be *.r3f files type");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    this->_vars.ifstream.is_active = true;
    this->_ifstream_copy_is_active();
    this->device_run();
    this->vars.ifstream.is_enabled_adc = true;
    this->_ifstream_set_is_enabled_adc();

    // while(this->_vars.ifstream.is_active == true)   ....you need a split timer to break out...
    // {
    //     this->_ifstream_get_is_active();
    // }
    bool is_active = true;
    while(is_active == true)
    {
        this->_vars.gp.api_status = 
            RSA_API::IFSTREAM_GetActiveStatus(&is_active);
    }
    

    this->vars.ifstream.is_enabled_adc = false;
    this->_ifstream_set_is_enabled_adc();
    this->_ifstream_get_is_active();
    this->device_stop();

    #ifdef DEBUG_MAX
        (void)printf("\n\trecording complete, check:  %s%s*\n", 
            this->_vars.ifstream.file_path, 
            this->_vars.ifstream.file_name_base);
    #endif
}


////~~~~


/*
    < 3 > public
    "RSA_API::IFSTREAM_GetIFDataBufferSize()" + "RSA_API::IFSTREAM_GetIFData()"
    user initiates direct data acquisition, no files are generated
    "vars.ifstream.adc_data_v" is populated with the entire raw ADC buffer
    see "vars.ifstream.if_data_length" and "vars.ifstream.data_info_type"
        for additional output
*/
CODEZ rsa306b_class::ifstream_acquire_adc_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
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
    this->device_run();
    this->vars.ifstream.is_enabled_adc = true;
    this->_ifstream_set_is_enabled_adc();
    this->_ifstream_get_buffer_size();
            
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
    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetIFData(
            data_getter, 
            &this->_vars.ifstream.if_data_length, 
            &this->_vars.ifstream.data_info_type);
    this->_gp_confirm_api_status();

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


////~~~~


/*
    < 4 > public
    "RSA_API::IFSTREAM_GetIFFrames()"
    user initiates direct data acquisition, no files are generated
    "vars.ifstream.framed_adc_data_v" is populated with the entire raw ADC buffer
        orgainzed by frame
    see "vars.ifstream.if_data_length" and "vars.ifstream.data_info_type"
        for additional output
*/
CODEZ rsa306b_class::ifstream_acquire_adc_frames()
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
    uint8_t* frame_data = NULL;
    this->device_run();
    this->vars.ifstream.is_enabled_adc = true;
    this->_ifstream_set_is_enabled_adc();

    this->_vars.gp.api_status = 
        RSA_API::IFSTREAM_GetIFFrames(
            &frame_data, 
            &this->_vars.ifstream.frame_bytes, 
            &this->_vars.ifstream.number_of_frames);
    this->_gp_confirm_api_status();

    int bytes_per_frame = 
        this->_vars.ifstream.frame_bytes / this->_vars.ifstream.number_of_frames;
    std::size_t placer = 0;
    this->_vars.ifstream.framed_adc_data_v.resize(this->_vars.ifstream.number_of_frames);
    for (int ii = 0; ii < this->_vars.ifstream.number_of_frames; ii++)
    {
        this->_vars.ifstream.framed_adc_data_v[ii].resize(
            this->constants.ADC_SAMPLES_PER_FRAME);
        for (int jj = 0; jj < bytes_per_frame; jj++)
        {
            this->_vars.ifstream.framed_adc_data_v[ii][placer] = 
                (int16_t)((frame_data[ii*jj + jj] << 8) | (frame_data[ii*jj + jj + 1] << 0));
            placer++;
            if (placer == this->constants.ADC_SAMPLES_PER_FRAME -1) 
            {
                placer = 0;
                break;
            }
        }
    }
    this->vars.ifstream.is_enabled_adc = false;
    this->_ifstream_set_is_enabled_adc();
    this->device_stop();
    this->_ifstream_copy_if_frames();
    frame_data = NULL;
}


////////~~~~~~~~END>  rsa306b_ifstream_user1.cpp
