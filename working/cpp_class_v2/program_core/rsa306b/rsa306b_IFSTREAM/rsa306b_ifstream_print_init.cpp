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
    printf("\tfile name suffix      :  %d  ", this->_vars.ifstream.file_name_suffix);
    switch (this->_vars.ifstream.file_name_suffix)
    {
        case (RSA_API::IFSSDFN_SUFFIX_NONE)          : printf("{none}\n");                break;
        case (RSA_API::IFSSDFN_SUFFIX_TIMESTAMP)     : printf("{timestamp included}\n");  break;
        case (RSA_API::IFSSDFN_SUFFIX_INCRINDEX_MIN) : printf("{minimal, auto-index}\n"); break;
        default                                      : printf("{! UNKNOWN !}\n");         break;
    }
    printf("\tfile path             :  %s\n", this->_vars.ifstream.file_path);
    printf("\tfile base name        :  %s\n", this->_vars.ifstream.file_name_base);
    printf("\tfile length (ms)      :  %d\n", this->_vars.ifstream.file_length_ms);
    printf("\tfile count            :  %d\n", this->_vars.ifstream.file_count);
    printf("\toutput configuration  :  %d  ", this->_vars.ifstream.output_configuration_select);
    switch (this->_vars.ifstream.output_configuration_select)
    {
        case (RSA_API::IFSOD_CLIENT)         : printf("{output direct to client, no file written}\n");                   break;
        case (RSA_API::IFSOD_FILE_R3F)       : printf("{R3F file output}\n");                                            break;
        case (RSA_API::IFSOD_FILE_R3HA_DET)  : printf("{R3H+R3A file output}\n");                                        break;
        case (RSA_API::IFSOD_FILE_MIDAS)     : printf("{Midas CDIF file output, combined header+data file}\n");          break;
        case (RSA_API::IFSOD_FILE_MIDAS_DET) : printf("{Midas CDIF+DET file output, separate header and data files}\n"); break;
        default                              : printf("{! UNKNOWN !}\n");                                                break;
    }
    printf("\tis enabled ADC        :  %d\n", this->_vars.ifstream.is_enabled_adc);
	printf("\tis active streaming   :  %d\n", this->_vars.ifstream.is_active);		 
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

    this->_vars.ifstream.output_configuration_select = RSA_API::IFSOD_FILE_R3F;
    this->_vars.ifstream.is_enabled_adc = false;
    this->_vars.ifstream.is_active = false;

    this->_vars.ifstream.file_name_suffix = this->_vars.constants.IFSTREAM_SUFFIX;
    strcpy(this->_vars.ifstream.file_path, this->_vars.constants.IFSTREAM_FILE_PATH);
    strcpy(this->_vars.ifstream.file_name_base, this->_vars.constants.IFSTREAM_FILE_NAME_BASE);
    this->_vars.ifstream.file_length_ms = this->_vars.constants.IFSTREAM_DEFAULT_MS;
    this->_vars.ifstream.file_count = this->_vars.constants.IFSTREAM_DEFAULT_FILE_COUNT;
    
    this->_vars.ifstream.if_data_getter = NULL;
    this->_vars.ifstream.if_data_length = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.data_info_type.acqStatus = this->_vars.constants.INIT_UINT;
    this->_vars.ifstream.data_info_type.timestamp = this->_vars.constants.INIT_UINT;
    this->_vars.ifstream.data_info_type.triggerCount = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.data_info_type.triggerIndices = NULL;
    //this->_vars.ifstream.adc_data.push_back(this->_vars.constants.INIT_UINT);
    //this->_vars.ifstream.adc_data.reserve(this->_vars.constants.SAMPLES_IN_BUFFER);
    this->_vars.ifstream.frame_data = NULL;
    this->_vars.ifstream.frame_bytes = this->_vars.constants.INIT_INT;
    this->_vars.ifstream.number_of_frames = this->_vars.constants.INIT_INT;
    for (int ii = 0; ii < 3; ii++)
    {
       this->_vars.ifstream.framed_adc_data[ii].push_back(this->_vars.constants.INIT_UINT);
       this->_vars.ifstream.framed_adc_data[ii].push_back(this->_vars.constants.INIT_UINT);
       this->_vars.ifstream.framed_adc_data[ii].push_back(this->_vars.constants.INIT_UINT);
    }
    for (int ii = 0; ii < 3; ii++)
    {
        printf("%d , %d , %d\n", 
            this->_vars.ifstream.framed_adc_data[ii][0],
            this->_vars.ifstream.framed_adc_data[ii][1],
            this->_vars.ifstream.framed_adc_data[ii][2]);
    }



    this->_ifstream_copy_vars();
}


////////~~~~~~~~END>  rsa306b_ifstream_print_init.cpp
/*
    // GetIFData(), retrieves the entire ADC buffer
    // the API struct "IFSTRMDATAINFO" is what would be in the footer of a "*.r3f" file
    int16_t* if_data_getter;                   // receives data buffer as a block, usually 8178 samples per block
    int if_data_length;                        // number of signed 16-bit samples returned
    RSA_API::IFSTRMDATAINFO data_info_type;    // contains aquisition information, "aqcStatus" needs a bit check
    //std::vector<uint16_t> adc_data;            // collects internal buffer "if_data_getter" is placed on

    // GetIFFrames(), retrieves availible frames
    uint8_t* frame_data;                               // do not have to allocate, pointer to buffer with IF frames
    int frame_bytes;                                   // frame data length, in bytes (includes data + footer)
    int number_of_frames;                              // number of of frames acquired
    std::vector<std::vector<int16_t>> framed_adc_data; // frame index and ADC sample value
    
    // GetIFDataBufferSize(), call to prepare "GetIFData()"
    int buffer_size_bytes;    // size in bytes for "if_data_getter" when calling "GetIFData()" .../2
    int number_of_samples;    // number of 16-bit samples "GetIFData()" will return

    // GetEQParameters(), this correction data is used for proper analysis
    int points_in_equalization_buffer;    // number of points in the equalization buffer
    float** eq_frequency_getter;          // receives internal buffer, EQ frequency, x-axis in Hz
    float** eq_amplitude_getter;          // receives internal buffer, EQ amplitude correction in dB
    float** eq_phase_getter;              // receives internal buffer, EQ phase correction in degrees
    std::vector<float> eq_frequency_v;    // collects "freq_getter" in Hz
    std::vector<float> eq_amplitude_v;    // collects "ampl_getter" in dB
    std::vector<float> eq_phase_v;        // collects "phase_getter" in degrees

    // GetScalingParameters(), to align data
    double scale_factor;       // multiply ADC data for equivelent of 50 ohm termination
    double scale_frequency;    // IF frequency the scale factor applies

    //GetAcqParameters(), for the client to get data
    double if_bandwidth_hz;        // usuable IF signal bandwidth in Hz
    double samples_per_second;     // IF data sample rate in samples per second
    double if_center_frequency;    // IF frequency where original center frequency was translated
*/