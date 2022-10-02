/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >   _iqstream_copy_vars()
        < 2 >   _iqstream_copy_acq_status_messages()
        < 3 >   _iqstream_copy_bandwidth()
        < 4 >   _iqstream_copy_bandwidth_max()
        < 5 >   _iqstream_copy_bandwidth_min()
        < 6 >   _iqstream_copy_sample_rate()
        < 7 >   _iqstream_copy_fileinfo_type()
        < 8 >   _iqstream_copy_is_enabled()        
        < 9 >   _iqstream_copy_pairs_copied()   
        < 10 >  _iqstream_copy_info_type() 
        < 11 >  _iqstream_copy_cplx32_v()
        < 12 >  _iqstream_copy_cplxInt16_v()
        < 13 >  _iqstream_copy_cplxInt32_v()
        < 14 >  _iqstream_copy_pairs_max()
        < 15 >  _iqstream_copy_record_time_ms()
        < 16 >  _iqstream_copy_filename_base()
        < 17 >  _iqstream_copy_suffix_control()
        < 18 >  _iqstream_copy_buffer_multiplier()
        < 19 >  _iqstream_copy_destination_select()
        < 20 >  _iqstream_copy_datatype_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqstream_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    constexpr int callz = 19;
    CODEZ caught_call[callz];

    caught_call[0]  = this->_iqstream_copy_acq_status_messages();
    caught_call[1]  = this->_iqstream_copy_bandwidth          ();
    caught_call[2]  = this->_iqstream_copy_bandwidth_max      ();
    caught_call[3]  = this->_iqstream_copy_bandwidth_min      ();
    caught_call[4]  = this->_iqstream_copy_sample_rate        ();
    caught_call[5]  = this->_iqstream_copy_fileinfo_type      ();
    caught_call[6]  = this->_iqstream_copy_is_enabled         ();       
    caught_call[7]  = this->_iqstream_copy_pairs_copied       ();   
    caught_call[8]  = this->_iqstream_copy_info_type          ();
    caught_call[9]  = this->_iqstream_copy_cplx32_v           ();
    caught_call[10] = this->_iqstream_copy_cplxInt16_v        ();
    caught_call[11] = this->_iqstream_copy_cplxInt32_v        ();
    caught_call[12] = this->_iqstream_copy_pairs_max          ();
    caught_call[13] = this->_iqstream_copy_record_time_ms     ();
    caught_call[14] = this->_iqstream_copy_filename_base      ();
    caught_call[15] = this->_iqstream_copy_suffix_control     ();
    caught_call[16] = this->_iqstream_copy_buffer_multiplier  ();
    caught_call[17] = this->_iqstream_copy_destination_select ();
    caught_call[18] = this->_iqstream_copy_datatype_select    ();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_iqstream_copy_acq_status_messages()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        (void)strcpy(this->vars.iqstream.acq_status_messages[ii],
            this->_vars.iqstream.acq_status_messages[ii]);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_iqstream_copy_bandwidth()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.bandwidth = this->_vars.iqstream.bandwidth;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_iqstream_copy_bandwidth_max()
{ 
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.bandwidth_max = this->_vars.iqstream.bandwidth_max;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_iqstream_copy_bandwidth_min()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.bandwidth_min = this->_vars.iqstream.bandwidth_min;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_iqstream_copy_sample_rate()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.sample_rate = this->_vars.iqstream.sample_rate;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_iqstream_copy_fileinfo_type()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.fileinfo_type.acqStatus          = this->_vars.iqstream.fileinfo_type.acqStatus;
    this->vars.iqstream.fileinfo_type.numberSamples      = this->_vars.iqstream.fileinfo_type.numberSamples;
    this->vars.iqstream.fileinfo_type.sample0Timestamp   = this->_vars.iqstream.fileinfo_type.sample0Timestamp;
    this->vars.iqstream.fileinfo_type.triggerSampleIndex = this->_vars.iqstream.fileinfo_type.triggerSampleIndex;
    this->vars.iqstream.fileinfo_type.triggerTimestamp   = this->_vars.iqstream.fileinfo_type.triggerTimestamp;
    
    // taking 2x char* and ignoring wchar_t**
    (void)strcpy(this->vars.iqstream.filenames_0_data, this->_vars.iqstream.filenames_0_data);
    (void)strcpy(this->vars.iqstream.filenames_1_header, this->_vars.iqstream.filenames_1_header);
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_iqstream_copy_is_enabled()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.is_enabled = this->_vars.iqstream.is_enabled;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 9 > private
*/
CODEZ rsa306b_class::_iqstream_copy_pairs_copied() 
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.pairs_copied = this->_vars.iqstream.pairs_copied;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 10 > private
*/
CODEZ rsa306b_class::_iqstream_copy_info_type() 
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.info_type.acqStatus    = this->_vars.iqstream.info_type.acqStatus;
    this->vars.iqstream.info_type.scaleFactor  = this->_vars.iqstream.info_type.scaleFactor;
    this->vars.iqstream.info_type.timestamp    = this->_vars.iqstream.info_type.timestamp;
    this->vars.iqstream.info_type.triggerCount = this->_vars.iqstream.info_type.triggerCount;
    
    // take the address to the internal buffer, if availible
    if (this->_vars.iqstream.info_type.triggerCount <= 0)
    {
        this->vars.iqstream.info_type.triggerIndices = NULL;
    }
    else    // shallow copy to address
    {
        this->vars.iqstream.info_type.triggerIndices = this->vars.iqstream.info_type.triggerIndices;
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 11 > private
*/
CODEZ rsa306b_class::_iqstream_copy_cplx32_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.cplx32_v.resize(
        this->_vars.iqstream.cplx32_v.size());
    this->vars.iqstream.cplx32_v = this->_vars.iqstream.cplx32_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 12 > private
*/
CODEZ rsa306b_class::_iqstream_copy_cplxInt16_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.cplxInt16_v.resize(
        this->_vars.iqstream.cplxInt16_v.size());
    this->vars.iqstream.cplxInt16_v = this->_vars.iqstream.cplxInt16_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 13 > private
*/
CODEZ rsa306b_class::_iqstream_copy_cplxInt32_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.cplxInt32_v.resize(
        this->_vars.iqstream.cplxInt32_v.size());
    this->vars.iqstream.cplxInt32_v = this->_vars.iqstream.cplxInt32_v;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 14 > private
*/
CODEZ rsa306b_class::_iqstream_copy_pairs_max()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.pairs_max = this->_vars.iqstream.pairs_max;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 15 > private
*/
CODEZ rsa306b_class::_iqstream_copy_record_time_ms()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.record_time_ms = this->_vars.iqstream.record_time_ms;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 16 > private
*/
CODEZ rsa306b_class::_iqstream_copy_filename_base()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    strcpy(this->vars.iqstream.filename_base, this->_vars.iqstream.filename_base);
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 17 > private
*/
CODEZ rsa306b_class::_iqstream_copy_suffix_control()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.suffix_control = this->_vars.iqstream.suffix_control;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 18 > private
*/
CODEZ rsa306b_class::_iqstream_copy_buffer_multiplier()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.buffer_multiplier = this->_vars.iqstream.buffer_multiplier;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 19 > private
*/
CODEZ rsa306b_class::_iqstream_copy_destination_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.destination_select = this->_vars.iqstream.destination_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 20 > private
*/
CODEZ rsa306b_class::_iqstream_copy_datatype_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->vars.iqstream.datatype_select = this->_vars.iqstream.datatype_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_iqstream_copy.cpp
