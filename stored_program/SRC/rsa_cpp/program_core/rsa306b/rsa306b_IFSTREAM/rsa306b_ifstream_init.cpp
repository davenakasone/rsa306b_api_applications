/*
    API group "IFSTREAM"

    public :
        #  none
    
    private :
        < 1 >  _ifstream_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_ifstream_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.ifstream.file_name_suffix              = this->_vars.ifstream._FILE_NAME_SUFFIX;
    this->_vars.ifstream.is_active                     = this->_vars.ifstream._IS_ACTIVE;
    this->_vars.ifstream.is_enabled                    = this->_vars.ifstream._IS_ENABLED;
    this->_vars.ifstream.if_bandwidth_hz               = this->_vars.ifstream._IF_BANDWIDTH_HZ;
    this->_vars.ifstream.samples_per_second            = this->_vars.ifstream._SAMPLES_PER_SECOND;
    this->_vars.ifstream.if_center_frequency           = this->_vars.ifstream._IF_CENTER_FREQUENCY;
    this->_vars.ifstream.points_in_equalization_buffer = this->_vars.ifstream._POINTS_IN_EQUALIZATION_BUFFER;

    this->_vars.ifstream.eq_frequency_v.assign(this->_vars.ifstream._EQ_FREQUENCY_V_size, this->_vars.ifstream._EQ_FREQUENCY_V_element);
    this->_vars.ifstream.eq_amplitude_v.assign(this->_vars.ifstream._EQ_AMPLITUDE_V_size, this->_vars.ifstream._EQ_AMPLITUDE_V_element);
    this->_vars.ifstream.eq_phase_v.    assign(this->_vars.ifstream._EQ_PHASE_V_size    , this->_vars.ifstream._EQ_PHASE_V_element    );

    this->_vars.ifstream.adc_data_v.    assign(this->_vars.ifstream._ADC_DATA_V_size    , this->_vars.ifstream._ADC_DATA_V_element  );
    this->_vars.ifstream.adc_triggers_v.assign(this->_vars.ifstream._ADC_TRIGGERS_V_size, this->_vars.ifstream._ADC_TRIGGERS_element);

    this->_vars.ifstream.if_data_length = this->_vars.ifstream._IF_DATA_LENGTH;
    
    for (int ii = 0; ii < IFSTREAM_BITCHECKS; ii++)
    {
        //(void)strcpy(this->_vars.ifstream.acq_status_messages[ii], this->_vars.ifstream._ACQ_STATUS_MESSAGES);
        (void)strcpy(this->_vars.ifstream.acq_status_messages[ii], BITCHECK_SUCCESS_MESSAGE);
    }
    
    this->_vars.ifstream.data_info_type.acqStatus      = this->_vars.ifstream._DATA_INFO_TYPE_acqStatus;
    this->_vars.ifstream.data_info_type.timestamp      = this->_vars.ifstream._DATA_INFO_TYPE_timestamp;
    this->_vars.ifstream.data_info_type.triggerCount   = this->_vars.ifstream._DATA_INFO_TYPE_triggerCount;
    //this->_vars.ifstream.data_info_type.triggerIndices = this->_vars.ifstream._DATA_INFO_TYPE_triggerIndices;

    this->_vars.ifstream.buffer_size_bytes = this->_vars.ifstream._BUFFER_SIZE_BYTES;
    this->_vars.ifstream.buffer_samples    = this->_vars.ifstream._BUFFER_SAMPLES;

    this->_vars.ifstream.framed_adc_data_v.resize(this->_vars.ifstream._FRAMED_ADC_DATA_V_rows);
    for (std::size_t ii = 0; ii < this->_vars.ifstream.framed_adc_data_v.size(); ii++)
    {
        this->_vars.ifstream.framed_adc_data_v[ii].assign(
            this->_vars.ifstream._FRAMED_ADC_DATA_V_cols, 
            this->_vars.ifstream._FRAMED_ADC_DATA_V_element);
    }

    this->_vars.ifstream.frame_bytes        = this->_vars.ifstream._FRAME_BYTES;
    this->_vars.ifstream.number_of_frames   = this->_vars.ifstream._NUMBER_OF_FRAMES;
    this->_vars.ifstream.scale_factor       = this->_vars.ifstream._SCALE_FACTOR;
    this->_vars.ifstream.scale_frequency    = this->_vars.ifstream._SCALE_FREQUENCY;
    this->_vars.ifstream.file_count         = this->_vars.ifstream._FILE_COUNT;
    this->_vars.ifstream.file_length_max_ms = this->_vars.ifstream._FILE_LENGTH_MAX_MS;

    (void)strcpy(this->_vars.ifstream.file_name_base, IFSTREAM_FILE_NAME_BASE);
    (void)strcpy(this->_vars.ifstream.file_path     , DATA_DIRECTORY_RAW     );

    this->_vars.ifstream.output_destination_select = this->_vars.ifstream._OUTPUT_DESTINATION_SELECT;

    return this->_ifstream_copy_vars();
}


////////~~~~~~~~END>  rsa306b_ifstream_init.cpp
