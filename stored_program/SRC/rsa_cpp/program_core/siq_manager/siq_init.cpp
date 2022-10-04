/*
    'siq_handler_class', initializer

    public:
        #  none
    
    private:
        < 1 > _init()

*/

#include "siq_manager_class.h"


/*
    < 1 > private
    initializing class members to known values
*/
CODEZ siq_manager_class::_init()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // initialize the private members
    this->_bytes_in_file = INIT_INT;
    this->_byte_index    = INIT_INT;

    if (this->_fp_write != NULL)
    {
        (void)fclose(this->_fp_write);
    }
    this->_fp_write = NULL;

    if (this->_fp_read != NULL)
    {
        (void)fclose(this->_fp_read);
    }
    this->_fp_read = NULL;

    memset(this->_holder, '\0', sizeof(this->_holder));
    memset(this->_helper, '\0', sizeof(this->_helper));
    
    
    // initialize the private variable struct
    this->_vars.f0_header_size_in_bytes = INIT_INT;
    this->_vars.f0_iq_file_version      = SIQ_CORRECT_IQ_FILE_VERSION;
    
    this->_vars.f1_file_year         = INIT_INT;
    this->_vars.f1_file_month        = INIT_INT;
    this->_vars.f1_file_day          = INIT_INT;
    this->_vars.f1_file_hour         = INIT_INT;
    this->_vars.f1_file_minute       = INIT_INT;
    this->_vars.f1_file_second       = INIT_INT;
    this->_vars.f1_file_milli_second = INIT_INT;

    memset(this->_vars.f2_instrument_nomenclature, '\0', BUF_A);
    strcpy(this->_vars.f2_instrument_nomenclature, INIT_CHARP);
    memset(this->_vars.f2_serial_number          , '\0', BUF_A);
    strcpy(this->_vars.f2_serial_number          , INIT_CHARP);
    memset(this->_vars.f2_version                , '\0', BUF_A);
    strcpy(this->_vars.f2_version                , INIT_CHARP);

    memset(this->_vars.f3_version_api, '\0', BUF_A);
    strcpy(this->_vars.f3_version_api, INIT_CHARP);
    //memset(this->_vars.f3_version_board, '\0', BUF_A);
    //strcpy(this->_vars.f3_version_board, INIT_CHARP);
    memset(this->_vars.f3_version_fpga, '\0', BUF_A);
    strcpy(this->_vars.f3_version_fpga, INIT_CHARP);
    memset(this->_vars.f3_version_usb , '\0', BUF_A);
    strcpy(this->_vars.f3_version_usb , INIT_CHARP);

    this->_vars.f4_reference_level_dbm = INIT_DOUBLE;

    this->_vars.f5_center_frequency_hz = INIT_DOUBLE;

    this->_vars.f6_samples_per_second = INIT_DOUBLE;

    this->_vars.f7_bandwidth_hz = INIT_DOUBLE;

    this->_vars.f8_iq_sample_pairs = INIT_INT;

    memset(this->_vars.f9_number_format, '\0', BUF_A);
    strcpy(this->_vars.f9_number_format, INIT_CHARP);

    this->_vars.f10_scale_factor = INIT_DOUBLE;

    memset(this->_vars.f11_endian, '\0', BUF_A);
    strcpy(this->_vars.f11_endian, INIT_CHARP);

    this->_vars.f12_first_sample_utc_seconds      = INIT_INT;
    this->_vars.f12_first_sample_utc_nano_seconds = INIT_INT;
    
    this->_vars.f13_first_sample_utc_timestamp_year        = INIT_INT;
    this->_vars.f13_first_sample_utc_timestamp_month       = INIT_INT;
    this->_vars.f13_first_sample_utc_timestamp_day         = INIT_INT;
    this->_vars.f13_first_sample_utc_timestamp_hour        = INIT_INT;
    this->_vars.f13_first_sample_utc_timestamp_minute      = INIT_INT;
    this->_vars.f13_first_sample_utc_timestamp_second      = INIT_INT;
    this->_vars.f13_first_sample_utc_timestamp_nano_second = INIT_INT;

    this->_vars.f14_first_sample_local_timestamp_year        = INIT_INT;
    this->_vars.f14_first_sample_local_timestamp_month       = INIT_INT;
    this->_vars.f14_first_sample_local_timestamp_day         = INIT_INT;
    this->_vars.f14_first_sample_local_timestamp_hour        = INIT_INT;
    this->_vars.f14_first_sample_local_timestamp_minute      = INIT_INT;
    this->_vars.f14_first_sample_local_timestamp_second      = INIT_INT;
    this->_vars.f14_first_sample_local_timestamp_nano_second = INIT_INT;

    this->_vars.f15_tigger_index = INIT_INT;

    this->_vars.f16_trigger_utc_seconds      = INIT_INT;
    this->_vars.f16_trigger_utc_nano_seconds = INIT_INT;

    this->_vars.f17_trigger_utc_timestamp_year        = INIT_INT;
    this->_vars.f17_trigger_utc_timestamp_month       = INIT_INT;
    this->_vars.f17_trigger_utc_timestamp_day         = INIT_INT;
    this->_vars.f17_trigger_utc_timestamp_hour        = INIT_INT;
    this->_vars.f17_trigger_utc_timestamp_minute      = INIT_INT;
    this->_vars.f17_trigger_utc_timestamp_second      = INIT_INT;
    this->_vars.f17_trigger_utc_timestamp_nano_second = INIT_INT;

    this->_vars.f18_trigger_local_timestamp_year        = INIT_INT;
    this->_vars.f18_trigger_local_timestamp_month       = INIT_INT;
    this->_vars.f18_trigger_local_timestamp_day         = INIT_INT;
    this->_vars.f18_trigger_local_timestamp_hour        = INIT_INT;
    this->_vars.f18_trigger_local_timestamp_minute      = INIT_INT;
    this->_vars.f18_trigger_local_timestamp_second      = INIT_INT;
    this->_vars.f18_trigger_local_timestamp_nano_second = INIT_INT;

    this->_vars.f19_acq_status = INIT_INT;

    memset(this->_vars.f20_reference_time_source, '\0', BUF_A);
    strcpy(this->_vars.f20_reference_time_source, INIT_CHARP);

    memset(this->_vars.f21_frequency_reference_source, '\0', BUF_A);
    strcpy(this->_vars.f21_frequency_reference_source, INIT_CHARP);

    this->_vars.data_block_cplx32_v.clear();
    // this->_vars.data_block_cplx32_v.resize(INIT_STL_LENGTH);
    // for (std::size_t kk = 0; kk < INIT_STL_LENGTH; kk++)
    // {
    //     this->_vars.data_block_cplx32_v[kk].i = INIT_FLOAT;
    //     this->_vars.data_block_cplx32_v[kk].q = INIT_FLOAT;
    // }

    this->_vars.data_block_cplxint32_v.clear();
    // this->_vars.data_block_cplxint32_v.resize(INIT_STL_LENGTH);
    // for (std::size_t kk = 0; kk < INIT_STL_LENGTH; kk++)
    // {
    //     this->_vars.data_block_cplxint32_v[kk].i = INIT_INT32;
    //     this->_vars.data_block_cplxint32_v[kk].q = INIT_INT32;
    // }

    this->_vars.data_block_cplxint16_v.clear();
    // this->_vars.data_block_cplxint16_v.resize(INIT_STL_LENGTH);
    // for (std::size_t kk = 0; kk < INIT_STL_LENGTH; kk++)
    // {
    //     this->_vars.data_block_cplxint16_v[kk].i = INIT_INT16;
    //     this->_vars.data_block_cplxint16_v[kk].q = INIT_INT16;
    // }

    return this->_copy_vars();                 // updates the public struct with initialized values
}


////////~~~~~~~~END>  siq_init.cpp
