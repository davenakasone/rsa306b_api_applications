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
        rsa306b_class_ALIGN.cpp 
        rsa306b_class_CONFIG.cpp
        rsa306b_class_DEVICE.cpp 
        rsa306b_class_REFTIME.cpp 
        rsa306b_class_SPECTRUM.cpp
        rsa306b_class.cpp  // general purpose


    functions used, by API group:

        Alignment
            ALIGN_GetAlignmentNeeded()
            ALIGN_GetWarmupStatus()
            ALIGN_RunAlignment()

        Audio # might want to use, look into these later

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

        Device # used to get basic information and perform basic tasks
            DEVICE_Connect()
            DEVICE_Disconnect()
            DEVICE_GetEnable()
            DEVICE_GetErrorString()
            DEVICE_GetInfo()
            DEVICE_GetOverTemperatureStatus()
            DEVICE_Reset()
            DEVICE_Run()
            DEVICE_Search()
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

        Trigger # this group looks useful, try it out later


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
            "_<group>_<task>()"        // manages API interface, usually activated by public counter part
            "_<group>_set_<task>()"    // setter, sets most private member variables after validation
        
        private member variables are classifed as:
            "_<group>_<description>"        // for common parameters to API funciton calls
            "_<group>_<api_name>_select"    // for API enums
            "_<group>_<api_name>_type"      // for API structs

        not all member variables have a getter and setter
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
        date-time-stamp
        ...helper class by composition or make this a big API class
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

#define DEBUG_CLI 1776    // when activated, prints __LINE__, __FILE__, __func__ for each call
#define DEBUG_MIN 1917    // when activated, prints essential information
#define DEBUG_ERR 1492    // when activated, prints error_checks() that result in an error condition

#define BUF_A 32
#define BUF_B 64
#define BUF_C 128
#define BUF_D 256
#define BUF_E 512
#define BUF_F 1024


class rsa306b
{
    public:
        // access to constants:

            // status of internal function calls
            const int CALL_SUCCESS = -777;    // the function call was successful
            const int CALL_FAILURE = -444;    // the function call failed

            // common initialization values, by data type
            const char INIT_CHAR = 'Z';
            const double INIT_DOUBLE = -9999.9999;
            const float INIT_FLOAT = -9999.9;
            const int INIT_INT = -9999;
            const char INIT_STR[6] = "ZZZZZ";

            // device limits for the RSA-306B
            const double FREQUENCY_MIN_HZ = 9e3;           // lowest measurable frequency  
            const double FREQUENCY_MAX_HZ = 6.2e9;         // highest measurable frequency
            const double EXTERNAL_FREQUENCY = 10e6;        // external reference allows +/- 10 Hz
            const double REFERENCE_LEVEL_MIN_DB = -130;    // smallest measurable signal power
            const double REFERENCE_LEVEL_MAX_DB = 30;      // highest measurable signal power
            const double SPAN_MAX_HZ = 40e6;               // largest measurable bandwith
            const double SPAN_MIN_HZ = 10;                 // smallest measurable bandwith

        // general purpouse
        rsa306b();    
        ~rsa306b();
        RSA_API::ReturnStatus get_api_return_status();
        void get_api_return_status_string(char* carrier);
        int get_internal_return_status();   

        // ALIGN
        void align_execute_alignment();
        void align_execute_warm_up();
        bool align_get_is_needed();
        bool align_get_is_warmed();
        void align_print_all();   

        // CONFIG
        void config_cf_rl(double cf, double rl);
        void print_config_all();

        // DEVICE
        void print_device_all();
        void device_connect();              
        bool get_device_temperature_check();              
        void device_reset();                
        void device_run();                  
        void device_stop();   

        // REFTIME
        void print_time_begin();
        void print_time_info();
        void print_time_now();
        void print_time_running();
        void print_time_split();
        
    private:

        // general purpose
        char _helper_string[BUF_E];
        char _holder_string[BUF_F];
        int _internal_return_status;                 // set when calling non-API functions
        RSA_API::ReturnStatus _api_return_status;    // enum, all API functions return this
        void _api_error_check();                     // checks status of API function calls
        void _internal_error_check();                // checks status of internal function calls
        void _init_member_variables();               // initializes all member variables

        // API group "ALIGN"
        bool _align_is_needed;
        bool _align_is_warmed;
        int _align_set_is_needed(bool new_value);
        int _align_set_is_warmed(bool new_value);
        
        
        // API group "AUDIO"

        // API group "CONFIG"
        double _config_center_frequency;
        double _config_center_frequency_max;
        double _config_center_frequency_min;
        double _config_reference_level;
        RSA_API::FREQREF_SOURCE _config_frequency_reference_source_select;    // enum

        // API group "DEVICE"
        bool _device_is_connected;
        bool _device_is_over_temperature_limit;
        bool _device_is_running;
        int _device_id;
        RSA_API::DEVICE_INFO _device_info_type;    // struct, has 6 strings
        
        
        // API group "DPX"

        // API group "IFSTREAM"

        // API group "IQBLK"

        // API group "IQSTREAM"

        // API group "PLAYBACK"

        // API group "SPECTRUM"
        RSA_API::SpectrumDetectors 
            _spectrum_detector_select;         // enum, condition to aquire bin
        RSA_API::SpectrumVerticalUnits 
            _spectrum_vertical_unit_select;    // enum, data to be output on Y-axis
        RSA_API::SpectrumTraces 
            _spectrum_trace_select;            // enum, type of trace to get
        RSA_API::SpectrumWindows 
            _spectrum_window_select;           // enum, type of filtering window
        RSA_API::Spectrum_Limits 
            _spectrum_limits_type;             // struct, with 6 doubles and 2 ints as limits
        RSA_API::Spectrum_Settings 
            _spectrum_settings_type;           // struct, with internal + external settings
        RSA_API::Spectrum_TraceInfo 
            _spectrum_trace_info_type;         // struct, used for timing and "AcqDataStatus"
        
        
        bool is_enabled_trace;
        float* trace_data; // dynamic
        






        // API group "REFTIME", do not initialize member variables
        char _reftime_dateTimeStamp[BUF_B];                   
        double _reftime_seconds_since_reference_time_set;
        double _reftime_split;
        double _reftime_split_lead;
        double _time_split_trail;
        RSA_API::REFTIME_SRC 
            _reftime_reference_time_source_select;     // enum, where time source is located
        time_t _reftime_current_seconds;               // seconds since 00:00:00, Jan 1, 1970, UTC
        time_t _reftime_begin_seconds;                 // seconds since 00:00:00, Jan 1, 1970, UTC
        uint64_t _reftime_current_nano;                // off set from seconds
        uint64_t _reftime_current_stamp;               // counter valued
        uint64_t _reftime_begin_nano;                  // off set from seconds
        uint64_t _reftime_begin_stamp;                 // counter valued
        uint64_t _reftime_time_stamp_sampling_rate;    // rate of the time-stamp counter's clock 
        void _reftime_date_time_stamp
            (time_t time_in, uint64_t nano_in);
        void _reftime_record_running();
        void _reftime_record_start();
        void _reftime_record_current();
        void _reftime_record_split();
        void _reftime_timestamp_2_time (uint64_t in_time_stamp, time_t* out_seconds, uint64_t* out_nanos);
        void _reftime_time_2_timestamp (time_t in_seconds, uint64_t in_nanos, uint64_t* out_time_stamp);
        void _reftime_update_time_stamp_rate();

        // API group "TRIG"
};


#endif


////////~~~~~~~~END>  rsa306b.h
