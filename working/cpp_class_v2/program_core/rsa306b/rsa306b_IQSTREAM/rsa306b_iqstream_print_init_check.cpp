/*
    API group "IQSTREAM"

    public :
        < 1 >  print_iqstream()
    
    private :
        < 1 >  _iqstream_init()
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
    printf("\tbandwidth       :  %lf\n", this->_vars.iqstream.bandwidth);
    printf("\tbandwidth_max   :  %lf\n", this->_vars.iqstream.bandwidth_max);
    printf("\tbandwidth_min   :  %lf\n", this->_vars.iqstream.bandwidth_min);
    printf("\tsample_rate     :  %lf\n", this->_vars.iqstream.sample_rate);
    printf("\tpairs_max       :  %d\n", this->_vars.iqstream.pairs_max);
    printf("\trecord_time_ms  :  %d\n", this->_vars.iqstream.record_time_ms);
    printf("\tsuffix_control  :  %d  ,  ", this->_vars.iqstream.suffix_control);
    switch (this->_vars.iqstream.suffix_control)
    {
        case (RSA_API::IQSSDFN_SUFFIX_NONE)          : printf("none\n");           break;
        case (RSA_API::IQSSDFN_SUFFIX_TIMESTAMP)     : printf("timestamp\n");      break;
        case (RSA_API::IQSSDFN_SUFFIX_INCRINDEX_MIN) : printf("auto-increment\n"); break;
        default                                      : printf("unknown\n");        break;
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

    this->_vars.iqstream.bandwidth     = this->_vars.constants.INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_max = this->_vars.constants.INIT_DOUBLE;
    this->_vars.iqstream.bandwidth_min = this->_vars.constants.INIT_DOUBLE;
    this->_vars.iqstream.sample_rate   = this->_vars.constants.INIT_DOUBLE;

    this->_vars.iqstream.pairs_max       = this->_vars.constants.INIT_INT;
    this->_vars.iqstream.record_time_ms  = this->_vars.constants.INIT_INT;
    this->_vars.iqstream.suffix_control  = this->_vars.constants.INIT_INT;
    this->_vars.iqstream.pairs_requested = this->_vars.constants.INIT_INT;
    this->_vars.iqstream.pairs_copied    = this->_vars.constants.INIT_INT;

    this->_vars.iqstream.data_buffer = NULL;

    memset(this->_vars.iqstream.name_of_file, '\0', BUF_C);
    strcpy(this->_vars.iqstream.name_of_file, this->_vars.constants.INIT_STR);
    memset(this->_vars.iqstream.name_of_header, '\0', BUF_C);
    strcpy(this->_vars.iqstream.name_of_header, this->_vars.constants.INIT_STR);
    memset(this->_vars.iqstream.filename_base, '\0', BUF_C);
    strcpy(this->_vars.iqstream.filename_base, this->_vars.constants.INIT_STR);

    this->_vars.iqstream.cplx32_v.resize(this->_vars.constants.INIT_STL_LENGTH);
    this->_vars.iqstream.cplxInt16_v.resize(this->_vars.constants.INIT_STL_LENGTH);
    this->_vars.iqstream.cplxInt32_v.resize(this->_vars.constants.INIT_STL_LENGTH);
    for (std::size_t ii = 0; ii < this->_vars.constants.INIT_STL_LENGTH; ii++)
    {
        this->_vars.iqstream.cplx32_v[ii].i    = this->_vars.constants.INIT_FLOAT;
        this->_vars.iqstream.cplx32_v[ii].q    = this->_vars.constants.INIT_FLOAT;
        this->_vars.iqstream.cplxInt16_v[ii].i = this->_vars.constants.INIT_UINT;
        this->_vars.iqstream.cplxInt16_v[ii].q = this->_vars.constants.INIT_UINT;
        this->_vars.iqstream.cplxInt32_v[ii].i = this->_vars.constants.INIT_UINT;
        this->_vars.iqstream.cplxInt32_v[ii].q = this->_vars.constants.INIT_UINT;
    }

    this->_vars.iqstream.destination_select = RSA_API::IQSOD_FILE_SIQ;
    this->_vars.iqstream.datatype_select    = RSA_API::IQSODT_SINGLE;

    this->_vars.iqstream.info_type.acqStatus      = this->_vars.constants.INIT_UINT;
    this->_vars.iqstream.info_type.scaleFactor    = this->_vars.constants.INIT_DOUBLE;
    this->_vars.iqstream.info_type.timestamp      = this->_vars.constants.INIT_UINT;
    this->_vars.iqstream.info_type.triggerCount   = this->_vars.constants.INIT_INT;
    this->_vars.iqstream.info_type.triggerIndices = NULL;

    this->_vars.iqstream.file_info_type.acqStatus          = this->_vars.constants.INIT_UINT;
    this->_vars.iqstream.file_info_type.numberSamples      = this->_vars.constants.INIT_UINT;
    this->_vars.iqstream.file_info_type.sample0Timestamp   = this->_vars.constants.INIT_UINT;
    this->_vars.iqstream.file_info_type.triggerSampleIndex = this->_vars.constants.INIT_UINT;
    this->_vars.iqstream.file_info_type.triggerTimestamp   = this->_vars.constants.INIT_UINT;
    this->_vars.iqstream.file_info_type.filenames          = NULL;

    //copy...
}


////////~~~~~~~~END>  rsa306b_iqstream_print_init.cpp       
        