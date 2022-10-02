/*
    r3f_manager_class", initialization

        public:
            #  none
            
        private:
            < 1 >  _init()
*/

#include "r3f_manager_class.h"


/*
    public < 3 >
    ensure member variables are set to known values
*/
CODEZ r3f_manager_class::_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)memset(this->_helper, '\0', sizeof(this->_helper));
    (void)memset(this->_holder, '\0', sizeof(this->_holder));
    this->_fp_read            = NULL;
    this->_fp_write           = NULL;
    this->_byte_index           = 0;
    this->_bytes_in_file        = 0;

    // the private struct with processing variables:
    (void)memset(this->_vars.file_id, '\0', sizeof(this->_vars.file_id));
    this->_vars.endian_check              = 0;
    this->_vars.file_format_version       = 0;
    this->_vars.file_format_version_part  = 0;
    this->_vars.file_format_version_sub   = 0;
    this->_vars.api_software_version      = 0;
    this->_vars.api_software_version_part = 0;
    this->_vars.api_software_version_sub  = 0;
    this->_vars.firmware_version          = 0;
    this->_vars.firmware_version_part     = 0;
    this->_vars.firmware_version_sub      = 0;
    this->_vars.fpga_version              = 0;
    this->_vars.fpga_version_part         = 0;
    this->_vars.fpga_version_sub          = 0;
    (void)memset(this->_vars.device_serial_number, '\0', sizeof(this->_vars.device_serial_number));
    (void)memset(this->_vars.device_nomenclature, '\0', sizeof(this->_vars.device_nomenclature));

    this->_vars.reference_level_dbm                     = 0;
    this->_vars.rf_center_frequency_hz                  = 0;
    this->_vars.device_temperature_celsius              = 0;
    this->_vars.alignment_state                         = 0;
    this->_vars.frequecny_reference_state               = 0;
    this->_vars.trigger_mode                            = 0;
    this->_vars.trigger_source                          = 0;
    this->_vars.trigger_transition                      = 0;
    this->_vars.trigger_level_dbm                       = 0;
    this->_vars.file_data_type                          = 0;
    this->_vars.byte_offset_to_first_frame              = 0;
    this->_vars.size_of_frame_bytes                     = 0;
    this->_vars.byte_offset_to_sample_data_in_frame     = 0;
    this->_vars.number_of_samples_per_frame             = 0;
    this->_vars.byte_offset_to_non_sample_data_in_frame = 0;
    this->_vars.size_of_non_sample_data_in_frame_bytes  = 0;
    this->_vars.center_frequency_if_sampled_hz          = 0;
    this->_vars.samples_per_second                      = 0;
    this->_vars.usable_bandwidth                        = 0;
    this->_vars.file_data_corrected                     = 0;
    this->_vars.reftime_local_source                    = 0;
    
    for (int ii = 0; ii < R3F_REFTIME_ELEMENTS; ii++)
    {
        this->_vars.reftime_local[ii]        = 0;
        this->_vars.reftime_utc[ii]          = 0;
        this->_vars.reftime_first_sample[ii] = 0;
    }

    this->_vars.fpga_sample_count                    = 0;
    this->_vars.fpga_sample_counter_ticks_per_second = 0;
    this->_vars.reftime_source                       = 0;
    this->_vars.timestamp_of_first_sample            = 0;
    this->_vars.sample_gain_scaling_factor           = 0;
    this->_vars.signal_path_delay_seconds            = 0;
    this->_vars.channel_correction_type              = 0;
    this->_vars.number_of_table_entries              = 0;

    for (int ii = 0; ii < R3F_MAX_TABLE_ENTRIES; ii++)
    {
        this->_vars.table_amplitude[ii] = 0;
        this->_vars.table_frequency[ii] = 0;
        this->_vars.table_phase[ii]     = 0;
    }

    for (int ii = 0; ii < R3F_FOOTER_DISCARD; ii++)
    {
        this->_vars.discard[ii] = 0;
    }
    
    this->_vars.extracted_sample           = 0;
    this->_vars.frame_id                   = 0;
    this->_vars.trigger_1_index            = 0;
    this->_vars.trigger_2_index            = 0;
    this->_vars.time_synchronization_index = 0;
    this->_vars.frame_status               = 0;
    this->_vars.frame_timestamp            = 0;

    this->_vars.v_adc.clear();
    for (std::size_t ii = 0; ii < R3F_EQL_FILEDS; ii++)
    {
        this->_vars.v_eqaul[ii].clear();
    }
    
    return this->_get_vars();   // initializes the public struct instance
}


////////~~~~~~~~END>  r3f_init.cpp
