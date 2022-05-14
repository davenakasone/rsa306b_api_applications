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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
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
    printf("\tis_enabled_ADC                            :  %d\n", this->_vars.ifstream.is_enabled_adc);
	printf("\tis_active_streaming                       :  %d\n", this->_vars.ifstream.is_active);	
    printf("\tif_stream_data_length                     :  %d\n", this->_vars.ifstream.if_data_length);
    printf("\tdata_info_type, 'acqStatus'               :  %u\n", this->_vars.ifstream.data_info_type.acqStatus);
    printf("\tdata_info_type, 'timestamp'               :  %ld\n", this->_vars.ifstream.data_info_type.timestamp);
    printf("\tdata_info_type, 'triggerCount'            :  %d\n",this->_vars.ifstream.data_info_type.triggerCount);
    printf("\tdata_info_type, 'triggerIndices' address  :  %p\n", this->_vars.ifstream.data_info_type.triggerIndices);
    printf("\tadc_data_v[0]                             :  %d\n", this->_vars.ifstream.adc_data_v[0]);
    printf("\tframe_bytes                               :  %d\n", this->_vars.ifstream.frame_bytes);
    printf("\tnumber_of_frames                          :  %d\n", this->_vars.ifstream.number_of_frames);
    printf("\tframed_adc_data_v[0][0]                   :  %u\n", this->_vars.ifstream.framed_adc_data_v[0][0]);
    printf("\tbuffer_size_bytes                         :  %d\n", this->_vars.ifstream.buffer_size_bytes);
    printf("\tnumber_of_samples                         :  %d\n", this->_vars.ifstream.number_of_samples);
    printf("\tpoints_in_equalization_buffer             :  %d\n", this->_vars.ifstream.points_in_equalization_buffer);
    printf("\teq_frequency_v[0]                         :  %f\n", this->_vars.ifstream.eq_frequency_v[0]);
    printf("\teq_amplitude_v[0]                         :  %f\n", this->_vars.ifstream.eq_amplitude_v[0]);
    printf("\teq_phase_v[0]                             :  %f\n", this->_vars.ifstream.eq_phase_v[0]);
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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

// variables for IF stream managment
    this->_vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
    this->_vars.ifstream.is_enabled_adc = false;
    this->_vars.ifstream.is_active = false;

// variables for output file handling
    this->_vars.ifstream.file_name_suffix = this->_vars.constants.IFSTREAM_SUFFIX;
    strcpy(this->_vars.ifstream.file_path, this->_vars.constants.IFSTREAM_FILE_PATH);
    strcpy(this->_vars.ifstream.file_name_base, this->_vars.constants.IFSTREAM_FILE_NAME_BASE);
    this->_vars.ifstream.file_length_ms = this->_vars.constants.IFSTREAM_DEFAULT_MS;
    this->_vars.ifstream.file_count = this->_vars.constants.IFSTREAM_DEFAULT_FILE_COUNT;

// variables for acquiring IF stream directly
    this->_vars.ifstream.if_data_length = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.data_info_type.acqStatus = this->_vars.constants.INIT_UINT;
    this->_vars.ifstream.data_info_type.timestamp = this->_vars.constants.INIT_UINT;
    this->_vars.ifstream.data_info_type.triggerCount = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.data_info_type.triggerIndices = NULL;
    this->_vars.ifstream.adc_data_v.resize(this->_vars.constants.SAMPLES_IN_BUFFER);

    this->_vars.ifstream.frame_bytes = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.number_of_frames = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.framed_adc_data_v.resize(this->_vars.constants.FRAMES_IN_BUFFER);
    for (size_t ii = 0; ii < this->_vars.constants.FRAMES_IN_BUFFER; ii++)
    {
        this->_vars.ifstream.framed_adc_data_v[ii].resize(
            this->_vars.constants.ADC_SAMPLES_PER_FRAME, this->_vars.constants.INIT_UINT);
    }
    
    this->_vars.ifstream.buffer_size_bytes = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.number_of_samples = this->_vars.constants.INIT_INT;

    this->_vars.ifstream.points_in_equalization_buffer = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.eq_frequency_v.resize(this->_vars.constants.CORRECTION_POINTS, this->_vars.constants.INIT_FLOAT);
    this->_vars.ifstream.eq_amplitude_v.resize(this->_vars.constants.CORRECTION_POINTS, this->_vars.constants.INIT_FLOAT);
    this->_vars.ifstream.eq_phase_v.resize(this->_vars.constants.CORRECTION_POINTS, this->_vars.constants.INIT_FLOAT);
    
    this->_vars.ifstream.scale_factor = this->_vars.constants.INIT_DOUBLE;
    this->_vars.ifstream.scale_frequency = this->_vars.constants.INIT_DOUBLE;

    this->_vars.ifstream.if_bandwidth_hz = this->_vars.constants.INIT_DOUBLE;
    this->_vars.ifstream.samples_per_second = this->_vars.constants.INIT_DOUBLE;
    this->_vars.ifstream.if_center_frequency = this->_vars.constants.INIT_DOUBLE;

    this->_ifstream_copy_vars();
}


////////~~~~~~~~END>  rsa306b_ifstream_print_init.cpp
