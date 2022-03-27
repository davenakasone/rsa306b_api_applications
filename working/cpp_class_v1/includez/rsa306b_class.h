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
        rsa306b_class_DEVICE_get_set.cpp 
        rsa306b_class_REFTIME_get.cpp 
        rsa306b_class_REFTIME_set.cpp 
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

            general purpouse
            DEVICE
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
#define DEBUG_MIN 1917    // when activated, prints essential information
//#define DEBUG_ERR 1492    // when activated, prints *_error_checks() that result in an error condition

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
        // status of internal non-API function calls
        const int CALL_SUCCESS = 7777777;             // the function call was successful
        const int CALL_FAILURE = -7777777;            // the function call failed
        // common initialization values, by data type
        const char INIT_CHAR = 'Z';
        const char INIT_STR[6] = "ZZZZZ";
        const double INIT_DOUBLE = -9999.9999;
        const float INIT_FLOAT = -9999.9;
        const int INIT_INT = -9999;
        // device limits for the RSA-306B
        const double EXTERNAL_FREQUENCY = 10e6;         // external reference frequency, required
        const double EXTERNAL_AMPLITUDE_dbm = 10;           // allows +/- 10 dbm maximum amplitude  
        const double REFERENCE_LEVEL_MAX_dbm = 30;      // highest measurable signal power
        const double REFERENCE_LEVEL_MIN_dbm = -130;    // smallest measurable signal power
        const double SPAN_MAX_Hz = 40e6;                // largest measurable bandwith
        const double SPAN_MIN_Hz = 100;                 // smallest measurable bandwith 

    // general purpouse
        rsa306b();    
        ~rsa306b(); 
        RSA_API::ReturnStatus get_api_return_status();
        void get_api_return_status_string(char* carrier);
        int get_gp_return_status();
        void print_all_const();

    // ALIGN
        // functions for user action
        void align_execute_alignment();
        void align_print_all(); 
        // getters
        bool align_get_is_warmed();
        bool align_get_need_alignment();
          
    // CONFIG
        // functions for user action
        void config_update_cf_rl(double cf_Hz, double rl_dbm);
        void config_print_all();
        void config_use_external_reference_source(RSA_API::FREQREF_SOURCE source);
        // getters
        double config_get_center_frequency_hz();
        double config_get_center_frequency_max_hz();
        double config_get_center_frequency_min_hz();
        double config_get_reference_level_dbm();
        RSA_API::FREQREF_SOURCE config_get_frequency_reference_source();
        double config_get_external_frequency_reference_hz();

    // DEVICE
        // functions for user action
        void device_connect(); 
        void device_disconnect();
        void device_prepare_run();
        void device_print_all();        
        void device_reset();                
        void device_run();
        void device_start_frame_transfer();                  
        void device_stop();  
        // getters
        int device_get_id();
        void device_get_info_type(RSA_API::DEVICE_INFO* devInfo);
        bool device_get_is_connected();
        bool device_get_is_over_temperature();
        bool device_get_is_running(); 

    // REFTIME
        struct reftime_type
        {
            time_t seconds;    // seconds since 00:00:00, Jan 1, 1970, UTC
            uint64_t nanos;    // off set from seconds                               
            uint64_t stamp;    // counter-valued, depends on timestamp rate                                
        }; typedef struct reftime_type reftime_type;
        // functions for user action
        void reftime_start_split();
        void reftime_stop_split();
        void reftime_print_all();
        void reftime_timestamp_2_time (reftime_type* r_t);    // tool to make any time
        void reftime_time_2_timestamp (reftime_type* r_t);    // tool to make any timestamp
        // getters
        void reftime_get_date_timestamp(char* dts);           // gets current internal date-time-stamp
        double reftime_get_running();
        double reftime_get_split();
        RSA_API::REFTIME_SRC reftime_get_source_select();
        uint64_t reftime_get_timestamp_rate();
        void reftime_get_begin_type(reftime_type* r_t);
        void reftime_get_current_type(reftime_type* r_t);
        double reftime_get_split_cpu();
        double reftime_get_running_cpu();
        

    private:

    // general purpose
        char _helper_string[BUF_E];
        char _holder_string[BUF_F];
        int _gp_return_status;                       // set when calling non-API functions
        RSA_API::ReturnStatus _api_return_status;    // enum, all API functions return this
        // internal-use functions
        void _api_error_check();                     // checks status of API function calls
        void _gp_error_check();                      // checks status of internal function calls
        void _init_member_variables();               // initializes all member variables

    // API group "ALIGN"
        bool _align_need_alignment;
        bool _align_is_warmed;
        // setters
        void _align_set_need_alignment();
        void _align_set_is_warmed();
        
    // API group "AUDIO"

    // API group "CONFIG"
        double _config_center_frequency_hz;
        double _config_center_frequency_max_hz;
        double _config_center_frequency_min_hz;
        double _config_reference_level_dbm;
        double _config_external_reference_frequency_hz;
        RSA_API::FREQREF_SOURCE _config_frequency_reference_source_select;    // enum
        void _config_init();                                                  // called during each connection
        // setters
        void _config_set_center_frequency_hz();
        void _config_set_reference_level_dbm();
        void _config_set_frequency_reference_source();

    // API group "DEVICE"
        bool _device_is_connected;
        bool _device_is_over_temperature;
        bool _device_is_running;
        int _device_id;
        RSA_API::DEVICE_INFO _device_info_type;    // struct, has 6 strings
        // setters
        void _device_set_id(int new_value);
        void _device_set_info_type();
        void _device_set_is_connected(bool new_value);
        void _device_set_is_over_temperature();
        void _device_set_is_running();
        
    // API group "DPX"

    // API group "IFSTREAM"

    // API group "IQBLK"

    // API group "IQSTREAM"

    // API group "PLAYBACK"

    // API group "SPECTRUM"
        RSA_API::SpectrumDetectors _spectrum_detector_select;             // enum, condition to aquire bin
        RSA_API::SpectrumVerticalUnits _spectrum_vertical_unit_select;    // enum, data to be output on Y-axis
        RSA_API::SpectrumTraces _spectrum_trace_select;                   // enum, type of trace to get
        RSA_API::SpectrumWindows _spectrum_window_select;                 // enum, type of filtering window
        RSA_API::Spectrum_Limits _spectrum_limits_type;                   // struct, with 6 doubles and 2 ints as limits
        RSA_API::Spectrum_Settings _spectrum_settings_type;               // struct, with internal + external settings
        RSA_API::Spectrum_TraceInfo _spectrum_trace_info_type;            // struct, used for timing and "AcqDataStatus"
        bool is_enabled_trace;
        float* trace_data; // dynamic
        // setters
        void _spectrum_set_detector_select();
        void _spectrum_set_vertical_unit_select();
        void _spectrum_set_trace_select();
        void _spectrum_set_window_select();
        void _spectrum_set_limits_type();
        void _spectrum_set_settings_type();
        void _spectrum_set_trace_info_type();
        void _spectrum_set_is_enabled_trace();
        void _spectrum_set_trace_data(); // ??? where are the freqs?
        
    // API group "REFTIME"
        char _reftime_date_timestamp[BUF_C];                   
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
            clock_t begin;
            clock_t lead;
            clock_t trail;
            double running;
            double split;
        }; typedef struct t_cpu t_cpu;    // need a CPU clock capability
        t_cpu _reftime_cpu;
        // setters
        void _reftime_set_date_timestamp();
        void _reftime_set_running();
        void _reftime_set_split();
        void _reftime_set_split_lead();
        void _reftime_set_split_trail();
        void _reftime_set_source_select();
        void _reftime_set_timestamp_rate();
        void _reftime_set_begin_type();
        void _reftime_set_current_type();

    // API group "TRIG"

};


#endif


////////~~~~~~~~END>  rsa306b.h
