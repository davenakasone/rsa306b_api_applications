/*
    this class uses a provided API to interface with the RSA-306B Spectrum Analyzer
    Tektronix requires 2 shared objects (dynamic libraries) to be linked and the RSA_API.h header
    the API is designed to run on a 64-bit Linux OS using an intel processor

    if using more than 1 instance of this class, only allow one instance to connect at a time
    see documentation for general details
    see the unit test section for examples of class use cases
    
    purpose of this class:
        - organize API procedures to meet use cases
        - consolidate common API procedures
        - foundation for implementing future spectrum analyzer API interface needs


    class source files, by API function group:
        rsa306b_class_gp.cpp
        rsa306b_class_ALIGN.cpp 
        rsa306b_class_CONFIG_get_set.cpp
        rsa306b_class_CONFIG.cpp
        rsa306b_class_DEVICE_get_set.cpp 
        rsa306b_class_DEVICE.cpp 
        rsa306b_class_REFTIME_get.cpp 
        rsa306b_class_REFTIME_set.cpp 
        rsa306b_class_REFTIME.cpp 
        rsa306b_class_SPECTRUM_get.cpp
        rsa306b_class_SPECTRUM_private.cpp
        rsa306b_class_SPECTRUM_public.cpp
        rsa306b_class_SPECTRUM_set.cpp

    
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

        GNSS # not used, only the RSA500/600 has position data

        IF Streaming

        IQ Block

        IQ Streaming

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
            
    notes:

        public member functions are classified as:
            "<group>_print_all()"       // for diagnostic use and monitoring
            "<group>_get_<member>()"    // getter, most member variables have a value-returning getter
            "<group>_<task>()"          // for user to interact with API
            constructor                 // only need 1
            destructor                  // there can only be 1
        
        public variables: 
            none, just constants for user reference

        private member functions are classified as:
            "_<group>_<task>()"          // manages API interface, usually activated by public counter part
            "_<group>_set_<member>()"    // setter, sets most private member variables after validation
        
        private member variables are classifed as:
            "_<group>_<description>"        // for common parameters to API funciton calls
            "_<group>_<api_name>_select"    // for API enums
            "_<group>_<api_name>_type"      // for API structs

        not all member variables have a getter and setter
        "general purpose" functions and variables do not a have a <group>
        private members use the python-inspired "_*" to facilitate programing
        this API often nests enums in structs
        some structs in this API incorporate other API structs by composition
        member variables are kept private because they influence the API interaction
        setters are kept private because user sets through public "<group>_<task>()"
        there is no need for "protected" member variables or functions
        use of this class by composition is acceptable
        inheritance, virtualization, and templates with this class is not advisable
        the API was not made for polymorphsim, meta programming, and virulazation techniques
        this class emphasizes taking data from static buffers on the hardware
        const data types are used to assure type-safe constants
        #define <VALUE> is used  when static allocation is required
        any fixed value should be controlled in this header file
        any library or header needed for the class should be included in this header file 

    TODO:
        see what function groups are useful
        DEBUG logger .txt
        ...helper class by composition or make this a big API class
        unit tests
        keep building the API
        playback / reading recorded files is of interest
        spectrum-group functions may be too basic
*/

#ifndef H_rsa306b_class
#define H_rsa306b_class


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../api_resourcez/RSA_API.h" // has <time.h> and <stdint.h> 

#define GET_NAME(var) #var

//#define DEBUG_CLI 1776    // when activated, prints __LINE__, __FILE__, __func__ for each call
//#define DEBUG_MIN 1917    // when activated, prints essential information
//#define DEBUG_ERR 1492    // when activated, prints *_error_checks() that result in an error condition

#define BUF_A 32                    // a short general purpose buffer
#define BUF_B 64                    // ..
#define BUF_C 128                   // ...
#define BUF_D 256                   // ....
#define BUF_E 512                   // .....
#define BUF_F 1024                  // a long general purpose buffer
#define SPECTRUM_DATA_LENGTH 2048   // spectrum aquisitions, stops need for dynamic allocation, trying dynamic first?
#define AUDIO_DATA_LENGTH 65535     // audio data points, 2^16 - 1


class rsa306b
{
    public:

    // access to constants:
        // status of internal non-API function calls
        const int CALL_SUCCESS = 7777;    // the function call was successful
        const int CALL_FAILURE = -777;    // the function call failed
        // common initialization values, by data type
        const char INIT_CHAR = 'Z';
        const char INIT_STR[6] = "ZZZZZ";
        const double INIT_DOUBLE = -9999.9999;
        const float INIT_FLOAT = -9999.9;
        const int INIT_INT = -9999;
        // device limits for the RSA-306B
        const double EXTERNAL_FREQUENCY = 10e6;                       // external reference frequency, required
        const double EXTERNAL_AMPLITUDE_dbm = 10;                     // allows +/- 10 dbm maximum amplitude  
        const double REFERENCE_LEVEL_MAX_dbm = 30;                    // highest measurable signal power
        const double REFERENCE_LEVEL_MIN_dbm = -130;                  // smallest measurable signal power
        const double SPAN_MAX_Hz = 40e6;                              // largest measurable bandwith
        const double SPAN_MIN_Hz = 100;                               // smallest measurable bandwith 
        const double POSITION_PERCENT_MIN = 1;                        // smallest trigger position percentage
        const double POSITION_PERCENT_MAX = 99;                       // largest trigger position percentage
        const float AUDIO_VOLUME_MAX = 1.0;                           // maximum audio volume API will accept
        const float AUDIO_VOLUME_MIN = 0.0;                           // minimum audio volume API will accept
        const double AUDIO_CENTER_FREQUENCY_OFFSET_MAX_Hz = 20e6;     // highest audio demodulator API accepts
        const double AUDIO_CENTER_FREQUENCY_OFFSET_MIN_Hz = -20e6;    // highest audio demodulator API accepts

    // general purpouse
        rsa306b();    
        ~rsa306b(); 
        RSA_API::ReturnStatus get_api_return_status();       // get validation of API calls
        void get_api_return_status_string(char* carrier);    // get state of API call in a string
        int get_gp_return_status();                          // get validation of internal funciton calls
        void print_constants();                              // prints macros and const types to stdout
        void print_variables();                              // prints device variables by API function group

    // API group "ALIGN"
        // functions for user action
        void align_execute_alignment();    // called when connected, callable anytime
        void align_print_all();            // prints state of members to stdout
        // getters
        bool align_get_is_warmed();         // device can take a while to warmup, not too important
        bool align_get_need_alignment();    // align_execute_alignment() should be called if true
    
    // API group "AUDIO"
        int16_t aduio_data[AUDIO_DATA_LENGTH];    // public member for user access to audio data
        struct audio_type                          // for user convenience in getting audio information
        {
            bool is_demodulating;                                // true indicates device is demodulating
            bool is_mute;                                        // false means that the speakers are on
            double center_frequency_offset_hz;                   // must be in range, does not require changing center frequency
            float volume;                                        // must be in range, adjusts speaker volume
            RSA_API::AudioDemodMode demodulation_mode_select;    // type of demodulation applied
            uint16_t data_length_received;                       // data points written to "audio_data[]" during a data call
        }; typedef struct audio_type audio_type;
        // functions for user action
        void audio_print_all();                      // prints audio status to stdout
        void audio_prepare(audio_type* settings);    // configure device audio settings with struct
        // getters
        void audio_get_data(audio_type* settings);        // updates "audio_data" and elements aquired
        void audio_get_settings(audio_type* settings);    // updates struct with current device audio settings

    // API group "CONFIG"
        // functions for user action
        int config_update_cf_rl(double cf_Hz, double rl_dBm);                         // user defined center frequency and reference level
        void config_print_all();                                                      // print members to stdout
        void config_use_external_reference_source(RSA_API::FREQREF_SOURCE source);    // be careful with this
        // getters
        double config_get_center_frequency_hz();                            // user selection enforced
        double config_get_center_frequency_max_hz();                        // 6.2 GHz for RSA-306B
        double config_get_center_frequency_min_hz();                        // 9 kHz for RSA-306B
        double config_get_reference_level_dbm();                            // the range is -130 to 30 dbm
        RSA_API::FREQREF_SOURCE config_get_frequency_reference_source();    // RSA-306B only has internal and external
        double config_get_external_frequency_reference_hz();                // the +/- 10 dbm range is enforced

    // API group "DEVICE"
        // functions for user action
        void device_connect();                 // user must call to connect device
        void device_disconnect();              // destructor calls, but user can also
        void device_prepare_run();             // trigger for device_start_frame_transfer()
        void device_print_all();               // prints device members to stdout      
        void device_reset();                   // try not to use, will crash program        
        void device_run();                     // not needed, but can be called
        void device_start_frame_transfer();    // overides device_run()                
        void device_stop();                    // not needed, but can be called
        // getters 
        int device_get_id();                                         // only 1, API only allows one device per machine
        void device_get_info_type(RSA_API::DEVICE_INFO* devInfo);    // see struct in API, has device information
        bool device_get_is_connected();                              // should be true once device_connect() is called
        bool device_get_is_over_temperature();                       // stop device if this is true
        bool device_get_is_running();                                // don't configure if this is true

    // API group "DPX"

    // API group "IFSTREAM"

    // API group "IQBLK"

    // API group "IQSTREAM"

    // API group "PLAYBACK"

    // API group "REFTIME"
        struct reftime_type    // for user convenience in getting reference time information
        {
            time_t seconds;    // seconds since 00:00:00, Jan 1, 1970, UTC
            uint64_t nanos;    // off set from seconds                               
            uint64_t stamp;    // counter-valued, depends on timestamp rate                                
        }; typedef struct reftime_type reftime_type;
        // functions for user action
        void reftime_start_split();                           // starts wall clock and cpu time split
        void reftime_stop_split();                            // stops wall clock and cpu time split
        void reftime_print_all();                             // prints all timing information to stdout
        void reftime_timestamp_2_time (reftime_type* r_t);    // tool to make any time
        void reftime_time_2_timestamp (reftime_type* r_t);    // tool to make any timestamp
        // getters
        void reftime_get_date_timestamp(char* dts);          // gets current internal date-time-stamp
        double reftime_get_running();                        // time since connected, wall clock
        double reftime_get_split();                          // time since start_split()/stop_split(), wall clock
        RSA_API::REFTIME_SRC reftime_get_source_select();    // identifies the API timing source
        uint64_t reftime_get_timestamp_rate();               // rate device produces time stamps per second
        void reftime_get_begin_type(reftime_type* r_t);      // time device was connected
        void reftime_get_current_type(reftime_type* r_t);    // time device reads now
        double reftime_get_split_cpu();                      // time since start_split()/stop_split(), cpu
        double reftime_get_running_cpu();                    // time since connected, cpu
    
    // API group "SPECTRUM"
        struct spectrum_3_traces_type    // for user convenience in getting information of the 3 traces
        {
            RSA_API::SpectrumTraces trace_select[3];          // enum, specify 1 of 3 traces
            RSA_API::SpectrumDetectors detector_select[3];    // enum, for each of 3 traces, they average
            bool trace_enabled[3];                            // tracks activation for each of the 3 traces
        }; typedef struct spectrum_3_traces_type spectrum_3_traces_type;
        struct spectrum_data_collector    // for user convenience in getting trace data
        {
            RSA_API::SpectrumTraces trace_number[3];    // enum, specify 1 of 3 traces
            double x_frequency;                         // frequency of the measurement
            float y_measurement[3];                     // value of the measurement, each trace
        }; typedef struct spectrum_data_collector spectrum_data_collector;
        // functions for user action
        void spectrum_print_all();                                                       // prints spectrum information to stdout
        void spectrum_prepare(double cf_Hz, double rl_dBm,                               // set through "config_update_cf_rl()"
            RSA_API::Spectrum_Settings* settings,                                        // desired settings
            spectrum_3_traces_type* traces3);                                            // desired characteristics of each trace
        void spectrum_acquire_trace(RSA_API::SpectrumTraces trace_number);               // gets trace for specified trace number
        int spectrum_index_of_peak_measurement(RSA_API::SpectrumTraces trace_number);    // gets index of peak after trace acquired
        void spectrum_collect_data(spectrum_data_collector* data_getter, int index);     // collect data for a trace and index of interest 
        // getters
        void spectrum_get_limits_type(RSA_API::Spectrum_Limits* limits);               // get _spectrum_limits_type
        bool spectrum_get_measurement_enabled();                                       // get _spectrum_measurement_enabled
        void spectrum_get_settings_type(RSA_API::Spectrum_Settings* settings);         // get _spectrum_settings_type
        void spectrum_get_trace_info_type(RSA_API::Spectrum_TraceInfo* trace_info);    // get _spectrum_trace_info_type
        void spectrum_get_3_traces_type(spectrum_3_traces_type* your_3_traces);        // get type of all 3 traces

    // API group "TRIG"
        struct trig_type    // for user convenience in getting or setting the trigger
        {
            double if_power_level;
            double position_percent;
            RSA_API::TriggerMode mode_select;
            RSA_API::TriggerSource source_select;
            RSA_API::TriggerTransition transition_select;
        }; typedef struct trig_type trig_type;
        // functions for user action
        void trig_print_all();                             // prints trig information to stdout
        void trig_force_trigger();                         // API call to force trigger event
        void trig_prepare(trig_type* trigger_settings);    // place trigger settings in "trig_type" before calling
        // getters
        void trig_get_settings(trig_type* trigger_settings);    // struct is overwritten with current trigger settings


    private:


    // general purpose
        char _helper_string[BUF_E];                  // string for utility
        char _holder_string[BUF_F];                  // big string for utility
        int _gp_return_status;                       // set when calling non-API functions
        RSA_API::ReturnStatus _api_return_status;    // enum, all API functions return this
        // internal-use functions
        void _api_error_check();                     // checks status of API function calls
        void _gp_error_check();                      // checks status of internal function calls
        void _init_member_variables();               // initializes all member variables

    // API group "ALIGN"
        bool _align_need_alignment;    // indicates API alignment status
        bool _align_is_warmed;         // indicates API warm-up status
        // setters
        void _align_set_need_alignment();    // uses API to set _align_need_alignment
        void _align_set_is_warmed();         // uses API to set _align_is_warmed
        
    // API group "AUDIO"
        audio_type _audio_type;                                            // maintains audio-group member variables of the class
        int _audio_set_center_frequency_offset(double cf_offset);          // API sets offset from center frequency
        int _audio_set_demodulation_mode(RSA_API::AudioDemodMode mode);    // API sets demodulation mode
        int _audio_set_mute_status(bool new_value);                        // API sets the mute state
        int _audio_set_volume(float new_value);                            // API sets the volume

    // API group "CONFIG"
        double _config_center_frequency_hz;                                   // user can pick, within limits
        double _config_center_frequency_max_hz;                               // device limit, 6.2 GHz
        double _config_center_frequency_min_hz;                               // device limit, 9 kHz
        double _config_reference_level_dbm;                                   // must be [-130 : 30] dbm
        double _config_external_reference_frequency_hz;                       // must be 10 MHz
        RSA_API::FREQREF_SOURCE _config_frequency_reference_source_select;    // enum, only internal or external RSA-306B
        void _config_init();                                                  // called during each connection
        // setters
        void _config_set_center_frequency_hz();           // updates _config_center_frequency_hz
        void _config_set_reference_level_dbm();           // updates _config_reference_level_dbm
        void _config_set_frequency_reference_source();    // updates _config_frequency_reference_source_select

    // API group "DEVICE"
        bool _device_is_connected;                 // device connection status, important
        bool _device_is_over_temperature;          // status of device over the temperature limit
        bool _device_is_running;                   // status of run state
        int _device_id;                            // only 1 spectrum analyzer can connect per machine
        RSA_API::DEVICE_INFO _device_info_type;    // struct, has 6 strings
        // setters
        void _device_set_id(int new_value);               // called after device_connect() is called
        void _device_set_info_type();                     // sets _device_info_type with API
        void _device_set_is_connected(bool new_value);    // sets _device_is_connected when connecting, uses API
        void _device_set_is_over_temperature();           // sets _device_is_over_temperature, uses API
        void _device_set_is_running();                    // sets _device_is_running, uses API
        
    // API group "DPX"

    // API group "IFSTREAM"

    // API group "IQBLK"

    // API group "IQSTREAM"

    // API group "PLAYBACK"
        
    // API group "REFTIME"
        char _reftime_date_timestamp[BUF_C];            // a date-time-stamp good for naming files    
        double _reftime_running;                        // time since reference time set, in seconds
        double _reftime_split;                          // difference of lead - trail, in seconds
        double _reftime_split_lead;                     // not for user access
        double _reftime_split_trail;                    // not for user access
        RSA_API::REFTIME_SRC _reftime_source_select;    // enum, where time source is located
        uint64_t _reftime_timestamp_rate;               // rate of the time-stamp counter's clock 
        reftime_type _reftime_begin_type;               // marks start of time
        reftime_type _reftime_current_type;             // updated periodically
        struct t_cpu
        {
            clock_t begin;     // marks time connected
            clock_t lead;      // set on reftime_start_split()
            clock_t trail;     // set on reftime_stop_split()
            double running;    // returned to user in reftime_get_running_cpu()
            double split;      // returned to user in reftime_get_split_cpu()
        }; typedef struct t_cpu t_cpu;    
        t_cpu _reftime_cpu;    // need a CPU clock capability
        // setters
        void _reftime_set_date_timestamp();    // _reftime_date_timestamp is updated to current time
        void _reftime_set_running();           // API sets _reftime_running
        void _reftime_set_split();             // time difference is calculated, API values
        void _reftime_set_split_lead();        // API sets _reftime_split_lead to current time
        void _reftime_set_split_trail();       // API sets _reftime_split_trail to current time
        void _reftime_set_source_select();     // API updates _reftime_source_select
        void _reftime_set_timestamp_rate();    // API updates _reftime_timestamp_rate
        void _reftime_set_begin_type();        // API updates _reftime_begin_type, should not change
        void _reftime_set_current_type();      // API updates _reftime_current_typ, will change
    
    // API group "SPECTRUM"        
        spectrum_3_traces_type _spectrum_3_traces_type;                              // public struct, info of the 3 traces
        bool _spectrum_good_aquisition;                                              // bit mask result of AcqDataStatus enum
        bool _spectrum_measurement_enabled;                                          // status of instrument for spectrum aquisition
        double _spectrum_frequency_array[SPECTRUM_DATA_LENGTH];                      // X axis, frequencies, all 3 traces 
        float _spectrum_trace_data[3][SPECTRUM_DATA_LENGTH];                         // Y axis, measurments, all 3 traces
        int _spectrum_valid_trace_points;                                            // number of valid points spectrum analyzer recorded
        RSA_API::Spectrum_Limits _spectrum_limits_type;                              // struct, with 6 doubles and 2 ints as limits
        RSA_API::Spectrum_Settings _spectrum_settings_type;                          // struct, with internal + 2 enums + external settings
        RSA_API::Spectrum_TraceInfo _spectrum_trace_info_type;                       // struct, used for timing and "AcqDataStatus"
        void _spectrum_init();                                                       // called when connecting
        void _spectrum_create_frequency_array();                                     // makes array for _spectrum_frequency_array, sized to _spectrum_trace_data
        int _spectrum_trace_number_2_index(RSA_API::SpectrumTraces trace_number);    // convert a trace number to proper index
        int _spectrum_find_peak_index(RSA_API::SpectrumTraces trace_number);         // finds peak index of desired trace
        // setters
        int _spectrum_set_limits_type();                                              //API sets _spectrum_limits_type
        int _spectrum_set_measurement_enabled(bool new_value);                        // API updates _spectrum_measurement_enabled
        int _spectrum_set_settings_type(RSA_API::Spectrum_Settings* new_settings);    // updates _spectrum_settings_type with API
        void _spectrum_set_trace_info_type();                                         // updates _spectrum_trace_info_type with API
        int _spectrum_set_3_traces_type(spectrum_3_traces_type* traces3);             // updates _spectrum_trace_enabled, _spectrum_trace_select, 
                                                                                      //     and _spectrum_detector_select
    // API group "TRIG"
        trig_type _trig_type;
        // setters
        int _trig_set_if_power_trigger_level(double level);                         // API call to set IF power level of trigger
        int _trig_set_trigger_mode(RSA_API::TriggerMode mode);                      // API call, free run or use trigger settings
        int _trig_set_trigger_position_percent(double percent);                     // API call to set how much data is saved before and after trigger
        int _trig_set_trigger_source(RSA_API::TriggerSource source);                // API call to set the source of the trigger
        int _trig_set_trigger_transition(RSA_API::TriggerTransition transition);    // API call to set triggering event
};


#endif


////////~~~~~~~~END>  rsa306b.h
