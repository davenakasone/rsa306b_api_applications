// /*
//     API group "IQBLK"

//     public :
//         < 1 >  print_iqblk()
    
//     private :
//         < 1 >  _iqblk_init()
//         < 2 >  _iqblk_bitcheck()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > public
// */
// CODEZ rsa306b_class::print_iqblk()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     (void)printf("\n'IQBLK' group >>>\n");
//     (void)printf("\tgetter                            :  %d  ,  ", this->_vars.iqblk.getter);
//     if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA)
//     {
//         (void)printf("IQBLK_GetIQData()\n");
//     }
//     else if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA_CPLX)
//     {
//         (void)printf("IQBLK_GetIQDataCplx()\n");
//     }
//     else if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA_DEINETERLEAVED)
//     {
//         (void)printf("IQBLK_GetIQDataDeinterleaved()\n");
//     }
//     else
//     {
//         (void)printf("unknown\n"); 
//     }
//     (void)printf("\trecord_length                     :  %d\n", this->_vars.iqblk.record_length);
//     (void)printf("\tmax_record_length                 :  %d\n", this->_vars.iqblk.max_record_length);
//     (void)printf("\tactual_buffer_samples             :  %d\n", this->_vars.iqblk.actual_buffer_samples);
//     //(void)printf("\tsample_pairs_requested            :  %d\n", this->_vars.iqblk.sample_pairs_requested);
//     (void)printf("\tcplx32_v.size()                   :  %ld\n", this->_vars.iqblk.cplx32_v.size());    
//     (void)printf("\t    cplx32_v[0].i                 :  %0.3f\n", this->_vars.iqblk.cplx32_v[0].i);    
//     (void)printf("\t    cplx32_v[0].q                 :  %0.3f\n", this->_vars.iqblk.cplx32_v[0].q);   
//     (void)printf("\tbitcheck                          :  %s\n", this->_vars.iqblk.bitcheck);
//     (void)printf("\tacq_info_type.acqStatus           :  %u\n", this->_vars.iqblk.acq_info_type.acqStatus);
//     (void)printf("\tacq_info_type.sample0Timestamp    :  %lu\n", this->_vars.iqblk.acq_info_type.sample0Timestamp);
//     (void)printf("\tacq_info_type.triggerSampleIndex  :  %lu\n", this->_vars.iqblk.acq_info_type.triggerSampleIndex);
//     (void)printf("\tacq_info_type.triggerTimestamp    :  %lu\n", this->_vars.iqblk.acq_info_type.triggerTimestamp);
//     (void)printf("\tsample_rate                       :  %lf\n", this->_vars.iqblk.sample_rate);
//     (void)printf("\tbandwidth_hz                      :  %lf\n", this->_vars.iqblk.bandwidth_hz);
//     (void)printf("\tmin_bandwidth_hz                  :  %lf\n", this->_vars.iqblk.min_bandwidth_hz);
//     (void)printf("\tmax_bandwidth_hz                  :  %lf\n", this->_vars.iqblk.max_bandwidth_hz);          
// }


// ////~~~~


// /*
//     < 1 > private
// */
// CODEZ rsa306b_class::_iqblk_init()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif  

//     this->_vars.iqblk.getter                 = this->constants.IQBLK_GETTER_DEFAULT;
//     this->_vars.iqblk.actual_buffer_samples  = INIT_INT;
//     //this->_vars.iqblk.sample_pairs_requested = this->constants.INIT_INT;
//     this->_vars.iqblk.max_record_length      = INIT_INT;      
//     this->_vars.iqblk.record_length          = this->constants.IQBLK_STARTING_PAIRS;     

//     this->_vars.iqblk.cplx32_v.resize((size_t)this->_vars.iqblk.record_length);
//     for (size_t ii = 0; ii < this->_vars.iqblk.cplx32_v.size(); ii++)    
//     {
//         this->_vars.iqblk.cplx32_v[ii].i = INIT_FLOAT;
//         this->_vars.iqblk.cplx32_v[ii].q = INIT_FLOAT;
//     }             
                   
//     this->_vars.iqblk.acq_info_type.sample0Timestamp   = INIT_UINT;
//     this->_vars.iqblk.acq_info_type.triggerSampleIndex = INIT_UINT;
//     this->_vars.iqblk.acq_info_type.triggerTimestamp   = INIT_UINT;
//     this->_vars.iqblk.acq_info_type.acqStatus          = this->constants.ACQ_STATUS_SUCCESS;
//     this->_iqblk_bitcheck();    // updates "bitcheck"

//     this->_vars.iqblk.sample_rate      = INIT_DOUBLE;
//     this->_vars.iqblk.bandwidth_hz     = this->constants.IQBLK_STARTING_BANDWIDTH;
//     this->_vars.iqblk.min_bandwidth_hz = INIT_DOUBLE;
//     this->_vars.iqblk.max_bandwidth_hz = INIT_DOUBLE;

//     this->_iqblk_copy_vars();
// }


// ////~~~~


// /*
//     < 2 > private
// */
// CODEZ rsa306b_class::_iqblk_bitcheck()
// {
// #ifdef DEBUG_CALL_CHECKS
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif  

//     (void)memset(this->_vars.iqblk.bitcheck, '\0', BUF_D);
    
//     if ((this->_vars.iqblk.acq_info_type.acqStatus  & 
//             (uint32_t)RSA_API::IQBLK_STATUS_INPUT_OVERRANGE   &
//             (uint32_t)RSA_API::IQBLK_STATUS_FREQREF_UNLOCKED  &
//             (uint32_t)RSA_API::IQBLK_STATUS_ACQ_SYS_ERROR     &
//             (uint32_t)RSA_API::IQBLK_STATUS_DATA_XFER_ERROR) == 
//             this->constants.ACQ_STATUS_SUCCESS                )
//     {
//         (void)snprintf(this->_vars.iqblk.bitcheck, BUF_D, 
//             "acqStatus:  %d  ,  %s", 
//             this->_vars.iqblk.acq_info_type.acqStatus, 
//             this->constants.ACQ_STATUS_SUCCESS_MESSAGE);
//         this->_iqblk_copy_bitcheck();
//         return;
//     }

//     (void)snprintf(this->_vars.iqblk.bitcheck, BUF_D, "acqStatus:  %d  ,  ", 
//         this->_vars.iqblk.acq_info_type.acqStatus);
//     if ((this->_vars.iqblk.acq_info_type.acqStatus            & 
//             (uint32_t)RSA_API::IQBLK_STATUS_INPUT_OVERRANGE) !=
//             this->constants.ACQ_STATUS_SUCCESS                )
//     {
//         (void)strncat(this->_vars.iqblk.bitcheck, 
//             this->constants.IQBLK_BIT_0, 
//             BUF_B);
//     }
//     if ((this->_vars.iqblk.acq_info_type.acqStatus             & 
//             (uint32_t)RSA_API::IQBLK_STATUS_FREQREF_UNLOCKED) !=
//             this->constants.ACQ_STATUS_SUCCESS           )
//     {
//         (void)strncat(this->_vars.iqblk.bitcheck, 
//             this->constants.IQBLK_BIT_1, 
//             BUF_B);
//     }
//     if ((this->_vars.iqblk.acq_info_type.acqStatus          & 
//             (uint32_t)RSA_API::IQBLK_STATUS_ACQ_SYS_ERROR) !=
//             this->constants.ACQ_STATUS_SUCCESS        )
//     {
//         (void)strncat(this->_vars.iqblk.bitcheck, 
//             this->constants.IQBLK_BIT_2, 
//             BUF_B);
//     }
//     if ((this->_vars.iqblk.acq_info_type.acqStatus            & 
//             (uint32_t)RSA_API::IQBLK_STATUS_DATA_XFER_ERROR) !=
//             this->constants.ACQ_STATUS_SUCCESS          )
//     {
//         (void)strncat(this->_vars.iqblk.bitcheck, 
//             this->constants.IQBLK_BIT_3, 
//             BUF_B);
//     }
//     this->_iqblk_copy_bitcheck();
// }


// ////////~~~~~~~~END>  rsa306b_iqblk_print_init_check.cpp