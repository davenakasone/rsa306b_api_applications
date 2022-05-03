/*
    containment scheme for variables of the "r3f_manager_class"
        user has a public instance of the struct, variables are not at risk, just for access
        private instance of the struct is kept, for operations
*/


#ifndef H_r3f_manager_struct
#define H_r3f_manager_struct

#include <stdint.h>
#include <float.h>

#define BUF_STR 64

// header known field sizes:
#define FIELD_ID_SIZE_BYTES 28
#define DEVICE_SERIAL_NUMBER_SIZE_BYTES 64
#define DEVICE_NOMENCLATURE_SIZE_BYTES 32
#define REFTIME_ELEMENTS 7
#define MAX_TABLE_ENTRIES 501
#define FOOTER_DISCARD 8

// header byte indexes, by section:
#define BI_FILE_ID_START 0L  
#define BI_FILE_ID_STOP 511L
#define BI_VERSION_INFO_START 512L
#define BI_VERSION_INFO_STOP 1023L
#define BI_INSTRUMENT_STATE_START 1024L
#define BI_ISNTRUMENT_STATE_STOP 2047L
#define BI_DATA_FORMAT_START 2048L
#define BI_DATA_FORMAT_STOP 3071L
#define BI_SIGNAL_PATH_START 3072L
#define BI_SIGNAL_PATH_STOP 4095L
#define BI_CHANNEL_CORRECTION_START 4096L
#define BI_CHANNEL_CORRECTION_MID 4352L
#define BI_CHANNEL_CORRECTION_STOP 12287L


struct r3f_manager_struct
{
// HEADER
    // File ID, [0:511], 512 bytes
        char file_id[BUF_STR];    // [0:27], 28 bytes
    //[27:EOB] EMPTY
    
    // Version Info[512:1023], 512 bytes
        int32_t endian_check;                  // [512:515], 4 bytes, should be "0x12345678"
        int8_t file_format_version;            // [516], 1 byte
        int8_t file_format_version_sub;        // [517], 1 byte
        int16_t file_format_version_part;      // [518:519], 2 bytes
        // "<file_format_version>.<file_format_version_sub>.<file_format_version_part>"
        int8_t api_software_version;           // [520], 1 byte
        int8_t api_software_version_sub;       // [521], 1 byte
        int16_t api_software_version_part;     // [522:523], 2 bytes
        // "<api_software_version>.<api_software_version_sub>.<api_software_version_part>"
        int8_t firmware_version;               // [524], 1 byte
        int8_t firmware_version_sub;           // [525], 1 byte
        int16_t firmware_version_part;         // [526:527], 2 bytes
        // "<firmware_version>.<firmware_version_sub>.<firmware_version_part>"
        int8_t fpga_version;                   // [528], 1 byte
        int8_t fpga_version_sub;               // [529], 1 byte
        int16_t fpga_version_part;             // [530:531], 2 bytes
        // "<fpga_version>.<fpga_version_sub>.<fpga_version_part>"
        char device_serial_number[BUF_STR];    // [532:595], 64 bytes
        char device_nomenclature[BUF_STR];     // [596:627], 32 bytes
    // [628:EOB] EMPTY

    // Instrument State[1024:2047], 1024 bytes
        double reference_level_dbm; // [1024:1031], 8 bytes
        double rf_center_frequency_hz; // [1032:1039], 8 bytes
        double device_temperature_celsius; // [1040:1047], 8 bytes
        int32_t alignment_state; // [1048:1051], 4 bytes, {0= not aligned, 1= aligned}
        int32_t frequecny_reference_state; // [1052:1055], 4 bytes, {0= internal, 1= external, 2=GNSS, 3=user}
        int32_t trigger_mode; // [1056:1059], 4 bytes, {0= free run, 1= triggered}
        int32_t trigger_source; // [1060:1063], 4 bytes, {0= external, 1=power}
        int32_t trigger_transition; // [1064:1067], 4 bytes, {1=rising, 2=falling}
        double trigger_level_dbm; // [1068:1075], 8 bytes
    // [1076:EOB] EMPTY

    // Data Format[2048:3071], 1024 bytes
        int32_t file_data_type;                             // [2048:2051], 4 bytes, {should be "161" for 16-bit integer IF samples}
        int32_t byte_offset_to_first_frame;                 // [2052:2055], 4 bytes, {should be "16384"}
        int32_t size_of_frame_bytes;                        // [2056:2059], 4 bytes, {should be "16384"}
        int32_t byte_offset_to_sample_data_in_frame;        // [2060:2063], 4 bytes, {should be "0"}
        int32_t number_of_samples_per_frame;                // [2064:2067], 4 bytes, {should be "8178"}
        int32_t byte_offset_to_non_sample_data_in_frame;    // [2068:2071], 4 bytes, {should be "16356"}
        int32_t size_of_non_sample_data_in_frame_bytes;     // [2072:2075], 4 bytes, {should be "28"}
        double center_frequency_if_sampled_hz;              // [2076:2083], 8 bytes, {IF samples are 28 MHz + LO offset}
        double samples_per_second;                          // [2084:2091], 8 bytes, {should be "112e6"}
        double usable_bandwidth;                            // [2092:2099], 8 bytes, {the rbw of the IF filter set}
        int32_t file_data_corrected;                        // [2300:2303], 4 bytes, {0=uncorrected}
        int32_t reftime_local_source;                       // [2304:2307], 4 bytes, {0=local}
        int32_t reftime_local[REFTIME_ELEMENTS];            // 7*4 bytes each, [2308:2335], YY:MM:DD:hh:mm:ss:nn, local wall clock
        uint64_t fpga_sample_count;                         // [2336:2343], 8 bytes
        uint64_t fpga_sample_counter_ticks_per_second;      // [2344:2351], 8 bytes
        int32_t reftime_utc[REFTIME_ELEMENTS];              // 7*4 bytes each, [2352:2379], YY:MM:DD:hh:mm:ss:nn, zulu wall clock
        int32_t reftime_source;                             // [2380:2383], 4 bytes, {0=unknown, 1=system, 2=GNSS, 3=user}
        uint64_t timestamp_of_first_sample;                 // [2384:2391], 8 bytes
        int32_t reftime_first_sample[REFTIME_ELEMENTS];     // 7*4 bytes each, [2392:2419], YY:MM:DD:hh:mm:ss:nn, local wall clock, first sample
    // [2420:EOB] EMPTY

    // Signal Path[3072:4095], 1024 bytes
        double sample_gain_scaling_factor;    // [3072:3079], 8 bytes, {IF and IQ data should be scaled to V on 50 ohms}
        double signal_path_delay_seconds;     // [3080:3087], 8 bytes, {hopefully it is zero}
    // [3088:EOB] EMPTY

    // Channel Correction[4096:12287], 8192 bytes
        int32_t channel_correction_type;             // [4096:4099], 4 bytes, {0=LF, 1=RF/IF}
        // [4100:4351] EMPTY, 252 bytes of dead space
        int32_t number_of_table_entries;             // [4352:4355], 4 bytes, {the max is "501"}
        float table_frequency[MAX_TABLE_ENTRIES];    // <number_of_table_entries> * 4 bytes
        float table_amplitude[MAX_TABLE_ENTRIES];    // <number_of_table_entries> * 4 bytes
        float table_phase[MAX_TABLE_ENTRIES];        // <number_of_table_entries> * 4 bytes
    // [:12287] EMPTY

    // [12288:16383] reserved, EMPTY ...first data on 16384

// DATA
    int16_t extracted_sample;    // holds the 16-bit sample

// FOOTER
    uint8_t discard[FOOTER_DISCARD];
    uint32_t frame_id;
    uint16_t trigger_2_index;
    uint16_t trigger_1_index;
    uint16_t time_synchronization_index;
    uint16_t frame_status;
    uint64_t frame_timestamp;

}; typedef struct r3f_manager_struct r3f_manager_struct;


#endif


////////~~~~~~~~END>  r3f_manager_struct.h
        