/*
    'siq_handler_class', writing parsed output

    public:
        #  none
    
    private:
        < 1 >  _write_csv_iq()
        < 2 >  _write_parsed()

*/

#include "siq_manager_class.h"


/*
    < 1 > private
        if user selected "write_iq == true"
        when load_file() or batch_process_files() was called,
        then this function helps made the output file of IQ values over time
*/
CODEZ siq_manager_class::_write_csv_iq()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_fp_write == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
    }
    if
    (
        (this->_vars.data_block_cplx32_v.size()    < static_cast<std::size_t>(0)) &&
        (this->_vars.data_block_cplxint32_v.size() < static_cast<std::size_t>(0)) &&
        (this->_vars.data_block_cplxint16_v.size() < static_cast<std::size_t>(0)) 
    )
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    (void)sprintf(this->_helper, "%s,%s,%s\n",   // place the CSV header
        IQSTREAM_FIELD_1,
        IQSTREAM_FIELD_2,
        IQSTREAM_FIELD_3);
    (void)fputs(this->_helper, this->_fp_write);

    // RSA_API::Cplx32
    if (this->_vars.data_block_cplx32_v.size() > static_cast<std::size_t>(0))
    {
        for (std::size_t xx = 0; xx < this->_vars.data_block_cplx32_v.size(); xx++)
        {
            (void)sprintf(this->_holder, "%0.12lf,%0.9f,%0.9f\n", 
                static_cast<double>(xx) / this->_vars.f6_samples_per_second,
                this->_vars.data_block_cplx32_v[xx].i,
                this->_vars.data_block_cplx32_v[xx].q);
            (void)fputs(this->_holder, this->_fp_write);
        }
    }

    // RSA_API::CplxInt32
    if (this->_vars.data_block_cplxint32_v.size() > static_cast<std::size_t>(0))
    {
        for (std::size_t xx = 0; xx < this->_vars.data_block_cplxint32_v.size(); xx++)
        {
            (void)sprintf(this->_holder, "%0.12lf,%15d,%15d\n", 
                static_cast<double>(xx) / this->_vars.f6_samples_per_second,
                this->_vars.data_block_cplxint32_v[xx].i,
                this->_vars.data_block_cplxint32_v[xx].q);
            (void)fputs(this->_holder, this->_fp_write);
        }
    }

    // RSA_API::CplxInt16
    if (this->_vars.data_block_cplxint16_v.size() > static_cast<std::size_t>(0))
    {
        for (std::size_t xx = 0; xx < this->_vars.data_block_cplxint16_v.size(); xx++)
        {
            (void)sprintf(this->_holder, "%0.12lf,%15d,%15d\n", 
                static_cast<double>(xx) / this->_vars.f6_samples_per_second,
                this->_vars.data_block_cplxint16_v[xx].i,
                this->_vars.data_block_cplxint16_v[xx].q);
            (void)fputs(this->_holder, this->_fp_write);
        }
    }

    return CODEZ::_0_no_errors;
}


////~~~~


/*
    < 2 >
    only called from "load_file()" if user requests it
    "_fp_write" must be opened
*/
CODEZ siq_manager_class::_write_parsed()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    if (this->_fp_write == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
    }
    
    (void)sprintf(this->_holder, "\nSIQ file Header, total bytes:  %ld  >>>\n", this->_bytes_in_file);
    (void)fputs(this->_holder, this->_fp_write);
    
    (void)sprintf(this->_holder, "\tf0  header size in bytes            :  %d\n", this->_vars.f0_header_size_in_bytes);
    (void)fputs(this->_holder, this->_fp_write);
    
    (void)sprintf(this->_holder, "\tf0  IQ file version                 :  %d\n", this->_vars.f0_iq_file_version);
    (void)fputs(this->_holder, this->_fp_write);
    
    (void)sprintf(this->_holder, "\tf1  file date time                  :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
        this->_vars.f1_file_year,
        this->_vars.f1_file_month,
        this->_vars.f1_file_day,
        this->_vars.f1_file_hour,
        this->_vars.f1_file_minute,
        this->_vars.f1_file_second,
        this->_vars.f1_file_milli_second);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf2  instrument nomenclature         :  %s\n", this->_vars.f2_instrument_nomenclature);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf2  serial number                   :  %s\n", this->_vars.f2_serial_number);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf2  version                         :  %s\n", this->_vars.f2_version);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf3  version API                     :  %s\n", this->_vars.f3_version_api);
    (void)fputs(this->_holder, this->_fp_write);

    //printf("\tf3  version board                   :  %s\n", this->_vars.f3_version_board);
    
    (void)sprintf(this->_holder, "\tf3  version FPGA                    :  %s\n", this->_vars.f3_version_fpga);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf3  version USB                     :  %s\n", this->_vars.f3_version_usb);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf4  reference level dBm             :  %lf\n", this->_vars.f4_reference_level_dbm);
    (void)fputs(this->_holder, this->_fp_write);
    
    (void)sprintf(this->_holder, "\tf5  center frequency Hz             :  %lf\n", this->_vars.f5_center_frequency_hz);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf6  samples per second              :  %lf\n", this->_vars.f6_samples_per_second);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf7  bandwidth Hz                    :  %lf\n", this->_vars.f7_bandwidth_hz);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf8  IQ sample pairs                 :  %d\n", this->_vars.f8_iq_sample_pairs);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf9  number format                   :  %s\n", this->_vars.f9_number_format);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf10 scale factor                    :  %0.12lf\n", this->_vars.f10_scale_factor);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf11 endian                          :  %s\n", this->_vars.f11_endian);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf12 first sample UTC seconds.nanos  :  %d.%d\n",
        this->_vars.f12_first_sample_utc_seconds,
        this->_vars.f12_first_sample_utc_nano_seconds);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf13 first sample UTC timestamp      :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
        this->_vars.f13_first_sample_utc_timestamp_year,
        this->_vars.f13_first_sample_utc_timestamp_month,
        this->_vars.f13_first_sample_utc_timestamp_day,
        this->_vars.f13_first_sample_utc_timestamp_hour,
        this->_vars.f13_first_sample_utc_timestamp_minute,
        this->_vars.f13_first_sample_utc_timestamp_second,
        this->_vars.f13_first_sample_utc_timestamp_nano_second);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf14 first sample LOCAL timestamp    :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
        this->_vars.f14_first_sample_local_timestamp_year,
        this->_vars.f14_first_sample_local_timestamp_month,
        this->_vars.f14_first_sample_local_timestamp_day,
        this->_vars.f14_first_sample_local_timestamp_hour,
        this->_vars.f14_first_sample_local_timestamp_minute,
        this->_vars.f14_first_sample_local_timestamp_second,
        this->_vars.f14_first_sample_local_timestamp_nano_second);
    (void)sprintf(this->_holder, "\tf15 trigger index                   :  %d\n", this->_vars.f15_tigger_index);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf16 trigger UTC seconds.nanos       :  %d.%d\n",
        this->_vars.f16_trigger_utc_seconds,
        this->_vars.f16_trigger_utc_nano_seconds);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf17 trigger UTC timestamp           :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
        this->_vars.f17_trigger_utc_timestamp_year,
        this->_vars.f17_trigger_utc_timestamp_month,
        this->_vars.f17_trigger_utc_timestamp_day,
        this->_vars.f17_trigger_utc_timestamp_hour,
        this->_vars.f17_trigger_utc_timestamp_minute,
        this->_vars.f17_trigger_utc_timestamp_second,
        this->_vars.f17_trigger_utc_timestamp_nano_second);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf18 trigger LOCAL timestamp         :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
        this->_vars.f18_trigger_local_timestamp_year,
        this->_vars.f18_trigger_local_timestamp_month,
        this->_vars.f18_trigger_local_timestamp_day,
        this->_vars.f18_trigger_local_timestamp_hour,
        this->_vars.f18_trigger_local_timestamp_minute,
        this->_vars.f18_trigger_local_timestamp_second,
        this->_vars.f18_trigger_local_timestamp_nano_second);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf19 acq status                      :  0x%08X\n", this->_vars.f19_acq_status);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf20 reference time source           :  %s\n", this->_vars.f20_reference_time_source);
    (void)fputs(this->_holder, this->_fp_write);

    (void)sprintf(this->_holder, "\tf21 frequency reference source      :  %s\n", this->_vars.f21_frequency_reference_source);   
    (void)fputs(this->_holder, this->_fp_write);

    // RSA_API::Cplx32
    if (this->_vars.data_block_cplx32_v.size() > static_cast<std::size_t>(0))
    {
        (void)sprintf(this->_holder, "\nCplx32, elements:  %d\n", static_cast<int>(this->_vars.data_block_cplx32_v.size()));
        (void)fputs(this->_holder, this->_fp_write);
        
        (void)sprintf(this->_holder, "                               I  |  Q\n");
        (void)fputs(this->_holder, this->_fp_write);

        (void)sprintf(this->_holder, "                ---------------------------------------\n");
        (void)fputs(this->_holder, this->_fp_write);

        for (std::size_t xx = 0; xx < this->_vars.data_block_cplx32_v.size(); xx++)
        {
            (void)sprintf(this->_holder, "                 %14.7f   |  %14.7f\n", 
                this->_vars.data_block_cplx32_v[xx].i,
                this->_vars.data_block_cplx32_v[xx].q);
            (void)fputs(this->_holder, this->_fp_write);
        }
    }

    // RSA_API::CplxInt32
    if (this->_vars.data_block_cplxint32_v.size() > static_cast<std::size_t>(0))
    {
        (void)sprintf(this->_holder, "\nCplxInt32, elements:  %d\n", static_cast<int>(this->_vars.data_block_cplxint32_v.size()));
        (void)fputs(this->_holder, this->_fp_write);

        (void)sprintf(this->_holder, "                               I  |  Q\n");
        (void)fputs(this->_holder, this->_fp_write);

        (void)sprintf(this->_holder, "                ---------------------------------------\n");
        (void)fputs(this->_holder, this->_fp_write);

        for (std::size_t xx = 0; xx < this->_vars.data_block_cplxint32_v.size(); xx++)
        {
            (void)sprintf(this->_holder, "                 %15d  |  %15d\n", 
                this->_vars.data_block_cplxint32_v[xx].i,
                this->_vars.data_block_cplxint32_v[xx].q);
            (void)fputs(this->_holder, this->_fp_write);
        }
    }

    // RSA_API::CplxInt16
    if (this->_vars.data_block_cplxint16_v.size() > static_cast<std::size_t>(0))
    {
        (void)sprintf(this->_holder, "\nCplxInt16, elements:  %d\n", static_cast<int>(this->_vars.data_block_cplxint16_v.size()));
        (void)fputs(this->_holder, this->_fp_write);

        (void)sprintf(this->_holder, "                               I  |  Q\n");
        (void)fputs(this->_holder, this->_fp_write);

        (void)sprintf(this->_holder, "                ---------------------------------------\n");
        (void)fputs(this->_holder, this->_fp_write);

        for (std::size_t xx = 0; xx < this->_vars.data_block_cplxint16_v.size(); xx++)
        {
            (void)sprintf(this->_holder, "                 %15d  |  %15d\n", 
                this->_vars.data_block_cplxint16_v[xx].i,
                this->_vars.data_block_cplxint16_v[xx].q);
            (void)fputs(this->_holder, this->_fp_write);
        }
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  siq_write.cpp
