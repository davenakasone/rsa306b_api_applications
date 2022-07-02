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
void rsa306b_class::print_iqstream()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    printf("\n'IQSTREAM' group >>>\n");
    printf("\tbandwidth                         :  %lf\n", this->_vars.iqstream.bandwidth);
    printf("\tbandwidth_max                     :  %lf\n", this->_vars.iqstream.bandwidth_max);
    printf("\tbandwidth_min                     :  %lf\n", this->_vars.iqstream.bandwidth_min);
    printf("\tsample_rate                       :  %lf\n", this->_vars.iqstream.sample_rate);
    printf("\tpairs_max                         :  %d\n", this->_vars.iqstream.pairs_max);
    printf("\trecord_time_ms                    :  %d\n", this->_vars.iqstream.record_time_ms);
    
    printf("\tsuffix_control                    :  %d  ,  ", this->_vars.iqstream.suffix_control);
    switch (this->_vars.iqstream.suffix_control)
    {
        case (RSA_API::IQSSDFN_SUFFIX_NONE)          : printf("none\n");           break;
        case (RSA_API::IQSSDFN_SUFFIX_TIMESTAMP)     : printf("timestamp\n");      break;
        case (RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN) : printf("auto-increment\n"); break;
        default                                      : printf("unknown\n");        break;
    }

     printf("\tdestination_select                :  %d  ,  ", this->_vars.iqstream.destination_select);
    switch (this->_vars.iqstream.destination_select)
    {
        case(RSA_API::IQSOD_CLIENT)         : printf("output direct to client, no file written\n");                   break;
        case(RSA_API::IQSOD_FILE_TIQ)       : printf("TIQ file output\n");                                            break;
        case(RSA_API::IQSOD_FILE_SIQ)       : printf("SIQ file output, combined header+data\n");                      break;
        case(RSA_API::IQSOD_FILE_SIQ_SPLIT) : printf("SIQH+SIQD file output, split header and data\n");               break;
        case(RSA_API::IQSOD_FILE_MIDAS)     : printf("Midas CDIF file output, combined header+data file\n");          break;
        case(RSA_API::IQSOD_FILE_MIDAS_DET) : printf("Midas CDIF+DET file output, separate header and data files\n"); break;
        default : printf("unknown\n"); break;
    }

    printf("\tdatatype_select                   :  %d  ,  ", this->_vars.iqstream.datatype_select);
    switch (this->_vars.iqstream.datatype_select)
    {
        case(RSA_API::IQSODT_SINGLE)             : printf("float32, scaled to volts/50 ohms\n"); break;
        case(RSA_API::IQSODT_INT32)              : printf("Int32\n");                            break;
        case(RSA_API::IQSODT_INT16)              : printf("Int16\n");                            break;
        case(RSA_API::IQSODT_SINGLE_SCALE_INT32) : printf("float32, scaled to int32 range\n");   break;
        default : printf("unknown\n"); break;
    }

    printf("\tpairs_requested                   :  %d\n", this->_vars.iqstream.pairs_requested);
    printf("\tpairs_copied                      :  %d\n", this->_vars.iqstream.pairs_copied);
    printf("\tname_of_file                      :  %s\n", this->_vars.iqstream.name_of_file);
    printf("\tname_of_header                    :  %s\n", this->_vars.iqstream.name_of_header);
    printf("\tcplx32_v.size()                   :  %lu\n", this->_vars.iqstream.cplx32_v.size());    
    printf("\t    cplx32_v[0].i                 :  %f\n", this->_vars.iqstream.cplx32_v[0].i);    
    printf("\t    cplx32_v[0].q                 :  %f\n", this->_vars.iqstream.cplx32_v[0].q);
    printf("\tcplxInt32_v.size()                :  %lu\n", this->_vars.iqstream.cplxInt32_v.size());    
    printf("\t    cplxInt32_v[0].i              :  %d\n", this->_vars.iqstream.cplxInt32_v[0].i);    
    printf("\t    cplxInt32_v[0].q              :  %d\n", this->_vars.iqstream.cplxInt32_v[0].q);
    printf("\tcplxInt16_v.size()                :  %lu\n", this->_vars.iqstream.cplxInt16_v.size());    
    printf("\t    cplxInt16_v[0].i              :  %d\n", this->_vars.iqstream.cplxInt16_v[0].i);    
    printf("\t    cplxInt16_v[0].q              :  %d\n", this->_vars.iqstream.cplxInt16_v[0].q);

    printf("\tinfo_type.acqStatus               :  %u\n", this->_vars.iqstream.info_type.acqStatus);
    printf("\tinfo_type.scaleFactor             :  %lf\n", this->_vars.iqstream.info_type.scaleFactor);
    printf("\tinfo_type.timestamp               :  %lu\n", this->_vars.iqstream.info_type.timestamp);
    printf("\tinfo_type.triggerCount            :  %d\n", this->_vars.iqstream.info_type.triggerCount);
    printf("\tinfo_type.triggerIndices          :  %p\n", this->_vars.iqstream.info_type.triggerIndices);
    
    printf("\tfileinfo_type.acqStatus           : %u\n", this->_vars.iqstream.fileinfo_type.acqStatus);
    printf("\tfileinfo_type.numberSamples       : %ld\n", this->_vars.iqstream.fileinfo_type.numberSamples);
    printf("\tfileinfo_type.sample0Timestamp    : %ld\n", this->_vars.iqstream.fileinfo_type.sample0Timestamp);
    printf("\tfileinfo_type.triggerSampleIndex  : %ld\n", this->_vars.iqstream.fileinfo_type.triggerSampleIndex);
    printf("\tfileinfo_type.triggerTimestamp    : %lu\n", this->_vars.iqstream.fileinfo_type.triggerTimestamp);
    if (this->_vars.iqstream.fileinfo_type.filenames == NULL)
    {
        printf("\tfileinfo_type.filenames           :  %p\n", this->_vars.iqstream.fileinfo_type.filenames);
    }
    else
    {
        printf("\tfileinfo_type.filenames[0]        : %s\n", this->_vars.iqstream.name_of_file);
        printf("\tfileinfo_type.filenames[1]        : %s\n", this->_vars.iqstream.name_of_header);
    }
    printf("\t%s\n", this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1]);
    for (int ii = 0; ii < IQSTREAM_BITCHECKS-1; ii++)
    {
        printf("\t  acqstatus_message [%2d]   :  %s\n", 
        ii,
        this->_vars.iqstream.acqStatus_message[ii]);
    }
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_iqstream_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_vars.iqstream.is_enabled = false;

    this->_vars.iqstream.bandwidth     = this->constants.INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_max = this->constants.INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_min = this->constants.INIT_DOUBLE;
    this->_vars.iqstream.sample_rate   = this->constants.INIT_DOUBLE;

    this->_vars.iqstream.pairs_max       = this->constants.INIT_INT;
    this->_vars.iqstream.record_time_ms  = this->constants.INIT_INT;
    this->_vars.iqstream.suffix_control  = this->constants.INIT_INT;
    this->_vars.iqstream.pairs_requested = this->constants.INIT_INT;
    this->_vars.iqstream.pairs_copied    = this->constants.INIT_INT;

    //this->_vars.iqstream.data_buffer = NULL;

    memset(this->_vars.iqstream.name_of_file, '\0', BUF_C);
    strcpy(this->_vars.iqstream.name_of_file, this->constants.INIT_STR);
    memset(this->_vars.iqstream.name_of_header, '\0', BUF_C);
    strcpy(this->_vars.iqstream.name_of_header, this->constants.INIT_STR);
    memset(this->_vars.iqstream.filename_base, '\0', BUF_C);
    strcpy(this->_vars.iqstream.filename_base, this->constants.INIT_STR);
    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        memset(this->_vars.iqstream.acqStatus_message[ii], '\0', BUF_C);
        strcpy(this->_vars.iqstream.acqStatus_message[ii], this->constants.INIT_STR);
    }

    this->_vars.iqstream.cplx32_v.resize(this->constants.INIT_STL_LENGTH);
    this->_vars.iqstream.cplxInt16_v.resize(this->constants.INIT_STL_LENGTH);
    this->_vars.iqstream.cplxInt32_v.resize(this->constants.INIT_STL_LENGTH);
    for (std::size_t ii = 0; ii < this->constants.INIT_STL_LENGTH; ii++)
    {
        this->_vars.iqstream.cplx32_v[ii].i    = this->constants.INIT_FLOAT;
        this->_vars.iqstream.cplx32_v[ii].q    = this->constants.INIT_FLOAT;
        this->_vars.iqstream.cplxInt16_v[ii].i = this->constants.INIT_UINT;
        this->_vars.iqstream.cplxInt16_v[ii].q = this->constants.INIT_UINT;
        this->_vars.iqstream.cplxInt32_v[ii].i = this->constants.INIT_UINT;
        this->_vars.iqstream.cplxInt32_v[ii].q = this->constants.INIT_UINT;
    }

    this->_vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
    this->_vars.iqstream.datatype_select    = RSA_API::IQSODT_SINGLE;

    this->_vars.iqstream.info_type.acqStatus      = this->constants.INIT_UINT;
    this->_vars.iqstream.info_type.scaleFactor    = this->constants.INIT_DOUBLE;
    this->_vars.iqstream.info_type.timestamp      = this->constants.INIT_UINT;
    this->_vars.iqstream.info_type.triggerCount   = this->constants.INIT_INT;
    this->_vars.iqstream.info_type.triggerIndices = NULL;

    this->_vars.iqstream.fileinfo_type.acqStatus          = this->constants.INIT_UINT;
    this->_vars.iqstream.fileinfo_type.numberSamples      = this->constants.INIT_UINT;
    this->_vars.iqstream.fileinfo_type.sample0Timestamp   = this->constants.INIT_UINT;
    this->_vars.iqstream.fileinfo_type.triggerSampleIndex = this->constants.INIT_UINT;
    this->_vars.iqstream.fileinfo_type.triggerTimestamp   = this->constants.INIT_UINT;
    this->_vars.iqstream.fileinfo_type.filenames          = NULL;

    this->_iqstream_copy_vars();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqstream_bitcheck
(
    uint32_t acqStatus
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        memset(this->_vars.iqstream.acqStatus_message[ii], '\0', BUF_C);
        strcpy(this->_vars.iqstream.acqStatus_message[ii], this->constants.INIT_STR);
    }
    strcpy(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], 
        this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_SUMMARY]);

    // bit 0
    if ((acqStatus & RSA_API::IQSTRM_STATUS_OVERRANGE) 
            == this->constants.ACQ_STATUS_SUCCESS    )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_0],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_0],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_0], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b0 ");
    }
    // bit 1
    if ((acqStatus & RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY) 
            == this->constants.ACQ_STATUS_SUCCESS             )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_1],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_1],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_1], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b1 ");
    }
    // bit 2
    if ((acqStatus & RSA_API::IQSTRM_STATUS_IBUFF75PCT) 
            == this->constants.ACQ_STATUS_SUCCESS     )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_2],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_2],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_2], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b2 ");
    }
    // bit 3
    if ((acqStatus & RSA_API::IQSTRM_STATUS_IBUFFOVFLOW) 
            == this->constants.ACQ_STATUS_SUCCESS      )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_3],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_3],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_3], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b3 ");
    }
    // bit 4
    if ((acqStatus & RSA_API::IQSTRM_STATUS_OBUFF75PCT) 
            == this->constants.ACQ_STATUS_SUCCESS      )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_4],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_4],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_4], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b4 ");
    }
    // bit 5
    if ((acqStatus & RSA_API::IQSTRM_STATUS_OBUFF75PCT) 
            == this->constants.ACQ_STATUS_SUCCESS      )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_5],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_5],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_5], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b5 ");
    }
    // bit 16
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_OVERRANGE << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                             )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_16],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_16],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_16], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b16 ");
    }
    // bit 17
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                                      )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_17],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_17],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_17], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b17 ");
    }
    // bit 18
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_IBUFF75PCT << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                              )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_18],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_18],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_18], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b18 ");
    }
    // bit 19
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_IBUFFOVFLOW << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                               )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_19],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_19],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_19], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b19 ");
    }
    // bit 20
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_OBUFF75PCT << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                              )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_20],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_20],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_20], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b20 ");
    }
    // bit 21
    if ((acqStatus & (RSA_API::IQSTRM_STATUS_OBUFFOVFLOW << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) 
            == this->constants.ACQ_STATUS_SUCCESS                                               )
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_21],
            this->constants.ACQ_STATUS_SUCCESS_MESSAGE, BUF_C);
    }
    else
    {
        strncpy(this->_vars.iqstream.acqStatus_message[this->constants.IQS_BIT_21],
            this->constants.IQSTREAM_FAIL_BIT[this->constants.IQS_BIT_21], BUF_C);
        strcat(this->_vars.iqstream.acqStatus_message[IQSTREAM_BITCHECKS-1], "b21 ");
    }

    this->_iqstream_copy_acqStatus_message();
}


////////~~~~~~~~END>  rsa306b_iqstream_print_init.cpp       
        