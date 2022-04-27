/*
    this is the top-level class of the program
    subordinate classes (included by composition) not designed to be used independently
    this class uses a provided API to interface with the RSA-306B Spectrum Analyzer
    Tektronix requires 2 shared objects (dynamic libraries) to be linked and the RSA_API.h header
    the API is designed to run on a 64-bit Linux OS using an intel processor
    only one instance of this class can connect to the spectrum analyzer
    for most use cases, only one instance of this class is required

    see documentation for general details
    see the test section for examples 

    Class source files, 
    
        "./program_core/rsa306b"
            - rsa306b_struct.h
                struct rsa306b_struct
            - rsa306b_class.h
                class rsa306b_class

        "./program_core/rsa306b/rsa306_GP/"
            - rsa306b_gp_struct.h
                struct rsa306b_gp_struct
            - rsa306b_class_cons_dest.cpp
                rsa306b_class()
                ~rsa306b_class()
            - rsa306b_gp_confirm.cpp
                _gp_confirm_api_status()
                _gp_confirm_call_status()
                _gp_confirm_return()
            - rsa306b_gp_copy.cpp
                get_everything()
                _gp_copy_vars()
                _gp_copy_helper()
                _gp_copy_holder()
                _gp_copy_call_status()
                _gp_copy_api_status()
            - rsa306b_gp_init.cpp
                _init_everything()
                _gp_init()
            - rsa306b_gp_print.cpp
                print_everything()
                print_constants()
                print_gp()

        "./program_core/rsa306b/rsa306b_CONST"
            - rsa306b_constants_class.h
                class rsa306b_constants_class
            - rsa306b_constants_constructor.cpp
                rsa306b_constants_class()
                ~rsa306b_constants_class()
        
        "./program_core/rsa306b/rsa306_ALIGN"
            - rsa306b_align_struct.h
                struct rsa306b_align_struct
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
                struct rsa306b_audio_struct
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
                _audio_copy_data_samples_output()
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
                struct rsa306b_config_struct    
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
                struct rsa306b_device_struct
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

        "./program_core/rsa306b/rsa306_REFTIME/"
            - rsa306b_reftime_struct.h
                struct rsa306b_reftime_struct
                struct reftime_type
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
            
        "./program_core/rsa306b/rsa306_TRIG/"
            - rsa306b_trig_struct.h
                struct rsa306b_trig_struct
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

// INSERT POINTS: device_connect(), _init_everything(), print_everything(), get_everything()


    Purpose of this class:
        - automate API by abstracting mandatory procedures
        - enforce correct use of the API 
        - foundation for implementing future spectrum analyzer API interface needs

    TODO:
        # clock_t CPU timer class
        # bring in the "*.r3f" class
        # bring in the "*.sig" class
        # bring in the spectrogram handler
        # DEBUG logger .txt
        # helper classes by composition
        # keep building and testing the API function groups
        # time series, spectrogram, and other user requests
        # worker thread, request thread --> mutex control
        # DPX
        # IFSTREAM
        # IQBLK
        # IQSTREAM
        # PLAYBACK
*/

#ifndef H_rsa306b_class
#define H_rsa306b_class


#include "../control/resourcez.h"
#include "rsa306b_struct.h"


class rsa306b_class
{
    public :

        rsa306b_struct vars;    // public variables

    // general purpose
        rsa306b_class();            // constructor
        ~rsa306b_class();           // destructor
        void get_everything();      // updates user's variable struct
        void print_everything();    // prints all variables, using the private struct
        void print_constants();     // prints the constant variables of the class
        void print_gp();            // prints the "general purpose" variables, using the private struct
    
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
    
    // API group "REFTIME"
        void print_reftime();               // prints the "REFTIME" variables to stdout, using the private struct
        void reftime_reset();               // resets start time of the device
        void reftime_get_vars();            // gets all the "REFTIME" variables
        void reftime_timestamp_2_time();    // set "vars.reftime.helper.timestamp", then call, updates time_t and uint64_t
        void reftime_time_2_timestamp();    // set "vars.reftime.helper.seconds  and nanos", then call, updates timestamp

    // API group "TRIG"
        void print_trig();       // prints the "TRIG" variables to stdout, using the private struct
        void trig_set_vars();    // user changes "TRIG" variables in public struct, then calls to set new values
        void trig_force();       // a trigger event is forced, user calls "device_run()" before and "device_stop()" after

        
    private : 

        rsa306b_struct _vars;    // private variables
    
    // general purpose
        void _init_everything();    // initialize all class variables
        void _gp_init();            // initialize the "general purpose" variables
        // monitor the program
        void _gp_confirm_api_status();     // called to check error conditions after API function calls     
        void _gp_confirm_call_status();    // called to check error conditions in the class
        int _gp_confirm_return();          // called to provide a return value corresponding to the API status
        // copiers, private --> public
        void _gp_copy_vars();
        void _gp_copy_helper();
        void _gp_copy_holder();
        void _gp_copy_call_status();
        void _gp_copy_api_status();
    
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
        void _audio_copy_data_samples_output();
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
};


#endif


////////~~~~~~~~END>  rsa306b.h