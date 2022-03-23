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

        Time
            REFTIME_GetReferenceTime()
            REFTIME_GetCurrentTime()
            REFTIME_GetIntervalSinceRefTimeSet()
            REFTIME_GetReferenceTimeSource()

        Tracking # not used, only for RSA500/600 series

        Trigger # this group looks useful, try it out later


    a method of form "rsa_*" will directly use the API
    a method of form "print_*" may use the API, but just prints to stdout

    TODO:
        timer with splits
        DEBUG logger .txt
        date-time-stamp
        ...helper class by composition or make this a big API class

*/

#ifndef H_rsa306b_class
#define H_rsa306b_class

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../api_resourcez/RSA_API.h" // has <time.h> and <stdint.h> already

#define GET_NAME(var) #var

//#define DEBUG_CLI 1776    // when activated, prints __LINE__, __FILE__, __func__ for each call
//#define DEBUG_MIN 1917    // when activated, prints essential information
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
        void print_temperature();    
        void print_device_info();          
        void rsa_reset();                
        void rsa_run();                  
        void rsa_stop();   

        // REFTIME
        void print_date_time_stamp();
        void print_running_time_seconds();
        void print_time_info();
        void print_time_now();
        void print_time_split_seconds();
        

    private:

        // general purpose
            void init_member_variables();
        char helper_string[BUF_E];
        char holder_string[BUF_F];
        RSA_API::ReturnStatus api_return_status;  // do not initialize

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
        RSA_API::FREQREF_SOURCE frequency_reference_source;

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
        RSA_API::Spectrum_Settings spectrum_settings;

        // API group "REFTIME"
            void record_date_time_stamp();
            void record_start_time();
            void record_time_now();
            void record_time_split();
        char date_time_stamp[BUF_B];
        double seconds_since_reference_time_set;
        double time_split_lead;
        double time_split_trail;
        RSA_API::REFTIME_SRC reference_time_source;
        time_t current_time_seconds;             // seconds since 00:00:00, Jan 1, 1970, UTC
        time_t reference_time_seconds;           // seconds since 00:00:00, Jan 1, 1970, UTC, do not initialize
        uint64_t current_time_nano_seconds;      // off set from seconds
        uint64_t current_time_stamp;             // counter valued
        uint64_t reference_time_nano_seconds;    // off set from seconds, do not initialize
        uint64_t reference_time_stamp;           // counter valued, do not initialize

        // API group "TRIG"
};


#endif


////////~~~~~~~~END>  rsa306b.h
