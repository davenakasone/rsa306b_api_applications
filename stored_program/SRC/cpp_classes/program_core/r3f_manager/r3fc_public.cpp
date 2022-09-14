/*
    basic member functions of "r3f_manager_class", public

        public:
            < 1 >  r3f_manager_class()
            < 2 >  ~r3f_manager_class()
            < 3 >  get_bytes_in_file()
            < 4 >  time_split_begin()
            < 5 >  time_split_end()
            < 6 >  get_running_time()
            < 7 >  get_vars()

        private:
            #  none
*/

#include "r3f_manager_class.h"


/*
    public < 1 >
    only constructor of the class
*/
r3f_manager_class::r3f_manager_class()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_cpu_start = clock();
    this->_initialize();
}


////~~~~


/*
    public < 2 >
    there can only be 1 destructor
*/
r3f_manager_class::~r3f_manager_class()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

#ifdef DE_BUG
    debug_stop();
#endif
}


////~~~~


/*
    public < 3 >
    returns bytes in file if input file is open
    should be called after calling "r3f_decode" or "r3f_process"
*/
long int r3f_manager_class::get_bytes_in_file()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_bytes_in_file;
}


////~~~~


/*
    public < 4 >
    private member indicates that time split was marked
    the trailing time marker is set to the CPU clock
*/
void r3f_manager_class::time_split_begin()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_time_split_is_marked = true;
    this->_cpu_mark = clock();
}


////~~~~


/*
    public < 5 >
    if the time split was properly marked,
    the elapsed time in seconds is returned
    else,
    a negative value is returned
*/
double r3f_manager_class::time_split_end()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_time_split_is_marked == false)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "time-split was never started");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return -1;
    }
    this->_cpu_now = clock();
    this->_time_split_is_marked = false;
    double cpu_diff = (double)this->_cpu_now - (double)this->_cpu_mark;
    return (cpu_diff / CLOCKS_PER_SEC);
}


////~~~~


/*
    public < 6 >
    returns the running time in seconds,
    since the instance of the object was created
*/
double r3f_manager_class::get_running_time()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_cpu_now = clock();
    double cpu_diff = (double)this->_cpu_now - (double)this->_cpu_start;
    return (cpu_diff / CLOCKS_PER_SEC);
}


////~~~~


/*
    public < 7 >
    deep copy of the private struct to the public struct
    the user has an inert struct for extra needs
    should be called after calling "r3f_decode" or "r3f_process"
*/
void r3f_manager_class::get_vars
(
    r3f_manager_struct* sptr
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (sptr == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "allocate the variable struct");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return;
    }

    sptr->endian_check              = this->_vars.endian_check;
    sptr->file_format_version       = this->_vars.file_format_version;
    sptr->file_format_version_part  = this->_vars.file_format_version_part;
    sptr->file_format_version_sub   = this->_vars.file_format_version_sub;
    sptr->api_software_version      = this->_vars.api_software_version;
    sptr->api_software_version_part = this->_vars.api_software_version_part;
    sptr->api_software_version_sub  = this->_vars.api_software_version_sub;
    sptr->firmware_version          = this->_vars.firmware_version;
    sptr->firmware_version_part     = this->_vars.firmware_version_part;
    sptr->firmware_version_sub      = this->_vars.firmware_version_sub;
    sptr->fpga_version              = this->_vars.fpga_version;
    sptr->fpga_version_part         = this->_vars.fpga_version_part;
    sptr->fpga_version_sub          = this->_vars.fpga_version_sub;
    
    strcpy(sptr->device_nomenclature, this->_vars.device_nomenclature);
    strcpy(sptr->device_serial_number,this->_vars.device_serial_number);
    strcpy(sptr->file_id, this->_vars.file_id);
   
    sptr->reference_level_dbm                     = this->_vars.reference_level_dbm;
    sptr->rf_center_frequency_hz                  = this->_vars.rf_center_frequency_hz;
    sptr->device_temperature_celsius              = this->_vars.device_temperature_celsius;
    sptr->alignment_state                         = this->_vars.alignment_state;
    sptr->frequecny_reference_state               = this->_vars.frequecny_reference_state;
    sptr->trigger_mode                            = this->_vars.trigger_mode;
    sptr->trigger_source                          = this->_vars.trigger_source;
    sptr->trigger_transition                      = this->_vars.trigger_transition;
    sptr->trigger_level_dbm                       = this->_vars.trigger_level_dbm;
    sptr->file_data_type                          = this->_vars.file_data_type;
    sptr->byte_offset_to_first_frame              = this->_vars.byte_offset_to_first_frame;
    sptr->size_of_frame_bytes                     = this->_vars.size_of_frame_bytes;
    sptr->byte_offset_to_sample_data_in_frame     = this->_vars.byte_offset_to_sample_data_in_frame;
    sptr->number_of_samples_per_frame             = this->_vars.number_of_samples_per_frame;
    sptr->byte_offset_to_non_sample_data_in_frame = this->_vars.byte_offset_to_non_sample_data_in_frame;
    sptr->size_of_non_sample_data_in_frame_bytes  = this->_vars.size_of_non_sample_data_in_frame_bytes;
    sptr->center_frequency_if_sampled_hz          = this->_vars.center_frequency_if_sampled_hz;
    sptr->samples_per_second                      = this->_vars.samples_per_second;
    sptr->usable_bandwidth                        = this->_vars.usable_bandwidth;
    sptr->file_data_corrected                     = this->_vars.file_data_corrected;
    sptr->reftime_local_source                    = this->_vars.reftime_local_source;

    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
    {
        sptr->reftime_local[ii]        = this->_vars.reftime_local[ii];
        sptr->reftime_utc[ii]          = this->_vars.reftime_utc[ii];
        sptr->reftime_first_sample[ii] = this->_vars.reftime_first_sample[ii];
    }

    sptr->fpga_sample_count                    = this->_vars.fpga_sample_count;
    sptr->fpga_sample_counter_ticks_per_second = this->_vars.fpga_sample_counter_ticks_per_second;
    sptr->reftime_source                       = this->_vars.reftime_source;
    sptr->timestamp_of_first_sample            = this->_vars.timestamp_of_first_sample;
    sptr->sample_gain_scaling_factor           = this->_vars.sample_gain_scaling_factor;
    sptr->signal_path_delay_seconds            = this->_vars.signal_path_delay_seconds;
    sptr->channel_correction_type              = this->_vars.channel_correction_type;
    sptr->number_of_table_entries              = this->_vars.number_of_table_entries;

    for (int ii = 0; ii < MAX_TABLE_ENTRIES; ii++)
    {
        sptr->table_amplitude[ii] = this->_vars.table_amplitude[ii];
        sptr->table_frequency[ii] = this->_vars.table_frequency[ii];
        sptr->table_phase[ii]     = this->_vars.table_phase[ii];
    }
}


////////~~~~~~~~END>  r3fc_public.cpp
