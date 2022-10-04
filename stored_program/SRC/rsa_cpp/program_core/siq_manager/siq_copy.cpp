/*
    'siq_handler_class', deep copier

    public:
        #  none
    
    private:
        < 2 > _copy_vars()

*/

#include "siq_manager_class.h"


/*
    < 1 > private
    assign public struct the values in the private struct
*/
CODEZ siq_manager_class::_copy_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.f0_header_size_in_bytes = this->_vars.f0_header_size_in_bytes;
    this->vars.f0_iq_file_version      = this->_vars.f0_iq_file_version;
    
    this->vars.f1_file_year         = this->_vars.f1_file_year;
    this->vars.f1_file_month        = this->_vars.f1_file_month;
    this->vars.f1_file_day          = this->_vars.f1_file_day;
    this->vars.f1_file_hour         = this->_vars.f1_file_hour;
    this->vars.f1_file_minute       = this->_vars.f1_file_minute;
    this->vars.f1_file_second       = this->_vars.f1_file_second;
    this->vars.f1_file_milli_second = this->_vars.f1_file_milli_second;

    memset(this->vars.f2_instrument_nomenclature, '\0', BUF_A);
    strcpy(this->vars.f2_instrument_nomenclature, this->_vars.f2_instrument_nomenclature);
    memset(this->vars.f2_serial_number, '\0', BUF_A);
    strcpy(this->vars.f2_serial_number, this->_vars.f2_serial_number);
    memset(this->vars.f2_version, '\0', BUF_A);
    strcpy(this->vars.f2_version, this->_vars.f2_version);
    
    memset(this->vars.f3_version_api, '\0', BUF_A);
    strcpy(this->vars.f3_version_api, this->_vars.f3_version_api);
    //memset(this->vars.f3_version_board, '\0', BUF_A);
    //strcpy(this->vars.f3_version_board, this->_vars.f3_version_board);
    memset(this->vars.f3_version_fpga, '\0', BUF_A);
    strcpy(this->vars.f3_version_fpga, this->_vars.f3_version_fpga);
    memset(this->vars.f3_version_usb, '\0', BUF_A);
    strcpy(this->vars.f3_version_usb, this->_vars.f3_version_usb);

    this->vars.f4_reference_level_dbm = this->_vars.f4_reference_level_dbm;

    this->vars.f5_center_frequency_hz = this->_vars.f5_center_frequency_hz;

    this->vars.f6_samples_per_second = this->_vars.f6_samples_per_second;

    this->vars.f7_bandwidth_hz = this->_vars.f7_bandwidth_hz;

    this->vars.f8_iq_sample_pairs = this->_vars.f8_iq_sample_pairs;

    memset(this->vars.f9_number_format, '\0', BUF_A);
    strcpy(this->vars.f9_number_format, this->_vars.f9_number_format);

    this->vars.f10_scale_factor = this->_vars.f10_scale_factor;

    memset(this->vars.f11_endian, '\0', BUF_A);
    strcpy(this->vars.f11_endian, this->_vars.f11_endian);

    this->vars.f12_first_sample_utc_seconds      = this->_vars.f12_first_sample_utc_seconds;
    this->vars.f12_first_sample_utc_nano_seconds = this->vars.f12_first_sample_utc_nano_seconds;
    
    this->vars.f13_first_sample_utc_timestamp_year        = this->_vars.f13_first_sample_utc_timestamp_year;
    this->vars.f13_first_sample_utc_timestamp_month       = this->_vars.f13_first_sample_utc_timestamp_month;
    this->vars.f13_first_sample_utc_timestamp_day         = this->_vars.f13_first_sample_utc_timestamp_day;
    this->vars.f13_first_sample_utc_timestamp_hour        = this->_vars.f13_first_sample_utc_timestamp_hour;
    this->vars.f13_first_sample_utc_timestamp_minute      = this->_vars.f13_first_sample_utc_timestamp_minute;
    this->vars.f13_first_sample_utc_timestamp_second      = this->_vars.f13_first_sample_utc_timestamp_second;
    this->vars.f13_first_sample_utc_timestamp_nano_second = this->_vars.f13_first_sample_utc_timestamp_nano_second;

    this->vars.f14_first_sample_local_timestamp_year        = this->_vars.f14_first_sample_local_timestamp_year;
    this->vars.f14_first_sample_local_timestamp_month       = this->_vars.f14_first_sample_local_timestamp_month;
    this->vars.f14_first_sample_local_timestamp_day         = this->_vars.f14_first_sample_local_timestamp_day;
    this->vars.f14_first_sample_local_timestamp_hour        = this->_vars.f14_first_sample_local_timestamp_hour;
    this->vars.f14_first_sample_local_timestamp_minute      = this->_vars.f14_first_sample_local_timestamp_minute;
    this->vars.f14_first_sample_local_timestamp_second      = this->_vars.f14_first_sample_local_timestamp_second;
    this->vars.f14_first_sample_local_timestamp_nano_second = this->_vars.f14_first_sample_local_timestamp_nano_second;

    this->vars.f15_tigger_index = this->_vars.f15_tigger_index;

    this->vars.f16_trigger_utc_seconds      = this->_vars.f16_trigger_utc_seconds;
    this->vars.f16_trigger_utc_nano_seconds = this->_vars.f16_trigger_utc_nano_seconds;

    this->vars.f17_trigger_utc_timestamp_year        = this->_vars.f17_trigger_utc_timestamp_year;
    this->vars.f17_trigger_utc_timestamp_month       = this->_vars.f17_trigger_utc_timestamp_month;
    this->vars.f17_trigger_utc_timestamp_day         = this->_vars.f17_trigger_utc_timestamp_day;
    this->vars.f17_trigger_utc_timestamp_hour        = this->_vars.f17_trigger_utc_timestamp_hour;
    this->vars.f17_trigger_utc_timestamp_minute      = this->_vars.f17_trigger_utc_timestamp_minute;
    this->vars.f17_trigger_utc_timestamp_second      = this->_vars.f17_trigger_utc_timestamp_second;
    this->vars.f17_trigger_utc_timestamp_nano_second = this->_vars.f17_trigger_utc_timestamp_nano_second;

    this->vars.f18_trigger_local_timestamp_year        = this->_vars.f18_trigger_local_timestamp_year;
    this->vars.f18_trigger_local_timestamp_month       = this->_vars.f18_trigger_local_timestamp_month;
    this->vars.f18_trigger_local_timestamp_day         = this->_vars.f18_trigger_local_timestamp_day;
    this->vars.f18_trigger_local_timestamp_hour        = this->_vars.f18_trigger_local_timestamp_hour;
    this->vars.f18_trigger_local_timestamp_minute      = this->_vars.f18_trigger_local_timestamp_minute;
    this->vars.f18_trigger_local_timestamp_second      = this->_vars.f18_trigger_local_timestamp_second;
    this->vars.f18_trigger_local_timestamp_nano_second = this->_vars.f18_trigger_local_timestamp_nano_second;

    this->vars.f19_acq_status = this->_vars.f19_acq_status;

    memset(this->vars.f20_reference_time_source, '\0', BUF_A);
    strcpy(this->vars.f20_reference_time_source, this->_vars.f20_reference_time_source);

    memset(this->vars.f21_frequency_reference_source, '\0', BUF_A);
    strcpy(this->vars.f21_frequency_reference_source, this->_vars.f21_frequency_reference_source);

    this->vars.data_block_cplx32_v.clear();
    if (this->_vars.data_block_cplx32_v.size() > static_cast<std::size_t>(0))
    {
        this->vars.data_block_cplx32_v.resize(
            this->_vars.data_block_cplx32_v.size());
        for (std::size_t kk = 0; kk < this->_vars.data_block_cplx32_v.size(); kk++)
        {
            this->vars.data_block_cplx32_v[kk].i = this->_vars.data_block_cplx32_v[kk].i;
            this->vars.data_block_cplx32_v[kk].q = this->_vars.data_block_cplx32_v[kk].q;
        }
    }
    
    this->vars.data_block_cplxint32_v.clear();
    if (this->_vars.data_block_cplxint32_v.size() > static_cast<std::size_t>(0))
    {
        this->vars.data_block_cplxint32_v.resize(
            this->_vars.data_block_cplxint32_v.size());
        for (std::size_t kk = 0; kk < this->_vars.data_block_cplxint32_v.size(); kk++)
        {
            this->vars.data_block_cplxint32_v[kk].i = this->_vars.data_block_cplxint32_v[kk].i;
            this->vars.data_block_cplxint32_v[kk].q = this->_vars.data_block_cplxint32_v[kk].q;
        }
    }

    this->vars.data_block_cplxint16_v.clear();
    if (this->_vars.data_block_cplxint16_v.size() > static_cast<std::size_t>(0))
    {
        this->vars.data_block_cplxint16_v.resize(
            this->_vars.data_block_cplxint16_v.size());
        for (std::size_t kk = 0; kk < this->_vars.data_block_cplxint16_v.size(); kk++)
        {
            this->vars.data_block_cplxint16_v[kk].i = this->_vars.data_block_cplxint16_v[kk].i;
            this->vars.data_block_cplxint16_v[kk].q = this->_vars.data_block_cplxint16_v[kk].q;
        }
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  siq_copy.cpp
