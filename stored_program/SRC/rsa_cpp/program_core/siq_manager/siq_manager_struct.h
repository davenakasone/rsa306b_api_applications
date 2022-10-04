/*
    variables for the 'siq_manager_class'
*/

#ifndef H_siq_manager_struct
#define H_siq_manager_struct


#include "../control/resourcez.h"


struct siq_manager_struct
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
    //char f3_version_board[BUF_A];  does not appear to be in current version

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
    std::vector<RSA_API::Cplx32>    data_block_cplx32_v;
    std::vector<RSA_API::CplxInt16> data_block_cplxint16_v;
    std::vector<RSA_API::CplxInt32> data_block_cplxint32_v;
};
typedef struct siq_manager_struct siq_manager_struct;


#endif


////////~~~~~~~~END>  siq_manager_struct.h
