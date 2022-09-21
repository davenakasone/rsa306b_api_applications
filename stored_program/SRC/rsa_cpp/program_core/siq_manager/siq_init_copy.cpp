// /*
//     initializer of the 'siq_handler_class'
//     copies private struct to the public struct

//     public:
//         #  none
    
//     private:
//         < 1 > _init()
//         < 2 > _copy_vars()

// */

// #include "siq_manager_class.h"


// /*
//     < 1 > private
//     initializing class members to known values
// */
// CODEZ siq_manager_class::_init()
// {
// #ifdef DEBUG_CLI
//     snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     // initialize the private members (error code updates last)
//     this->_file_loaded   = false;
//     this->_bytes_in_file = INIT_INT;
//     this->_byte_offset   = INIT_INT;
//     this->_fptr_write    = NULL;
//     this->_fptr_read     = NULL;
//     memset(this->_holder, '\0', BUF_F);
//     strcpy(this->_holder, INIT_CHARP);
//     memset(this->_helper, '\0', BUF_E);
//     strcpy(this->_helper, INIT_CHARP);
    
//     // initialize the private variable struct
//     this->_vars.f0_header_size_in_bytes = INIT_INT;
//     this->_vars.f0_iq_file_version      = CORRECT_IQ_FILE_VERSION;
    
//     this->_vars.f1_file_year         = INIT_INT;
//     this->_vars.f1_file_month        = INIT_INT;
//     this->_vars.f1_file_day          = INIT_INT;
//     this->_vars.f1_file_hour         = INIT_INT;
//     this->_vars.f1_file_minute       = INIT_INT;
//     this->_vars.f1_file_second       = INIT_INT;
//     this->_vars.f1_file_milli_second = INIT_INT;

//     memset(this->_vars.f2_instrument_nomenclature, '\0', BUF_A);
//     strcpy(this->_vars.f2_instrument_nomenclature, INIT_CHARP);
//     memset(this->_vars.f2_serial_number          , '\0', BUF_A);
//     strcpy(this->_vars.f2_serial_number          , INIT_CHARP);
//     memset(this->_vars.f2_version                , '\0', BUF_A);
//     strcpy(this->_vars.f2_version                , INIT_CHARP);

//     memset(this->_vars.f3_version_api, '\0', BUF_A);
//     strcpy(this->_vars.f3_version_api, INIT_CHARP);
//     //memset(this->_vars.f3_version_board, '\0', BUF_A);
//     //strcpy(this->_vars.f3_version_board, INIT_CHARP);
//     memset(this->_vars.f3_version_fpga, '\0', BUF_A);
//     strcpy(this->_vars.f3_version_fpga, INIT_CHARP);
//     memset(this->_vars.f3_version_usb , '\0', BUF_A);
//     strcpy(this->_vars.f3_version_usb , INIT_CHARP);

//     this->_vars.f4_reference_level_dbm = INIT_DOUBLE;

//     this->_vars.f5_center_frequency_hz = INIT_DOUBLE;

//     this->_vars.f6_samples_per_second = INIT_DOUBLE;

//     this->_vars.f7_bandwidth_hz = INIT_DOUBLE;

//     this->_vars.f8_iq_sample_pairs = INIT_INT;

//     memset(this->_vars.f9_number_format, '\0', BUF_A);
//     strcpy(this->_vars.f9_number_format, INIT_CHARP);

//     this->_vars.f10_scale_factor = INIT_DOUBLE;

//     memset(this->_vars.f11_endian, '\0', BUF_A);
//     strcpy(this->_vars.f11_endian, INIT_CHARP);

//     this->_vars.f12_first_sample_utc_seconds      = INIT_INT;
//     this->_vars.f12_first_sample_utc_nano_seconds = INIT_INT;
    
//     this->_vars.f13_first_sample_utc_timestamp_year        = INIT_INT;
//     this->_vars.f13_first_sample_utc_timestamp_month       = INIT_INT;
//     this->_vars.f13_first_sample_utc_timestamp_day         = INIT_INT;
//     this->_vars.f13_first_sample_utc_timestamp_hour        = INIT_INT;
//     this->_vars.f13_first_sample_utc_timestamp_minute      = INIT_INT;
//     this->_vars.f13_first_sample_utc_timestamp_second      = INIT_INT;
//     this->_vars.f13_first_sample_utc_timestamp_nano_second = INIT_INT;

//     this->_vars.f14_first_sample_local_timestamp_year        = INIT_INT;
//     this->_vars.f14_first_sample_local_timestamp_month       = INIT_INT;
//     this->_vars.f14_first_sample_local_timestamp_day         = INIT_INT;
//     this->_vars.f14_first_sample_local_timestamp_hour        = INIT_INT;
//     this->_vars.f14_first_sample_local_timestamp_minute      = INIT_INT;
//     this->_vars.f14_first_sample_local_timestamp_second      = INIT_INT;
//     this->_vars.f14_first_sample_local_timestamp_nano_second = INIT_INT;

//     this->_vars.f15_tigger_index = INIT_INT;

//     this->_vars.f16_trigger_utc_seconds      = INIT_INT;
//     this->_vars.f16_trigger_utc_nano_seconds = INIT_INT;

//     this->_vars.f17_trigger_utc_timestamp_year        = INIT_INT;
//     this->_vars.f17_trigger_utc_timestamp_month       = INIT_INT;
//     this->_vars.f17_trigger_utc_timestamp_day         = INIT_INT;
//     this->_vars.f17_trigger_utc_timestamp_hour        = INIT_INT;
//     this->_vars.f17_trigger_utc_timestamp_minute      = INIT_INT;
//     this->_vars.f17_trigger_utc_timestamp_second      = INIT_INT;
//     this->_vars.f17_trigger_utc_timestamp_nano_second = INIT_INT;

//     this->_vars.f18_trigger_local_timestamp_year        = INIT_INT;
//     this->_vars.f18_trigger_local_timestamp_month       = INIT_INT;
//     this->_vars.f18_trigger_local_timestamp_day         = INIT_INT;
//     this->_vars.f18_trigger_local_timestamp_hour        = INIT_INT;
//     this->_vars.f18_trigger_local_timestamp_minute      = INIT_INT;
//     this->_vars.f18_trigger_local_timestamp_second      = INIT_INT;
//     this->_vars.f18_trigger_local_timestamp_nano_second = INIT_INT;

//     this->_vars.f19_acq_status = INIT_INT;

//     memset(this->_vars.f20_reference_time_source, '\0', BUF_A);
//     strcpy(this->_vars.f20_reference_time_source, INIT_CHARP);

//     memset(this->_vars.f21_frequency_reference_source, '\0', BUF_A);
//     strcpy(this->_vars.f21_frequency_reference_source, INIT_CHARP);

//     this->_vars.data_block_cplx32_v.clear();
//     this->_vars.data_block_cplx32_v.resize(INIT_STL_LENGTH);
//     for (std::size_t kk = 0; kk < INIT_STL_LENGTH; kk++)
//     {
//         this->_vars.data_block_cplx32_v[kk].i = INIT_FLOAT;
//         this->_vars.data_block_cplx32_v[kk].q = INIT_FLOAT;
//     }

//     this->_vars.data_block_cplxint32_v.clear();
//     this->_vars.data_block_cplxint32_v.resize(INIT_STL_LENGTH);
//     for (std::size_t kk = 0; kk < INIT_STL_LENGTH; kk++)
//     {
//         this->_vars.data_block_cplxint32_v[kk].i = INIT_INT;
//         this->_vars.data_block_cplxint32_v[kk].q = INIT_INT;
//     }

//     this->_vars.data_block_cplxint16_v.clear();
//     this->_vars.data_block_cplxint16_v.resize(INIT_STL_LENGTH);
//     for (std::size_t kk = 0; kk < INIT_STL_LENGTH; kk++)
//     {
//         this->_vars.data_block_cplxint16_v[kk].i = INIT_INT;
//         this->_vars.data_block_cplxint16_v[kk].q = INIT_INT;
//     }

//     this->_copy_vars();                 // updates the public struct with initialized values
//     this->_set_error_code(no_error);    // resting guaruntees no error (except segfaults, stack bashing, etc)
// }


// ////~~~~


// /*
//     < 2 > private
//     assign public struct the values in the private struct
// */
// CODEZ siq_manager_class::_copy_vars()
// {
// #ifdef DEBUG_CLI
//     snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     this->vars.f0_header_size_in_bytes = this->_vars.f0_header_size_in_bytes;
//     this->vars.f0_iq_file_version      = this->_vars.f0_iq_file_version;
    
//     this->vars.f1_file_year         = this->_vars.f1_file_year;
//     this->vars.f1_file_month        = this->_vars.f1_file_month;
//     this->vars.f1_file_day          = this->_vars.f1_file_day;
//     this->vars.f1_file_hour         = this->_vars.f1_file_hour;
//     this->vars.f1_file_minute       = this->_vars.f1_file_minute;
//     this->vars.f1_file_second       = this->_vars.f1_file_second;
//     this->vars.f1_file_milli_second = this->_vars.f1_file_milli_second;

//     memset(this->vars.f2_instrument_nomenclature, '\0', BUF_A);
//     strcpy(this->vars.f2_instrument_nomenclature, this->_vars.f2_instrument_nomenclature);
//     memset(this->vars.f2_serial_number, '\0', BUF_A);
//     strcpy(this->vars.f2_serial_number, this->_vars.f2_serial_number);
//     memset(this->vars.f2_version, '\0', BUF_A);
//     strcpy(this->vars.f2_version, this->_vars.f2_version);
    
//     memset(this->vars.f3_version_api, '\0', BUF_A);
//     strcpy(this->vars.f3_version_api, this->_vars.f3_version_api);
//     //memset(this->vars.f3_version_board, '\0', BUF_A);
//     //strcpy(this->vars.f3_version_board, this->_vars.f3_version_board);
//     memset(this->vars.f3_version_fpga, '\0', BUF_A);
//     strcpy(this->vars.f3_version_fpga, this->_vars.f3_version_fpga);
//     memset(this->vars.f3_version_usb, '\0', BUF_A);
//     strcpy(this->vars.f3_version_usb, this->_vars.f3_version_usb);

//     this->vars.f4_reference_level_dbm = this->_vars.f4_reference_level_dbm;

//     this->vars.f5_center_frequency_hz = this->_vars.f5_center_frequency_hz;

//     this->vars.f6_samples_per_second = this->_vars.f6_samples_per_second;

//     this->vars.f7_bandwidth_hz = this->_vars.f7_bandwidth_hz;

//     this->vars.f8_iq_sample_pairs = this->_vars.f8_iq_sample_pairs;

//     memset(this->vars.f9_number_format, '\0', BUF_A);
//     strcpy(this->vars.f9_number_format, this->_vars.f9_number_format);

//     this->vars.f10_scale_factor = this->_vars.f10_scale_factor;

//     memset(this->vars.f11_endian, '\0', BUF_A);
//     strcpy(this->vars.f11_endian, this->_vars.f11_endian);

//     this->vars.f12_first_sample_utc_seconds      = this->_vars.f12_first_sample_utc_seconds;
//     this->vars.f12_first_sample_utc_nano_seconds = this->vars.f12_first_sample_utc_nano_seconds;
    
//     this->vars.f13_first_sample_utc_timestamp_year        = this->_vars.f13_first_sample_utc_timestamp_year;
//     this->vars.f13_first_sample_utc_timestamp_month       = this->_vars.f13_first_sample_utc_timestamp_month;
//     this->vars.f13_first_sample_utc_timestamp_day         = this->_vars.f13_first_sample_utc_timestamp_day;
//     this->vars.f13_first_sample_utc_timestamp_hour        = this->_vars.f13_first_sample_utc_timestamp_hour;
//     this->vars.f13_first_sample_utc_timestamp_minute      = this->_vars.f13_first_sample_utc_timestamp_minute;
//     this->vars.f13_first_sample_utc_timestamp_second      = this->_vars.f13_first_sample_utc_timestamp_second;
//     this->vars.f13_first_sample_utc_timestamp_nano_second = this->_vars.f13_first_sample_utc_timestamp_nano_second;

//     this->vars.f14_first_sample_local_timestamp_year        = this->_vars.f14_first_sample_local_timestamp_year;
//     this->vars.f14_first_sample_local_timestamp_month       = this->_vars.f14_first_sample_local_timestamp_month;
//     this->vars.f14_first_sample_local_timestamp_day         = this->_vars.f14_first_sample_local_timestamp_day;
//     this->vars.f14_first_sample_local_timestamp_hour        = this->_vars.f14_first_sample_local_timestamp_hour;
//     this->vars.f14_first_sample_local_timestamp_minute      = this->_vars.f14_first_sample_local_timestamp_minute;
//     this->vars.f14_first_sample_local_timestamp_second      = this->_vars.f14_first_sample_local_timestamp_second;
//     this->vars.f14_first_sample_local_timestamp_nano_second = this->_vars.f14_first_sample_local_timestamp_nano_second;

//     this->vars.f15_tigger_index = this->_vars.f15_tigger_index;

//     this->vars.f16_trigger_utc_seconds      = this->_vars.f16_trigger_utc_seconds;
//     this->vars.f16_trigger_utc_nano_seconds = this->_vars.f16_trigger_utc_nano_seconds;

//     this->vars.f17_trigger_utc_timestamp_year        = this->_vars.f17_trigger_utc_timestamp_year;
//     this->vars.f17_trigger_utc_timestamp_month       = this->_vars.f17_trigger_utc_timestamp_month;
//     this->vars.f17_trigger_utc_timestamp_day         = this->_vars.f17_trigger_utc_timestamp_day;
//     this->vars.f17_trigger_utc_timestamp_hour        = this->_vars.f17_trigger_utc_timestamp_hour;
//     this->vars.f17_trigger_utc_timestamp_minute      = this->_vars.f17_trigger_utc_timestamp_minute;
//     this->vars.f17_trigger_utc_timestamp_second      = this->_vars.f17_trigger_utc_timestamp_second;
//     this->vars.f17_trigger_utc_timestamp_nano_second = this->_vars.f17_trigger_utc_timestamp_nano_second;

//     this->vars.f18_trigger_local_timestamp_year        = this->_vars.f18_trigger_local_timestamp_year;
//     this->vars.f18_trigger_local_timestamp_month       = this->_vars.f18_trigger_local_timestamp_month;
//     this->vars.f18_trigger_local_timestamp_day         = this->_vars.f18_trigger_local_timestamp_day;
//     this->vars.f18_trigger_local_timestamp_hour        = this->_vars.f18_trigger_local_timestamp_hour;
//     this->vars.f18_trigger_local_timestamp_minute      = this->_vars.f18_trigger_local_timestamp_minute;
//     this->vars.f18_trigger_local_timestamp_second      = this->_vars.f18_trigger_local_timestamp_second;
//     this->vars.f18_trigger_local_timestamp_nano_second = this->_vars.f18_trigger_local_timestamp_nano_second;

//     this->vars.f19_acq_status = this->_vars.f19_acq_status;

//     memset(this->vars.f20_reference_time_source, '\0', BUF_A);
//     strcpy(this->vars.f20_reference_time_source, this->_vars.f20_reference_time_source);

//     memset(this->vars.f21_frequency_reference_source, '\0', BUF_A);
//     strcpy(this->vars.f21_frequency_reference_source, this->_vars.f21_frequency_reference_source);

//     this->vars.data_block_cplx32_v.clear();
//     this->vars.data_block_cplx32_v.resize(
//         this->_vars.data_block_cplx32_v.size());
//     for (std::size_t kk = 0; kk < this->_vars.data_block_cplx32_v.size(); kk++)
//     {
//         this->vars.data_block_cplx32_v[kk].i = this->_vars.data_block_cplx32_v[kk].i;
//         this->vars.data_block_cplx32_v[kk].q = this->_vars.data_block_cplx32_v[kk].q;
//     }

//     this->vars.data_block_cplxint32_v.clear();
//     this->vars.data_block_cplxint32_v.resize(
//         this->_vars.data_block_cplxint32_v.size());
//     for (std::size_t kk = 0; kk < this->_vars.data_block_cplxint32_v.size(); kk++)
//     {
//         this->vars.data_block_cplxint32_v[kk].i = this->_vars.data_block_cplxint32_v[kk].i;
//         this->vars.data_block_cplxint32_v[kk].q = this->_vars.data_block_cplxint32_v[kk].q;
//     }

//     this->vars.data_block_cplxint16_v.clear();
//     this->vars.data_block_cplxint16_v.resize(
//         this->_vars.data_block_cplxint16_v.size());
//     for (std::size_t kk = 0; kk < this->_vars.data_block_cplxint16_v.size(); kk++)
//     {
//         this->vars.data_block_cplxint16_v[kk].i = this->_vars.data_block_cplxint16_v[kk].i;
//         this->vars.data_block_cplxint16_v[kk].q = this->_vars.data_block_cplxint16_v[kk].q;
//     }

//     this->_set_error_code(no_error);
// }


// ////////~~~~~~~~END>  siq_init_copy.cpp
