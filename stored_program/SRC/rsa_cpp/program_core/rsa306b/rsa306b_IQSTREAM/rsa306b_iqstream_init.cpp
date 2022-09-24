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

    this->_vars.iqstream.is_enabled = this->_vars.iqstream._IS

    this->_vars.iqstream.bandwidth     = INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_max = INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_min = INIT_DOUBLE;
    this->_vars.iqstream.sample_rate   = INIT_DOUBLE;

    this->_vars.iqstream.pairs_max         = INIT_INT;
    this->_vars.iqstream.record_time_ms    = INIT_INT;
    this->_vars.iqstream.suffix_control    = INIT_INT;
    this->_vars.iqstream.buffer_multiplier = this->_vars.iqstream._BUFFER_MULTIPLIER;
    this->_vars.iqstream.pairs_copied      = INIT_INT;

    (void)memset(this->_vars.iqstream.filename_base, '\0', BUF_C);
    (void)strcpy(this->_vars.iqstream.filename_base, INIT_CHARP);
    (void)memset(this->_vars.iqstream.fileinfo_type.filenames_0, '\0', BUF_E);
    (void)memset(this->_vars.iqstream.fileinfo_type.filenames_0, '\0', BUF_E);
    (void)strcpy(this->_vars.iqstream.fileinfo_type.filenames_0, INIT_CHARP);
    (void)strcpy(this->_vars.iqstream.fileinfo_type.filenames_0, INIT_CHARP);

    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        (void)memset(this->_vars.iqstream.acqStatus_message[ii], '\0', BUF_C);
        (void)strncpy(this->_vars.iqstream.acqStatus_message[ii], INIT_CHARP, BUF_C);
    }

    this->_vars.iqstream.cplx32_v.resize(INIT_STL_LENGTH);
    this->_vars.iqstream.cplxInt16_v.resize(INIT_STL_LENGTH);
    this->_vars.iqstream.cplxInt32_v.resize(INIT_STL_LENGTH);
    for (std::size_t ii = 0; ii < INIT_STL_LENGTH; ii++)
    {
        this->_vars.iqstream.cplx32_v[ii].i    = INIT_FLOAT;
        this->_vars.iqstream.cplx32_v[ii].q    = INIT_FLOAT;
        this->_vars.iqstream.cplxInt16_v[ii].i = INIT_INT16;
        this->_vars.iqstream.cplxInt16_v[ii].q = INIT_INT16;
        this->_vars.iqstream.cplxInt32_v[ii].i = INIT_UINT;
        this->_vars.iqstream.cplxInt32_v[ii].q = INIT_UINT;
    }

    this->_vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
    this->_vars.iqstream.datatype_select    = RSA_API::IQSODT_SINGLE;

    this->_vars.iqstream.info_type.acqStatus      = INIT_UINT;
    this->_vars.iqstream.info_type.scaleFactor    = INIT_DOUBLE;
    this->_vars.iqstream.info_type.timestamp      = INIT_UINT;
    this->_vars.iqstream.info_type.triggerCount   = INIT_INT;
    this->_vars.iqstream.info_type.triggerIndices = NULL;

    this->_vars.iqstream.fileinfo_type.acqStatus          = INIT_UINT;
    this->_vars.iqstream.fileinfo_type.numberSamples      = INIT_UINT;
    this->_vars.iqstream.fileinfo_type.sample0Timestamp   = INIT_UINT;
    this->_vars.iqstream.fileinfo_type.triggerSampleIndex = INIT_UINT;
    this->_vars.iqstream.fileinfo_type.triggerTimestamp   = INIT_UINT;
    this->_vars.iqstream.fileinfo_type.filenames          = NULL;

    this->_iqstream_copy_vars();
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_iqstream_bitcheck
(
    uint32_t acqStatus
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        (void)memset(this->_vars.iqstream.acqStatus_message[ii], '\0', BUF_C);
        (void)strcpy(this->_vars.iqstream.acqStatus_message[ii], INIT_CHARP);
    }
    (void)strcpy(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], 
        this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_SUMMARY]);

    // bit 0
    if ((acqStatus & RSA_API::IQSTRM_STATUS_OVERRANGE) 
            == this->constants.ACQ_STATUS_SUCCESS    )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_0],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_0],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_0], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b0 ");
    }
    // bit 1
    if ((acqStatus & RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY) 
            == this->constants.ACQ_STATUS_SUCCESS             )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_1],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_1],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_1], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b1 ");
    }
    // bit 2
    if ((acqStatus & RSA_API::IQSTRM_STATUS_IBUFF75PCT) 
            == this->constants.ACQ_STATUS_SUCCESS     )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_2],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_2],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_2], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b2 ");
    }
    // bit 3
    if ((acqStatus & RSA_API::IQSTRM_STATUS_IBUFFOVFLOW) 
            == this->constants.ACQ_STATUS_SUCCESS      )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_3],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_3],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_3], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b3 ");
    }
    // bit 4
    if ((acqStatus & RSA_API::IQSTRM_STATUS_OBUFF75PCT) 
            == this->constants.ACQ_STATUS_SUCCESS     )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_4],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_4],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_4], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b4 ");
    }
    // bit 5
    if ((acqStatus & RSA_API::IQSTRM_STATUS_OBUFF75PCT) 
            == this->constants.ACQ_STATUS_SUCCESS     )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_5],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_5],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_5], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b5 ");
    }
    // bit 16
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_OVERRANGE << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                             )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_16],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_16],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_16], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b16 ");
    }
    // bit 17
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                                      )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_17],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_17],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_17], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b17 ");
    }
    // bit 18
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_IBUFF75PCT << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                              )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_18],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_18],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_18], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b18 ");
    }
    // bit 19
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_IBUFFOVFLOW << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                               )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_19],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_19],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_19], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b19 ");
    }
    // bit 20
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_OBUFF75PCT << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                              )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_20],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_20],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_20], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b20 ");
    }
    // bit 21
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_OBUFFOVFLOW << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                               )
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_21],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        (void)strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQSTREAM_BIT_21],
            this->constants.IQSTREAM_FAIL_BITS[this->constants.IQSTREAM_BIT_21], BUF_C);
        (void)strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b21 ");
    }

    this->_iqstream_copy_acqStatus_message();
}


////////~~~~~~~~END>  rsa306b_iqstream_init.cpp
