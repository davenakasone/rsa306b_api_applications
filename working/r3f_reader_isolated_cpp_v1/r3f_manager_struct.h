/*
    containment scheme for variables of the "r3f_manager_class"
        user has a public instance of the struct, variables are not at risk, just for access
        private instance of the struct is kept, for operations
*/


#ifndef H_r3f_manager_struct
#define H_r3f_manager_struct

#include <stdint.h>
#include <float.h>

struct r3f_manager_struct
{



}; typedef struct r3f_manager_struct r3f_manager_struct;


#endif


////////~~~~~~~~END>  r3f_manager_struct.h

File ID[0:511], 512 bytes
        [0:27]  28 bytes, char* file_id
        [27:EOB] EMPTY

    Version Info[512:1023], 512 bytes
        [512:515], 4 bytes, int32_t endian_check, should be "0x12345678"
        [516], 1 byte, int8_t file_format_version
        [517], 1 byte, int8_t file_format_version_sub
        [518:519] 2 bytes, int16_t file_format_version_part
            "<file_format_version>.<file_format_version_sub>.<file_format_version_part>"
        [520], 1 byte, int8_t api_software_version
        [521], 1 byte, int8_t api_software_version_sub
        [522:523], 2 bytes, int16_t api_software_version_part
            "<api_software_version>.<api_software_version_sub>.<api_software_version_part>"
        [524], 1 byte, int8_t firmware_version
        [525], 1 byte, int8_t firmware_version_sub
        [526:527], 2 bytes, int16_t firmware_version_part
            "<firmware_version>.<firmware_version_sub>.<firmware_version_part>"
        [528], 1 byte, int8_t fpga_version
        [529], 1 byte, int8_t fpga_version_sub
        [530:531], 2 bytes, int16_t_t fpga_version_part
            "<fpga_version>.<fpga_version_sub>.<fpga_version_part>"
        [532:595], 64 bytes, char* device_serial_number
        [596:627], 32 bytes, char* device_nomenclature
        [628:EOB] EMPTY

    Instrument State[1024:2047], 1024 bytes
        [1024:1031], 8 bytes, double reference_level_dbm
        [1032:1039], 8 bytes, double rf_center_frequency_hz
        [1040:1047], 8 bytes, double device_temperature_celsius
        [1048:1051], 4 bytes, int32_t alignment_state {0= not aligned, 1= aligned}
        [1052:1055], 4 bytes, int32_t frequecny_reference_state {0= internal, 1= external, 2=GNSS, 3=user}
        [1056:1059], 4 bytes, int32_t trigger_mode {0= free run, 1= triggered}
        [1060:1063], 4 bytes, int32_t trigger_source {0= external, 1=power}
        [1064:1067], 4 bytes, int32_t trigger_transition {0=rising, 1=falling}
        [1068:1075], 8 bytes, double trigger_level_dbm
        [1076:EOB] EMPTY

    Data Format[2048:3071], 1024 bytes
        [2048:2051], 4 bytes, int32_t file_data_type {should be "161" for 16-bit integer IF samples}
        file data structure descriptor
            [2052:2055], 4 bytes, int32_t byte_offset_to_first_frame {should be "16384"}
            [2056:2059], 4 bytes, int32_t size_of_frame_bytes {should be "16384"}
            [2060:2063], 4 bytes, int32_t byte_offset_to_sample_data_in_frame {should be "0"}
            [2064:2067], 4 bytes, int32_t number_of_samples_per_frame {should be "8178"}
            [2068:2071], 4 bytes, int32_t byte_offset_to_non_sample_data_in_frame {should be "16356"}
            [2072:2075], 4 bytes, int32_t size_of_non_sample_data_in_frame_bytes {should be "28"}
        [2076:2083], 8 bytes, double center_frequency_if_sampled_hz {IF samples are 28 MHz + LO offset}
        [2084:2091], 8 bytes, double samples_per_second {should be "112e6"}
        [2092:2099], 8 bytes, double usable_bandwidth {the rbw of the IF filter set}
        [2300:2303], 4 bytes, int32_t file_data_corrected {0=uncorrected}
        [2304:2307], 4 bytes, int32_t reftime_local_source {0=local}
        REFTIME Wall time
            [2308:2311], 4 bytes, int32_t reftime_year
            [2312:2315], 4 bytes, int32_t reftime_month
            [2316:2319], 4 bytes, int32_t reftime_day
            [2320:2323], 4 bytes, int32_t reftime_hour
            [2324:2327], 4 bytes, int32_t reftime_minute
            [2328:2331], 4 bytes, int32_t reftime_second
            [2332:2335], 4 bytes, int32_t reftime_nano_second
        [2336:2343], 8 bytes, uint64_t fpga_sample_count
        [2344:2351], 8 bytes, utin64_t fpga_sample_counter_ticks_per_second
        REFTIME UTC
            [2352:2355], 4 bytes, int32_t reftime_utc_year
            [2356:2359], 4 bytes, int32_t reftime_utc_month
            [2360:2363], 4 bytes, int32_t reftime_utc_day
            [2364:2367], 4 bytes, int32_t reftime_utc_hour
            [2368:2371], 4 bytes, int32_t reftime_utc_minute
            [2372:2375], 4 bytes, int32_t reftime_utc_second
            [2376:2379], 4 bytes, int32_t reftime_utc_nano_second
        [2380:2383], 4 bytes, int32_t reftime_source {0=unknown, 1=system, 2=GNSS, 3=user}
        [2384:2391], 8 bytes, uint64_t timestamp_of_first_sample
        Start Time (local)
            [2392:2395], 4 bytes, int32_t first_sample_year
            [2396:2399], 4 bytes, int32_t first_sample_month
            [2400:2403], 4 bytes, int32_t first_sample_day
            [2404:2407], 4 bytes, int32_t first_sample_hour
            [2408:2411], 4 bytes, int32_t first_sample_minute
            [2412:2415], 4 bytes, int32_t first_sample_second
            [2416:2419], 4 bytes, int32_t first_sample_nano_second
        [2420:EOB] EMPTY

    Signal Path[3072:4095], 1024 bytes
        [3072:3079], 8 bytes, double sample_gain_scaling_factor {IF and IQ data should be scaled to V on 50 ohms}
        [3080:3087], 8 bytes, double signal_path_delay_seconds {hopefully it is zero}
        [3088:EOB] EMPTY

    Channel Correction[4096:12287], 8192 bytes
        [4096:4099], 4 bytes, int32_t channel_correction_type {0=LF, 1=RF/IF}
        [5000:5251] EMPTY
        [5252:5255], 4 bytes, int32_t number_of_table_entries {the max is "501"}
        <number_of_table_entries> * 4 bytes, float* table_frequency
        <number_of_table_entries> * 4 bytes, float* table_amplitude
        <number_of_table_entries> * 4 bytes, float* table_phase
        [:12287] EMPTY
    
    [12288:16383] reserved, EMPTY
