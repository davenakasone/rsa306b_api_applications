/*
    variables, constants, and macros for the 'siq_manager_class'
    with annonymous enums guarunteed to take "int" datatype
*/

#ifndef H_siq_manager_struct
#define H_siq_manager_struct


#include "../control/resourcez.h"

#define SIQ_ERROR_CODES 23        // return status and error code possibilities within "siq_manager_class"
#define SIQ_HEADER_FIELDS 22      // number of fields in an IQ data file header
#define SIQ_NUMBER_FORMATS 3      // f9 NumberFormat, possible formats data samples in IQ file can use
#define SIQ_ENDIANS 2             // f11 DataEndian, possible endians data samples in IQ file can use
#define SIQ_REF_TIME_SOURCES 3    // f20 RefTimeSource, possible time sources IQ file can use 
#define SIQ_FREQ_REF_SOURCES 4    // f21 FreqRefSource, possible frequency sources IQ file can use

const int CORRECT_IQ_FILE_VERSION = 1;               // f0 RSASIQHT, all "siq" files should be on version #1 for the RSA-306B
const char GOOD_ACQ_STATUS[11]    = "0x00000000";    // f19 AcqStatus, expected field value for a clean acquisition
const std::size_t INIT_STL        = 3;
const char INIT_CHARP[5]          = "ZZZZ";
const int INIT_INT                = 0;
const float INIT_FLOAT            = 0.001;
const double INIT_DOUBLE          = 0.0001;

// used for error-return code + associated message
const char ERROR_CODES[SIQ_ERROR_CODES][BUF_A] =
{
    "no error",                         // index 0
    "print_data() range failure",       // index 1
    "fptr_read busy",                   // index 2
    "input_file not found",             // index 3
    "fseek() returned non-zero",        // index 4
    "fclose() returned non-zero",       // index 5
    "empty string, allocate it",        // index 6
    "input_file was bad",               // index 7
    "invalid *.siq file",               // index 8
    "low bytes in siq file",            // index 9
    "fread() failure",                  // index 10
    "output_file not open",             // index 11
    "fputs() failed to write",          // index 12
    "fgets() nothing",                  // index 13
    "failure parsing header fields",    // index 14
    "snprintf() failed",                // index 15
    "strncat() failed",                 // index 16
    "strtod() failed",                  // index 17
    "failed to find field",             // index 18
    "file loaded with no data",         // index 19
    "data load mismatch",               // index 20
    "directory not found"               // index 21
};
typedef enum 
{
    no_error                      = 0 ,        
    print_data_range_failure      = 1 ,        
    fptr_read_busy                = 2 ,         
    input_file_not_found          = 3 ,         
    fseek_returned_non_zero       = 4 ,         
    fclose_returned_non_zero      = 5 ,        
    empty_string                  = 6 ,         
    input_file_bad                = 7 ,         
    invalid_siq_file              = 8 ,         
    low_bytes_in_siq_file         = 9 ,        
    fread_failure                 = 10,        
    out_file_not_open             = 11,         
    fputs_failed_write            = 12,         
    fgets_nothing                 = 13,         
    failure_parsing_header_fields = 14,
    snprintf_failed               = 15,
    strncat_failed                = 16,
    strtod_failed                 = 17,
    failed_to_find_field          = 18,
    file_loaded_with_no_data      = 19,
    data_load_mismatch            = 20,
    directory_not_found           = 21             
} error_code_select;

// for searching the header of the "siq" file for field entries
const char HEADER_FIELDS[SIQ_HEADER_FIELDS][BUF_A] =
{
    "RSASIQHT",             // index 0
    "FileDateTime",         // index 1
    "Hardware",             // index 2
    "Software/Firmware",    // index 3
    "ReferenceLevel",       // index 4
    "CenterFrequency",      // index 5
    "SampleRate",           // index 6
    "AcqBandwidth",         // index 7
    "NumberSamples",        // index 8
    "NumberFormat",         // index 9
    "DataScale",            // index 10
    "DataEndian",           // index 11
    "RecordUtcSec",         // index 12
    "RecordUtcTime",        // index 13
    "RecordLclTime",        // index 14
    "TriggerIndex",         // index 15
    "TriggerUtcSec",        // index 16
    "TriggerUtcTime",       // index 17
    "TriggerLclTime",       // index 18
    "AcqStatus",            // index 19
    "RefTimeSource",        // index 20
    "FreqRefSource"         // index 21

};
enum
{
    RSASIQHT          = 0,     // index 0
    FileDateTime      = 1,     // index 1
    Hardware          = 2,     // index 2
    Software_Firmware = 3,     // index 3
    ReferenceLevel    = 4,     // index 4
    CenterFrequency   = 5,     // index 5
    SampleRate        = 6,     // index 6
    AcqBandwidth      = 7,     // index 7
    NumberSamples     = 8,     // index 8
    NumberFormat      = 9,     // index 9
    DataScale         = 10,    // index 10
    DataEndian        = 11,    // index 11
    RecordUtcSec      = 12,    // index 12
    RecordUtcTime     = 13,    // index 13
    RecordLclTime     = 14,    // index 14
    TriggerIndex      = 15,    // index 15
    TriggerUtcSec     = 16,    // index 16
    TriggerUtcTime    = 17,    // index 17
    TriggerLclTime    = 18,    // index 18
    AcqStatus         = 19,    // index 19
    RefTimeSource     = 20,    // index 20
    FreqRefSource     = 21     // index 21
};

// f9 NumberFormat
const char NUMBER_FORMATS[SIQ_NUMBER_FORMATS][BUF_A] =
{
    "IQ-Single",    // index 0
    "IQ-Int16",     // index 1
    "IQ-Int32"      // index 2
};
enum
{
    NUMBER_FORMAT_SINGLE = 0,    // index 0
    NUMBER_FORMAT_INT16  = 1,    // index 1
    NUMBER_FORMAT_INT32  = 2     // index 2
};

// f11 DataEndian
const char ENDIANS[SIQ_ENDIANS][BUF_A] =
{
    "Little",    // index 0
    "Big"        // index 1
};
enum
{
    Little = 0,    // index 0
    Big = 1        // index 1
};

// f20 RefTimeSource
const char REF_TIME_SOURCES[SIQ_REF_TIME_SOURCES][BUF_A] =
{
    "System",    // index 0
    "GnssRx",    // index 1
    "UserCa"     // index 2
};

// f21 FreqRefSource
const char FREQ_REF_SOURCES[SIQ_FREQ_REF_SOURCES][BUF_A] =
{
    "Intern",    // index 0
    "Extern",    // index 1
    "GnssRx",    // index 2
    "UserCa"     // index 3
};

////~~~~


struct siq_manager
{
    // f0 RSASIQHT , header identifier
    int f0_header_size_in_bytes;
    int f0_iq_file_version;

    // f1 FileDateTime, file creation date and time
    int f1_file_year;
    int f1_file_month;
    int f1_file_day;
    int f1_file_hour;
    int f1_file_minute;
    int f1_file_second;
    int f1_file_milli_second;

    // f2 Hardware, hardware information
    char f2_instrument_nomenclature[BUF_A];
    char f2_serial_number[BUF_A];
    char f2_version[BUF_A];
    
    // f3 Software/Firmware, versions of the software and firmware
    char f3_version_api[BUF_A];
    char f3_version_usb[BUF_A];
    char f3_version_fpga[BUF_A];
    //char f3_version_board[BUF_A];

    // f4 ReferenceLevel, instrument reference level in dBm
    double f4_reference_level_dbm;

    // f5 CenterFrequency, instrument center frequency in Hz
    double f5_center_frequency_hz;

    // f6 SampleRate, the data sample rate in samples per second
    double f6_samples_per_second;

    // f7 AcqBandwidth, flat acquisition bandwidth of data, centered at 0Hz, IQ baseband
    double f7_bandwidth_hz;

    // f8 NumberSamples, number of IQ sample pairs stored in the data block
    int f8_iq_sample_pairs;

    // f9 NumberFormat, what format numbers in data block use
    char f9_number_format[BUF_A];

    // f10 DataScale, scale factor to convert int16_t and int32_t IQ formats 'volts into 50 ohms'
    double f10_scale_factor;    // the 'Single' or 'float' format will have this == 1

    // f11 DataEndian, indicates endian used to store values in the data block
    char f11_endian[BUF_A];

    // f12 RecordUtc-Sec, record time UTC seconds of first IQ sample in the data block
    int f12_first_sample_utc_seconds;
    int f12_first_sample_utc_nano_seconds;

    // f13 RecordUtcTime, UTC timestamp of first IQ sample in the data block
    int f13_first_sample_utc_timestamp_year;
    int f13_first_sample_utc_timestamp_month;
    int f13_first_sample_utc_timestamp_day;
    int f13_first_sample_utc_timestamp_hour;
    int f13_first_sample_utc_timestamp_minute;
    int f13_first_sample_utc_timestamp_second;
    int f13_first_sample_utc_timestamp_nano_second;

    // f14 RecordLclTime, Local timestamp of first IQ sample in the data block
    int f14_first_sample_local_timestamp_year;
    int f14_first_sample_local_timestamp_month;
    int f14_first_sample_local_timestamp_day;
    int f14_first_sample_local_timestamp_hour;
    int f14_first_sample_local_timestamp_minute;
    int f14_first_sample_local_timestamp_second;
    int f14_first_sample_local_timestamp_nano_second;

    // f15 TriggerIndex, sample index where tigger event occured
    int f15_tigger_index;    // if triggering is not enabled, == 0

    // f16 TriggerUtcSec, tigger time UTC seconds of sample at trigger index
    // if triggering is not enabled, == f12_first_sample_utc_*
    int f16_trigger_utc_seconds;         
    int f16_trigger_utc_nano_seconds; 
    
    // f17 TriggerUtcTime, UTC timestamp of the triggering event
    // if triggering is not enabled, == f13_first_sample_utc_timestamp_*
    int f17_trigger_utc_timestamp_year;
    int f17_trigger_utc_timestamp_month;
    int f17_trigger_utc_timestamp_day;
    int f17_trigger_utc_timestamp_hour;
    int f17_trigger_utc_timestamp_minute;
    int f17_trigger_utc_timestamp_second;
    int f17_trigger_utc_timestamp_nano_second;
    
    // f18 TriggerLclTime, local timestamp of the tiggering event
    // if triggering is not enabled, == f14_local_timestamp_*
    int f18_trigger_local_timestamp_year;
    int f18_trigger_local_timestamp_month;
    int f18_trigger_local_timestamp_day;
    int f18_trigger_local_timestamp_hour;
    int f18_trigger_local_timestamp_minute;
    int f18_trigger_local_timestamp_second;
    int f18_trigger_local_timestamp_nano_second;

    // f19 AcqStatus, see IQSTRM_STATUS_* enums to decode
    uint32_t f19_acq_status;

    // f20 RefTimeSource, time source used to set the API
    char f20_reference_time_source[BUF_A];

    // f21 FreqRefSource, frequency source used to set the API
    char f21_frequency_reference_source[BUF_A];

    // data block, interleaved... 'n == number of samples' 
    // I(0), Q(0), I(1), Q(1), ..., I(n-2), Q(n-2), I(n-1), Q(n-1)  
    std::vector<RSA_API::Cplx32> data_block_cplx32_v;
    std::vector<RSA_API::CplxInt16> data_block_cplxint16_v;
    std::vector<RSA_API::CplxInt32> data_block_cplxint32_v;
};


#endif


////////~~~~~~~~END>  siq_manager_struct.h
