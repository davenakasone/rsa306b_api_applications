/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >  _iqstream_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqstream_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.iqstream.is_enabled = this->_vars.iqstream._IS_ENABLED;

    this->_vars.iqstream.bandwidth     = this->_vars.iqstream._BANDWIDTH;
    this->_vars.iqstream.bandwidth_max = this->_vars.iqstream._BANDWIDTH_MAX;
    this->_vars.iqstream.bandwidth_min = this->_vars.iqstream._BANDWIDTH_MIN;
    this->_vars.iqstream.sample_rate   = this->_vars.iqstream._SAMPLE_RATE;

    this->_vars.iqstream.pairs_max         = this->_vars.iqstream._PAIRS_MAX;
    this->_vars.iqstream.record_time_ms    = this->_vars.iqstream._RECORD_TIME_MS;
    this->_vars.iqstream.suffix_control    = this->_vars.iqstream._SUFFIX_CONTROL;
    this->_vars.iqstream.buffer_multiplier = this->_vars.iqstream._BUFFER_MULTIPLIER;
    this->_vars.iqstream.pairs_copied      = this->_vars.iqstream._PAIRS_COPIED;

    (void)memset(this->_vars.iqstream.filename_base, '\0', sizeof(this->_vars.iqstream.filename_base));
    (void)strcpy(this->_vars.iqstream.filename_base, this->_vars.iqstream._FILENAME_BASE);

    (void)memset(this->_vars.iqstream.filenames_0_data, '\0', sizeof(this->_vars.iqstream.filenames_0_data));
    (void)strcpy(this->_vars.iqstream.filenames_0_data, this->_vars.iqstream._FILENAMES);

    (void)memset(this->_vars.iqstream.filenames_1_header, '\0', sizeof(this->_vars.iqstream.filenames_1_header));
    (void)strcpy(this->_vars.iqstream.filenames_1_header, this->_vars.iqstream._FILENAMES);

    for (int kk = 0; kk < IQSTREAM_BITCHECKS; kk++)
    {
        (void)memset(this->_vars.iqstream.acq_status_messages[kk], '\0', BUF_C);
        (void)strcpy(this->_vars.iqstream.acq_status_messages[kk], BITCHECK_SUCCESS_MESSAGE);
    }

    this->_vars.iqstream.cplx32_v.resize(this->_vars.iqstream._CPLX_V_size);
    this->_vars.iqstream.cplxInt16_v.resize(this->_vars.iqstream._CPLX_V_size);
    this->_vars.iqstream.cplxInt32_v.resize(this->_vars.iqstream._CPLX_V_size);
    for (std::size_t kk = 0; kk < this->_vars.iqstream._CPLX_V_size; kk++)
    {
        this->_vars.iqstream.cplx32_v[kk].i    = INIT_FLOAT;
        this->_vars.iqstream.cplx32_v[kk].q    = INIT_FLOAT;
        this->_vars.iqstream.cplxInt16_v[kk].i = INIT_INT16;
        this->_vars.iqstream.cplxInt16_v[kk].q = INIT_INT16;
        this->_vars.iqstream.cplxInt32_v[kk].i = INIT_INT32;
        this->_vars.iqstream.cplxInt32_v[kk].q = INIT_INT32;
    }

    this->_vars.iqstream.destination_select = this->_vars.iqstream._DESTINATION_SELECT;
    this->_vars.iqstream.datatype_select    = this->_vars.iqstream._DATATYPE_SELECT;

    this->_vars.iqstream.info_type.acqStatus      = this->_vars.iqstream._INFO_TYPE_acqStatus;
    this->_vars.iqstream.info_type.scaleFactor    = this->_vars.iqstream._INFO_TYPE_scaleFactor;
    this->_vars.iqstream.info_type.timestamp      = this->_vars.iqstream._INFO_TYPE_timestamp;
    this->_vars.iqstream.info_type.triggerCount   = this->_vars.iqstream._INFO_TYPE_triggerCount;
    // there is a pointer

    this->_vars.iqstream.fileinfo_type.acqStatus          = this->_vars.iqstream._FILEINFO_TYPE_acqStatus;
    this->_vars.iqstream.fileinfo_type.numberSamples      = this->_vars.iqstream._FILEINFO_TYPE_numberSamples;
    this->_vars.iqstream.fileinfo_type.sample0Timestamp   = this->_vars.iqstream._FILEINFO_TYPE_sample0Timestamp;
    this->_vars.iqstream.fileinfo_type.triggerSampleIndex = this->_vars.iqstream._FILEINFO_TYPE_triggerSampleIndex;
    this->_vars.iqstream.fileinfo_type.triggerTimestamp   = this->_vars.iqstream._FILEINFO_TYPE_triggerTimestamp;
    // there is a pointer

    return this->_iqstream_copy_vars();
}


////////~~~~~~~~END>  rsa306b_iqstream_init.cpp
    