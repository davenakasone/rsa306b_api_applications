/*
    variables for the 'siq_manager_class'
    at some point, make the constants class applicable to all these...
*/

#include "../control/resourcez.h"

#define FIELDS_IN_IQ_FILE 20

typedef enum
{
    no_error = 0,

} return_status_enum;


////~~~~


typedef struct siq_manager_constants
{
    const std::size_t INIT_STL = 3;
    const char INIT_CHAR_PTR[5] = "ZZZZ";
    const int INIT_NUMBER = 0;

    const int CORRECT_IQ_FILE_VERSION = 1;

    const char header_fields[FIELDS_IN_IQ_FILE][BUF_A] =
        {
            "RSASIQHT",        // 0
            "FileDateTime",    // 1
            "Hardware",        // 2
            "Software/Firmware",  // 3
            "ReferenceLevel",  // 4
            "CenterFrequency", // 5
            "SampleRate", // 6
            "AcqBandwidth", // 7
            "NumberSamples", // 8
            "NumberFormat", // 9
            "DataScale", // 10
            "DataEndian", // 11
            "RecordUtc-Sec", // 12
            "RecordUtcTime", // 13
        };
    
    const char DATA_FORMAT_SINGLE[BUF_A] = "IQ-Single";
    const char DATA_FORMAT_INT16[BUF_A] = "IQ-Int16";
    const char DATA_FORMAT_INT32[BUF_A] = "IQ-Int32";

    const char ENDIAN_BIG[BUF_A] = "Big";
    const char ENDIAN_LITTLE[BUF_A] = "Little";

} siq_manager_constants;


////~~~~


typedef struct siq_manager_struct
{
    // header identifier
    size_t header_size_in_bytes;
    int iq_file_version;

    // file date time
    int file_year;
    int file_month;
    int file_day;
    int file_hour;
    int file_minute;
    int file_second;
    int file_milli_second;

    // hardware
    char instrument_nomenclature[BUF_A];
    char serial_number[BUF_A];

    // Software and Firmware
    char version_api[BUF_A];
    char version_usb[BUF_A];
    char version_fpga[BUF_A];
    char version_board[BUF_A];

    // reference level
    double reference_level_dbm;

    // center frequency
    double center_frequency_hz;

    // sample rate
    double samples_per_second;

    // acquisition bandwidth
    double bandwidth_hz;

    // number of samples
    size_t iq_sample_pairs;

    // number format
    char data_format[BUF_A];

    // data scale
    double scale_factor;

    // data endian
    char edian[BUF_A];

    // record time UTC seconds
    int first_sample_utc_seconds;
    int first_sample_utc_nano_seconds;

    // record time UTC, timestamp
    int first_sample_utc_timestamp_year;
    int first_sample_utc_timestamp_month;
    int first_sample_utc_timestamp_day;
    int first_sample_utc_timestamp_hour;
    int first_sample_utc_timestamp_minute;

    // data block
    std::vector<RSA_API::Cplx32> data_block_cplx32_q;
    std::vector<RSA_API::CplxInt16> data_block_cplxint16_q;
    std::vector<RSA_API::CplxInt32> data_block_cplxint32_q;

} siq_manager_struct;


////////~~~~~~~~END>  siq_manager_struct.h





    
    RecordUtcTime
        the timestamp for the first IQ sample, UTC zone
        YYYY-MM-DDThh:mm:ss.ns    // formated date-time stamp...check this
        ie
            <string>:<YYYY>-<MM>-<DD>T<hh>:<mm>:<ss>.<ns>
            RecordUtcTime:2015-04-29T17:12:33.177054669
                parse with: 
                    utc_timestamp_year
                    utc_timestamp_month
                    utc_timestamp_day
                    utc_timestamp_hour
                    utc_timestamp_minute
                    utc_timestamp_second
                    utc_timestamp_nano_second
    RecordLclTime
        the timestamp for the first IQ sample, local time zone
        YYYY-MM-DDThh:mm:ss.ns    // formated date-time stamp...check this
        ie
            <string>:<YYYY>-<MM>-<DD>T<hh>:<mm>:<ss>.<ns>
            RecordLclTime:2015-04-29T17:12:33.177054669
                parse with: 
                    local_timestamp_year
                    local_timestamp_month
                    local_timestamp_day
                    local_timestamp_hour
                    local_timestamp_minute
                    local_timestamp_second
                    local_timestamp_nano_second
    TriggerIndex
        if triggering is not enabled, this index == 0
        sampleIndex    // the IQ sample index in the data block where the tigger event occured
        ie
            TriggerIndex:21733
                parse with:
                    trigger_index
    TriggerUtcSec
        if triggering is not enabled, these values == RecordUtcSec
        seconds        // seconds since ephoch, UTC
        nanoseconds    // nano seconds since epoch, UTC
        ie
            <string>:<seconds>.<nanoseconds>
            TriggerUtcSec:001430327553.177054669
                parse with:
                    trigger_seconds
                    trigger_nano_seconds
    TriggerUtcTime
        the timestamp for the first IQ sample trigger, UTC time
        if triggering is not enabled, this value is RecordUtcTime
        YYYY-MM-DDThh:mm:ss.ns    // formated date-time stamp...check this
        ie
            <string>:<YYYY>-<MM>-<DD>T<hh>:<mm>:<ss>.<ns>
            TriggerUtcTime:2015-04-29T17:12:33.177054669
                parse with: 
                    utc_trigger_timestamp_year
                    utc_trigger_timestamp_month
                    utc_trigger_timestamp_day
                    utc_trigger_timestamp_hour
                    utc_trigger_timestamp_minute
                    utc_trigger_timestamp_second
                    utc_trigger_timestamp_nano_second
    TriggerLclTime
        the timestamp for the first IQ sample trigger, local time
        if triggering is not enabled, this value is RecordLclTime
        YYYY-MM-DDThh:mm:ss.ns    // formated date-time stamp...check this
        ie
            <string>:<YYYY>-<MM>-<DD>T<hh>:<mm>:<ss>.<ns>
            TriggerLclTime:2015-04-29T17:12:33.177054669
                parse with: 
                    local_trigger_timestamp_year
                    local_trigger_timestamp_month
                    local_trigger_timestamp_day
                    local_trigger_timestamp_hour
                    local_trigger_timestamp_minute
                    local_trigger_timestamp_second
                    local_trigger_timestamp_nano_second
    AcqStatus
        acqStatusWord    // hex file status
        ie
            <string>:<acqStatusWord>
            AcqStatus:0x00000000
                parse with:
                    acq_status
    RefTimeSource
        only can be one at a time
        RSA-306B can't use all options
        System    // means the API us just using your computer's time    
        GnssRx    // GNSs receiver is providing timing data
        UserCa    // the user has made up their own timing system
        ie
            <string>:<refTimeSource>
            RefTimeSource:System
                parse with: 
                    reference_time_source
    FreqRefSource
        only can be one at a time
        RSA-306B can't use all options
        Intern    // the internal reference
        Extern    // the external reference source (see the SMA)
        GnssRx    // GNSS receiver provides oscillator
        UserCa    // user's calibration setting provides oscillator
        ie
            <string>:<freqRefSource>
            FreqRefSource:Intern
                parse with:
                    frequency_reference_source

