/*
    API group "IQSTREAM"

    public :
        < 1 >  print_iqstream()
    
    private :
        < 1 >  _iqstream_init()
        < 2 >  _iqstream_bitcheck()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::print_iqstream()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'IQSTREAM' group >>>\n");
    (void)printf("\tis_enabled                            :  %d\n", this->_vars.iqstream.is_enabled);
    (void)printf("\tbandwidth                             :  %lf\n", this->_vars.iqstream.bandwidth);
    (void)printf("\tbandwidth_max                         :  %lf\n", this->_vars.iqstream.bandwidth_max);
    (void)printf("\tbandwidth_min                         :  %lf\n", this->_vars.iqstream.bandwidth_min);
    (void)printf("\tsample_rate                           :  %lf\n", this->_vars.iqstream.sample_rate);
    (void)printf("\tdestination_select                    :  %d  ,  ", this->_vars.iqstream.destination_select);
    switch (this->_vars.iqstream.destination_select)
    {
        case(RSA_API::IQSOD_CLIENT)         : (void)printf("output direct to client, no file written\n");                   break;
        case(RSA_API::IQSOD_FILE_TIQ)       : (void)printf("TIQ file output\n");                                            break;
        case(RSA_API::IQSOD_FILE_SIQ)       : (void)printf("SIQ file output, combined header+data\n");                      break;
        case(RSA_API::IQSOD_FILE_SIQ_SPLIT) : (void)printf("SIQH+SIQD file output, split header and data\n");               break;
        case(RSA_API::IQSOD_FILE_MIDAS)     : (void)printf("Midas CDIF file output, combined header+data file\n");          break;
        case(RSA_API::IQSOD_FILE_MIDAS_DET) : (void)printf("Midas CDIF+DET file output, separate header and data files\n"); break;
        default : (void)printf("unknown\n"); break;
    }
    (void)printf("\tdatatype_select                       :  %d  ,  ", this->_vars.iqstream.datatype_select);
    switch (this->_vars.iqstream.datatype_select)
    {
        case(RSA_API::IQSODT_SINGLE)             : (void)printf("float32, scaled to volts/50 ohms\n"); break;
        case(RSA_API::IQSODT_INT32)              : (void)printf("Int32\n");                            break;
        case(RSA_API::IQSODT_INT16)              : (void)printf("Int16\n");                            break;
        case(RSA_API::IQSODT_SINGLE_SCALE_INT32) : (void)printf("float32, scaled to int32 range\n");   break;
        default : (void)printf("unknown\n"); break;
    }
    
    (void)printf("\tSTL containers >>>\n");
    (void)printf("\t    cplx32_v.size()                   :  %lu\n", this->_vars.iqstream.cplx32_v.size());    
    (void)printf("\t        cplx32_v[0].i                 :  %f\n", this->_vars.iqstream.cplx32_v[0].i);    
    (void)printf("\t        cplx32_v[0].q                 :  %f\n", this->_vars.iqstream.cplx32_v[0].q);
    (void)printf("\t    cplxInt32_v.size()                :  %lu\n", this->_vars.iqstream.cplxInt32_v.size());    
    (void)printf("\t        cplxInt32_v[0].i              :  %d\n", this->_vars.iqstream.cplxInt32_v[0].i);    
    (void)printf("\t        cplxInt32_v[0].q              :  %d\n", this->_vars.iqstream.cplxInt32_v[0].q);
    (void)printf("\t    cplxInt16_v.size()                :  %lu\n", this->_vars.iqstream.cplxInt16_v.size());    
    (void)printf("\t        cplxInt16_v[0].i              :  %d\n", this->_vars.iqstream.cplxInt16_v[0].i);    
    (void)printf("\t        cplxInt16_v[0].q              :  %d\n", this->_vars.iqstream.cplxInt16_v[0].q);
    
    (void)printf("\tstreaming direct >>>\n");
    (void)printf("\t    pairs_max                         :  %d\n", this->_vars.iqstream.pairs_max);
    (void)printf("\t    pairs_copied                      :  %d\n", this->_vars.iqstream.pairs_copied);
    (void)printf("\t    buffer_multiplier                 :  %d\n", this->_vars.iqstream.buffer_multiplier);
    (void)printf("\t    info_type.acqStatus               :  %u\n", this->_vars.iqstream.info_type.acqStatus);
    (void)printf("\t    info_type.scaleFactor             :  %lf\n", this->_vars.iqstream.info_type.scaleFactor);
    (void)printf("\t    info_type.timestamp               :  %lu\n", this->_vars.iqstream.info_type.timestamp);
    (void)printf("\t    info_type.triggerCount            :  %d\n", this->_vars.iqstream.info_type.triggerCount);
    (void)printf("\t    info_type.triggerIndices          :  %p\n", this->_vars.iqstream.info_type.triggerIndices);
    
    (void)printf("\tstreaming to file >>>\n");
    (void)printf("\t    record_time_ms                    :  %d\n", this->_vars.iqstream.record_time_ms);
    (void)printf("\t    filename_base                     :  %s\n", this->_vars.iqstream.filename_base);
    (void)printf("\t    suffix_control                    :  %d  ,  ", this->_vars.iqstream.suffix_control);
    switch (this->_vars.iqstream.suffix_control)
    {
        case (RSA_API::IQSSDFN_SUFFIX_NONE)          : (void)printf("none\n");           break;
        case (RSA_API::IQSSDFN_SUFFIX_TIMESTAMP)     : (void)printf("timestamp\n");      break;
        case (RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN) : (void)printf("auto-increment\n"); break;
        default                                      : (void)printf("unknown\n");        break;
    }
    (void)printf("\t    fileinfo_type.acqStatus           : %u\n", this->_vars.iqstream.fileinfo_type.acqStatus);
    (void)printf("\t    fileinfo_type.numberSamples       : %ld\n", this->_vars.iqstream.fileinfo_type.numberSamples);
    (void)printf("\t    fileinfo_type.sample0Timestamp    : %ld\n", this->_vars.iqstream.fileinfo_type.sample0Timestamp);
    (void)printf("\t    fileinfo_type.triggerSampleIndex  : %ld\n", this->_vars.iqstream.fileinfo_type.triggerSampleIndex);
    (void)printf("\t    fileinfo_type.triggerTimestamp    : %lu\n", this->_vars.iqstream.fileinfo_type.triggerTimestamp);
    (void)printf("\t    fileinfo_type.filenames           :  %p\n", this->_vars.iqstream.fileinfo_type.filenames);
    (void)printf("\t    fileinfo_type.filenames_0         :  %s\n", this->_vars.iqstream.fileinfo_type.filenames_0);
    (void)printf("\t    fileinfo_type.filenames_1         :  %s\n", this->_vars.iqstream.fileinfo_type.filenames_1);

    (void)printf("\t%s\n", this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1]);
    for (int ii = 0; ii < IQSTREAM_BITCHECKS-1; ii++)
    {
        (void)printf("\t  acqstatus_message [%2d]   :  %s\n", 
        ii,
        this->_vars.iqstream.acqStatus_message[ii]);
    }
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqstream_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.iqstream.is_enabled = false;

    this->_vars.iqstream.bandwidth     = INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_max = INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_min = INIT_DOUBLE;
    this->_vars.iqstream.sample_rate   = INIT_DOUBLE;

    this->_vars.iqstream.pairs_max         = INIT_INT;
    this->_vars.iqstream.record_time_ms    = INIT_INT;
    this->_vars.iqstream.suffix_control    = INIT_INT;
    this->_vars.iqstream.buffer_multiplier = this->constants.IQSTREAM_BUFFER_X_6;
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
        this->_vars.iqstream.cplxInt16_v[ii].i = INIT_UINT;
        this->_vars.iqstream.cplxInt16_v[ii].q = INIT_UINT;
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


////////~~~~~~~~END>  rsa306b_iqstream_print_init.cpp       
        