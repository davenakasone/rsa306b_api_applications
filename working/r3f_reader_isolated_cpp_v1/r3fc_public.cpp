/*
    basic member functions of "r3f_manager_class", public

        public:
            < 1 >  r3f_manager_class()
            < 2 >  ~r3f_manager_class()
            < 3 >  get_bytes_in_file()
            < 4 >  time_split_begin()
            < 5 >  time_split_end()
            < 6 >  get_running_time()
            < 7 >  get_members()

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
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->_cpu_start = clock();
    #ifdef DEBUG_MIN
        printf("\n\tinstance constructed\n");
    #endif
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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    #ifdef DEBUG_MIN
        printf("\n\tinstance destructed, total running time:  %lf seconds\n",
            this->get_running_time());
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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_time_split_is_marked == false)
    {
        #ifdef DEBUG_MIN
            printf("\t\ntime split was not started\n");
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
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
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
void r3f_manager_class::get_members
(
    r3f_manager_struct* sptr
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (sptr == NULL)
    {
        #ifdef DEBUG_MIN
            printf("\n\tallocate the struct\n");
        #endif
        return;
    }

    strcpy(sptr->file_id, this->_members.file_id);
    sptr->endian_check = this->_members.endian_check;
    sptr->file_format_version = this->_members.file_format_version;
    sptr->file_format_version_part = this->_members.file_format_version_part;
    sptr->file_format_version_sub = this->_members.file_format_version_sub;
    sptr->api_software_version = this->_members.api_software_version;
    sptr->api_software_version_part = this->_members.api_software_version_part;
    sptr->api_software_version_sub = this->_members.api_software_version_sub;
    sptr->firmware_version = this->_members.firmware_version;
    sptr->firmware_version_part = this->_members.firmware_version_part;
    sptr->firmware_version_sub = this->_members.firmware_version_sub;
    sptr->fpga_version = this->_members.fpga_version;
    sptr->fpga_version_part = this->_members.fpga_version_part;
    sptr->fpga_version_sub = this->_members.fpga_version_sub;
    strcpy(sptr->device_nomenclature, this->_members.device_nomenclature);
    strcpy(sptr->device_serial_number,this->_members.device_serial_number);
   
    sptr->reference_level_dbm = this->_members.reference_level_dbm;
    sptr->rf_center_frequency_hz = this->_members.rf_center_frequency_hz;
    sptr->device_temperature_celsius = this->_members.device_temperature_celsius;
    sptr->alignment_state = this->_members.alignment_state;
    sptr->frequecny_reference_state = this->_members.frequecny_reference_state;
    sptr->trigger_mode = this->_members.trigger_mode;
    sptr->trigger_source = this->_members.trigger_source;
    sptr->trigger_transition = this->_members.trigger_transition;
    sptr->trigger_level_dbm = this->_members.trigger_level_dbm;
    sptr->file_data_type = this->_members.file_data_type;
    sptr->byte_offset_to_first_frame = this->_members.byte_offset_to_first_frame;
    sptr->size_of_frame_bytes = this->_members.size_of_frame_bytes;
    sptr->byte_offset_to_sample_data_in_frame = this->_members.byte_offset_to_sample_data_in_frame;
    sptr->number_of_samples_per_frame = this->_members.number_of_samples_per_frame;
    sptr->byte_offset_to_non_sample_data_in_frame = this->_members.byte_offset_to_non_sample_data_in_frame;
    sptr->size_of_non_sample_data_in_frame_bytes = this->_members.size_of_non_sample_data_in_frame_bytes;
    sptr->center_frequency_if_sampled_hz = this->_members.center_frequency_if_sampled_hz;
    sptr->samples_per_second = this->_members.samples_per_second;
    sptr->usable_bandwidth = this->_members.usable_bandwidth;
    sptr->file_data_corrected = this->_members.file_data_corrected;
    sptr->reftime_local_source = this->_members.reftime_local_source;
    for (int ii = 0; ii < REFTIME_ELEMENTS; ii++)
    {
        sptr->reftime_local[ii] = this->_members.reftime_local[ii];
        sptr->reftime_utc[ii] = this->_members.reftime_utc[ii];
        sptr->reftime_first_sample[ii] = this->_members.reftime_first_sample[ii];
    }
    sptr->fpga_sample_count = this->_members.fpga_sample_count;
    sptr->fpga_sample_counter_ticks_per_second = this->_members.fpga_sample_counter_ticks_per_second;
    sptr->reftime_source = this->_members.reftime_source;
    sptr->timestamp_of_first_sample = this->_members.timestamp_of_first_sample;
    sptr->sample_gain_scaling_factor = this->_members.sample_gain_scaling_factor;
    sptr->signal_path_delay_seconds = this->_members.signal_path_delay_seconds;
    sptr->channel_correction_type = this->_members.channel_correction_type;
    sptr->number_of_table_entries = this->_members.number_of_table_entries;
    for (int ii = 0; ii < MAX_TABLE_ENTRIES; ii++)
    {
        sptr->table_amplitude[ii] = this->_members.table_amplitude[ii];
        sptr->table_frequency[ii] = this->_members.table_frequency[ii];
        sptr->table_phase[ii] = this->_members.table_phase[ii];
    }
}


////////~~~~~~~~END>  r3fc_public.cpp
