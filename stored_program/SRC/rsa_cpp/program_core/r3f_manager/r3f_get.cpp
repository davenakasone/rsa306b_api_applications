/*
    r3f_manager_class", getting

        public:
            #  none
            
        private:
            < 1 >  _get_vars()
*/

#include "r3f_manager_class.h"


/*
    public < 7 >
    deep copy of the private struct to the public struct
    the user has an inert struct for extra needs
    should be called after loading an r3f file successfully
*/
CODEZ r3f_manager_class::_get_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.endian_check              = this->_vars.endian_check;
    this->vars.file_format_version       = this->_vars.file_format_version;
    this->vars.file_format_version_part  = this->_vars.file_format_version_part;
    this->vars.file_format_version_sub   = this->_vars.file_format_version_sub;
    this->vars.api_software_version      = this->_vars.api_software_version;
    this->vars.api_software_version_part = this->_vars.api_software_version_part;
    this->vars.api_software_version_sub  = this->_vars.api_software_version_sub;
    this->vars.firmware_version          = this->_vars.firmware_version;
    this->vars.firmware_version_part     = this->_vars.firmware_version_part;
    this->vars.firmware_version_sub      = this->_vars.firmware_version_sub;
    this->vars.fpga_version              = this->_vars.fpga_version;
    this->vars.fpga_version_part         = this->_vars.fpga_version_part;
    this->vars.fpga_version_sub          = this->_vars.fpga_version_sub;
    
    strcpy(this->vars.device_nomenclature, this->_vars.device_nomenclature);
    strcpy(this->vars.device_serial_number,this->_vars.device_serial_number);
    strcpy(this->vars.file_id, this->_vars.file_id);
   
    this->vars.reference_level_dbm                     = this->_vars.reference_level_dbm;
    this->vars.rf_center_frequency_hz                  = this->_vars.rf_center_frequency_hz;
    this->vars.device_temperature_celsius              = this->_vars.device_temperature_celsius;
    this->vars.alignment_state                         = this->_vars.alignment_state;
    this->vars.frequecny_reference_state               = this->_vars.frequecny_reference_state;
    this->vars.trigger_mode                            = this->_vars.trigger_mode;
    this->vars.trigger_source                          = this->_vars.trigger_source;
    this->vars.trigger_transition                      = this->_vars.trigger_transition;
    this->vars.trigger_level_dbm                       = this->_vars.trigger_level_dbm;
    this->vars.file_data_type                          = this->_vars.file_data_type;
    this->vars.byte_offset_to_first_frame              = this->_vars.byte_offset_to_first_frame;
    this->vars.size_of_frame_bytes                     = this->_vars.size_of_frame_bytes;
    this->vars.byte_offset_to_sample_data_in_frame     = this->_vars.byte_offset_to_sample_data_in_frame;
    this->vars.number_of_samples_per_frame             = this->_vars.number_of_samples_per_frame;
    this->vars.byte_offset_to_non_sample_data_in_frame = this->_vars.byte_offset_to_non_sample_data_in_frame;
    this->vars.size_of_non_sample_data_in_frame_bytes  = this->_vars.size_of_non_sample_data_in_frame_bytes;
    this->vars.center_frequency_if_sampled_hz          = this->_vars.center_frequency_if_sampled_hz;
    this->vars.samples_per_second                      = this->_vars.samples_per_second;
    this->vars.usable_bandwidth                        = this->_vars.usable_bandwidth;
    this->vars.file_data_corrected                     = this->_vars.file_data_corrected;
    this->vars.reftime_local_source                    = this->_vars.reftime_local_source;

    for (int ii = 0; ii < R3F_REFTIME_ELEMENTS; ii++)
    {
        this->vars.reftime_local[ii]        = this->_vars.reftime_local[ii];
        this->vars.reftime_utc[ii]          = this->_vars.reftime_utc[ii];
        this->vars.reftime_first_sample[ii] = this->_vars.reftime_first_sample[ii];
    }

    this->vars.fpga_sample_count                    = this->_vars.fpga_sample_count;
    this->vars.fpga_sample_counter_ticks_per_second = this->_vars.fpga_sample_counter_ticks_per_second;
    this->vars.reftime_source                       = this->_vars.reftime_source;
    this->vars.timestamp_of_first_sample            = this->_vars.timestamp_of_first_sample;
    this->vars.sample_gain_scaling_factor           = this->_vars.sample_gain_scaling_factor;
    this->vars.signal_path_delay_seconds            = this->_vars.signal_path_delay_seconds;
    this->vars.channel_correction_type              = this->_vars.channel_correction_type;
    this->vars.number_of_table_entries              = this->_vars.number_of_table_entries;

    for (int ii = 0; ii < R3F_MAX_TABLE_ENTRIES; ii++)
    {
        this->vars.table_amplitude[ii] = this->_vars.table_amplitude[ii];
        this->vars.table_frequency[ii] = this->_vars.table_frequency[ii];
        this->vars.table_phase[ii]     = this->_vars.table_phase[ii];
    }

    this->vars.v_adc.resize(this->_vars.v_adc.size());
    this->vars.v_adc = this->_vars.v_adc;

    for (std::size_t ii = 0; ii < R3F_EQL_FILEDS; ii++)
    {
        this->vars.v_eqaul[ii].resize(this->_vars.v_eqaul[ii].size());
        this->vars.v_eqaul[ii] = this->_vars.v_eqaul[ii];
    }
    

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  r3f_get.cpp
