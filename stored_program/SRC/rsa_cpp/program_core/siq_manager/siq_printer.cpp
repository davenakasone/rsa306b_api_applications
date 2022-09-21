// /*
//     initializer of the 'siq_handler_class'

//     public:
//         < 1 >  print_header()
//         < 2 >  print_data()
    
//     private:
//         #  none

// */

// #include "siq_manager_class.h"


// /*
//     < 1 >
//     called for diagnostic printing of the header
//     should be called after successfully loading a file
// */
// CODEZ siq_manager_class::print_header()
// {
// #ifdef DEBUG_CLI
//     snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
//         __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif
    
//     printf("\nSIQ file Header, total bytes:  %lu  >>>\n", this->_bytes_in_file);
//     printf("\tf0  header size in bytes            :  %d\n", this->vars.f0_header_size_in_bytes);
//     printf("\tf0  IQ file version                 :  %d\n", this->vars.f0_iq_file_version);
//     printf("\tf1  file date time                  :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
//         this->vars.f1_file_year,
//         this->vars.f1_file_month,
//         this->vars.f1_file_day,
//         this->vars.f1_file_hour,
//         this->vars.f1_file_minute,
//         this->vars.f1_file_second,
//         this->vars.f1_file_milli_second);
//     printf("\tf2  instrument nomenclature         :  %s\n", this->vars.f2_instrument_nomenclature);
//     printf("\tf2  serial number                   :  %s\n", this->vars.f2_serial_number);
//     printf("\tf2  version                         :  %s\n", this->vars.f2_version);
//     printf("\tf3  version API                     :  %s\n", this->vars.f3_version_api);
//     //printf("\tf3  version board                   :  %s\n", this->vars.f3_version_board);
//     printf("\tf3  version FPGA                    :  %s\n", this->vars.f3_version_fpga);
//     printf("\tf3  version USB                     :  %s\n", this->vars.f3_version_usb);
//     printf("\tf4  reference level dBm             :  %lf\n", this->vars.f4_reference_level_dbm);
//     printf("\tf5  center frequency Hz             :  %lf\n", this->vars.f5_center_frequency_hz);
//     printf("\tf6  samples per second              :  %lf\n", this->vars.f6_samples_per_second);
//     printf("\tf7  bandwidth Hz                    :  %lf\n", this->vars.f7_bandwidth_hz);
//     printf("\tf8  IQ sample pairs                 :  %d\n", this->vars.f8_iq_sample_pairs);
//     printf("\tf9  number format                   :  %s\n", this->vars.f9_number_format);
//     printf("\tf10 scale factor                    :  %0.12lf\n", this->vars.f10_scale_factor);
//     printf("\tf11 endian                          :  %s\n", this->vars.f11_endian);
//     printf("\tf12 first sample UTC seconds.nanos  :  %d.%d\n",
//         this->vars.f12_first_sample_utc_seconds,
//         this->vars.f12_first_sample_utc_nano_seconds);
//     printf("\tf13 first sample UTC timestamp      :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
//         this->vars.f13_first_sample_utc_timestamp_year,
//         this->vars.f13_first_sample_utc_timestamp_month,
//         this->vars.f13_first_sample_utc_timestamp_day,
//         this->vars.f13_first_sample_utc_timestamp_hour,
//         this->vars.f13_first_sample_utc_timestamp_minute,
//         this->vars.f13_first_sample_utc_timestamp_second,
//         this->vars.f13_first_sample_utc_timestamp_nano_second);
//     printf("\tf14 first sample LOCAL timestamp    :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
//         this->vars.f14_first_sample_local_timestamp_year,
//         this->vars.f14_first_sample_local_timestamp_month,
//         this->vars.f14_first_sample_local_timestamp_day,
//         this->vars.f14_first_sample_local_timestamp_hour,
//         this->vars.f14_first_sample_local_timestamp_minute,
//         this->vars.f14_first_sample_local_timestamp_second,
//         this->vars.f14_first_sample_local_timestamp_nano_second);
//     printf("\tf15 trigger index                   :  %d\n", this->vars.f15_tigger_index);
//     printf("\tf16 trigger UTC seconds.nanos       :  %d.%d\n",
//         this->vars.f16_trigger_utc_seconds,
//         this->vars.f16_trigger_utc_nano_seconds);
//     printf("\tf17 trigger UTC timestamp           :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
//         this->vars.f17_trigger_utc_timestamp_year,
//         this->vars.f17_trigger_utc_timestamp_month,
//         this->vars.f17_trigger_utc_timestamp_day,
//         this->vars.f17_trigger_utc_timestamp_hour,
//         this->vars.f17_trigger_utc_timestamp_minute,
//         this->vars.f17_trigger_utc_timestamp_second,
//         this->vars.f17_trigger_utc_timestamp_nano_second);
//     printf("\tf18 trigger LOCAL timestamp         :  %04d-%02d-%02dT%02d:%02d:%02d.%d\n",
//         this->vars.f18_trigger_local_timestamp_year,
//         this->vars.f18_trigger_local_timestamp_month,
//         this->vars.f18_trigger_local_timestamp_day,
//         this->vars.f18_trigger_local_timestamp_hour,
//         this->vars.f18_trigger_local_timestamp_minute,
//         this->vars.f18_trigger_local_timestamp_second,
//         this->vars.f18_trigger_local_timestamp_nano_second);
//     printf("\tf19 acq status                      :  0x%08X\n", this->vars.f19_acq_status);
//     printf("\tf20 reference time source           :  %s\n", this->vars.f20_reference_time_source);
//     printf("\tf21 frequency reference source      :  %s\n", this->vars.f21_frequency_reference_source);   

//     this->_set_error_code(no_error);
// }


// ////~~~~


// /*
//     < 2 >
//     called for diagnostic printing of the data block
//     should be called after successfully loading a file
//     call with idx_start==0, idx_stop==0 to print all the data
// */
// CODEZ siq_manager_class::print_data
// (
//     std::size_t idx_start, 
//     std::size_t idx_stop
// )
// {
// #ifdef DEBUG_CLI
//     snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
//         __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     if (idx_start < 0 || idx_stop < 0)
//     {
//         this->_set_error_code(print_data_range_failure);
//         return;
//     }
//     if (idx_start > idx_stop)
//     {
//         this->_set_error_code(print_data_range_failure);
//         return;
//     }
//     std::size_t idx_begin = 0;
//     std::size_t idx_end = 0;

//     // RSA_API::Cplx32
//     if (this->_vars.data_block_cplx32_v.size() > INIT_STL_LENGTH)
//     {
//         idx_begin = idx_start;
//         idx_end = idx_stop;
//         if ((idx_start == 0 && idx_stop == 0)                   ||
//             idx_start > this->vars.data_block_cplx32_v.size()-1 ||
//             idx_stop > this->vars.data_block_cplx32_v.size()-1   )
//         {
//             idx_begin = 0;
//             idx_end = this->vars.data_block_cplx32_v.size()-1;
//         }
//         printf("\nCplx32, elements:  %d\n", static_cast<int>(this->vars.data_block_cplx32_v.size()));
//         printf("                               I  |  Q\n");
//         printf("                ---------------------------------------\n");
//         while(idx_begin <= idx_end)
//         {
//             printf("                 %14.7f   |  %14.7f\n", 
//                 this->vars.data_block_cplx32_v[idx_begin].i,
//                 this->vars.data_block_cplx32_v[idx_begin].q);
//             idx_begin++;
//         }
//     }
//     else
//     {
//         printf("\nthe RSA_API::Cplx32 vector does not have data\n");
//     }
    
//     // RSA_API::CplxInt32
//     if (this->_vars.data_block_cplxint32_v.size() > INIT_STL_LENGTH)
//     {
//         idx_begin = idx_start;
//         idx_end = idx_stop;
//         if ((idx_start == 0 && idx_stop == 0)                      ||
//             idx_start > this->vars.data_block_cplxint32_v.size()-1 ||
//             idx_stop > this->vars.data_block_cplxint32_v.size()-1   )
//         {
//             idx_begin = 0;
//             idx_end = this->vars.data_block_cplxint32_v.size()-1;
//         }
//         printf("\nCplxInt32, elements:  %d\n", static_cast<int>(this->vars.data_block_cplxint32_v.size()));
//         printf("                               I  |  Q\n");
//         printf("                ---------------------------------------\n");
//         while(idx_begin <= idx_end)
//         {
//             printf("                 %15d  |  %15d\n", 
//                 static_cast<int>(this->vars.data_block_cplxint32_v[idx_begin].i),
//                 static_cast<int>(this->vars.data_block_cplxint32_v[idx_begin].q));
//             idx_begin++;
//         }
//     }
//     else
//     {
//         printf("\nthe RSA_API::CplxInt32 vector does not have data\n");
//     }
    

//     // RSA_API::CplxInt16
//     if (this->_vars.data_block_cplxint16_v.size() > INIT_STL_LENGTH)
//     {
//         idx_begin = idx_start;
//         idx_end = idx_stop;
//         if ((idx_start == 0 && idx_stop == 0)                      ||
//             idx_start > this->vars.data_block_cplxint16_v.size()-1 ||
//             idx_stop > this->vars.data_block_cplxint16_v.size()-1   )
//         {
//             idx_begin = 0;
//             idx_end = this->vars.data_block_cplxint16_v.size()-1;
//         }
//         printf("\nCplxInt16, elements:  %d\n", static_cast<int>(this->vars.data_block_cplxint16_v.size()));
//         printf("                               I  |  Q\n");
//         printf("                ---------------------------------------\n");
//         while(idx_begin <= idx_end)
//         {
//             printf("                 %15d  |  %15d\n", 
//                 static_cast<int>(this->vars.data_block_cplxint16_v[idx_begin].i),
//                 static_cast<int>(this->vars.data_block_cplxint16_v[idx_begin].q));
//             idx_begin++;
//         }
//     }
//     else
//     {
//         printf("\nthe RSA_API::CplxInt16 vector does not have data\n");
//     }
    
//     this->_set_error_code(no_error);
// }


// ////////~~~~~~~~END>  siq_printer.cpp
