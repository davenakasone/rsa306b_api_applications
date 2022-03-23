/*
    this class uses the API to interface with the RSA-306B Spectrum Analyzer
    Tektronix requires the 2 shared objects to be linked and the RSA_API.h header
    using 1, and only one instance of this class, can remove the abstraction in the API
    do not try to use more than one instance


    Source files, by API function group:
        rsa306b_class_ALIGN.cpp 
        rsa306b_class_CONFIG.cpp
        rsa306b_class_DEVICE.cpp 
        rsa306b_class_REFTIME.cpp 
        rsa306b_class_SPECTRUM.cpp
        rsa306b_class.cpp  // general purpose


    API function groups:

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
            DEVICE_GetFPGAVersion()
            DEVICE_GetFWVersion()
            DEVICE_GetHWVersion()
            DEVICE_GetNomenclature()
            DEVICE_GetAPIVersion()
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
            REFTIME_GetTimestampRate()

        Tracking # not used, only for RSA500/600 series

        Trigger # this group looks useful, try it out later


    a method of form "rsa_*" replaces the user's need to interact with the API
    a method of form "print_*" may use the API, but just prints to stdout
    an API enum has form "*_select"
    an API struct has form "*_type"
    const data types are used to assure type-safe constants
    #define VALUE is used when const is not possible
    any fixed value should be controlled in this header file
    any library or header needed for the class should be included in this header file (not source files)

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

// initialization values
const char INIT_CHAR = 'Z';
const double INIT_DOUBLE = -9999.9999;
const float INIT_FLOAT = -9999.9;
const int INIT_INT = -9999;
const char INIT_STR[] = "ZZZZZ";

// device limits for the RSA-306B
const double FREQUENCY_MIN_HZ = 9e3;           // lowest measurable frequency  
const double FREQUENCY_MAX_HZ = 6.2e9;         // highest measurable frequency
const double EXTERNAL_FREQUENCY = 10e6;        // external reference allows +/- 10 Hz
const double REFERENCE_LEVEL_MIN_DB = -130;    // smallest measurable signal power
const double REFERENCE_LEVEL_MAX_DB = 30;      // highest measurable signal power
const double SPAN_MAX_HZ = 40e6;               // largest measurable bandwith
const double SPAN_MIN_HZ = 10;                 // smallest measurable bandwith


class rsa306b
{
    public:

        // general purpouse
        rsa306b();    
        ~rsa306b();   

        // ALIGN
        void rsa_align();
        void print_alignment();   

        // CONFIG
        void rsa_configure_cf_rl(double cf, double rl);
        void print_configuration();

        // DEVICE
        void rsa_connect();              
        void print_device_temperature();    
        void print_device_info();          
        void rsa_reset();                
        void rsa_run();                  
        void rsa_stop();   

        // REFTIME
        void print_time_begin();
        void print_time_info();
        void print_time_now();
        void print_time_running();
        void print_time_split();
        
    private:

        // general purpose
            void init_member_variables();
        char helper_string[BUF_E];
        char holder_string[BUF_F];
        RSA_API::ReturnStatus api_return_status;  // do not initialize, enum, most API functions return this

        // API group "ALIGN"
            void execute_alignment();
            void execute_warm_up();
        bool is_needed_alignment;
        bool is_warmed_up;

        // API group "AUDIO"

        // API group "CONFIG"
        double center_frequency;
        double center_frequency_max;
        double center_frequency_min;
        double reference_level;
        RSA_API::FREQREF_SOURCE frequency_reference_source_select;    // enum, where source of frequency is

        // API group "DEVICE"
            void error_check(); 
        bool is_connected;
        bool is_over_temperature_limit;
        bool is_running;
        char device_api_version[RSA_API::DEVINFO_MAX_STRLEN];
        char device_error_string[RSA_API::DEVINFO_MAX_STRLEN];
        char device_firm_ware_version[RSA_API::DEVINFO_MAX_STRLEN];
        char device_fpga_version[RSA_API::DEVINFO_MAX_STRLEN];
        char device_hardware_version[RSA_API::DEVINFO_MAX_STRLEN];
        char device_nomenclature[RSA_API::DEVINFO_MAX_STRLEN];
        char device_serials[RSA_API::DEVSRCH_MAX_NUM_DEVICES][RSA_API::DEVSRCH_SERIAL_MAX_STRLEN];
        char device_types[RSA_API::DEVSRCH_MAX_NUM_DEVICES][RSA_API::DEVSRCH_TYPE_MAX_STRLEN];
        int devices_found;
        int device_ids[RSA_API::DEVSRCH_MAX_NUM_DEVICES];
        
        // API group "DPX"

        // API group "IFSTREAM"

        // API group "IQBLK"

        // API group "IQSTREAM"

        // API group "PLAYBACK"

        // API group "SPECTRUM"
        RSA_API::SpectrumDetectors spectrum_detector_select;             // enum, condition to aquire bin
        RSA_API::SpectrumVerticalUnits spectrum_vertical_unit_select;    // enum, data to be output on Y-axis
        RSA_API::SpectrumTraces spectrum_trace_select;                   // enum, type of trace to get
        RSA_API::SpectrumWindows spectrum_window_select;                 // enum, type of filtering window
        RSA_API::Spectrum_Limits spectrum_limits_type;                   // struct, with 6 doubles and 2 ints as limits
        RSA_API::Spectrum_Settings spectrum_settings_type;               // struct, with internal + external settings
        RSA_API::Spectrum_TraceInfo spectrum_trace_info_type;            // struct, used for timing and "AcqDataStatus"
        
        
        bool is_enabled_trace;
        float* trace_data; // dynamic
        






        // API group "REFTIME", do not initialize member variables
            void record_date_time_stamp(time_t time_in, uint64_t nano_in);
            void record_running_time();
            void record_start_time();
            void record_time_now();
            void record_time_split();
        char date_time_stamp[BUF_B];                   
        double seconds_since_reference_time_set;
        double time_split;
        double time_split_lead;
        double time_split_trail;
        RSA_API::REFTIME_SRC reference_time_source_select;    // enum, where time source is located
        time_t current_time_seconds;                          // seconds since 00:00:00, Jan 1, 1970, UTC
        time_t reference_time_seconds;                        // seconds since 00:00:00, Jan 1, 1970, UTC
        uint64_t current_time_nano_seconds;                   // off set from seconds
        uint64_t current_time_stamp;                          // counter valued
        uint64_t reference_time_nano_seconds;                 // off set from seconds
        uint64_t reference_time_stamp;                        // counter valued
        uint64_t time_stamp_sampling_rate;                    // rate of the time-stamp counter's clock 

        // API group "TRIG"
};


#endif


////////~~~~~~~~END>  rsa306b.h
