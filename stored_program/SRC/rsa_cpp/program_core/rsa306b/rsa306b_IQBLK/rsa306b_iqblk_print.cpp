/*
    API group "IQBLK"

    public :
        < 1 >  print_iqblk()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::iqblk_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'IQBLK' group >>>\n");
    (void)printf("\tgetting_select                    :  %d  ,  ", this->_vars.iqblk.getting_select);
    (void)printf("\trecord_length                     :  %d\n", this->_vars.iqblk.record_length);
    (void)printf("\tmax_record_length                 :  %d\n", this->_vars.iqblk.max_record_length);
    (void)printf("\tactual_buffer_samples             :  %d\n", this->_vars.iqblk.actual_buffer_samples);
    (void)printf("\tcplx32_v.size()                   :  %ld\n", this->_vars.iqblk.cplx32_v.size());     
    (void)printf("\tacq_info_type.acqStatus           :  %u\n", this->_vars.iqblk.acq_info_type.acqStatus);
    (void)printf("\tacq_info_type.sample0Timestamp    :  %lu\n", this->_vars.iqblk.acq_info_type.sample0Timestamp);
    (void)printf("\tacq_info_type.triggerSampleIndex  :  %lu\n", this->_vars.iqblk.acq_info_type.triggerSampleIndex);
    (void)printf("\tacq_info_type.triggerTimestamp    :  %lu\n", this->_vars.iqblk.acq_info_type.triggerTimestamp);
    (void)printf("\tsample_rate                       :  %lf\n", this->_vars.iqblk.sample_rate);
    (void)printf("\tbandwidth_hz                      :  %lf\n", this->_vars.iqblk.bandwidth_hz);
    (void)printf("\tmin_bandwidth_hz                  :  %lf\n", this->_vars.iqblk.min_bandwidth_hz);
    (void)printf("\tmax_bandwidth_hz                  :  %lf\n", this->_vars.iqblk.max_bandwidth_hz);          
}


////////~~~~~~~~END>  rsa306b_iqblk_print.cpp
