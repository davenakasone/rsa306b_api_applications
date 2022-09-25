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
CODEZ rsa306b_class::iqstream_print()
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
    (void)printf("\t    fileinfo_type.filenames_0         :  %s\n", this->_vars.iqstream.filenames_0_data);
    (void)printf("\t    fileinfo_type.filenames_1         :  %s\n", this->_vars.iqstream.filenames_1_header);

    (void)printf("\t%s\n", this->_vars.iqstream.acq_status_messages[IQSTREAM_BITCHECKS-1]);
    for (int ii = 0; ii < IQSTREAM_BITCHECKS-1; ii++)
    {
        (void)printf("\t  acqstatus_message [%2d]   :  %s\n", 
        ii,
        this->_vars.iqstream.acq_status_messages[ii]);
    }
    
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_iqstream_print.cpp
