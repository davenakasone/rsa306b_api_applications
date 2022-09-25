/*
    API group "IQBLK"

    public :
        #  none
    
    private :
        < 1 >  _iqblk_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqblk_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.iqblk.acq_info_type.acqStatus          = this->_vars.iqblk._ACQ_INFO_TYPE_acqStatus;
    this->_vars.iqblk.acq_info_type.sample0Timestamp   = this->_vars.iqblk._ACQ_INFO_TYPE_sample0Timestamp;
    this->_vars.iqblk.acq_info_type.triggerSampleIndex = this->_vars.iqblk._ACQ_INFO_TYPE_triggerSampleIndex;
    this->_vars.iqblk.acq_info_type.triggerTimestamp   = this->_vars.iqblk._ACQ_INFO_TYPE_triggerTimestamp;

    for (int ii = 0; ii < IQBLK_BITCHECKS; ii++)
    {
        //(void)strcpy(this->_vars.iqblk.acq_status_messages[ii], this->_vars.iqblk._ACQ_STATUS_MESSAGES);
        (void)strcpy(this->_vars.iqblk.acq_status_messages[ii], BITCHECK_SUCCESS_MESSAGE);
    }

    this->_vars.iqblk.bandwidth_hz          = this->_vars.iqblk._BANDWIDTH_HZ;
    this->_vars.iqblk.actual_buffer_samples = this->_vars.iqblk._ACTUAL_BUFFER_SAMPLES;

    this->_vars.iqblk.cplx32_v.resize(this->_vars.iqblk._CPLX32_V_size);
    for (std::size_t kk = 0; kk < this->_vars.iqblk.cplx32_v.size(); kk++)
    {
        this->_vars.iqblk.cplx32_v[kk].i = this->_vars.iqblk._CPLX32_V_element;
        this->_vars.iqblk.cplx32_v[kk].q = this->_vars.iqblk._CPLX32_V_element;
    }

    this->_vars.iqblk.record_length = this->_vars.iqblk._RECORD_LENGTH;
    this->_vars.iqblk.sample_rate = this->_vars.iqblk._SAMPLE_RATE;
    this->_vars.iqblk.max_bandwidth_hz = this->_vars.iqblk._MAX_BANDWIDTH_HZ;
    this->_vars.iqblk.min_bandwidth_hz = this->_vars.iqblk._MIN_BANDWIDTH_HZ;
    this->_vars.iqblk.max_record_length = this->_vars.iqblk._MAX_RECORD_LENGTH;

    this->_vars.iqblk.getting_select = this->_vars.iqblk._GETTING_SELECT;

    return this->_iqblk_copy_vars();
}


////////~~~~~~~~END>  rsa306b_iqblk_init.cpp
