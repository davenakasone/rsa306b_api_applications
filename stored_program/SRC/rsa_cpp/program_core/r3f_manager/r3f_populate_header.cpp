/*
    "r3f_manager_class",  help populate the header frame

        public:
            #  none

        private:
            < 1 >  _populate_header()
*/

#include "r3f_manager_class.h"


/*
    private < 1 >
    the header information is needed first AND "*.r3f" file is open for reading
    if "write_parsed==true" a valid output file pointer must be open
    called only from "load_file()"
    this 16 kB block determines how to get the rest of the data
    validation should have occured before calling
    "field                                              :  value" 
*/
CODEZ  r3f_manager_class::_populate_header
(
    bool write_parsed
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    if (this->_fp_read == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
    }
    if (write_parsed == true)
    {
        if (this->_fp_write == NULL)
        {
            return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
        }
    }

// File ID section, 1 field
    (void)fseek(this->_fp_read, 0L, SEEK_SET);
    (void)fseek(this->_fp_read, R3F_BI_FILE_ID_START, SEEK_CUR); 
    // [1 of 1] file ID
    (void)fread(this->_vars.file_id, sizeof(char), R3F_FIELD_ID_SIZE_BYTES, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "File ID                                            :  %s\n", 
            this->_vars.file_id);
        (void)fputs(this->_holder, this->_fp_write);
    }

// Version Info section, 7 fields
    (void)fseek(this->_fp_read, 0L, SEEK_SET);
    (void)fseek(this->_fp_read, R3F_BI_VERSION_INFO_START, SEEK_CUR);
    // [1 of 7] endian check
    (void)fread(&this->_vars.endian_check, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Endian Check                                       :  0x%X\n", 
            this->_vars.endian_check);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [2 of 7] file format version
    (void)fread(&this->_vars.file_format_version, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.file_format_version_sub, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.file_format_version_part, sizeof(int16_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "File Format Version                                :  " 
            "%d.%d.%d\n", 
            this->_vars.file_format_version, 
            this->_vars.file_format_version_sub, 
            this->_vars.file_format_version_part);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [3 of 7] api software version
    (void)fread(&this->_vars.api_software_version, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.api_software_version_sub, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.api_software_version_part, sizeof(int16_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "API Software Version                               :  %d.%d.%d\n",
            this->_vars.api_software_version,
            this->_vars.api_software_version_sub,
            this->_vars.api_software_version_part);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [4 of 7] firmware version
    (void)fread(&this->_vars.firmware_version, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.firmware_version_sub, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.firmware_version_part, sizeof(int16_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Firmware Version                                   :  %d.%d.%d\n",
            this->_vars.firmware_version,
            this->_vars.firmware_version_sub,
            this->_vars.firmware_version_part);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [5 of 7] fpga version
    (void)fread(&this->_vars.fpga_version, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.fpga_version_sub, sizeof(int8_t), 1, this->_fp_read);
    (void)fread(&this->_vars.fpga_version_part, sizeof(int16_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "FPGA Version                                       :  %d.%d.%d\n",
            this->_vars.fpga_version,
            this->_vars.fpga_version_sub,
            this->_vars.fpga_version_part);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [6 of 7] device serial number
    (void)fread(&this->_vars.device_serial_number, sizeof(char), R3F_DEVICE_SERIAL_NUMBER_SIZE_BYTES, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Device Serial Number                               :  %s\n", 
            this->_vars.device_serial_number);
        (void)fputs(this->_holder, this->_fp_write);
    }
    
    // [ 7 of 7] device nomenclature
    (void)fread(this->_vars.device_nomenclature, sizeof(char), R3F_DEVICE_NOMENCLATURE_SIZE_BYTES, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Device Nomenclature                                :  %s\n", 
            this->_vars.device_nomenclature);
        (void)fputs(this->_holder, this->_fp_write);
    }

// Instrument State section, 9 fields
    (void)fseek(this->_fp_read, 0L, SEEK_SET);
    (void)fseek(this->_fp_read, R3F_BI_INSTRUMENT_STATE_START, SEEK_CUR);
    // [1 of 9] reference level dBm
    (void)fread(&this->_vars.reference_level_dbm, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Reference Level (dBm)                              :  %lf\n", 
            this->_vars.reference_level_dbm);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [2 of 9] RF center frequency Hz
    (void)fread(&this->_vars.rf_center_frequency_hz, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "RF Center Frequency (Hz)                           :  %lf\n", 
            this->_vars.rf_center_frequency_hz);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [3 of 9] device temperature celsius
    (void)fread(&this->_vars.device_temperature_celsius, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Device Temperature (C)                             :  %lf\n",
            this->_vars.device_temperature_celsius);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [4 of 9] alignment state
    (void)fread(&this->_vars.alignment_state, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        switch (this->_vars.alignment_state)
        {
            case (0) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Alignment State                                    :  not aligned\n"); break;
            case (1) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Alignment State                                    :  aligned\n");     break;
            default  : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Alignment State                                    :  unknown\n");     break;
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [5 of 9] frequency reference state
    (void)fread(&this->_vars.frequecny_reference_state, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        switch (this->_vars.frequecny_reference_state)
        {
            case (0) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Frequency Reference State                          :  internal\n"); break;
            case (1) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Frequency Reference State                          :  external\n"); break;
            case (2) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Frequency Reference State                          :  GNSS\n");     break;
            case (3) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Frequency Reference State                          :  user\n");     break;
            default  : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Frequency Reference State                          :  unknown\n");  break;
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [6 of 9] trigger mode
    (void)fread(&this->_vars.trigger_mode, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        switch (this->_vars.trigger_mode)
        {
            case (0) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Mode                                       :  free running\n"); break;
            case (1) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Mode                                       :  triggered\n");    break;
            default  : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Mode                                       :  unknown\n");      break;
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [7 of 9] trigger source
    (void)fread(&this->_vars.trigger_source, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        switch (this->_vars.trigger_source)
        {
            case (0) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Source                                     :  external\n"); break;
            case (1) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Source                                     :  power\n");    break;
            default  : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Source                                     :  unknown\n");  break;
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [8 of 9] trigger transition
    (void)fread(&this->_vars.trigger_transition, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        switch (this->_vars.trigger_transition)
        {
            case (1) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Transition                                 :  rising\n");  break;
            case (2) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Transition                                 :  falling\n"); break;
            default  : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Transition                                 :  unknown\n"); break;
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [9 of 9] trigger level dBm
    (void)fread(&this->_vars.trigger_level_dbm, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Trigger Level (dBm)                                :  %lf\n",
            this->_vars.trigger_level_dbm);
        (void)fputs(this->_holder, this->_fp_write);
    }

// Data Format section, 19 fields
    (void)fseek(this->_fp_read, 0L, SEEK_SET);
    (void)fseek(this->_fp_read, R3F_BI_DATA_FORMAT_START, SEEK_CUR);
    // [1 of 19] file data type
    (void)fread(&this->_vars.file_data_type, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        if (this->_vars.file_data_type == 161)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "File Data Type                                     :  16-bit integer IF samples\n");
        }
        else
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "File Data Type                                     :  unkown\n");
        }
        (void)fputs(this->_holder, this->_fp_write);
    }
    
    // [2 of 19] byte offset to first frame
    (void)fread(&this->_vars.byte_offset_to_first_frame, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Byte offset to first data frame                    :  %d\n",
            this->_vars.byte_offset_to_first_frame);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [3 of 19] size of frame in bytes
    (void)fread(&this->_vars.size_of_frame_bytes, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Size of Frame (bytes)                              :  %d\n",
            this->_vars.size_of_frame_bytes);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [4 of 19] byte offset to sample data in frame
    (void)fread(&this->_vars.byte_offset_to_non_sample_data_in_frame, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Byte offset to sample data in frame                :  %d\n",
            this->_vars.byte_offset_to_sample_data_in_frame);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [5 of 19] number of samples per frame
    (void)fread(&this->_vars.number_of_samples_per_frame, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Number of samples per frame                        :  %d\n",
            this->_vars.number_of_samples_per_frame);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [6 of 19] byte offset to non-sample data in frame
    (void)fread(&this->_vars.byte_offset_to_non_sample_data_in_frame, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Byte offset to non-sample data in frame            :  %d\n",
            this->_vars.byte_offset_to_non_sample_data_in_frame);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [7 of 19] size of non-sample data in frame
    (void)fread(&this->_vars.size_of_non_sample_data_in_frame_bytes, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Size of non-sample data in frame (bytes)           :  %d\n",
            this->_vars.size_of_non_sample_data_in_frame_bytes);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [8 of 19] center IF frequency sampled Hz
    (void)fread(&this->_vars.center_frequency_if_sampled_hz, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Center IF Frequency Sampled (Hz)                   :  %lf\n", 
            this->_vars.center_frequency_if_sampled_hz);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [9 of 19] samples per second
    (void)fread(&this->_vars.samples_per_second, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Samples per Second                                 :  %lf\n", 
            this->_vars.samples_per_second);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [10 of 19] usable bandwidth Hz
    (void)fread(&this->_vars.usable_bandwidth, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Usable Bandwidth (Hz)                              :  %lf\n",
            this->_vars.usable_bandwidth);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [11 of 19] file data corrected
    (void)fread(&this->_vars.file_data_corrected, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        if (this->_vars.file_data_corrected == 0)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "File Data                                          :  uncorrected\n");
        }
        else
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "File Data                                          :  correction unknown\n");
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [12 of 19] time source
    (void)fread(&this->_vars.reftime_local_source, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        if (this->_vars.reftime_local_source == 0)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Time Source                                        :  local\n");
        }
        else
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Time Source                                        :  unknown\n");
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [13 of 19] reftime local
    for (int ii = 0; ii < R3F_REFTIME_ELEMENTS; ii++)
    {
        (void)fread(&this->_vars.reftime_local[ii], sizeof(int32_t), 1, this->_fp_read);
    }
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Local Time {YY/MM/DD_hh:mm:ss_nano}                :  "
            "%04d/%02d/%02d_%02d:%02d:%02d_%d\n",
            this->_vars.reftime_local[0],
            this->_vars.reftime_local[1],
            this->_vars.reftime_local[2],
            this->_vars.reftime_local[3],
            this->_vars.reftime_local[4],
            this->_vars.reftime_local[5],
            this->_vars.reftime_local[6]);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [14 of 19] fpga sample count
    (void)fread(&this->_vars.fpga_sample_count, sizeof(uint64_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "FPGA Sample Count                                  :  %ld\n",
            this->_vars.fpga_sample_count);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [15 of 19] fpga sample counter ticks per second
    (void)fread(&this->_vars.fpga_sample_counter_ticks_per_second, sizeof(uint64_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "FPGA Sample Counter Ticks per Second               :  %ld\n",
            this->_vars.fpga_sample_counter_ticks_per_second);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [16 of 19] reftime utc
    for (int ii = 0; ii < R3F_REFTIME_ELEMENTS; ii++)
    {
        (void)fread(&this->_vars.reftime_utc[ii], sizeof(int32_t), 1, this->_fp_read);
    }
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "UTC Time {YY/MM/DD_hh:mm:ss_nano}                  :  "
            "%04d/%02d/%02d_%02d:%02d:%02d_%d\n",
            this->_vars.reftime_utc[0],
            this->_vars.reftime_utc[1],
            this->_vars.reftime_utc[2],
            this->_vars.reftime_utc[3],
            this->_vars.reftime_utc[4],
            this->_vars.reftime_utc[5],
            this->_vars.reftime_utc[6]);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [17 of 19] reftime source
    (void)fread(&this->_vars.reftime_source, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        switch (this->_vars.reftime_source)
        {
            case (1) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "REFTIME Source                                     :  system\n");  break;
            case (2) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "REFTIME Source                                     :  GNSS\n");    break;
            case (3) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "REFTIME Source                                     :  user\n");    break;
            default  : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "REFTIME Source                                     :  unknown\n"); break;
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [18 of 19] timestamp of first sample
    (void)fread(&this->_vars.timestamp_of_first_sample, sizeof(uint64_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "First sample, timestamp                            :  %ld\n",
            this->_vars.timestamp_of_first_sample);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [19 of 19] local time of first sample
    for (int ii = 0; ii < R3F_REFTIME_ELEMENTS; ii++)
    {
        (void)fread(&this->_vars.reftime_first_sample[ii], sizeof(int32_t), 1, this->_fp_read);
    }
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "First sample, local time {YY/MM/DD_hh:mm:ss_nano}  :  " 
            "%04d/%02d/%02d_%02d:%02d:%02d_%d\n",
            this->_vars.reftime_first_sample[0],
            this->_vars.reftime_first_sample[1],
            this->_vars.reftime_first_sample[2],
            this->_vars.reftime_first_sample[3],
            this->_vars.reftime_first_sample[4],
            this->_vars.reftime_first_sample[5],
            this->_vars.reftime_first_sample[6]);
        (void)fputs(this->_holder, this->_fp_write);
    }

// Signal Path section, 2 fields
    (void)fseek(this->_fp_read, 0L, SEEK_SET);
    (void)fseek(this->_fp_read, R3F_BI_SIGNAL_PATH_START, SEEK_CUR);
    // [1 of 2] sample gain scaling factor
    (void)fread(&this->_vars.sample_gain_scaling_factor, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Sample Gain Scaling Factor                         :  %lf\n",
            this->_vars.sample_gain_scaling_factor);
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [2 of 2] signal path delay seconds
    (void)fread(&this->_vars.signal_path_delay_seconds, sizeof(double), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Signal Path Delay (s)                              :  %lf\n",
            this->_vars.signal_path_delay_seconds);
        (void)fputs(this->_holder, this->_fp_write);
    }

// Channel Correction section, 5 fields
    (void)fseek(this->_fp_read, 0L, SEEK_SET);
    (void)fseek(this->_fp_read, R3F_BI_CHANNEL_CORRECTION_START, SEEK_CUR);
    // [1 of 5] channel correction type
    (void)fread(&this->_vars.channel_correction_type, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_helper, BUF_E-1, "Channel Correction                                 :  "); 
        switch (this->_vars.channel_correction_type)
        {
            case(0) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "%sLF\n", this->_helper);      break;
            case(1) : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "%sRF/IF\n", this->_helper);   break;
            default : (void)snprintf(this->_holder, sizeof(this->_holder)-1, "%sunknown\n", this->_helper); break;
        }
        (void)fputs(this->_holder, this->_fp_write);
    }

    // [2 of 5] number of table enteries
    (void)fseek(this->_fp_read, 0L, SEEK_SET);
    (void)fseek(this->_fp_read, R3F_BI_CHANNEL_CORRECTION_MID, SEEK_CUR);
    (void)fread(&this->_vars.number_of_table_entries, sizeof(int32_t), 1, this->_fp_read);
    if(write_parsed == true)
    {
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "Number of Table Entries                            :  %d\n", 
            this->_vars.number_of_table_entries);
        (void)fputs(this->_holder, this->_fp_write); 
    }

    // [3 of 5] table, frequency (Hz)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        (void)fread(&this->_vars.table_frequency[ii], sizeof(float), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "table_frequency[%3d]  (Hz)                         :  %f\n",
                ii, this->_vars.table_frequency[ii]);
            (void)fputs(this->_holder, this->_fp_write); 
        }
        this->_vars.v_eqaul[R3F_EQL_IDX_FREQ].push_back(this->_vars.table_frequency[ii]);    // vector is loaded
    } 
    // [4 of 5] table, amplitude (dB)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        (void)fread(&this->_vars.table_amplitude[ii], sizeof(float), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "table_amplitude[%3d]  (dB)                         :  %f\n",
                ii, this->_vars.table_amplitude[ii]);
            (void)fputs(this->_holder, this->_fp_write); 
        }
        this->_vars.v_eqaul[R3F_EQL_IDX_SCAL].push_back(this->_vars.table_amplitude[ii]);    // vector is loaded
    }    
    // [5 of 5] table, phase (degrees)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        (void)fread(&this->_vars.table_phase[ii], sizeof(float), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "table_phase[%3d]  (degrees)                        :  %f\n",
                ii, this->_vars.table_phase[ii]);
            (void)fputs(this->_holder, this->_fp_write); 
        }
        this->_vars.v_eqaul[R3F_EQL_IDX_PHAS].push_back(this->_vars.table_phase[ii]);    // vector is loaded
    } 

    if(write_parsed == true)
    {                      
        (void)snprintf(this->_holder, sizeof(this->_holder)-1, "%s\n", R3F_BLOCK_SEPERATOR);
        (void)fputs(this->_holder, this->_fp_write);
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  r3f_populate_header.cpp
