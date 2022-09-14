/*
    API group "IFSTREAM"

    public :
        < 1 >  print_ifstream()
    
    private :
        < 1 >  _ifstream_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::print_ifstream()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    printf("\n'IFSTREAM' group >>>\n");
    printf("\tfile_name_suffix                          :  %d  ", this->_vars.ifstream.file_name_suffix);
    switch (this->_vars.ifstream.file_name_suffix)
    {
        case (RSA_API::IFSSDFN_SUFFIX_NONE)          : printf("{none}\n");                break;
        case (RSA_API::IFSSDFN_SUFFIX_TIMESTAMP)     : printf("{timestamp included}\n");  break;
        case (RSA_API::IFSSDFN_SUFFIX_INCRINDEX_MIN) : printf("{minimal, auto-index}\n"); break;
        default                                      : printf("{! UNKNOWN !}\n");         break;
    }
    printf("\tfile_path                                 :  %s\n", this->_vars.ifstream.file_path);
    printf("\tfile_base_name                            :  %s\n", this->_vars.ifstream.file_name_base);
    printf("\tfile_length_ms                            :  %d\n", this->_vars.ifstream.file_length_ms);
    printf("\tfile_count                                :  %d\n", this->_vars.ifstream.file_count);
    printf("\toutput_configuration_select               :  %d  ", this->_vars.ifstream.output_configuration_select);
    switch (this->_vars.ifstream.output_configuration_select)
    {
        case (RSA_API::IFSOD_CLIENT)         : printf("{output direct to client, no file written}\n");                   break;
        case (RSA_API::IFSOD_FILE_R3F)       : printf("{R3F file output}\n");                                            break;
        case (RSA_API::IFSOD_FILE_R3HA_DET)  : printf("{R3H+R3A file output}\n");                                        break;
        case (RSA_API::IFSOD_FILE_MIDAS)     : printf("{Midas CDIF file output, combined header+data file}\n");          break;
        case (RSA_API::IFSOD_FILE_MIDAS_DET) : printf("{Midas CDIF+DET file output, separate header and data files}\n"); break;
        default                              : printf("{! UNKNOWN !}\n");                                                break;
    }
    printf("\tis_enabled_ADC                            :  %d\n" , this->_vars.ifstream.is_enabled_adc);
	printf("\tis_active_streaming                       :  %d\n" , this->_vars.ifstream.is_active);	
    printf("\tif_stream_data_length                     :  %d\n" , this->_vars.ifstream.if_data_length);
    printf("\tdata_info_type, 'acqStatus'               :  %u\n" , this->_vars.ifstream.data_info_type.acqStatus);
    printf("\tdata_info_type, 'timestamp'               :  %ld\n", this->_vars.ifstream.data_info_type.timestamp);
    printf("\tdata_info_type, 'triggerCount'            :  %d\n" , this->_vars.ifstream.data_info_type.triggerCount);
    printf("\tdata_info_type, 'triggerIndices' address  :  %p\n" , this->_vars.ifstream.data_info_type.triggerIndices);
    printf("\tadc_data_v[0]                             :  %d\n" , this->_vars.ifstream.adc_data_v[0]);
    printf("\tframe_bytes                               :  %d\n" , this->_vars.ifstream.frame_bytes);
    printf("\tnumber_of_frames                          :  %d\n" , this->_vars.ifstream.number_of_frames);
    printf("\tframed_adc_data_v[0][0]                   :  %u\n" , this->_vars.ifstream.framed_adc_data_v[0][0]);
    printf("\tbuffer_size_bytes                         :  %d\n" , this->_vars.ifstream.buffer_size_bytes);
    printf("\tnumber_of_samples                         :  %d\n" , this->_vars.ifstream.number_of_samples);
    printf("\tpoints_in_equalization_buffer             :  %d\n" , this->_vars.ifstream.points_in_equalization_buffer);
    printf("\teq_frequency_v[0]                         :  %f\n" , this->_vars.ifstream.eq_frequency_v[0]);
    printf("\teq_amplitude_v[0]                         :  %f\n" , this->_vars.ifstream.eq_amplitude_v[0]);
    printf("\teq_phase_v[0]                             :  %f\n" , this->_vars.ifstream.eq_phase_v[0]);
    printf("\tscale_factor                              :  %lf\n", this->_vars.ifstream.scale_factor);
    printf("\tscale_frequency                           :  %lf\n", this->_vars.ifstream.scale_frequency);
    printf("\tif_bandwidth_hz                           :  %lf\n", this->_vars.ifstream.if_bandwidth_hz);
    printf("\tsamples_per_second                        :  %lf\n", this->_vars.ifstream.samples_per_second);
    printf("\tif_center_frequency                       :  %lf\n", this->_vars.ifstream.if_center_frequency); 
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_ifstream_init()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

// variables for IF stream managment
    this->_vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
    this->_vars.ifstream.is_enabled_adc              = false;
    this->_vars.ifstream.is_active                   = false;

// variables for output file handling
    strcpy(this->_vars.ifstream.file_path     , DATA_DIRECTORY_RAW);
    strcpy(this->_vars.ifstream.file_name_base, this->constants.IFSTREAM_FILE_NAME_BASE);
    this->_vars.ifstream.file_name_suffix = this->constants.IFSTREAM_SUFFIX;
    this->_vars.ifstream.file_length_ms   = this->constants.IFSTREAM_DEFAULT_MS;
    this->_vars.ifstream.file_count       = this->constants.IFSTREAM_DEFAULT_FILE_COUNT;

// variables for acquiring IF stream directly
    this->_vars.ifstream.if_data_length                = INIT_INT;
    this->_vars.ifstream.data_info_type.acqStatus      = INIT_UINT;
    this->_vars.ifstream.data_info_type.timestamp      = INIT_UINT;
    this->_vars.ifstream.data_info_type.triggerCount   = INIT_INT;
    this->_vars.ifstream.data_info_type.triggerIndices = NULL;
    this->_vars.ifstream.adc_data_v.resize(this->constants.SAMPLES_IN_BUFFER);

    this->_vars.ifstream.frame_bytes      = INIT_INT;
    this->_vars.ifstream.number_of_frames = INIT_INT;
    this->_vars.ifstream.framed_adc_data_v.resize(this->constants.FRAMES_IN_BUFFER);
    for (size_t ii = 0; ii < this->constants.FRAMES_IN_BUFFER; ii++)
    {
        this->_vars.ifstream.framed_adc_data_v[ii].resize(
            this->constants.ADC_SAMPLES_PER_FRAME, INIT_UINT);
    }
    
    this->_vars.ifstream.buffer_size_bytes             = INIT_INT;
    this->_vars.ifstream.number_of_samples             = INIT_INT;
    this->_vars.ifstream.points_in_equalization_buffer = INIT_INT;

    this->_vars.ifstream.eq_frequency_v.resize(this->constants.CORRECTION_POINTS, INIT_FLOAT);
    this->_vars.ifstream.eq_amplitude_v.resize(this->constants.CORRECTION_POINTS, INIT_FLOAT);
    this->_vars.ifstream.eq_phase_v.resize(this->constants.CORRECTION_POINTS    , INIT_FLOAT);
    
    this->_vars.ifstream.scale_factor        = INIT_DOUBLE;
    this->_vars.ifstream.scale_frequency     = INIT_DOUBLE;
    this->_vars.ifstream.if_bandwidth_hz     = INIT_DOUBLE;
    this->_vars.ifstream.samples_per_second  = INIT_DOUBLE;
    this->_vars.ifstream.if_center_frequency = INIT_DOUBLE;

    this->_ifstream_copy_vars();
}


////////~~~~~~~~END>  rsa306b_ifstream_print_init.cpp
