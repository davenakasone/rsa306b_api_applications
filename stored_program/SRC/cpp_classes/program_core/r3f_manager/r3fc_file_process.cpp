/*
    basic member functions of "r3f_manager_class",
    the file processing capability

        public:
            < 1 >  file_process()

        private:
            < 1 >  _process_header()
            < 2 >  _process_data()
            < 3 >  _store_field()
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    the input file is validated
    member variables are reset
    the size of the file is registered
    the output file is opened with force
    processing occurs for every byte in the file
        header is processed first
        data is processed last (second)
*/
void r3f_manager_class::file_process
(
    const char* r3f_input_path_file_name,
    const char* r3f_output_path_file_name,
    bool print_while_processing
) 
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, DEBUG_WIDTH-1, DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (r3f_output_path_file_name == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "allocate file-path-name");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    this->_initialize();
    this->_return_status = this->_verify_r3f_extension(r3f_input_path_file_name);
    if (this->_return_status != _CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "not .r3f file:  %s", r3f_input_path_file_name);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    this->_return_status = this->_find_input_file_size();
    if (this->_return_status != _CALL_SUCCESS)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "input file too small: %s", r3f_input_path_file_name);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }
    
    this->_fptr_write = fopen(r3f_output_path_file_name, "w");
    fseek(this->_fptr_read, 0L, SEEK_SET);
    if (print_while_processing == true)
    {
        printf("\nmaking %s  ,  total bytes:  %ld\n<<< file processing begin >>>\n",
            r3f_output_path_file_name, this->_bytes_in_file);
    }

    this->_process_header(print_while_processing);
    this->_process_data(print_while_processing);    

    if (print_while_processing == true)
    {
        printf("\n<<< file processing end >>>  check:  '%s'\n", r3f_output_path_file_name);
    }
    fclose(this->_fptr_write); this->_fptr_write = NULL;
    fclose(this->_fptr_read); this->_fptr_read = NULL;
}


////~~~~


/*
    private < 1 >
    the header information is needed first
    this 16 kB block determines how to get the rest of the data
    validation should have occured before calling
    "field                                              :  value" 
*/
void r3f_manager_class::_process_header
(
    bool print_while_processing
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, DEBUG_WIDTH-1, DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
   
   if (print_while_processing == true)
   {
       printf("\n\t<<< header begin >>>\n\n");
   }
// File ID section, 1 field
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_FILE_ID_START, SEEK_CUR); 
    // [1 of 1] file ID
    fread(this->_vars.file_id, sizeof(char), FIELD_ID_SIZE_BYTES, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "File ID                                            :  %s\n", 
        this->_vars.file_id);
    this->_store_field(print_while_processing);

// Version Info section, 7 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_VERSION_INFO_START, SEEK_CUR);
    // [1 of 7] endian check
    fread(&this->_vars.endian_check, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Endian Check                                       :  0x%X\n", 
        this->_vars.endian_check);
    this->_store_field(print_while_processing);
    // [2 of 7] file format version
    fread(&this->_vars.file_format_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.file_format_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.file_format_version_part, sizeof(int16_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "File Format Version                                :  " 
        "%d.%d.%d\n", 
        this->_vars.file_format_version, 
        this->_vars.file_format_version_sub, 
        this->_vars.file_format_version_part);
    this->_store_field(print_while_processing);
    // [3 of 7] api software version
    fread(&this->_vars.api_software_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.api_software_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.api_software_version_part, sizeof(int16_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "API Software Version                               :  %d.%d.%d\n",
        this->_vars.api_software_version,
        this->_vars.api_software_version_sub,
        this->_vars.api_software_version_part);
    this->_store_field(print_while_processing);
    // [4 of 7] firmware version
    fread(&this->_vars.firmware_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.firmware_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.firmware_version_part, sizeof(int16_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Firmware Version                                   :  %d.%d.%d\n",
        this->_vars.firmware_version,
        this->_vars.firmware_version_sub,
        this->_vars.firmware_version_part);
    this->_store_field(print_while_processing);
    // [5 of 7] fpga version
    fread(&this->_vars.fpga_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.fpga_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.fpga_version_part, sizeof(int16_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "FPGA Version                                       :  %d.%d.%d\n",
        this->_vars.fpga_version,
        this->_vars.fpga_version_sub,
        this->_vars.fpga_version_part);
    this->_store_field(print_while_processing);
    // [6 of 7] device serial number
    fread(&this->_vars.device_serial_number, sizeof(char), DEVICE_SERIAL_NUMBER_SIZE_BYTES, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Device Serial Number                               :  %s\n", 
        this->_vars.device_serial_number);
    this->_store_field(print_while_processing);
    // [ 7 of 7] device nomenclature
    fread(this->_vars.device_nomenclature, sizeof(char), DEVICE_NOMENCLATURE_SIZE_BYTES, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Device Nomenclature                                :  %s\n", 
        this->_vars.device_nomenclature);
    this->_store_field(print_while_processing);

// Instrument State section, 9 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_INSTRUMENT_STATE_START, SEEK_CUR);
    // [1 of 9] reference level dBm
    fread(&this->_vars.reference_level_dbm, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Reference Level (dBm)                              :  %lf\n", 
        this->_vars.reference_level_dbm);
    this->_store_field(print_while_processing);
    // [2 of 9] RF center frequency Hz
    fread(&this->_vars.rf_center_frequency_hz, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "RF Center Frequency (Hz)                           :  %lf\n", 
        this->_vars.rf_center_frequency_hz);
    this->_store_field(print_while_processing);
    // [3 of 9] device temperature celsius
    fread(&this->_vars.device_temperature_celsius, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Device Temperature (C)                             :  %lf\n",
        this->_vars.device_temperature_celsius);
    this->_store_field(print_while_processing);
    // [4 of 9] alignment state
    fread(&this->_vars.alignment_state, sizeof(int32_t), 1, this->_fptr_read);
    switch (this->_vars.alignment_state)
    {
        case (0) : snprintf(this->_holder, BUF_F-1, "Alignment State                                    :  not aligned\n"); break;
        case (1) : snprintf(this->_holder, BUF_F-1, "Alignment State                                    :  aligned\n");     break;
        default  : snprintf(this->_holder, BUF_F-1, "Alignment State                                    :  unknown\n");     break;
    }
    this->_store_field(print_while_processing);
    // [5 of 9] frequency reference state
    fread(&this->_vars.frequecny_reference_state, sizeof(int32_t), 1, this->_fptr_read);
    switch (this->_vars.frequecny_reference_state)
    {
        case (0) : snprintf(this->_holder, BUF_F-1, "Frequency Reference State                          :  internal\n"); break;
        case (1) : snprintf(this->_holder, BUF_F-1, "Frequency Reference State                          :  external\n"); break;
        case (2) : snprintf(this->_holder, BUF_F-1, "Frequency Reference State                          :  GNSS\n");     break;
        case (3) : snprintf(this->_holder, BUF_F-1, "Frequency Reference State                          :  user\n");     break;
        default  : snprintf(this->_holder, BUF_F-1, "Frequency Reference State                          :  unknown\n");  break;
    }
    this->_store_field(print_while_processing);
    // [6 of 9] trigger mode
    fread(&this->_vars.trigger_mode, sizeof(int32_t), 1, this->_fptr_read);
    switch (this->_vars.trigger_mode)
    {
        case (0) : snprintf(this->_holder, BUF_F-1, "Trigger Mode                                       :  free running\n"); break;
        case (1) : snprintf(this->_holder, BUF_F-1, "Trigger Mode                                       :  triggered\n");    break;
        default  : snprintf(this->_holder, BUF_F-1, "Trigger Mode                                       :  unknown\n");      break;
    }
    this->_store_field(print_while_processing);
    // [7 of 9] trigger source
    fread(&this->_vars.trigger_source, sizeof(int32_t), 1, this->_fptr_read);
    switch (this->_vars.trigger_source)
    {
        case (0) : snprintf(this->_holder, BUF_F-1, "Trigger Source                                     :  external\n"); break;
        case (1) : snprintf(this->_holder, BUF_F-1, "Trigger Source                                     :  power\n");    break;
        default  : snprintf(this->_holder, BUF_F-1, "Trigger Source                                     :  unknown\n");  break;
    }
    this->_store_field(print_while_processing);
    // [8 of 9] trigger transition
    fread(&this->_vars.trigger_transition, sizeof(int32_t), 1, this->_fptr_read);
    switch (this->_vars.trigger_transition)
    {
        case (1) : snprintf(this->_holder, BUF_F-1, "Trigger Transition                                 :  rising\n");  break;
        case (2) : snprintf(this->_holder, BUF_F-1, "Trigger Transition                                 :  falling\n"); break;
        default  : snprintf(this->_holder, BUF_F-1, "Trigger Transition                                 :  unknown\n"); break;
    }
    this->_store_field(print_while_processing);
    // [9 of 9] trigger level dBm
    fread(&this->_vars.trigger_level_dbm, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Trigger Level (dBm)                                :  %lf\n",
        this->_vars.trigger_level_dbm);
    this->_store_field(print_while_processing);

// Data Format section, 19 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_DATA_FORMAT_START, SEEK_CUR);
    // [1 of 19] file data type
    fread(&this->_vars.file_data_type, sizeof(int32_t), 1, this->_fptr_read);
    if (this->_vars.file_data_type == 161)
    {
        snprintf(this->_holder, BUF_F-1, "File Data Type                                     :  16-bit integer IF samples\n");
    }
    else
    {
        snprintf(this->_holder, BUF_F-1, "File Data Type                                     :  unkown\n");
    }
    this->_store_field(print_while_processing);
    // [2 of 19] byte offset to first frame
    fread(&this->_vars.byte_offset_to_first_frame, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Byte offset to first data frame                    :  %d\n",
        this->_vars.byte_offset_to_first_frame);
    this->_store_field(print_while_processing);

    // [3 of 19] size of frame in bytes
    fread(&this->_vars.size_of_frame_bytes, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Size of Frame (bytes)                              :  %d\n",
        this->_vars.size_of_frame_bytes);
    this->_store_field(print_while_processing);

    // [4 of 19] byte offset to sample data in frame
    fread(&this->_vars.byte_offset_to_non_sample_data_in_frame, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Byte offset to sample data in frame                :  %d\n",
        this->_vars.byte_offset_to_sample_data_in_frame);
    this->_store_field(print_while_processing);

    // [5 of 19] number of samples per frame
    fread(&this->_vars.number_of_samples_per_frame, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Number of samples per frame                        :  %d\n",
        this->_vars.number_of_samples_per_frame);
    this->_store_field(print_while_processing);

    // [6 of 19] byte offset to non-sample data in frame
    fread(&this->_vars.byte_offset_to_non_sample_data_in_frame, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Byte offset to non-sample data in frame            :  %d\n",
        this->_vars.byte_offset_to_non_sample_data_in_frame);
    this->_store_field(print_while_processing);

    // [7 of 19] size of non-sample data in frame
    fread(&this->_vars.size_of_non_sample_data_in_frame_bytes, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Size of non-sample data in frame (bytes)           :  %d\n",
        this->_vars.size_of_non_sample_data_in_frame_bytes);
    this->_store_field(print_while_processing);
    // [8 of 19] center IF frequency sampled Hz
    fread(&this->_vars.center_frequency_if_sampled_hz, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Center IF Frequency Sampled (Hz)                   :  %lf\n", 
        this->_vars.center_frequency_if_sampled_hz);
    this->_store_field(print_while_processing);
    // [9 of 19] samples per second
    fread(&this->_vars.samples_per_second, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Samples per Second                                 :  %lf\n", 
        this->_vars.samples_per_second);
    this->_store_field(print_while_processing);
    // [10 of 19] usable bandwidth Hz
    fread(&this->_vars.usable_bandwidth, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Usable Bandwidth (Hz)                              :  %lf\n",
        this->_vars.usable_bandwidth);
    this->_store_field(print_while_processing);
    // [11 of 19] file data corrected
    fread(&this->_vars.file_data_corrected, sizeof(int32_t), 1, this->_fptr_read);
    if (this->_vars.file_data_corrected == 0)
    {
        snprintf(this->_holder, BUF_F-1, "File Data                                          :  uncorrected\n");
    }
    else
    {
        snprintf(this->_holder, BUF_F-1, "File Data                                          :  correction unknown\n");
    }
    this->_store_field(print_while_processing);
    // [12 of 19] time source
    fread(&this->_vars.reftime_local_source, sizeof(int32_t), 1, this->_fptr_read);
    if (this->_vars.reftime_local_source == 0)
    {
        snprintf(this->_holder, BUF_F-1, "Time Source                                        :  local\n");
    }
    else
    {
        snprintf(this->_holder, BUF_F-1, "Time Source                                        :  unknown\n");
    }
    this->_store_field(print_while_processing);
    // [13 of 19] reftime local
    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
    {
        fread(&this->_vars.reftime_local[ii], sizeof(int32_t), 1, this->_fptr_read);
    }
    snprintf(this->_holder, BUF_F-1, "Local Time {YY/MM/DD_hh:mm:ss_nano}                :  "
        "%04d/%02d/%02d_%02d:%02d:%02d_%d\n",
        this->_vars.reftime_local[0],
        this->_vars.reftime_local[1],
        this->_vars.reftime_local[2],
        this->_vars.reftime_local[3],
        this->_vars.reftime_local[4],
        this->_vars.reftime_local[5],
        this->_vars.reftime_local[6]);
    this->_store_field(print_while_processing);
    // [14 of 19] fpga sample count
    fread(&this->_vars.fpga_sample_count, sizeof(uint64_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "FPGA Sample Count                                  :  %ld\n",
        this->_vars.fpga_sample_count);
    this->_store_field(print_while_processing);
    // [15 of 19] fpga sample counter ticks per second
    fread(&this->_vars.fpga_sample_counter_ticks_per_second, sizeof(uint64_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "FPGA Sample Counter Ticks per Second               :  %ld\n",
        this->_vars.fpga_sample_counter_ticks_per_second);
    this->_store_field(print_while_processing);
    // [16 of 19] reftime utc
    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
    {
        fread(&this->_vars.reftime_utc[ii], sizeof(int32_t), 1, this->_fptr_read);
    }
    snprintf(this->_holder, BUF_F-1, "UTC Time {YY/MM/DD_hh:mm:ss_nano}                  :  "
        "%04d/%02d/%02d_%02d:%02d:%02d_%d\n",
        this->_vars.reftime_utc[0],
        this->_vars.reftime_utc[1],
        this->_vars.reftime_utc[2],
        this->_vars.reftime_utc[3],
        this->_vars.reftime_utc[4],
        this->_vars.reftime_utc[5],
        this->_vars.reftime_utc[6]);
    this->_store_field(print_while_processing);
    // [17 of 19] reftime source
    fread(&this->_vars.reftime_source, sizeof(int32_t), 1, this->_fptr_read);
    switch (this->_vars.reftime_source)
    {
        case (1) : snprintf(this->_holder, BUF_F-1, "REFTIME Source                                     :  system\n");  break;
        case (2) : snprintf(this->_holder, BUF_F-1, "REFTIME Source                                     :  GNSS\n");    break;
        case (3) : snprintf(this->_holder, BUF_F-1, "REFTIME Source                                     :  user\n");    break;
        default  : snprintf(this->_holder, BUF_F-1, "REFTIME Source                                     :  unknown\n"); break;
    }
    this->_store_field(print_while_processing);
    // [18 of 19] timestamp of first sample
    fread(&this->_vars.timestamp_of_first_sample, sizeof(uint64_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "First sample, timestamp                            :  %ld\n",
        this->_vars.timestamp_of_first_sample);
    this->_store_field(print_while_processing);
    // [19 of 19] local time of first sample
    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
    {
        fread(&this->_vars.reftime_first_sample[ii], sizeof(int32_t), 1, this->_fptr_read);
    }
    snprintf(this->_holder, BUF_F-1, "First sample, local time {YY/MM/DD_hh:mm:ss_nano}  :  " 
        "%04d/%02d/%02d_%02d:%02d:%02d_%d\n",
        this->_vars.reftime_first_sample[0],
        this->_vars.reftime_first_sample[1],
        this->_vars.reftime_first_sample[2],
        this->_vars.reftime_first_sample[3],
        this->_vars.reftime_first_sample[4],
        this->_vars.reftime_first_sample[5],
        this->_vars.reftime_first_sample[6]);
    this->_store_field(print_while_processing);

// Signal Path section, 2 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_SIGNAL_PATH_START, SEEK_CUR);
    // [1 of 2] sample gain scaling factor
    fread(&this->_vars.sample_gain_scaling_factor, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Sample Gain Scaling Factor                         :  %lf\n",
        this->_vars.sample_gain_scaling_factor);
    this->_store_field(print_while_processing);
    // [2 of 2] signal path delay seconds
    fread(&this->_vars.signal_path_delay_seconds, sizeof(double), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Signal Path Delay (s)                              :  %lf\n",
        this->_vars.signal_path_delay_seconds);
    this->_store_field(print_while_processing);

// Channel Correction section, 5 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_CHANNEL_CORRECTION_START, SEEK_CUR);
    // [1 of 5] channel correction type
    fread(&this->_vars.channel_correction_type, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_helper, BUF_E-1, "Channel Correction                                 :  "); 
    switch (this->_vars.channel_correction_type)
    {
        case(0) : snprintf(this->_holder, BUF_F-1, "%sLF\n", this->_helper);      break;
        case(1) : snprintf(this->_holder, BUF_F-1, "%sRF/IF\n", this->_helper);   break;
        default : snprintf(this->_holder, BUF_F-1, "%sunknown\n", this->_helper); break;
    }
    this->_store_field(print_while_processing);                              
    // [2 of 5] number of table enteries
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_CHANNEL_CORRECTION_MID, SEEK_CUR);
    fread(&this->_vars.number_of_table_entries, sizeof(int32_t), 1, this->_fptr_read);
    snprintf(this->_holder, BUF_F-1, "Number of Table Entries                            :  %d\n", 
        this->_vars.number_of_table_entries);
    this->_store_field(print_while_processing); 
    // [3 of 5] table, frequency (Hz)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        fread(&this->_vars.table_frequency[ii], sizeof(float), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, "table_frequency[%3d]  (Hz)                         :  %f\n",
            ii, this->_vars.table_frequency[ii]);
        this->_store_field(print_while_processing); 
    } 
    // [4 of 5] table, amplitude (dB)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        fread(&this->_vars.table_amplitude[ii], sizeof(float), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, "table_amplitude[%3d]  (dB)                         :  %f\n",
            ii, this->_vars.table_amplitude[ii]);
        this->_store_field(print_while_processing); 
    }    
    // [5 of 5] table, phase (degrees)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        fread(&this->_vars.table_phase[ii], sizeof(float), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, "table_phase[%3d]  (degrees)                        :  %f\n",
            ii, this->_vars.table_phase[ii]);
        this->_store_field(print_while_processing); 
    }                       

    snprintf(this->_holder, BUF_F-1, "%s\n", this->_BLOCK_SEPERATOR);
    fputs(this->_holder, this->_fptr_write);
    if (print_while_processing == true)
   {
        printf("%s\n\t<<< header end >>>\n",
            this->_holder);
   }
}


////~~~~


/*
    private < 2 >
    using the header information to get the data
*/
void r3f_manager_class::_process_data
(
    bool print_while_processing
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, DEBUG_WIDTH-1, DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    int samples_to_get = (this->_bytes_in_file - 
                               this->_vars.size_of_frame_bytes) / 
                               this->_vars.size_of_frame_bytes;
    if (print_while_processing)
    {
        printf("\n\t<<< data extraction begin >>>  ...%d samples\n\n",
            samples_to_get);
    }
    
    for (int ii = 1; ii <= samples_to_get; ii++)
    {
        this->_byte_index = this->_vars.size_of_frame_bytes * ii;
        fseek(this->_fptr_read, 0L, SEEK_SET);
        fseek(this->_fptr_read, this->_byte_index, SEEK_CUR);
        
        snprintf(this->_holder, BUF_F-1, "%s  frame:  %5d of %5d  { %9ld }\n", 
            this->_BLOCK_SEPERATOR, ii, samples_to_get, ftell(this->_fptr_read));
        fputs(this->_holder, this->_fptr_write);
        if (print_while_processing == true)
        {
            printf("%s", this->_holder);
        }

        for (int32_t jj = 0; jj < this->_vars.number_of_samples_per_frame; jj++)
        {
            fread(&this->_vars.extracted_sample, sizeof(int16_t), 1, this->_fptr_read);
            snprintf(this->_holder, BUF_F-1,"%6d)  %d\n", 
                jj, this->_vars.extracted_sample);
            fputs(this->_holder, this->_fptr_write);
        }
        
        for (int kk = 0; kk < FOOTER_DISCARD; kk++)
        {
            fread(&this->_vars.discard[kk], sizeof(uint8_t), 1, this->_fptr_read);
        }
        fread(&this->_vars.frame_id, sizeof(uint32_t), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, 
            "Frame ID                                           :  %u\n", this->_vars.frame_id);
        this->_store_field(false);
        fread(&this->_vars.trigger_1_index, sizeof(uint16_t), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, 
            "Trigger 1 index                                    :  %u\n", this->_vars.trigger_1_index);
        this->_store_field(false);
        fread(&this->_vars.trigger_2_index, sizeof(uint16_t), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, 
            "Trigger 2 index                                    :  %u\n", this->_vars.trigger_1_index);
        this->_store_field(false);
        fread(&this->_vars.time_synchronization_index, sizeof(uint16_t), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, 
            "Time Synchronization index                         :  %u\n", this->_vars.time_synchronization_index);
        this->_store_field(false);
        fread(&this->_vars.frame_status, sizeof(uint16_t), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, 
            "Frame Status                                       :  %u\n", this->_vars.frame_status);
        this->_store_field(false);
        fread(&this->_vars.frame_timestamp, sizeof(uint64_t), 1, this->_fptr_read);
        snprintf(this->_holder, BUF_F-1, 
            "Timestamp                                          :  %ld    { %12ld }\n", 
            ftell(this->_fptr_read)-1,
            this->_vars.frame_timestamp);
        this->_store_field(false);                        
    }

    if (print_while_processing)
    {
        printf("\n\t<<< data extraction end >>>\n");
        printf("\ntotal bytes in file:  %ld  ,  fptr on byte:  %ld\n",
            this->_bytes_in_file, ftell(this->_fptr_read));
    }
}


////~~~~


/*
    private < 3 >
    a common task is placed into a function
    prints to stdout if requested
    writes to the _fptr_write file
*/
void r3f_manager_class::_store_field
(
    bool print_while_processing
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (print_while_processing == true)
    {
        printf("%12ld)  %s", ftell(this->_fptr_read)-1, this->_holder);
    }
    fputs(this->_holder, this->_fptr_write);
}


////////~~~~~~~~END>  r3fc_file_process.cpp
