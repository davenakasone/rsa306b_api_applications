/*
    API group "IQBLK"

    public :
        < 1 >  print_iqblk()
    
    private :
        < 1 >  _iqblk_init()
        < 2 >  _iqblk_bitcheck()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::print_iqblk()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'IQBLK' group >>>\n");
    printf("\tgetter                            :  %d  ,  ", this->_vars.iqblk.getter);
    if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA)
    {
        printf("IQBLK_GetIQData()\n");
    }
    else if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA_CPLX)
    {
        printf("IQBLK_GetIQDataCplx()\n");
    }
    else if (this->_vars.iqblk.getter == this->constants.IQBLK_GET_IQ_DATA_DEINETERLEAVED)
    {
        printf("IQBLK_GetIQDataDeinterleaved()\n");
    }
    else
    {
        printf("unknown\n"); 
    }
    printf("\trecord_length                     :  %d\n", this->_vars.iqblk.record_length);
    printf("\tmax_record_length                 :  %d\n", this->_vars.iqblk.max_record_length);
    printf("\tactual_buffer_samples             :  %d\n", this->_vars.iqblk.actual_buffer_samples);
    //printf("\tsample_pairs_requested            :  %d\n", this->_vars.iqblk.sample_pairs_requested);
    printf("\tcplx32_v.size()                   :  %ld\n", this->_vars.iqblk.cplx32_v.size());    
    printf("\t    cplx32_v[0].i                 :  %0.3f\n", this->_vars.iqblk.cplx32_v[0].i);    
    printf("\t    cplx32_v[0].q                 :  %0.3f\n", this->_vars.iqblk.cplx32_v[0].q);   
    printf("\tbitcheck                          :  %s\n", this->_vars.iqblk.bitcheck);
    printf("\tacq_info_type.acqStatus           :  %u\n", this->_vars.iqblk.acq_info_type.acqStatus);
    printf("\tacq_info_type.sample0Timestamp    :  %lu\n", this->_vars.iqblk.acq_info_type.sample0Timestamp);
    printf("\tacq_info_type.triggerSampleIndex  :  %lu\n", this->_vars.iqblk.acq_info_type.triggerSampleIndex);
    printf("\tacq_info_type.triggerTimestamp    :  %lu\n", this->_vars.iqblk.acq_info_type.triggerTimestamp);
    printf("\tsample_rate                       :  %lf\n", this->_vars.iqblk.sample_rate);
    printf("\tbandwidth_hz                      :  %lf\n", this->_vars.iqblk.bandwidth_hz);
    printf("\tmin_bandwidth_hz                  :  %lf\n", this->_vars.iqblk.min_bandwidth_hz);
    printf("\tmax_bandwidth_hz                  :  %lf\n", this->_vars.iqblk.max_bandwidth_hz);          
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_iqblk_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_vars.iqblk.getter                 = this->constants.IQBLK_GETTER_DEFAULT;
    this->_vars.iqblk.actual_buffer_samples  = this->constants.INIT_INT;
    //this->_vars.iqblk.sample_pairs_requested = this->constants.INIT_INT;
    this->_vars.iqblk.max_record_length      = this->constants.INIT_INT;      
    this->_vars.iqblk.record_length          = this->constants.IQBLK_STARTING_PAIRS;     

    this->_vars.iqblk.cplx32_v.resize((size_t)this->_vars.iqblk.record_length);
    for (size_t ii = 0; ii < this->_vars.iqblk.cplx32_v.size(); ii++)    
    {
        this->_vars.iqblk.cplx32_v[ii].i = this->constants.INIT_FLOAT;
        this->_vars.iqblk.cplx32_v[ii].q = this->constants.INIT_FLOAT;
    }             
                   
    this->_vars.iqblk.acq_info_type.sample0Timestamp   = this->constants.INIT_UINT;
    this->_vars.iqblk.acq_info_type.triggerSampleIndex = this->constants.INIT_UINT;
    this->_vars.iqblk.acq_info_type.triggerTimestamp   = this->constants.INIT_UINT;
    this->_vars.iqblk.acq_info_type.acqStatus          = this->constants.ACQ_STATUS_SUCCESS;
    this->_iqblk_bitcheck();    // updates "bitcheck"

    this->_vars.iqblk.sample_rate      = this->constants.INIT_DOUBLE;
    this->_vars.iqblk.bandwidth_hz     = this->constants.IQBLK_STARTING_BANDWIDTH;
    this->_vars.iqblk.min_bandwidth_hz = this->constants.INIT_DOUBLE;
    this->_vars.iqblk.max_bandwidth_hz = this->constants.INIT_DOUBLE;

    this->_iqblk_copy_vars();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqblk_bitcheck()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    memset(this->_vars.iqblk.bitcheck, '\0', BUF_D);
    
    if ((this->_vars.iqblk.acq_info_type.acqStatus  & 
            (uint32_t)RSA_API::IQBLK_STATUS_INPUT_OVERRANGE   &
            (uint32_t)RSA_API::IQBLK_STATUS_FREQREF_UNLOCKED  &
            (uint32_t)RSA_API::IQBLK_STATUS_ACQ_SYS_ERROR     &
            (uint32_t)RSA_API::IQBLK_STATUS_DATA_XFER_ERROR) == 
            this->constants.ACQ_STATUS_SUCCESS          )
    {
        snprintf(this->_vars.iqblk.bitcheck, BUF_D, 
            "acqStatus:  %d  ,  %s", 
            this->_vars.iqblk.acq_info_type.acqStatus, 
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE);
        this->_iqblk_copy_bitcheck();
        return;
    }

    snprintf(this->_vars.iqblk.bitcheck, BUF_D, "acqStatus:  %d  ,  ", 
        this->_vars.iqblk.acq_info_type.acqStatus);
    if ((this->_vars.iqblk.acq_info_type.acqStatus            & 
            (uint32_t)RSA_API::IQBLK_STATUS_INPUT_OVERRANGE) !=
            this->constants.ACQ_STATUS_SUCCESS                )
    {
        strncat(this->_vars.iqblk.bitcheck, 
            this->constants.IQBLK_BIT_0, 
            BUF_B);
    }
    if ((this->_vars.iqblk.acq_info_type.acqStatus             & 
            (uint32_t)RSA_API::IQBLK_STATUS_FREQREF_UNLOCKED) !=
            this->constants.ACQ_STATUS_SUCCESS           )
    {
        strncat(this->_vars.iqblk.bitcheck, 
            this->constants.IQBLK_BIT_1, 
            BUF_B);
    }
    if ((this->_vars.iqblk.acq_info_type.acqStatus          & 
            (uint32_t)RSA_API::IQBLK_STATUS_ACQ_SYS_ERROR) !=
            this->constants.ACQ_STATUS_SUCCESS        )
    {
        strncat(this->_vars.iqblk.bitcheck, 
            this->constants.IQBLK_BIT_2, 
            BUF_B);
    }
    if ((this->_vars.iqblk.acq_info_type.acqStatus            & 
            (uint32_t)RSA_API::IQBLK_STATUS_DATA_XFER_ERROR) !=
            this->constants.ACQ_STATUS_SUCCESS          )
    {
        strncat(this->_vars.iqblk.bitcheck, 
            this->constants.IQBLK_BIT_3, 
            BUF_B);
    }
    this->_iqblk_copy_bitcheck();
}


////////~~~~~~~~END>  rsa306b_iqblk_print_init_check.cpp
