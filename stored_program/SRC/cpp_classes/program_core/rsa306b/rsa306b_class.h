/*
    this is the top-level class of the program
    subordinate classes (included by composition) not designed to be used independently
    this class uses the provided API to interface with the RSA-306B Spectrum Analyzer
    Tektronix requires 2 shared objects (dynamic libraries) to be linked and the RSA_API.h header
    the API is designed to run on a 64-bit Linux OS using an Intel processor (or AMD)
    only one instance of this class can connect to the spectrum analyzer
    for most use cases, only one instance of this class is required

    Purpose of this class:
        - automate API by abstracting mandatory procedures
        - enforce correct use of the API 
        - foundation for implementing future spectrum analyzer API interface needs
        - easy use, while meeting speed requirements

    see documentation for general details
    see the test section for examples 
    output files use a seperate file manager in the main program
        "r3f_manager"
        "siq_manager"
    a sperate timer is available: 
        "cpu_timer"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

    Class source files, 
    
        "./program_core/rsa306b"
            - rsa306b_struct.h
                struct rsa306b_struct
            - rsa306b_class.h
                class rsa306b_class

        "./program_core/rsa306b/rsa306_GP/"
            - rsa306b_gp_struct.h
                rsa306b_gp_struct
            - rsa306b_class_cons_dest.cpp
                rsa306b_class()
                ~rsa306b_class()
            - rsa306b_gp_confirm.cpp
                _gp_confirm_api_status()
                _gp_confirm_call_status()
                _gp_confirm_return()
                _gp_confirm_aquisition_code()
            - rsa306b_gp_copy.cpp
                get_everything()
                _gp_copy_vars()
                _gp_copy_helper()
                _gp_copy_holder()
                _gp_copy_call_status()
                _gp_copy_api_status()
                _gp_copy_acquisition_code()
                _gp_copy_acquistion_message()
            - rsa306b_gp_init.cpp
                _init_everything()
                _gp_init()
            - rsa306b_gp_print.cpp
                print_everything()
                print_constants()
                print_gp()
            - rsa306b_gp_utility.cpp
                gp_wchar_2_char()

        "./program_core/rsa306b/rsa306b_constants.h
            rsa306b_constants.h
        
        "./program_core/rsa306b/rsa306_ALIGN"
            - rsa306b_align_struct.h
                rsa306b_align_struct
            - rsa306b_align_print_init.cpp
                print_align()
                _align_init()
            - rsa306b_align_get_copy.cpp
                _align_get_vars()       
                _align_get_is_needed()
                _align_get_is_warmed()
                _align_copy_vars()
                _align_copy_is_needed()
                _align_copy_is_warmed()
            - rsa306b_align_user.cpp
                align_run()
                align_check_is_needed()
                align_check_is_warmed()
        
        "./program_core/rsa306b/rsa306_AUDIO"
            - rsa306b_audio_struct.h
                rsa306b_audio_struct
            - rsa306b_audio_print_init.cpp
                print_audio()
                _audio_init()
            - rsa306b_audio_copy.cpp
                _audio_copy_vars()
                _audio_copy_is_demodulating()
                _audio_copy_is_mute()
                _audio_copy_frequecny_offset_hz()
                _audio_copy_volume()
                _audio_copy_demodulation_select()
                _audio_copy_data()
                _audio_copy_data_samples_requested()
                _audio_copy_data_samples_acquired()
            - rsa306b_audio_get.cpp
                _audio_get_vars()
                _audio_get_is_demodulating()
                _audio_get_is_mute()
                _audio_get_frequency_offset_hz()
                _audio_get_volume()
                _audio_get_demodulation_select()
                _audio_get_data()
            - rsa306b_audio_set.cpp
                _audio_set_vars()
                _audio_set_is_mute()
                _audio_set_frequency_offset_hz()
                _audio_set_volume()
                _audio_set_demodulation_select()
                _audio_set_data_samples_requested()
            - rsa306b_audio_user.cpp
                audio_set_vars()
                audio_acquire_data()

        "./program_core/rsa306b/rsa306_CONFIG/"
            - rsa306b_config_struct.h
                rsa306b_config_struct    
            - rsa306b_config_print_init.cpp
                print_config()
                _config_init()
            - rsa306b_config_copy.cpp
                _config_copy_vars()
                _config_copy_reference_level_dbm()
                _config_copy_center_frequency_hz()
                _config_copy_min_center_frequency_hz()
                _config_copy_max_center_frequency_hz()
                _config_copy_external_reference_frequency_hz()
                _config_copy_frequency_reference_source_select()
            - rsa306b_config_get.cpp
                _config_get_vars()
                _config_get_reference_level_dbm()
                _config_get_center_frequency_hz()
                _config_get_min_center_frequency_hz()
                _config_get_max_center_frequency_hz()
                _config_get_external_reference_frequency_hz()
                _config_get_frequency_reference_source_select()
            - rsa306b_config_set.cpp
                _config_set_vars()
                _config_set_reference_level_dbm()
                _config_set_center_frequency_hz()
                _config_set_external_reference_frequency_source_select()
            - rsa306b_config_user.cpp
                config_preset()
                config_set_vars()

        "./program_core/rsa306b/rsa306_DEVICE/"
            - rsa306b_device_struct.h
                rsa306b_device_struct
            - rsa306b_device_print_init.cpp
                print_device()
                _device_init()
            - rsa306b_device_copy.cpp
                _device_copy_vars()
                _device_copy_is_connected()
                _device_copy_is_over_temperature()
                _device_copy_is_running()
                _device_copy_event_occured()
                _device_copy_error_string()
                _device_copy_id()
                _device_copy_event_id()
                _device_copy_info_type()
                _device_copy_event_timestamp()
            - rsa306b_device_get.cpp
                _device_get_vars()
                _device_get_is_running()
                _device_get_error_string()
                _device_get_info_type()
                _device_get_is_over_temperature()
                _device_get_event()
            - rsa306b_device_user1.cpp
                device_connect()
                device_disconnect()
                device_run()
                device_stop()
                device_reset()
            - rsa306b_device_user2.cpp
                device_check_run_state()
                device_check_temperature()
                device_check_event()
                device_prepare_for_run()
                device_start_frame_transfer()

        "./program_core/rsa306b/rsa306_IFSTREAM/"
            - rsa306b_ifstream_struct.h
                rsa306b_ifstream_struct
            - rsa306b_ifstream_print_init.cpp
                print_reftime()
                _reftime_init()
            - rsa306b_ifstream_copy.cpp
                _ifstream_copy_vars()
                _ifstream_copy_file_name_suffix()
                _ifstream_copy_file_path()
                _ifstream_copy_file_name_base()
                _ifstream_copy_file_length_ms()
                _ifstream_copy_file_count()
                _ifstream_copy_output_configuration_select()
                _ifstream_copy_is_enabled_adc()
                _ifstream_copy_is_active()
                _ifstream_copy_if_data()
                _ifstream_copy_if_data_length()
                _ifstream_copy_data_info_type()
                _ifstream_copy_adc_data_v()
                _ifstream_copy_if_frames()
                _ifstream_copy_frame_bytes()
                _ifstream_copy_number_of_frames()
                _ifstream_copy_framed_adc_data_v()
                _ifstream_copy_eq_parameters()
                _ifstream_copy_points_in_equalization_buffer()
                _ifstream_copy_eq_frequency_v()
                _ifstream_copy_eq_amplitude_v()
                _ifstream_copy_eq_phase_v()
                _ifstream_copy_scaling_parameters()
                _ifstream_copy_scale_factor()
                _ifstream_copy_scale_frequency()
                _ifstream_copy_acq_parameters()
                _ifstream_copy_if_bandwidth_hz()
                _ifstream_copy_samples_per_second()
                _ifstream_copy_if_center_frequency()
                _ifstream_copy_buffer_size()
                _ifstream_copy_buffer_size_bytes()
                _ifstream_copy_number_of_samples()
            - rsa306b_ifstream_get.cpp
                _ifstream_get_vars()
                _ifstream_get_is_active()
                _ifstream_get_acq_parameters()
                _ifstream_get_buffer_size()
                _ifstream_get_eq_parameters()
                _ifstream_get_scaling_parameters()
            - rsa306b_ifstream_set.cpp
                _ifstream_set_vars()
                _ifstream_set_file_name_suffix()
                _ifstream_set_file_path()
                _ifstream_set_file_name_base()
                _ifstream_set_file_length_ms()
                _ifstream_set_file_count()
                _ifstream_set_output_configuration_select()
                _ifstream_set_is_enabled_adc()
            - rsa306b_ifstream_user.cpp
                ifstream_set_vars()
                ifstream_record_file()
                ifstream_acquire_adc_data()
                ifstream_acquire_adc_frames()
        
        "./program_core/rsa306b/rsa306_IQBLK/"
            - rsa306b_iqblk_struct.h
                rsa306b_iqblk_struct
            - rsa306b_iqblk_print_init_check.cpp
                print_iqblk()
                _iqblk_init()
                _iqblk_bitcheck()
            - rsa306b_iqblk_copy.cpp
                _iqblk_copy_vars()
                _iqblk_copy_getter()
                _iqblk_copy_actual_buffer_samples()
                _iqblk_copy_sample_pairs_requested()
                _iqblk_copy_cplx32_v()
                _iqblk_copy_acq_info_type()
                _iqblk_copy_bitcheck()
                _iqblk_copy_sample_rate()
                _iqblk_copy_bandwidth_hz()
                _iqblk_copy_max_bandwidth_hz()
                _iqblk_copy_min_bandwidth_hz()
                _iqblk_copy_record_length()
                _iqblk_copy_max_record_length()
            - rsa306b_iqblk_get.cpp
                _iqblk_get_vars()
                _iqblk_get_acq_info_type()
                _iqblk_get_sample_rate()
                _iqblk_get_bandwidth_hz()
                _iqblk_get_max_bandwidth_hz()
                _iqblk_get_min_bandwidth_hz()
                _iqblk_get_max_record_length()
                _iqblk_get_record_length()
            - rsa306b_iqblk_set.cpp
                iqblk_set_vars()
                _iqblk_set_vars()
                _iqblk_set_getter()
                _iqblk_set_bandwidth_hz()
                _iqblk_set_record_length()
            - rsa306b_iqblk_user.cpp
                iqblk_acquire_data()
                iqblk_make_csv()
                _iqblk_get_iq_data()
                _iqblk_get_iq_data_cplx()
                _iqblk_get_iq_data_deinterleaved()

        "./program_core/rsa306b/rsa306_IQSTREAM/"
            - rsa306b_iqstream_struct.h
                rsa306b_iqstream_struct
            - rsa306b_iqstream_print_init_check.cpp
                print_iqstream()
                _iqstream_init()
                _iqstream_bitcheck()
            - rsa306b_iqstream_copy.cpp
                _iqstream_copy_vars()
                _iqstream_copy_acqStatus_message()
                _iqstream_copy_bandwidth()
                _iqstream_copy_bandwidth_max()
                _iqstream_copy_bandwidth_min()
                _iqstream_copy_sample_rate()
                _iqstream_copy_fileinfo_type() 
                _iqstream_copy_is_enabled()       
                _iqstream_copy_pairs_copied()   
                _iqstream_copy_info_type() 
                _iqstream_copy_cplx32_v()
                _iqstream_copy_cplxInt16_v()
                _iqstream_copy_cplxInt32_v()
                _iqstream_copy_pairs_max()
                _iqstream_copy_record_time_ms()
                _iqstream_copy_filename_base()
                _iqstream_copy_suffix_control()
                _iqstream_copy_buffer_multiplier()
                _iqstream_copy_destination_select()
                _iqstream_copy_datatype_select()
            - rsa306b_iqstream_get.cpp
                _iqstream_get_vars()
                _iqstream_get_max_acq_bandwidth()
                _iqstream_get_min_acq_bandwidth()
                _iqstream_get_acq_parameters()
                _iqstream_get_disk_fileinfo()
                _iqstream_get_enabled()
                _iqstream_get_iq_data_buffer_size()
            - rsa306b_iqstream_set.cpp
                iqstream_set_vars()
                _iqstream_set_vars()
                _iqstream_set_acq_bandwidth()
                _iqstream_set_disk_file_length()
                _iqstream_set_disk_filename_base()
                _iqstream_set_filename_suffix()
                _iqstream_set_iq_data_buffer_size()
                _iqstream_set_output_configuration()
            - rsa306b_iqstream_user.cpp
                iqstream_acquire_data()                   
                iqstream_make_csv()
                iqstream_clear_sticky()
            - rsa306b_iqstream_acquire.cpp
                _iqstream_acquire_data_to_file()
                _iqstream_acquire_data_direct_cplx32_v()
                _iqstream_acquire_data_direct_cplxInt16_v()
                _iqstream_acquire_data_direct_cplxInt32_v()

        "./program_core/rsa306b/rsa306_REFTIME/"
            - rsa306b_reftime_struct.h
                rsa306b_reftime_struct
                reftime_type
            - rsa306b_reftime_print_init.cpp
                print_reftime()
                _reftime_init()
            - rsa306b_reftime_copy.cpp
                _reftime_copy_vars()
                _reftime_copy_current()
                _reftime_copy_start()
                _reftime_copy_helper()
                _reftime_copy_dts()
                _reftime_copy_running_duration()
                _reftime_copy_source_select()
                _reftime_copy_timestamp_rate()
            - rsa306b_reftime_get.cpp
                _reftime_get_vars()
                _reftime_get_current()
                _reftime_get_start()
                _reftime_get_running_duration()
                _reftime_get_source_select()
                _reftime_get_timestamp_rate()
            - rsa306b_reftime_user.cpp
                reftime_reset()
                reftime_get_vars()
                reftime_timestamp_2_time()
                reftime_time_2_timestamp()
                _reftime_make_dts()
            
        "./program_core/rsa306b/rsa306_SPECTRUM/"
            - rsa306b_spectrum_struct.h
                rsa306b_spectrum_struct
            - rsa306b_spectrum_init_default.cpp
                spectrum_default()
                _spectrum_default()
                _spectrum_init()
            - rsa306b_spectrum_print.cpp
                print_spectrum()
                _print_spectrum_traces_long()
                _print_spectrum_traces_compact()
            - rsa306b_spectrum_copy.cpp
                _spectrum_copy_vars()
                _spectrum_copy_is_enabled_measurement()
                _spectrum_copy_settings_type()
                _spectrum_copy_limits_type()
                _spectrum_copy_trace_points_aquired()
                _spectrum_copy_array_frequency()
                _spectrum_copy_is_enabled_trace()
                _spectrum_copy_traces_select()
                _spectrum_copy_detectors_select()
                _spectrum_copy_trace_info_type()
                _spectrum_copy_array_power()
                _spectrum_copy_peak_index()
            - rsa306b_spectrum_get.cpp
                _spectrum_get_vars()
                _spectrum_get_is_enabled_measurement()
                _spectrum_get_limits_type()
                _spectrum_get_settings_type()
                _spectrum_get_trace_info_type()
                _spectrum_get_trace_type()
            - rsa306b_spectrum_set.cpp
                spectrum_set_vars()
                _spectrum_set_vars()
                _spectrum_set_is_enabled_measurement()
                _spectrum_set_settings_type()
                _spectrum_set_trace_type()
            - rsa306b_spectrum_user.cpp
                spectrum_aquire()
                spectrum_find_peak_index()
                spectrum_write_csv()
                _spectrum_make_array_frequency()

        "./program_core/rsa306b/rsa306_TRIG/"
            - rsa306b_trig_struct.h
                rsa306b_trig_struct
            - rsa306b_trig_print_init.cpp
                print_trig()
                _trig_init()
            - rsa306b_trig_copy.cpp
                _trig_copy_vars()
                _trig_copy_if_power_level()
                _trig_copy_mode_select()
                _trig_copy_position_percent()
                _trig_copy_source_select()
                _trig_copy_transition_select()
            - rsa306b_trig_get.cpp
                _trig_get_vars()
                _trig_get_if_power_level()
                _trig_get_mode_select()
                _trig_get_position_percent()
                _trig_get_source_select()
                _trig_get_transition_select()
            - rsa306b_trig_set.cpp
                _trig_set_vars()
                _trig_set_if_power_level()
                _trig_set_mode_select()
                _trig_set_position_percent()
                _trig_set_source_select()
                _trig_set_transition_select()
            - rsa306b_trig_user.cpp
                trig_set_vars()
                trig_force()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

        // INSERT POINTS: device_connect(), _init_everything(), print_everything(), get_everything(), print_constants()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

    functions used, by API group:

        Alignment
            ALIGN_GetAlignmentNeeded()
            ALIGN_GetWarmupStatus()
            ALIGN_RunAlignment()

        Audio
            AUDIO_SetFrequencyOffset()
            AUDIO_GetFrequencyOffset()
            AUDIO_GetEnable()
            AUDIO_GetData()
            AUDIO_GetMode()
            AUDIO_GetMute()
            AUDIO_GetVolume()
            AUDIO_SetMode()
            AUDIO_SetMute()
            AUDIO_SetVolume()
            AUDIO_Start()
            AUDIO_Stop()

        Configure
            GetCenterFreq()
            GetFrequecnyReferenceSource()
            GetMaxCenterFreq()
            GetMinCenterFreq()
            GetReferenceLevel()
            Preset()
            SetCenterFreq()
            SetFrequencyReferenceSource()
            SetReferenceLevel()

        Device 
            DEVICE_Connect()
            DEVICE_Disconnect()
            DEVICE_GetEnable()
            DEVICE_GetErrorString()
            DEVICE_GetInfo()
            DEVICE_GetOverTemperatureStatus()
            DEVICE_PrepareForRun()
            DEVICE_Reset()
            DEVICE_Run()
            DEVICE_Search()
            DEVICE_StartFrameTransfer()
            DEVICE_Stop()

        DPX
            DPX_Configure()
            DPX_FinishFrameBuffer()
            DPX_GetEnable()
            DPX_GetFrameBuffer()
            DPX_GetFrameInfo()
            DPX_GetRBWRange()
            DPX_GetSettings()
            DPX_GetSogramHiResLine()
            DPX_GetSogramHiResLineCountLatest()
            DPX_GetSogramHiResLineTimestamp()
            DPX_GetSogramHiResLineTriggered()
            DPX_GetSogramSettings()
            DPX_IsFrameBufferAvailable()
            DPX_Reset()
            DPX_SetEnable()
            DPX_SetParameters()
            DPX_SetSogramParameters()
            DPX_SetSogramTraceType()
            DPX_SetSpectrumTraceType()
            DPX_WaitForReady()
            
        GNSS # not used, only the RSA500/600 has position data

        IF Streaming
            IFSTREAM_GetActiveStatus()
            IFSTREAM_GetAcqParameters()
            IFSTREAM_GetEQParameters()
            IFSTREAM_GetIFData()
            IFSTREAM_GetIFDataBufferSize()
            IFSTREAM_GetIFFrames()
            IFSTREAM_GetScalingParameters()
            IFSTREAM_SetDiskFileCount()
            IFSTREAM_SetDiskFileLength()
            IFSTREAM_SetDiskFilenameBase()
            IFSTREAM_SetDiskFilenameSuffix()
            IFSTREAM_SetDiskFilePath()
            IFSTREAM_SetEnable()
            IFSTREAM_SetOutoutConfiguration()

        IQ Block
            IQBLK_GetAcqInfo()
            IQBLK_AcquireIQData()
            IQBLK_GetIQBandwidth()
            IQBLK_GetIQData()
            IQBLK_GetIQDataCplx()
            IQBLK_GetIQDataDeinterleaved()
            IQBLK_GetRecordLength()
            IQBLK_GetIQSampleRate()
            IQBLK_GetMaxIQBandwidth()
            IQBLK_GetMaxIQRecordLength()
            IQBLK_GetMinIQBandwidth()
            IQBLK_SetIQBandwidth()
            IQBLK_SetIQRecordLength()
            IQBLK_WaitForIQDataReady()

        IQ Streaming
            IQSTREAM_GetMaxAcqBandwidth()
            IQSTREAM_GetMinAcqBandwidth()
            IQSTREAM_ClearAcqStatus()
            IQSTREAM_GetAcqParameters()
            IQSTREAM_GetDiskFileInfo()
            IQSTREAM_GetDiskFileWriteStatus()
            IQSTREAM_GetEnable()
            IQSTREAM_GetIQData()
            IQSTREAM_GetIQDataBufferSize()
            IQSTREAM_SetAcqBandwidth()
            IQSTREAM_SetDiskFileLength()
            IQSTREAM_SetDiskFilenameBase()
            IQSTREAM_SetDiskFilenameSuffix()
            IQSTREAM_SetDataBufferSize()
            IQSTREAM_SetOutputConfiguration()
            IQSTREAM_Start()
            IQSTREAM_Stop()
            IQSTREAM_WaitForIQDataReady()

        Playback

        Power # not used, only for the RSA500 series

        Spectrum
            SPECTRUM_AquireTrace()
            SPECTRUM_GetEnable()
            SPECTRUM_GetLimits()
            SPECTRUM_GetSettings()
            SPECTRUM_GetTrace()
            SPECTRUM_GetTraceInfo()
            SPECTRUM_GetTraceType()
            SPECTRUM_SetDefault()
            SPECTRUM_SetEnable()
            SPECTRUM_SetSettings()
            SPECTRUM_SetTraceType()
            SPECTRUM_WaitForTraceReady()

        Time
            REFTIME_GetReferenceTime()
            REFTIME_GetCurrentTime()
            REFTIME_GetIntervalSinceRefTimeSet()
            REFTIME_GetReferenceTimeSource()
            REFTIME_GetTimeFromTimestamp()
            REFTIME_GetTimestampFromTime()
            REFTIME_GetTimestampRate()

        Tracking # not used, only for RSA500/600 series

        Trigger
            TRIG_ForceTrigger()
            TRIG_GetIFPowerTriggerLevel()
            TRIG_GetTriggerMode()
            TRIG_GetTriggerPositionPercent()
            TRIG_GetTriggerSource()
            TRIG_GetTriggerTransition()
            TRIG_SetIFPowerTriggerLevel()
            TRIG_SetTriggerMode()
            TRIG_SetTriggerPositionPercent()
            TRIG_SetTriggerSource()
            TRIG_SetTriggerTransition()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

    TODO :
        # the IFSTREAM and IQSTREAM are the best places to send direct to client
        # bring in the "*.siq" class
        # bring in the spectrogram handler
        # DEBUG logger .txt
        # helper classes by composition
        # keep building and testing the API function groups
        # time series, spectrogram, and other user requests
        # worker thread, request thread --> mutex control
        # there should be a restructing of all the functions
        # clean the flow of this class in V3
        # try out std::function instead of the 3/4 buffer
        # clean up the constants and controlls
        # CSV --> HDF5 format {or apache parquett?}
        # take out c-style code and use c++
        # catch all return values...
        # union wrapping annonymous struct for memcopy of static buffers
        # space the source code?
        # resolve the bitcheck string...
        # version3, refine more
            - will need a few name spaces
            - decodes, batch processes, bytes in file...those are all common, see if you can combine
            - stand alone...stand together {balance}
            - master error code, enum with isolated char** lookup
            - isolate the structs, always pass the objs....return something as an option
            - pull out the constants class, make it applicable to everything
            - need value returning functions with own enum...or struct with an int + string
            - refine the triggering capabilities [2 unkown API functions + a pure force through spectrum, IQ, IF]
            - the reset can probably be handled with a try-throw-catch and some sleep time
            - forget the "wchar_t" handlers...just use STL strings and wstrings, do for char* also
            - breakout the inits into each type + init_vars()...?
            - API group 'DEVICE' should have user interface reduced...reduce user interface as much as possible
            - junk/archive everything and leave MVP in top level
            - lots of uneeded constants, remove and consolidate
            - center source code "=", frame paramters of API calls (), like other functions
            - document the group structs better [user, setter, getter, ...every category] + API info
            - data directory to the source, reduce to "inputs" and "outputs"
            - setters pass public to API, take out copying unless API getter not possible ? must be same flow
            - user only has 1 set point, so 1 stop call is all that is needed...
            - constants include defualt values
            - constants enforce naming convention to match API group
            - struct variables enforce naming convention to match API function association
            - debug log?
            - clean the file handler objects, output something more efficient than CSV
            - parameterize file handlers with path/name (don't rely on struct set "3/4" buffer)
            - the 3/4 buffer should only be applied to API variables
            !!! unit tests are absolute, every object capability is stimulated

        # DPX
        # PLAYBACK
*/

#ifndef H_rsa306b_class
#define H_rsa306b_class


#include "rsa306b_struct.h"    
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class rsa306b_class
{
    public :
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        rsa306b_struct vars;                  // public variables
        //rsa306b_constants_class constants;    // important constants for the spectrum analyzer
        rsa306b_constants constants;    // important constants for the spectrum analyzer

    // general purpose
        rsa306b_class();                                             // constructor
        ~rsa306b_class();                                            // destructor
        void get_everything();                                       // updates user's variable struct
        void print_everything();                                     // prints all variables, using the private struct
        void print_constants();                                      // prints the constant variables of the class
        void print_gp();                                             // prints the "general purpose" variables, using the private struct
        void gp_wchar_2_char(wchar_t* source, char* destination);    // utility, as needed

    // API group "ALIGN"
        void print_align();              // prints the "ALIGN" variables to stdout, using the private struct
        void align_check_is_needed();    // see if the spectrum analyzer needs to be aligned
        void align_check_is_warmed();    // see if the spectrum analyser is warmed-up
        void align_run();                // execute the device alignment procedure
    
    // API group "AUDIO"
        void print_audio();           // prints the "AUDIO" variables to stdout, using the private struct
        void audio_set_vars();        // user changes "AUDIO" variables in public struct, then calls to set new values
        void audio_acquire_data();    // audio demodulation produces data, automatic start/stop

    // API group "CONFIG"
        void print_config();       // prints the "CONFIG" variables to stdout, using the private struct
        void config_preset();      // the default "preset" conditions are applied to the spectrum analyzer
        void config_set_vars();    // user changes "CONFIG" variables in public struct, then calls to set new values

    // API group "DEVICE"
        void print_device();                   // prints the "DEVICE" variables to stdout, using the private struct
        void device_connect();                 // searches and connects to a device, must call to use spectum analyzer
        void device_disconnect();              // disconnect from the spectrum analyzer
        void device_run();                     // the spectrum analyzer runs, configuration should have been applied
        void device_stop();                    // stop aquiring data
        void device_reset();                   // disconnects, makes spectrum analyzer restart, use sparingly
        void device_check_run_state();         // query run state of the spectrum analyzer
        void device_check_temperature();       // see if the spectrum analyzer it too hot
        void device_check_event();             // determine if an event occurred {0: ADC overange, 1: trigger}
        void device_prepare_for_run();         // make the device ready to run / trigger
        void device_start_frame_transfer();    // initiates run, data transfer begins
    
    // API group "IFSTREAM"
        void print_ifstream();                 // prints the "IFSTREAM" variables to stdout, using the private struct
        void ifstream_set_vars();              // user changes "IFSTREAM" variables in public struct, then calls to set new values
        void ifstream_record_file();           // output "*.r3f" file is produced according to the user settings
        void ifstream_acquire_adc_data();      // gets the entire ADC buffer, user struct updated
        void ifstream_acquire_adc_frames();    // gets the entire ADC buffer, by frame, user struct updated

    // API group "IQBLK"
        void print_iqblk();                           // prints the "IQBLK" variables to stdout, using the private struct
        void iqblk_set_vars();                        // user changes "IQBLK" variables in public struct, then calls to set new values
        void iqblk_acquire_data();                    // the "IQBLK" data is acquired into "vars.iqblk.cplx32_v"
        void iqblk_make_csv(char* file_path_name);    // call after acquring data, "*.csv" is produced
        // const std::string& more memory efficient
        // validation-->   try, catch, throw
        // always return something (fail silently is bad)

    // API group "IQSTREAM"
        void print_iqstream();                           // prints the "IQSTREAM" variables to stdout, using the private struct
        void iqstream_set_vars();                        // user changes "IQSTREAM" variables in public struct, then calls to set new values
        void iqstream_acquire_data();                    // the "IQSTREAM" data is acquired into "vars.iqstream.cplx*_v", based on setting
        void iqstream_make_csv(char* file_path_name);    // call after acquring data, "*.csv" is produced
        void iqstream_clear_sticky();                    // clears the sticky bits of "acqStatus"
    
    // API group "REFTIME"
        void print_reftime();               // prints the "REFTIME" variables to stdout, using the private struct
        void reftime_reset();               // resets start time of the device
        void reftime_get_vars();            // gets all the "REFTIME" variables
        void reftime_timestamp_2_time();    // set "vars.reftime.helper.timestamp", then call, updates time_t and uint64_t
        void reftime_time_2_timestamp();    // set "vars.reftime.helper.seconds  and nanos", then call, updates timestamp
    
    // API group "SPECTRUM"
        void print_spectrum();                            // prints the "SPECTRUM" variables to stdout, using the private struct
        void spectrum_set_vars();                         // user changes "SPECTRUM" variables in public struct, then calls to set new values
        void spectrum_default();                          // apply API default spectrum settings
        void spectrum_aquire();                           // gets all active traces
        void spectrum_find_peak_index();                  // gets peak index of active traces
        void spectrum_write_csv();                        // dumps trace data into a CSV file

    // API group "TRIG"
        void print_trig();       // prints the "TRIG" variables to stdout, using the private struct
        void trig_set_vars();    // user changes "TRIG" variables in public struct, then calls to set new values
        void trig_force();       // a trigger event is forced, user calls "device_run()" before and "device_stop()" after

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
    private : 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        rsa306b_struct _vars;    // private variables, structured
        FILE* _fptr_write;       // helper file pointer for writing data

    // general purpose
        void _init_everything();    // initialize all class variables
        void _gp_init();            // initialize the "general purpose" variables
        // monitor the program
        void _gp_confirm_api_status();         // called to check error conditions after API function calls     
        void _gp_confirm_call_status();        // called to check error conditions in the class
        int _gp_confirm_return();              // called to provide a return value corresponding to the API status
        void _gp_confirm_aquisition_code();    // bit-checks status code after a data aquisition {change in v3}
        // copiers, private --> public
        void _gp_copy_vars();
        void _gp_copy_helper();
        void _gp_copy_holder();
        void _gp_copy_call_status();
        void _gp_copy_api_status();
        void _gp_copy_acquisition_code();
        void _gp_copy_acquistion_message();
    
    // API group "AUDIO"
        void _audio_init();
        // copiers, private --> public
        void _audio_copy_vars();
        void _audio_copy_is_demodulating();
        void _audio_copy_is_mute();
        void _audio_copy_frequecny_offset_hz();
        void _audio_copy_volume();
        void _audio_copy_demodulation_select();
        void _audio_copy_data();
        void _audio_copy_data_samples_requested();
        void _audio_copy_data_samples_acquired();
        // getters, API is used
        void _audio_get_vars();                     // calls the getters
        void _audio_get_is_demodulating();          // determine if demodulation is occuring
        void _audio_get_is_mute();                  // query mute status
        void _audio_get_frequency_offset_hz();      // query frequency offset
        void _audio_get_volume();                   // query volume setting
        void _audio_get_demodulation_select();      // query demodulation mode
        void _audio_get_data();                     // get requested audio samples
        // setters, API is used
        int _audio_set_vars();                      // calls the setters
        int _audio_set_is_mute();                   // control speakers
        int _audio_set_frequency_offset_hz();       // set carrier frequency
        int _audio_set_volume();                    // control speaker volume
        int _audio_set_demodulation_select();       // control demodulation mode
        int _audio_set_data_samples_requested();    // sets a non-API, used to call API

    // API group "ALIGN"
        void _align_init();
        // copiers, private --> public
        void _align_copy_vars();
        void _align_copy_is_needed();
        void _align_copy_is_warmed();
        // getters, API is used
        void _align_get_vars();         // calls the getters
        void _align_get_is_needed();    // query "alignment is needed", with API
        void _align_get_is_warmed();    // query "device is warmed-up", with API

    // API group "CONFIG"
        void _config_init();
        // copiers, private --> public
        void _config_copy_vars();
        void _config_copy_reference_level_dbm();
        void _config_copy_center_frequency_hz();
        void _config_copy_min_center_frequency_hz();
        void _config_copy_max_center_frequency_hz();
        void _config_copy_external_reference_frequency_hz();
        void _config_copy_frequency_reference_source_select();
        // getters, API is used
        void _config_get_vars();
        void _config_get_reference_level_dbm();
        void _config_get_center_frequency_hz();
        void _config_get_min_center_frequency_hz();
        void _config_get_max_center_frequency_hz();
        void _config_get_external_reference_frequency_hz();
        void _config_get_frequency_reference_source_select();
        // setters, API is used
        int _config_set_vars();
        int _config_set_reference_level_dbm();
        int _config_set_center_frequency_hz();
        int _config_set_external_reference_frequency_source_select();

    // API group "DEVICE"
        void _device_init();
        // copiers, private --> public
        void _device_copy_vars();
        void _device_copy_is_connected();
        void _device_copy_is_over_temperature();
        void _device_copy_is_running();
        void _device_copy_event_occured();
        void _device_copy_error_string();
        void _device_copy_id();
        void _device_copy_event_id();
        void _device_copy_info_type();
        void _device_copy_event_timestamp();
        // getters, API is used
        void _device_get_vars();                   // calls the getters
        void _device_get_is_running();             // query the run state
        void _device_get_error_string();           // gets the API error code based on return status
        void _device_get_info_type();              // fill strings with device information
        void _device_get_is_over_temperature();    // query temerature warning
        void _device_get_event();                  // query an event of interest

    // API group "IFSTREAM"
        void _ifstream_init();
        // copiers, private --> public
        void _ifstream_copy_vars();
        void _ifstream_copy_file_name_suffix();
        void _ifstream_copy_file_path();
        void _ifstream_copy_file_name_base();
        void _ifstream_copy_file_length_ms();
        void _ifstream_copy_file_count();
        void _ifstream_copy_output_configuration_select();
        void _ifstream_copy_is_enabled_adc();
        void _ifstream_copy_is_active();
        void _ifstream_copy_if_data();
        void _ifstream_copy_if_data_length();
        void _ifstream_copy_data_info_type();
        void _ifstream_copy_adc_data_v();
        void _ifstream_copy_if_frames();
        void _ifstream_copy_frame_bytes();
        void _ifstream_copy_number_of_frames();
        void _ifstream_copy_framed_adc_data_v();
        void _ifstream_copy_eq_parameters();
        void _ifstream_copy_points_in_equalization_buffer();
        void _ifstream_copy_eq_frequency_v();
        void _ifstream_copy_eq_amplitude_v();
        void _ifstream_copy_eq_phase_v();
        void _ifstream_copy_scaling_parameters();
        void _ifstream_copy_scale_factor();
        void _ifstream_copy_scale_frequency();
        void _ifstream_copy_acq_parameters();
        void _ifstream_copy_if_bandwidth_hz();
        void _ifstream_copy_samples_per_second();
        void _ifstream_copy_if_center_frequency();
        void _ifstream_copy_buffer_size();
        void _ifstream_copy_buffer_size_bytes();
        void _ifstream_copy_number_of_samples();
        // getters, uses API
        void _ifstream_get_vars();
        void _ifstream_get_is_active();
        void _ifstream_get_acq_parameters();
        void _ifstream_get_buffer_size();
        void _ifstream_get_eq_parameters();
        void _ifstream_get_scaling_parameters();
        // setters, uses API
        void _ifstream_set_vars();
        void _ifstream_set_file_name_suffix();
        void _ifstream_set_file_path();
        void _ifstream_set_file_name_base();
        void _ifstream_set_file_length_ms();
        void _ifstream_set_file_count();
        void _ifstream_set_output_configuration_select();
        void _ifstream_set_is_enabled_adc();

    // API group "IQBLK"
        void _iqblk_init();
        void _iqblk_bitcheck();
        // copiers, private --> public
        void _iqblk_copy_vars();
        void _iqblk_copy_getter();
        void _iqblk_copy_actual_buffer_samples();
        void _iqstream_copy_sample_pairs_requested();
        void _iqblk_copy_cplx32_v();
        void _iqblk_copy_acq_info_type();
        void _iqblk_copy_bitcheck();
        void _iqblk_copy_sample_rate();
        void _iqblk_copy_bandwidth_hz();
        void _iqblk_copy_max_bandwidth_hz();
        void _iqblk_copy_min_bandwidth_hz();
        void _iqblk_copy_record_length();
        void _iqblk_copy_max_record_length();
        // getters, uses API
        void _iqblk_get_vars();
        void _iqblk_get_acq_info_type();
        void _iqblk_get_sample_rate();
        void _iqblk_get_bandwidth_hz();
        void _iqblk_get_max_bandwidth_hz();
        void _iqblk_get_min_bandwidth_hz();
        void _iqblk_get_max_record_length();
        void _iqblk_get_record_length();
        // setters
        void _iqblk_set_vars();
        void _iqblk_set_getter();           // does not use API
        void _iqblk_set_bandwidth_hz();
        void _iqblk_set_record_length();
        // data acquisiton, uses API
        void _iqblk_get_iq_data();
        void _iqblk_get_iq_data_cplx();
        void _iqblk_get_iq_data_deinterleaved();

    // API group "IQSTREAM"
        void _iqstream_init();
        void _iqstream_bitcheck(uint32_t acqStatus);
        // copiers, private --> public
        void _iqstream_copy_vars();
        void _iqstream_copy_acqStatus_message();
        void _iqstream_copy_bandwidth();
        void _iqstream_copy_bandwidth_max();
        void _iqstream_copy_bandwidth_min();
        void _iqstream_copy_sample_rate();
        void _iqstream_copy_fileinfo_type();  
        void _iqstream_copy_is_enabled();           
        void _iqstream_copy_pairs_copied();    
        void _iqstream_copy_info_type();    
        void _iqstream_copy_cplx32_v();
        void _iqstream_copy_cplxInt16_v();
        void _iqstream_copy_cplxInt32_v();
        void _iqstream_copy_pairs_max();
        void _iqstream_copy_record_time_ms();
        void _iqstream_copy_filename_base();
        void _iqstream_copy_suffix_control();
        void _iqstream_copy_buffer_multiplier();
        void _iqstream_copy_destination_select();
        void _iqstream_copy_datatype_select(); 
        // getters, uses API
        void _iqstream_get_vars();
        void _iqstream_get_max_acq_bandwidth();      // updates "bandwidth_min"
        void _iqstream_get_min_acq_bandwidth();      // updates "bandwidth_max"
        void _iqstream_get_acq_parameters();         // updates "bandwidth" and "sample_rate"
        void _iqstream_get_disk_fileinfo();          // updates "fileinfo_type"
        void _iqstream_get_enabled();                // updates "is_enabled"
        void _iqstream_get_iq_data_buffer_size();    // updates "pairs max"
        // setters, uses API
        void _iqstream_set_vars();
        void _iqstream_set_acq_bandwidth();
        void _iqstream_set_disk_file_length();
        void _iqstream_set_disk_filename_base();
        void _iqstream_set_filename_suffix();
        void _iqstream_set_iq_data_buffer_size();
        void _iqstream_set_output_configuration();
        // data acquisiton, uses API
        void _iqstream_acquire_data_to_file();     
        void _iqstream_acquire_data_direct_cplx32_v();
        void _iqstream_acquire_data_direct_cplxInt16_v();
        void _iqstream_acquire_data_direct_cplxInt32_v();

    // API group "REFTIME"
        void _reftime_init();
        void _reftime_make_dts();  // makes a date time stamp using the current time
        // copiers, private --> public
        void _reftime_copy_vars();
        void _reftime_copy_current();
        void _reftime_copy_start();
        void _reftime_copy_helper();
        void _reftime_copy_dts();
        void _reftime_copy_running_duration();
        void _reftime_copy_source_select();
        void _reftime_copy_timestamp_rate();
        // getters, uses API
        void _reftime_get_vars();
        void _reftime_get_current();
        void _reftime_get_start();
        void _reftime_get_running_duration();
        void _reftime_get_source_select();
        void _reftime_get_timestamp_rate();
    
    // API group "SPECTRUM"
        void _spectrum_default();
        void _spectrum_init();
        void _print_spectrum_traces_long();
        void _print_spectrum_traces_compact();
        void _spectrum_make_array_frequency();
        // copiers, private --> public
        void _spectrum_copy_vars();
        void _spectrum_copy_is_enabled_measurement();
        void _spectrum_copy_settings_type();
        void _spectrum_copy_limits_type();
        void _spectrum_copy_array_frequency();
        void _spectrum_copy_trace_points_aquired(int trace_index);
        void _spectrum_copy_is_enabled_trace(int trace_index);
        void _spectrum_copy_traces_select(int trace_index);
        void _spectrum_copy_detectors_select(int trace_index);
        void _spectrum_copy_trace_info_type(int trace_index);
        void _spectrum_copy_array_power(int trace_index);
        void _spectrum_copy_peak_index(int trace_index);
        // getters, uses API
        void _spectrum_get_vars();
        void _spectrum_get_is_enabled_measurement();
        void _spectrum_get_limits_type();
        void _spectrum_get_settings_type();
        void _spectrum_get_trace_info_type(int trace_index);
        void _spectrum_get_trace_type(int trace_index);
        // setters, uses API
        void _spectrum_set_vars();
        void _spectrum_set_is_enabled_measurement();
        void _spectrum_set_settings_type();
        void _spectrum_set_trace_type();

    // API group "TRIG"
        void _trig_init();
        // copiers, private --> public
        void _trig_copy_vars();
        void _trig_copy_if_power_level();
        void _trig_copy_mode_select();
        void _trig_copy_position_percent();
        void _trig_copy_source_select();
        void _trig_copy_transition_select();
        // getters, API is used
        void _trig_get_vars();
        void _trig_get_if_power_level();
        void _trig_get_mode_select();
        void _trig_get_position_percent();
        void _trig_get_source_select();
        void _trig_get_transition_select();
        // setters, API is used
        int _trig_set_vars();
        int _trig_set_if_power_level();
        int _trig_set_mode_select();
        int _trig_set_position_percent();
        int _trig_set_source_select();
        int _trig_set_transition_select();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif


////////~~~~~~~~END>  rsa306b_class.h
