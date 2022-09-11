/*
    basic member functions of "r3f_manager_class", private

        public:
            #  none

        private:
            < 1 >  _verify_r3f_extension()
            < 2 > _find_input_file_size()
            < 3 >  _initialize()
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    ensures "*.r3f" file is used as input
    opens the file
    any failure should halt the program
*/
int r3f_manager_class::_verify_r3f_extension
(
    const char* r3f_input_path_file_name
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (r3f_input_path_file_name == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "allocate input file-path-name");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_CALL_FAILURE;
    }

    int string_length = (int)strlen(r3f_input_path_file_name);
    if ( string_length < 5)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "input file too small:  %s", r3f_input_path_file_name);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_CALL_FAILURE;
    }

    char compare_to[5]; memset(compare_to, '\0', 5);
    compare_to[0] = r3f_input_path_file_name[string_length-4];
    compare_to[1] = r3f_input_path_file_name[string_length-3];
    compare_to[2] = r3f_input_path_file_name[string_length-2];
    compare_to[3] = r3f_input_path_file_name[string_length-1];
    if (strcmp(compare_to, ".r3f") != 0)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "not an .r3f extension:  %s", compare_to);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_CALL_FAILURE;
    }
    this->_fptr_read = fopen(r3f_input_path_file_name, "r");
    if (this->_fptr_read == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "failed to open input file:  %s", r3f_input_path_file_name);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_CALL_FAILURE;
    }
    return this->_CALL_SUCCESS;
}


////~~~~


/*
    public < 2 >
    the file is scanned until EOF
    the bytes in the file are saved to member variable
    EOF is cleared
    size check occurs
*/
int r3f_manager_class::_find_input_file_size()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_fptr_read == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "FILE* not ready to read");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_CALL_FAILURE;
    }

    fseek(this->_fptr_read, 0L, SEEK_END);
    this->_bytes_in_file = ftell(this->_fptr_read);
    fseek(this->_fptr_read, 0L, SEEK_SET);
    this->_byte_index = ftell(this->_fptr_read);
    if (this->_bytes_in_file <= 0)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "input file has bytes:  %ld", this->_bytes_in_file);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_CALL_FAILURE;
    }
    else
    {
        #ifdef DEBUG_MAX
            printf("\n\tthe files has:  %ld bytes\n",
                this->_bytes_in_file);
        #endif
        return this->_CALL_SUCCESS;
    }
}


////~~~~


/*
    public < 3 >
    ensure member variables are set to known values
*/
void r3f_manager_class::_initialize()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_return_status = this->_CALL_FAILURE;
    memset(this->_helper, '\0', BUF_E);
    memset(this->_holder, '\0', BUF_F);
    this->_fptr_decode          = NULL;
    this->_fptr_read            = NULL;
    this->_fptr_write           = NULL;
    this->_byte_index           = 0;
    this->_bytes_in_file        = 0;
    this->_time_split_is_marked = false;
    this->_cpu_mark             = 0;
    this->_cpu_now              = 0;
    // _cpu_start was already handled in the constructor

    // the private struct with processing variables:
    memset(this->_vars.file_id, '\0', BUF_B);
    this->_vars.endian_check = 0;
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
    memset(this->_vars.device_serial_number, '\0', BUF_B);
    memset(this->_vars.device_nomenclature, '\0', BUF_B);

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
    
    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
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

    for (int ii = 0; ii < MAX_TABLE_ENTRIES; ii++)
    {
        this->_vars.table_amplitude[ii] = 0;
        this->_vars.table_frequency[ii] = 0;
        this->_vars.table_phase[ii]     = 0;
    }

    for (int ii = 0; ii < FOOTER_DISCARD; ii++)
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

    this->get_vars(&this->members);   // initializes the public struct instance
}


////////~~~~~~~~END>  r3fc_private.cpp
