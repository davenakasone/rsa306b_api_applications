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
void rsa306b_class::ifstream_set_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_ifstream_set_vars();
}


////~~~~


/*
    < 2 > public
    produces "*.r3f" file
    user already set correct settings (or is using default)
*/
void rsa306b_class::ifstream_record_file()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    if (this->_vars.ifstream.output_configuration_select != 
        RSA_API::IFSOD_FILE_R3F                           )
    {
        #ifdef DEBUG_MIN
            printf("\n\tbad output configuration\n");
        #endif
        return;
    }
    this->_vars.ifstream.is_active = true;
    this->_ifstream_copy_is_active();
    this->device_run();
    this->vars.ifstream.is_enabled_adc = true;
    this->_ifstream_set_is_enabled_adc();

    while(this->_vars.ifstream.is_active == true)
    {
        this->_ifstream_get_is_active();
    }

    this->vars.ifstream.is_enabled_adc = false;
    this->_ifstream_set_is_enabled_adc();
    this->device_stop();

    #ifdef DEBUG_MIN
        printf("\n\trecording complete, check:  %s%s*\n", 
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
void rsa306b_class::ifstream_acquire_adc_data()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif 

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
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
            printf("\n\tfailure allocating '%s'\n", GET_NAME(data_getter));
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
void rsa306b_class::ifstream_acquire_adc_frames()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif 

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
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
    long unsigned int placer = 0;
    this->_vars.ifstream.framed_adc_data_v.resize(this->_vars.ifstream.number_of_frames);
    for (int ii = 0; ii < this->_vars.ifstream.number_of_frames; ii++)
    {
        this->_vars.ifstream.framed_adc_data_v[ii].resize(
            this->_vars.constants.ADC_SAMPLES_PER_FRAME);
        for (int jj = 0; jj < bytes_per_frame; jj++)
        {
            this->_vars.ifstream.framed_adc_data_v[ii][placer] = 
                (int16_t)((frame_data[ii*jj + jj] << 8) | (frame_data[ii*jj + jj + 1] << 0));
            placer++;
            if (placer == this->_vars.constants.ADC_SAMPLES_PER_FRAME -1) 
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
