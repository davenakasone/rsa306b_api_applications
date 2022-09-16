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
CODEZ rsa306b_class::print_ifstream()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'IFSTREAM' group >>>\n");
    (void)printf("\tfile_name_suffix                          :  %d  ", this->_vars.ifstream.file_name_suffix);
    switch (this->_vars.ifstream.file_name_suffix)
    {
        case (RSA_API::IFSSDFN_SUFFIX_NONE)          : (void)printf("{none}\n");                break;
        case (RSA_API::IFSSDFN_SUFFIX_TIMESTAMP)     : (void)printf("{timestamp included}\n");  break;
        case (RSA_API::IFSSDFN_SUFFIX_INCRINDEX_MIN) : (void)printf("{minimal, auto-index}\n"); break;
        default                                      : (void)printf("{! UNKNOWN !}\n");         break;
    }
    (void)printf("\tfile_path                                 :  %s\n", this->_vars.ifstream.file_path);
    (void)printf("\tfile_base_name                            :  %s\n", this->_vars.ifstream.file_name_base);
    (void)printf("\tfile_length_ms                            :  %d\n", this->_vars.ifstream.file_length_ms);
    (void)printf("\tfile_count                                :  %d\n", this->_vars.ifstream.file_count);
    (void)printf("\toutput_configuration_select               :  %d  ", this->_vars.ifstream.output_configuration_select);
    switch (this->_vars.ifstream.output_configuration_select)
    {
        case (RSA_API::IFSOD_CLIENT)         : (void)printf("{output direct to client, no file written}\n");                   break;
        case (RSA_API::IFSOD_FILE_R3F)       : (void)printf("{R3F file output}\n");                                            break;
        case (RSA_API::IFSOD_FILE_R3HA_DET)  : (void)printf("{R3H+R3A file output}\n");                                        break;
        case (RSA_API::IFSOD_FILE_MIDAS)     : (void)printf("{Midas CDIF file output, combined header+data file}\n");          break;
        case (RSA_API::IFSOD_FILE_MIDAS_DET) : (void)printf("{Midas CDIF+DET file output, separate header and data files}\n"); break;
        default                              : (void)printf("{! UNKNOWN !}\n");                                                break;
    }
    (void)printf("\tis_enabled_ADC                            :  %d\n" , this->_vars.ifstream.is_enabled_adc);
	(void)printf("\tis_active_streaming                       :  %d\n" , this->_vars.ifstream.is_active);	
    (void)printf("\tif_stream_data_length                     :  %d\n" , this->_vars.ifstream.if_data_length);
    (void)printf("\tdata_info_type, 'acqStatus'               :  %u\n" , this->_vars.ifstream.data_info_type.acqStatus);
    (void)printf("\tdata_info_type, 'timestamp'               :  %ld\n", this->_vars.ifstream.data_info_type.timestamp);
    (void)printf("\tdata_info_type, 'triggerCount'            :  %d\n" , this->_vars.ifstream.data_info_type.triggerCount);
    (void)printf("\tdata_info_type, 'triggerIndices' address  :  %p\n" , this->_vars.ifstream.data_info_type.triggerIndices);
    (void)printf("\tadc_data_v[0]                             :  %d\n" , this->_vars.ifstream.adc_data_v[0]);
    (void)printf("\tframe_bytes                               :  %d\n" , this->_vars.ifstream.frame_bytes);
    (void)printf("\tnumber_of_frames                          :  %d\n" , this->_vars.ifstream.number_of_frames);
    (void)printf("\tframed_adc_data_v[0][0]                   :  %u\n" , this->_vars.ifstream.framed_adc_data_v[0][0]);
    (void)printf("\tbuffer_size_bytes                         :  %d\n" , this->_vars.ifstream.buffer_size_bytes);
    (void)printf("\tnumber_of_samples                         :  %d\n" , this->_vars.ifstream.number_of_samples);
    (void)printf("\tpoints_in_equalization_buffer             :  %d\n" , this->_vars.ifstream.points_in_equalization_buffer);
    (void)printf("\teq_frequency_v[0]                         :  %f\n" , this->_vars.ifstream.eq_frequency_v[0]);
    (void)printf("\teq_amplitude_v[0]                         :  %f\n" , this->_vars.ifstream.eq_amplitude_v[0]);
    (void)printf("\teq_phase_v[0]                             :  %f\n" , this->_vars.ifstream.eq_phase_v[0]);
    (void)printf("\tscale_factor                              :  %lf\n", this->_vars.ifstream.scale_factor);
    (void)printf("\tscale_frequency                           :  %lf\n", this->_vars.ifstream.scale_frequency);
    (void)printf("\tif_bandwidth_hz                           :  %lf\n", this->_vars.ifstream.if_bandwidth_hz);
    (void)printf("\tsamples_per_second                        :  %lf\n", this->_vars.ifstream.samples_per_second);
    (void)printf("\tif_center_frequency                       :  %lf\n", this->_vars.ifstream.if_center_frequency); 
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_ifstream_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

// variables for IF stream managment
    this->_vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
    this->_vars.ifstream.is_enabled_adc              = false;
    this->_vars.ifstream.is_active                   = false;

// variables for output file handling
    (void)strcpy(this->_vars.ifstream.file_path     , DATA_DIRECTORY_RAW);
    (void)strcpy(this->_vars.ifstream.file_name_base, this->constants.IFSTREAM_FILE_NAME_BASE);
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
