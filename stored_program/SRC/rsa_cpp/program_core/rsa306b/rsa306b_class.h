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
    a utility object is composed into this class: 
        "cutil"
    
    API groups used:
        ALIGN
        AUDIO
        CONFIG
        DEVICE
        DPX
        IFSTREAM
        IQBLK
        IQSTREAM
        PLAYBACK
        REFTIME
        SPECTRUM
        TRIG

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

    Class source files, 
    
        "./program_core/rsa306b"
            - rsa306b_struct.h
                struct rsa306b_struct

        "./program_core/rsa306b/rsa306_GP/"
            - rsa306b_class.cpp
                rsa306b_class()
                ~rsa306b_class()
                clear()
                get_everything()
                _init_everything()
                _gp_init()
            - rsa306b_gp_confirm.cpp
                get_api_status_number()
                get_api_status_string()
                get_api_status 
                set_api_status()      
                _report_api_status()
            - rsa306b_gp_print.cpp
                print_everything()
                print_constants()
        
        "./program_core/rsa306b/rsa306_ALIGN"
            - rsa306b_align_struct.h
                rsa306b_align_struct
            - rsa306b_align_init.cpp
                _align_init()
            - rsa306b_align_print.cpp
                align_print()
            - rsa306b_align_copy.cpp
                _align_copy_vars()
                _align_copy_is_needed()
                _align_copy_is_warmed()
            - rsa306b_align_get.cpp
                _align_get_vars()       
                _align_get_is_needed()
                _align_get_is_warmed()
            - rsa306b_align_user.cpp
                align_run()
                align_check_is_needed()
                align_check_is_warmed()
        
        "./program_core/rsa306b/rsa306_AUDIO"
            - rsa306b_audio_struct.h
                rsa306b_audio_struct
            - rsa306b_audio_init.cpp
                _audio_init()
            - rsa306b_audio_print.cpp
                audio_print()
            - rsa306b_audio_copy.cpp
                _audio_copy_vars()
                _audio_copy_is_demodulating()
                _audio_copy_is_mute()
                _audio_copy_frequecny_offset_hz()
                _audio_copy_volume()
                _audio_copy_demodulation_select()
                _audio_copy_data_v()
                _audio_copy_data_samples_requested()
                _audio_copy_data_samples_acquired()
            - rsa306b_audio_get.cpp
                audio_set_vars()
                _audio_get_vars()
                _audio_get_is_demodulating()
                _audio_get_is_mute()
                _audio_get_frequency_offset_hz()
                _audio_get_volume()
                _audio_get_demodulation_select()
            - rsa306b_audio_set.cpp
                _audio_set_vars()
                _audio_set_is_mute()
                _audio_set_frequency_offset_hz()
                _audio_set_volume()
                _audio_set_demodulation_select()
                _audio_set_data_samples_requested()
            - rsa306b_audio_user.cpp
                audio_acquire_data()
                audio_start()
                audio_stop()
            - rsa306b_audio_write_csv.cpp
                audio_write_csv()

        "./program_core/rsa306b/rsa306_CONFIG/"
            - rsa306b_config_struct.h
                rsa306b_config_struct    
            - rsa306b_config_init.cpp
                _config_init()
            - rsa306b_config_print.cpp
                print_config()
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
                config_set_vars()
                _config_set_vars()
                _config_set_reference_level_dbm()
                _config_set_center_frequency_hz()
                _config_set_external_reference_frequency_source_select()
            - rsa306b_config_user.cpp
                config_preset()

        "./program_core/rsa306b/rsa306_DEVICE/"
            - rsa306b_device_struct.h
                rsa306b_device_struct
            - rsa306b_device_init.cpp
                _device_init()
            - rsa306b_device_print.cpp
                device_print()
            - rsa306b_device_copy.cpp
                _device_copy_vars()
                _device_copy_is_connected()
                _device_copy_is_over_temperature()
                _device_copy_is_running()
                _device_copy_event_occured()
                _device_copy_api_status_message()
                _device_copy_id()
                _device_copy_event_id()
                _device_copy_info_type()
                _device_copy_event_timestamp()
            - rsa306b_device_get.cpp
                _device_get_vars()
                _device_get_is_running()
                _device_get_api_status_message()
                _device_get_info_type()
                _device_get_is_over_temperature()
                _device_get_event()
            - rsa306b_device_user_checker.cpp
                device_check_run_state()
                device_check_temperature()
                device_check_event()
            - rsa306b_device_user_connector.cpp
                device_connect()
                device_disconnect()
            - rsa306b_device_user_operator.cpp
                device_run()
                device_stop()
                device_reset()
                device_prepare_for_run()
                device_start_frame_transfer()
                
        "./program_core/rsa306b/rsa306_DPX/"
            - rsa306b_dpx_struct.h
                rsa306b_dpx_struct
            - rsa306b_

        "./program_core/rsa306b/rsa306_IFSTREAM/"
            - rsa306b_ifstream_struct.h
                rsa306b_ifstream_struct
            - rsa306b_ifstream_init.cpp
                _ifstream_init()
            - rsa306b_ifstream_print.cpp
                print_ifstream()
            - rsa306b_ifstream_copy.cpp
                _ifstream_copy_vars()
                _ifstream_copy_file_name_suffix()
                _ifstream_copy_file_path()
                _ifstream_copy_file_name_base()
                _ifstream_copy_file_length_max_ms()
                _ifstream_copy_file_count()         
                _ifstream_copy_output_destination_select()
                _ifstream_copy_is_active()  
                _ifstream_copy_if_data_length()
                _ifstream_copy_data_info_type()          
                _ifstream_copy_adc_data_v()       
                _ifstream_copy_adc_tiggers_v()   
                _ifstream_copy_frame_bytes()
                _ifstream_copy_number_of_frames()
                _ifstream_copy_framed_adc_data_v()
                _ifstream_copy_points_in_equalization_buffer()
                _ifstream_copy_eq_frequency_v()
                _ifstream_copy_eq_amplitude_v()
                _ifstream_copy_eq_phase_v()
                _ifstream_copy_scale_factor()
                _ifstream_copy_scale_frequency()
                _ifstream_copy_if_bandwidth_hz()
                _ifstream_copy_samples_per_second()
                _ifstream_copy_if_center_frequency()
                _ifstream_copy_buffer_size_bytes()
                _ifstream_copy_buffer_samples()
                _ifstream_copy_acq_status_message()
            - rsa306b_ifstream_get.cpp
                _ifstream_get_vars()
                _ifstream_get_is_active()
                _ifstream_get_acq_parameters()
                _ifstream_get_buffer_size()
                _ifstream_get_eq_parameters()
                _ifstream_get_scaling_parameters()
            - rsa306b_ifstream_set.cpp
                ifstream_set_vars()
                _ifstream_set_vars()
                _ifstream_set_file_name_suffix()
                _ifstream_set_file_path()
                _ifstream_set_file_name_base()
                _ifstream_set_file_length_ms()
                _ifstream_set_file_count()
                _ifstream_set_output_configuration_select()
            - rsa306b_ifstream_user_acquire_adc_data.cpp
                 ifstream_acquire_adc_data()
            - rsa306b_ifstream_user_record_r3f.cpp
                ifstream_record_r3f()




            - rsa306b_ifstream_user.cpp
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
            - rsa306b_trig_init.cpp
                _trig_init()
            - rsa306b_trig_print.cpp
                trig_print()
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

        // INSERT POINTS: device_connect(), _init_everything(), print_everything(), get_everything()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
*/

#ifndef H_rsa306b_class
#define H_rsa306b_class


#include "rsa306b_struct.h" 
#include "../common_utility/common_utility.h"   
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class rsa306b_class
{
    public :
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        rsa306b_class ();    // constructor
        ~rsa306b_class();    // destructor

        rsa306b_struct vars;      // public variables, structured in API layers, by group, updated during 3/4 duplex
        common_utility cutil;     // public class instance, by composition, for "common utility" needs

    // general purpose
        CODEZ clear           ();    // re-initializes the instnace, connection is terminated
        CODEZ apply_defaults  ();    // connects if unconnected, applies default settings, and updates structs
        CODEZ get_everything  ();    // updates user's variable struct after calling all API getters
        CODEZ print_everything();    // prints all variables and constants using the private struct
        CODEZ print_vars      ();    // prints all variables and constants using the private struct
        CODEZ print_constants ();    // prints the constant variables of the class
        // monitor the api status
        int                   get_api_status_number                     ();    // returns current RSA status code, casted to "int"
        char*                 get_api_status_string                     ();    // return assoicated message of the current RSA status code
        RSA_API::ReturnStatus get_api_status                            ();    // returns current RSA API status as original enum
        CODEZ                 set_api_status(RSA_API::ReturnStatus result);    // check and set API calls
        
    // API group "ALIGN"
        CODEZ align_print          ();    // prints the "ALIGN" variables to stdout, using the private struct
        CODEZ align_check_is_needed();    // see if the spectrum analyzer needs to be aligned
        CODEZ align_check_is_warmed();    // see if the spectrum analyser is warmed-up
        CODEZ align_run            ();    // execute the device alignment procedure
    
    // API group "AUDIO"
        CODEZ audio_print                        ();    // prints the "AUDIO" variables to stdout, using the private struct
        CODEZ audio_set_vars                     ();    // user changes "AUDIO" variables in public struct, then calls to set new values
        CODEZ audio_acquire_data                 ();    // audio demodulation produces data, automatic start/stop
        CODEZ audio_start                        ();    // user controls start of audio acquisition
        CODEZ audio_stop                         ();    // user controls stop of audio acquisition
        CODEZ audio_write_csv(char* file_path_name);    // call after acquring data, "*.csv" is produced
    
    // API group "CONFIG"
        CODEZ config_print   ();    // prints the "CONFIG" variables to stdout, using the private struct
        CODEZ config_preset  ();    // the default "preset" conditions are applied to the spectrum analyzer
        CODEZ config_set_vars();    // user changes "CONFIG" variables in public struct, then calls to set new values

    // API group "DEVICE"
        CODEZ device_print               ();    // prints the "DEVICE" variables to stdout, using the private struct
        CODEZ device_connect             ();    // searches and connects to a device, must call to use spectum analyzer
        CODEZ device_disconnect          ();    // disconnect from the spectrum analyzer
        CODEZ device_run                 ();    // the spectrum analyzer runs, configuration should have been applied
        CODEZ device_stop                ();    // stop aquiring data
        CODEZ device_reset               ();    // disconnects, makes spectrum analyzer restart, use sparingly
        CODEZ device_check_run_state     ();    // query run state of the spectrum analyzer
        CODEZ device_check_temperature   ();    // see if the spectrum analyzer it too hot
        CODEZ device_check_event         ();    // determine if an event occurred {0: ADC overange, 1: trigger}, user sets "event_id"
        CODEZ device_prepare_for_run     ();    // make the device ready to run, a trigger is set
        CODEZ device_start_frame_transfer();    // initiates run, data transfer begins
    
    // API group "DPX"
        CODEZ dpx_print                                 ();    // prints the "DPX" variables to stdout, using the private struct                                      
        CODEZ dpx_set_vars                              ();    // user changes "DPX" variables in public struct, then calls to set new values
        CODEZ dpx_acquire_data                          ();    // spectrum and sogram bitmaps are loaded into std::vector members
        CODEZ dpx_sogram_write_csv  (char* file_path_name);    // after acquiring, dump the sogram into a csv
        CODEZ dpx_spectrum_write_csv(char* file_path_name);    // after acquiring, dump the spectrum into a csv

    // API group "IFSTREAM"
        CODEZ ifstream_print                                     ();    // prints the "IFSTREAM" variables to stdout, using the private struct
        CODEZ ifstream_set_vars                                  ();    // user changes "IFSTREAM" variables in public struct, then calls to set new values
        CODEZ ifstream_record_r3f                                ();    // output "*.r3f" file is produced according to the user settings
        CODEZ ifstream_acquire_adc_data                          ();    // gets the entire ADC buffer, user struct updated
        CODEZ ifstream_acquire_adc_frames                        ();    // gets the entire ADC buffer, by frame, user struct updated
        CODEZ ifstream_check_acq_status                          ();    // updates vars.ifstream.data_info_type.acqStatus + message     
        CODEZ ifstream_write_data_csv        (char* file_path_name);    // call after acquring data, "*.csv" is produced for "adc_data_v"
        CODEZ ifstream_write_framed_csv      (char* file_path_name);    // call after acquring data, "*.csv" is produced for "framed_adc_data_v"
        CODEZ ifstream_write_equalization_csv(char* file_path_name);    // call after acquring data, "*.csv" is produced for equalization values

    // API group "IQBLK"
        CODEZ iqblk_print                       ();    // prints the "IQBLK" variables to stdout, using the private struct
        CODEZ iqblk_set_vars                    ();    // user changes "IQBLK" variables in public struct, then calls to set new values
        CODEZ iqblk_acquire_data                ();    // the "IQBLK" data is acquired into "vars.iqblk.cplx32_v"
        CODEZ iqblk_make_csv(char* file_path_name);    // call after acquring data, "*.csv" is produced

    // API group "IQSTREAM"
        CODEZ iqstream_print                                          ();    // prints the "IQSTREAM" variables to stdout, using the private struct
        CODEZ iqstream_set_vars                                       ();    // user changes "IQSTREAM" variables in public struct, then calls to set new values
        CODEZ iqstream_acquire_data                                   ();    // the "IQSTREAM" data is acquired into "vars.iqstream.cplx*_v", based on setting
        CODEZ iqstream_write_csv(char* file_path_name, bool use_default);    // call after acquring data, "*.csv" is produced
        CODEZ iqstream_clear_sticky                                   ();    // clears the sticky bits of "acqStatus"
    
    // API group "REFTIME"
        CODEZ reftime_print           ();    // prints the "REFTIME" variables to stdout, using the private struct
        CODEZ reftime_reset           ();    // resets start time of the device
        CODEZ reftime_get_vars        ();    // gets all the "REFTIME" variables
        CODEZ reftime_timestamp_2_time();    // set "vars.reftime.helper.timestamp", then call, updates time_t and uint64_t
        CODEZ reftime_time_2_timestamp();    // set "vars.reftime.helper.seconds  and nanos", then call, updates timestamp
    
    // API group "PLAYBACK"
        CODEZ playback_print   ();    // prints the "PLAYBACK" variables to stdout, using the private struct
        CODEZ playback_set_vars();    // user changes "PLAYBACK" variables in public struct, then calls to set new values
        CODEZ playback_execute ();    // playback of selected "*.r3f" file

    // API group "SPECTRUM"
        CODEZ spectrum_print                        ();    // prints the "SPECTRUM" variables to stdout, using the private struct
        CODEZ spectrum_set_vars                     ();    // user changes "SPECTRUM" variables in public struct, then calls to set new values
        CODEZ spectrum_default                      ();    // apply API default spectrum settings
        CODEZ spectrum_acquire_data                 ();    // gets all active traces
        CODEZ spectrum_find_peak_index              ();    // gets peak index of active traces
        CODEZ spectrum_write_csv(char* file_path_name);    // call after acquring data, "*.csv" is produced

    // API group "TRIG"
        CODEZ trig_print   ();    // prints the "TRIG" variables to stdout, using the private struct
        CODEZ trig_set_vars();    // user changes "TRIG" variables in public struct, then calls to set new values
        CODEZ trig_force   ();    // a trigger event is forced, user calls "device_run()" before and "device_stop()" after

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////        
    private : 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    rsa306b_struct _vars;    // private variables, structured in API layers, by group

    // general purpose
        FILE*                 _fp_write;         // file pointer for writing output data
        RSA_API::ReturnStatus _api_status;       // enum, most API functions return this
        char                  _helper[BUF_E];    // smaller cstring
        char                  _holder[BUF_F];    // large cstring
        CODEZ                 _init_everything                               ();    // initialize all class variables
        CODEZ                 _gp_init                                       ();    // initialize the GP private variables
        CODEZ                 _report_api_status                             ();    // used to check API calls, after setting "_api_status"
    
    // API group "ALIGN"
        CODEZ _align_init          ();
        // copiers, public = private;
        CODEZ _align_copy_vars     ();
        CODEZ _align_copy_is_needed();
        CODEZ _align_copy_is_warmed();
        // getters, API is used
        CODEZ _align_get_vars      ();    // calls the getters
        CODEZ _align_get_is_needed ();    // query "alignment is needed", with API
        CODEZ _align_get_is_warmed ();    // query "device is warmed-up", with API

    // API group "AUDIO"
        CODEZ _audio_init                       ();
        // copiers, public = private;
        CODEZ _audio_copy_vars                  ();
        CODEZ _audio_copy_is_demodulating       ();
        CODEZ _audio_copy_is_mute               ();
        CODEZ _audio_copy_frequecny_offset_hz   ();
        CODEZ _audio_copy_volume                ();
        CODEZ _audio_copy_demodulation_select   ();
        CODEZ _audio_copy_data_v                ();
        CODEZ _audio_copy_data_samples_requested();
        CODEZ _audio_copy_data_samples_acquired ();
        // getters, API is used
        CODEZ _audio_get_vars                   ();    // calls the getters
        CODEZ _audio_get_is_demodulating        ();    // determine if demodulation is occuring
        CODEZ _audio_get_is_mute                ();    // query mute status
        CODEZ _audio_get_frequency_offset_hz    ();    // query frequency offset
        CODEZ _audio_get_volume                 ();    // query volume setting
        CODEZ _audio_get_demodulation_select    ();    // query demodulation mode
        // setters, API is used
        CODEZ _audio_set_vars                   ();    // calls the setters
        CODEZ _audio_set_is_mute                ();    // control speakers
        CODEZ _audio_set_frequency_offset_hz    ();    // set carrier frequency
        CODEZ _audio_set_volume                 ();    // control speaker volume
        CODEZ _audio_set_demodulation_select    ();    // control demodulation mode
        CODEZ _audio_set_data_samples_requested ();    // sets a non-API, used to call API

    // API group "CONFIG"
        CODEZ _config_init                                          ();
        // copiers, public = private;
        CODEZ _config_copy_vars                                     ();
        CODEZ _config_copy_reference_level_dbm                      ();
        CODEZ _config_copy_center_frequency_hz                      ();
        CODEZ _config_copy_min_center_frequency_hz                  ();
        CODEZ _config_copy_max_center_frequency_hz                  ();
        CODEZ _config_copy_external_reference_frequency_hz          ();
        CODEZ _config_copy_frequency_reference_source_select        ();
        // getters, API is used
        CODEZ _config_get_vars                                      ();
        CODEZ _config_get_reference_level_dbm                       ();
        CODEZ _config_get_center_frequency_hz                       ();
        CODEZ _config_get_min_center_frequency_hz                   ();
        CODEZ _config_get_max_center_frequency_hz                   ();
        CODEZ _config_get_external_reference_frequency_hz           ();
        CODEZ _config_get_frequency_reference_source_select         ();
        // setters, API is used
        CODEZ _config_set_vars                                      ();
        CODEZ _config_set_reference_level_dbm                       ();
        CODEZ _config_set_center_frequency_hz                       ();
        CODEZ _config_set_external_reference_frequency_source_select();
        
    // API group "DEVICE"
        CODEZ _device_init                    ();
        // copiers, public = private;
        CODEZ _device_copy_vars               ();
        CODEZ _device_copy_is_connected       ();
        CODEZ _device_copy_is_over_temperature();
        CODEZ _device_copy_is_running         ();
        CODEZ _device_copy_event_occured      ();
        CODEZ _device_copy_api_status_message ();
        CODEZ _device_copy_id                 ();
        CODEZ _device_copy_event_id           ();
        CODEZ _device_copy_info_type          ();
        CODEZ _device_copy_event_timestamp    ();
        // getters, API is used
        CODEZ _device_get_vars                ();    
        CODEZ _device_get_is_running          ();    
        CODEZ _device_get_api_status_message  ();    
        CODEZ _device_get_info_type           ();    
        CODEZ _device_get_is_over_temperature ();    
        CODEZ _device_get_event               ();
        
    // API group "DPX"

    // API group "IFSTREAM"
        CODEZ _ifstream_init                              ();
        // copiers, public = private;
        CODEZ _ifstream_copy_vars                         ();
        CODEZ _ifstream_copy_file_name_suffix             ();
        CODEZ _ifstream_copy_file_path                    ();
        CODEZ _ifstream_copy_file_name_base               ();
        CODEZ _ifstream_copy_file_length_max_ms           ();
        CODEZ _ifstream_copy_file_count                   ();
        CODEZ _ifstream_copy_output_destination_select    ();
        CODEZ _ifstream_copy_is_active                    ();
        CODEZ _ifstream_copy_if_data_length               ();
        CODEZ _ifstream_copy_data_info_type               ();
        CODEZ _ifstream_copy_adc_data_v                   ();
        CODEZ _ifstream_copy_adc_tiggers_v                ();
        CODEZ _ifstream_copy_frame_bytes                  ();
        CODEZ _ifstream_copy_number_of_frames             ();
        CODEZ _ifstream_copy_framed_adc_data_v            ();
        CODEZ _ifstream_copy_points_in_equalization_buffer();
        CODEZ _ifstream_copy_eq_frequency_v               ();
        CODEZ _ifstream_copy_eq_amplitude_v               ();
        CODEZ _ifstream_copy_eq_phase_v                   ();
        CODEZ _ifstream_copy_scale_factor                 ();
        CODEZ _ifstream_copy_scale_frequency              ();
        CODEZ _ifstream_copy_if_bandwidth_hz              ();
        CODEZ _ifstream_copy_samples_per_second           ();
        CODEZ _ifstream_copy_if_center_frequency          ();
        CODEZ _ifstream_copy_buffer_size_bytes            ();
        CODEZ _ifstream_copy_buffer_samples               ();
        CODEZ _ifstream_copy_acq_status_message           ();

        // getters, uses API
        CODEZ _ifstream_get_vars                          ();
        CODEZ _ifstream_get_is_active                     ();
        CODEZ _ifstream_get_acq_parameters                ();
        CODEZ _ifstream_get_buffer_size                   ();
        CODEZ _ifstream_get_eq_parameters                 ();
        CODEZ _ifstream_get_scaling_parameters            ();
        // setters, uses API
        CODEZ _ifstream_set_vars                          ();
        CODEZ _ifstream_set_file_name_suffix              ();
        CODEZ _ifstream_set_file_path                     ();
        CODEZ _ifstream_set_file_name_base                ();
        CODEZ _ifstream_set_file_length_ms                ();
        CODEZ _ifstream_set_file_count                    ();
        CODEZ _ifstream_set_output_configuration_select   ();

    // API group "IQBLK"
        CODEZ _iqblk_init                          ();
        CODEZ _iqblk_bitcheck                      ();
        // copiers, public = private;
        CODEZ _iqblk_copy_vars                     ();
        CODEZ _iqblk_copy_getter                   ();
        CODEZ _iqblk_copy_actual_buffer_samples    ();
        CODEZ _iqstream_copy_sample_pairs_requested();
        CODEZ _iqblk_copy_cplx32_v                 ();
        CODEZ _iqblk_copy_acq_info_type            ();
        CODEZ _iqblk_copy_bitcheck                 ();
        CODEZ _iqblk_copy_sample_rate              ();
        CODEZ _iqblk_copy_bandwidth_hz             ();
        CODEZ _iqblk_copy_max_bandwidth_hz         ();
        CODEZ _iqblk_copy_min_bandwidth_hz         ();
        CODEZ _iqblk_copy_record_length            ();
        CODEZ _iqblk_copy_max_record_length        ();
        // getters, uses API
        CODEZ _iqblk_get_vars                      ();
        CODEZ _iqblk_get_acq_info_type             ();
        CODEZ _iqblk_get_sample_rate               ();
        CODEZ _iqblk_get_bandwidth_hz              ();
        CODEZ _iqblk_get_max_bandwidth_hz          ();
        CODEZ _iqblk_get_min_bandwidth_hz          ();
        CODEZ _iqblk_get_max_record_length         ();
        CODEZ _iqblk_get_record_length             ();
        // setters
        CODEZ _iqblk_set_vars                      ();
        CODEZ _iqblk_set_getter                    ();    // does not use API
        CODEZ _iqblk_set_bandwidth_hz              ();
        CODEZ _iqblk_set_record_length             ();
        // data acquisiton, uses API
        CODEZ _iqblk_get_iq_data                   ();
        CODEZ _iqblk_get_iq_data_cplx              ();
        CODEZ _iqblk_get_iq_data_deinterleaved     ();

    // API group "IQSTREAM"
        CODEZ _iqstream_init                           ();
        CODEZ _iqstream_bitcheck                       (uint32_t acqStatus);
        // copiers, public = private;
        CODEZ _iqstream_copy_vars                      ();
        CODEZ _iqstream_copy_acqStatus_message         ();
        CODEZ _iqstream_copy_bandwidth                 ();
        CODEZ _iqstream_copy_bandwidth_max             ();
        CODEZ _iqstream_copy_bandwidth_min             ();
        CODEZ _iqstream_copy_sample_rate               ();
        CODEZ _iqstream_copy_fileinfo_type             ();  
        CODEZ _iqstream_copy_is_enabled                ();           
        CODEZ _iqstream_copy_pairs_copied              ();    
        CODEZ _iqstream_copy_info_type                 ();    
        CODEZ _iqstream_copy_cplx32_v                  ();
        CODEZ _iqstream_copy_cplxInt16_v               ();
        CODEZ _iqstream_copy_cplxInt32_v               ();
        CODEZ _iqstream_copy_pairs_max                 ();
        CODEZ _iqstream_copy_record_time_ms            ();
        CODEZ _iqstream_copy_filename_base             ();
        CODEZ _iqstream_copy_suffix_control            ();
        CODEZ _iqstream_copy_buffer_multiplier         ();
        CODEZ _iqstream_copy_destination_select        ();
        CODEZ _iqstream_copy_datatype_select           (); 
        // getters, uses API
        CODEZ _iqstream_get_vars                       ();
        CODEZ _iqstream_get_max_acq_bandwidth          ();    // updates "bandwidth_min"
        CODEZ _iqstream_get_min_acq_bandwidth          ();    // updates "bandwidth_max"
        CODEZ _iqstream_get_acq_parameters             ();    // updates "bandwidth" and "sample_rate"
        CODEZ _iqstream_get_disk_fileinfo              ();    // updates "fileinfo_type"
        CODEZ _iqstream_get_enabled                    ();    // updates "is_enabled"
        CODEZ _iqstream_get_iq_data_buffer_size        ();    // updates "pairs max"
        // setters, uses API
        CODEZ _iqstream_set_vars                       ();
        CODEZ _iqstream_set_acq_bandwidth              ();
        CODEZ _iqstream_set_disk_file_length           ();
        CODEZ _iqstream_set_disk_filename_base         ();
        CODEZ _iqstream_set_filename_suffix            ();
        CODEZ _iqstream_set_iq_data_buffer_size        ();
        CODEZ _iqstream_set_output_configuration       ();
        // data acquisiton, uses API
        CODEZ _iqstream_acquire_data_to_file           ();     
        CODEZ _iqstream_acquire_data_direct_cplx32_v   ();
        CODEZ _iqstream_acquire_data_direct_cplxInt16_v();
        CODEZ _iqstream_acquire_data_direct_cplxInt32_v();

    // API group "PLAYBACK"

    // API group "REFTIME"
        CODEZ _reftime_init                 ();
        CODEZ _reftime_make_dts             ();  // makes a date time stamp using the current time
        // copiers, public = private;
        CODEZ _reftime_copy_vars            ();
        CODEZ _reftime_copy_current         ();
        CODEZ _reftime_copy_start           ();
        CODEZ _reftime_copy_helper          ();
        CODEZ _reftime_copy_dts             ();
        CODEZ _reftime_copy_running_duration();
        CODEZ _reftime_copy_source_select   ();
        CODEZ _reftime_copy_timestamp_rate  ();
        // getters, uses API
        CODEZ _reftime_get_vars             ();
        CODEZ _reftime_get_current          ();
        CODEZ _reftime_get_start            ();
        CODEZ _reftime_get_running_duration ();
        CODEZ _reftime_get_source_select    ();
        CODEZ _reftime_get_timestamp_rate   ();
    
    // API group "SPECTRUM"
        CODEZ _spectrum_default                    ();
        CODEZ _spectrum_init                       ();
        CODEZ _print_spectrum_traces_long          ();
        CODEZ _print_spectrum_traces_compact       ();
        CODEZ _spectrum_make_array_frequency       ();
        // copiers, public = private;
        CODEZ _spectrum_copy_vars                  ();
        CODEZ _spectrum_copy_is_enabled_measurement();
        CODEZ _spectrum_copy_settings_type         ();
        CODEZ _spectrum_copy_limits_type           ();
        CODEZ _spectrum_copy_array_frequency       ();
        CODEZ _spectrum_copy_trace_points_aquired  (RSA_API::SpectrumTraces trace_index);
        CODEZ _spectrum_copy_is_enabled_trace      (RSA_API::SpectrumTraces trace_index);
        CODEZ _spectrum_copy_traces_select         (RSA_API::SpectrumTraces trace_index);
        CODEZ _spectrum_copy_detectors_select      (RSA_API::SpectrumTraces trace_index);
        CODEZ _spectrum_copy_trace_info_type       (RSA_API::SpectrumTraces trace_index);
        CODEZ _spectrum_copy_array_power           (RSA_API::SpectrumTraces trace_index);
        CODEZ _spectrum_copy_peak_index            (RSA_API::SpectrumTraces trace_index);
        // getters, uses API
        CODEZ _spectrum_get_vars                  ();
        CODEZ _spectrum_get_is_enabled_measurement();
        CODEZ _spectrum_get_limits_type           ();
        CODEZ _spectrum_get_settings_type         ();
        CODEZ _spectrum_get_trace_info_type       (RSA_API::SpectrumTraces trace_index);
        CODEZ _spectrum_get_trace_type            (RSA_API::SpectrumTraces trace_index);
        // setters, uses API
        CODEZ _spectrum_set_vars                  ();
        CODEZ _spectrum_set_is_enabled_measurement();
        CODEZ _spectrum_set_settings_type         ();
        CODEZ _spectrum_set_trace_type            ();

    // API group "TRIG"
        CODEZ _trig_init                  ();
        // copiers, public = private;
        CODEZ _trig_copy_vars             ();
        CODEZ _trig_copy_if_power_level   ();
        CODEZ _trig_copy_mode_select      ();
        CODEZ _trig_copy_position_percent ();
        CODEZ _trig_copy_source_select    ();
        CODEZ _trig_copy_transition_select();
        // getters, API is used
        CODEZ _trig_get_vars              ();
        CODEZ _trig_get_if_power_level    ();
        CODEZ _trig_get_mode_select       ();
        CODEZ _trig_get_position_percent  ();
        CODEZ _trig_get_source_select     ();
        CODEZ _trig_get_transition_select ();
        // setters, API is used
        CODEZ _trig_set_vars              ();
        CODEZ _trig_set_if_power_level    ();
        CODEZ _trig_set_mode_select       ();
        CODEZ _trig_set_position_percent  ();
        CODEZ _trig_set_source_select     ();
        CODEZ _trig_set_transition_select ();

        // these are not in the manaul, but in the "RSA_API.h"...they look useful
        // RSA_API_DLL ReturnStatus TRIG_SetTriggerTime(time_t startTimeSec, uint64_t startTimeNsec, uint64_t repeatTimeNsec);
		// RSA_API_DLL ReturnStatus TRIG_GetTriggerTime(time_t* startTimeSec, uint64_t* startTimeNsec, uint64_t* repeatTimeNsec);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif


////////~~~~~~~~END>  rsa306b_class.h
