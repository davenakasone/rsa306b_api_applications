/*
    for obtaining raw ADC values in CSV file

        public:
            < 1 >  prepare_plot_from_adc()

        private:
            < 1 >  _adc_helper()
            < 2 >  _process_header_direct()
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    
    trying to read "*.r3f" in batch
    should get all files in the directory
    need a good input path with data already present
*/
void r3f_manager_class::prepare_plot_from_adc
(
    const char* input_file_path, 
    const char* output_file_path
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (input_file_path == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the input file path\n");
        #endif
        return;
    }
    if (output_file_path == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the output file path name\n");
        #endif
        return;
    }
    if (this->_fptr_read != NULL || 
        this->_fptr_write != NULL )
    {
        #ifdef DEBUG_MIN
            printf("\n\terror in FILE* members\n");
        #endif
        return;
    }

    DIR* dir;
    struct dirent* diread;
    std::vector<std::string> input_file_list;
    std::vector<std::string> output_file_list;
    dir = opendir(input_file_path);
    if (dir == NULL) 
    {
        #ifdef DEBUG_MIN
            printf("\n\tinput file path not found: %s\n",
                input_file_path);
        #endif
        return;
    }
    while ( (diread = readdir(dir)) != NULL)
    {
        if (diread->d_name[0] != '.')
        {
            snprintf(this->_helper, BUF_E-1, "%s%s", 
                input_file_path, diread->d_name);

            int string_length = (int)strlen(this->_helper);
            char compare_to[5]; 
            memset(compare_to, '\0', 5);
            compare_to[0] = this->_helper[string_length-4];
            compare_to[1] = this->_helper[string_length-3];
            compare_to[2] = this->_helper[string_length-2];
            compare_to[3] = this->_helper[string_length-1];
            if (strcmp(compare_to, ".r3f") == 0)
            {
                std::string temp(this->_helper);
                input_file_list.push_back(temp);
                snprintf(this->_helper, BUF_E-1, "%sadc_%s",
                    output_file_path, diread->d_name);
                temp = this->_helper;
                temp.resize(temp.length()-4);
                temp.append(".csv");
                output_file_list.push_back(temp);
            }
        }
    }
    if (closedir(dir) != 0)
    {
        #ifdef DEBUG_MIN
            printf("\n\tDEBUG_MIN, <%4d> %s/%s()  failed to close directory\n",
                __LINE__, __FILE__, __func__);
        #endif
    }
    if (input_file_list.size() <= 0)
    if (dir == NULL) 
    {
        #ifdef DEBUG_MIN
            printf("\n\tinput data not found\n");
        #endif
        return;
    }

    for (long unsigned int fdx = 0; fdx < input_file_list.size(); fdx++)
    {
        snprintf(this->_helper, BUF_E-1, "%s", input_file_list[fdx].c_str());
        snprintf(this->_holder, BUF_F-1, "%s", output_file_list[fdx].c_str());
        this->_adc_helper(this->_helper, this->_holder);
    }    
}


////~~~~


/*
    private < 1 >
    makes raw ADC output file as 
    the input files are itterated over
*/
void r3f_manager_class::_adc_helper
(
    const char* input_fpn, 
    const char* output_fpn
)
{
    this->_fptr_read = fopen(input_fpn, "r");
    if (this->_fptr_read == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tinput file not found\n");
        #endif
        return;
    }
    fseek(this->_fptr_read, 0L, SEEK_END);
    this->_bytes_in_file = ftell(this->_fptr_read);
    fseek(this->_fptr_read, 0L, SEEK_SET);
    this->_byte_index = ftell(this->_fptr_read);
    this->_process_header_direct();

    fseek(this->_fptr_read, 0L, SEEK_SET);
    this->_fptr_write = fopen(output_fpn, "w");
    
    int total_data_frames = (this->_bytes_in_file - 
                             this->_vars.size_of_frame_bytes) / 
                             this->_vars.size_of_frame_bytes; 
    long int total_samples = this->_vars.number_of_samples_per_frame *
                             total_data_frames;

    int16_t sample_getter;
    for (long int ii = 1; ii <= total_data_frames; ii++)
    {
        this->_byte_index = this->_vars.size_of_frame_bytes * ii;
        fseek(this->_fptr_read, 0L, SEEK_SET);
        fseek(this->_fptr_read, this->_byte_index, SEEK_CUR);

        for (int jj = 0; jj < this->_vars.number_of_samples_per_frame; jj++)
        {
            fread(&sample_getter, sizeof(int16_t), 1, this->_fptr_read);
            snprintf(this->_helper, BUF_E-1, "%d,\n", sample_getter);
            fputs(this->_helper, this->_fptr_write);
        }
    }

    #ifdef DEBUG_MIN
        printf("\n\traw ADC files '%s' is ready,  %d frames  ,  %ld samples\n",
            output_fpn, total_data_frames, total_samples);
    #endif
    fclose(this->_fptr_read); this->_fptr_read = NULL;
    fclose(this->_fptr_write); this->_fptr_write = NULL;
}


////~~~~


/*
    private < 2 >
    the header information is needed first
    this 16 kB block determines how to get the rest of the data
    processed without producing output file, only populates struct
*/
void r3f_manager_class::_process_header_direct()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
   
// File ID section, 1 field
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_FILE_ID_START, SEEK_CUR); 
    // [1 of 1] file ID
    fread(this->_vars.file_id, sizeof(char), FIELD_ID_SIZE_BYTES, this->_fptr_read);

// Version Info section, 7 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_VERSION_INFO_START, SEEK_CUR);
    // [1 of 7] endian check
    fread(&this->_vars.endian_check, sizeof(int32_t), 1, this->_fptr_read);
    // [2 of 7] file format version
    fread(&this->_vars.file_format_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.file_format_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.file_format_version_part, sizeof(int16_t), 1, this->_fptr_read);
    // [3 of 7] api software version
    fread(&this->_vars.api_software_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.api_software_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.api_software_version_part, sizeof(int16_t), 1, this->_fptr_read);
   
    // [4 of 7] firmware version
    fread(&this->_vars.firmware_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.firmware_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.firmware_version_part, sizeof(int16_t), 1, this->_fptr_read);
    // [5 of 7] fpga version
    fread(&this->_vars.fpga_version, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.fpga_version_sub, sizeof(int8_t), 1, this->_fptr_read);
    fread(&this->_vars.fpga_version_part, sizeof(int16_t), 1, this->_fptr_read);
    // [6 of 7] device serial number
    fread(&this->_vars.device_serial_number, sizeof(char), DEVICE_SERIAL_NUMBER_SIZE_BYTES, this->_fptr_read);
    // [ 7 of 7] device nomenclature
    fread(this->_vars.device_nomenclature, sizeof(char), DEVICE_NOMENCLATURE_SIZE_BYTES, this->_fptr_read);

// Instrument State section, 9 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_INSTRUMENT_STATE_START, SEEK_CUR);
    // [1 of 9] reference level dBm
    fread(&this->_vars.reference_level_dbm, sizeof(double), 1, this->_fptr_read);
    // [2 of 9] RF center frequency Hz
    fread(&this->_vars.rf_center_frequency_hz, sizeof(double), 1, this->_fptr_read);
    // [3 of 9] device temperature celsius
    fread(&this->_vars.device_temperature_celsius, sizeof(double), 1, this->_fptr_read);
    // [4 of 9] alignment state
    fread(&this->_vars.alignment_state, sizeof(int32_t), 1, this->_fptr_read);
    // [5 of 9] frequency reference state
    fread(&this->_vars.frequecny_reference_state, sizeof(int32_t), 1, this->_fptr_read);
    // [6 of 9] trigger mode
    fread(&this->_vars.trigger_mode, sizeof(int32_t), 1, this->_fptr_read);
    // [7 of 9] trigger source
    fread(&this->_vars.trigger_source, sizeof(int32_t), 1, this->_fptr_read);
    // [8 of 9] trigger transition
    fread(&this->_vars.trigger_transition, sizeof(int32_t), 1, this->_fptr_read);
    // [9 of 9] trigger level dBm
    fread(&this->_vars.trigger_level_dbm, sizeof(double), 1, this->_fptr_read);

// Data Format section, 19 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_DATA_FORMAT_START, SEEK_CUR);
    // [1 of 19] file data type
    fread(&this->_vars.file_data_type, sizeof(int32_t), 1, this->_fptr_read);
    // [2 of 19] byte offset to first frame
    fread(&this->_vars.byte_offset_to_first_frame, sizeof(int32_t), 1, this->_fptr_read);
    // [3 of 19] size of frame in bytes
    fread(&this->_vars.size_of_frame_bytes, sizeof(int32_t), 1, this->_fptr_read);
    // [4 of 19] byte offset to sample data in frame
    fread(&this->_vars.byte_offset_to_non_sample_data_in_frame, sizeof(int32_t), 1, this->_fptr_read);
    // [5 of 19] number of samples per frame
    fread(&this->_vars.number_of_samples_per_frame, sizeof(int32_t), 1, this->_fptr_read);
    // [6 of 19] byte offset to non-sample data in frame
    fread(&this->_vars.byte_offset_to_non_sample_data_in_frame, sizeof(int32_t), 1, this->_fptr_read);
    // [7 of 19] size of non-sample data in frame
    fread(&this->_vars.size_of_non_sample_data_in_frame_bytes, sizeof(int32_t), 1, this->_fptr_read);
    // [8 of 19] center IF frequency sampled Hz
    fread(&this->_vars.center_frequency_if_sampled_hz, sizeof(double), 1, this->_fptr_read);
    // [9 of 19] samples per second
    fread(&this->_vars.samples_per_second, sizeof(double), 1, this->_fptr_read);
    // [10 of 19] usable bandwidth Hz
    fread(&this->_vars.usable_bandwidth, sizeof(double), 1, this->_fptr_read);
    // [11 of 19] file data corrected
    fread(&this->_vars.file_data_corrected, sizeof(int32_t), 1, this->_fptr_read);
    // [12 of 19] time source
    fread(&this->_vars.reftime_local_source, sizeof(int32_t), 1, this->_fptr_read);
    // [13 of 19] reftime local
    // [14 of 19] fpga sample count
    fread(&this->_vars.fpga_sample_count, sizeof(uint64_t), 1, this->_fptr_read);
    // [15 of 19] fpga sample counter ticks per second
    fread(&this->_vars.fpga_sample_counter_ticks_per_second, sizeof(uint64_t), 1, this->_fptr_read);
    // [16 of 19] reftime utc
    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
    {
        fread(&this->_vars.reftime_utc[ii], sizeof(int32_t), 1, this->_fptr_read);
    }
    // [17 of 19] reftime source
    fread(&this->_vars.reftime_source, sizeof(int32_t), 1, this->_fptr_read);
    // [18 of 19] timestamp of first sample
    fread(&this->_vars.timestamp_of_first_sample, sizeof(uint64_t), 1, this->_fptr_read);
    // [19 of 19] local time of first sample
    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
    {
        fread(&this->_vars.reftime_first_sample[ii], sizeof(int32_t), 1, this->_fptr_read);
    }

// Signal Path section, 2 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_SIGNAL_PATH_START, SEEK_CUR);
    // [1 of 2] sample gain scaling factor
    fread(&this->_vars.sample_gain_scaling_factor, sizeof(double), 1, this->_fptr_read);
    // [2 of 2] signal path delay seconds
    fread(&this->_vars.signal_path_delay_seconds, sizeof(double), 1, this->_fptr_read);

// Channel Correction section, 5 fields
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_CHANNEL_CORRECTION_START, SEEK_CUR);
    // [1 of 5] channel correction type
    fread(&this->_vars.channel_correction_type, sizeof(int32_t), 1, this->_fptr_read);                             
    // [2 of 5] number of table enteries
    fseek(this->_fptr_read, 0L, SEEK_SET);
    fseek(this->_fptr_read, BI_CHANNEL_CORRECTION_MID, SEEK_CUR);
    fread(&this->_vars.number_of_table_entries, sizeof(int32_t), 1, this->_fptr_read);
    // [3 of 5] table, frequency (Hz)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        fread(&this->_vars.table_frequency[ii], sizeof(float), 1, this->_fptr_read); 
    } 
    // [4 of 5] table, amplitude (dB)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        fread(&this->_vars.table_amplitude[ii], sizeof(float), 1, this->_fptr_read); 
    }    
    // [5 of 5] table, phase (degrees)
    for (int ii = 0; ii < this->_vars.number_of_table_entries; ii++)
    {
        fread(&this->_vars.table_phase[ii], sizeof(float), 1, this->_fptr_read);
    }                       
}


////////~~~~~~~~END>  r3fc_handle_adc.cpp
