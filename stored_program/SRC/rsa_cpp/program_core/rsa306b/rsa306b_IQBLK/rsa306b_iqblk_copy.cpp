/*
    API group "IQBLK"

    public :
        #  none
    
    private :
        < 1 >   _iqblk_copy_vars()
        < 2 >   _iqblk_copy_getting_select()
        < 3 >   _iqblk_copy_actual_buffer_samples()
        < 4 >   _iqblk_copy_cplx32_v()
        < 5 >   _iqblk_copy_acq_info_type()
        < 6 >   _iqblk_copy_sample_rate()
        < 7 >   _iqblk_copy_bandwidth_hz()
        < 8 >   _iqblk_copy_max_bandwidth_hz()
        < 9 >   _iqblk_copy_min_bandwidth_hz()
        < 10 >  _iqblk_copy_record_length()
        < 11 >  _iqblk_copy_max_record_length()
        < 12 >  _iqblk_copy_acq_status_messages()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqblk_copy_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    constexpr int callz = 11;
    CODEZ caught_call[callz];

    caught_call[0]  = this->_iqblk_copy_getting_select       ();
    caught_call[1]  = this->_iqblk_copy_actual_buffer_samples();
    caught_call[2]  = this->_iqblk_copy_cplx32_v             ();
    caught_call[3]  = this->_iqblk_copy_acq_info_type        ();
    caught_call[4]  = this->_iqblk_copy_sample_rate          ();
    caught_call[5]  = this->_iqblk_copy_bandwidth_hz         ();
    caught_call[6]  = this->_iqblk_copy_max_bandwidth_hz     ();
    caught_call[7]  = this->_iqblk_copy_min_bandwidth_hz     ();
    caught_call[8]  = this->_iqblk_copy_record_length        ();
    caught_call[9]  = this->_iqblk_copy_max_record_length    ();
    caught_call[10] = this->_iqblk_copy_acq_status_messages  ();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_iqblk_copy_getting_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.getting_select = this->_vars.iqblk.getting_select;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_iqblk_copy_actual_buffer_samples()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.actual_buffer_samples = this->_vars.iqblk.actual_buffer_samples;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


/*
    < 4 > private
*/
CODEZ rsa306b_class::_iqblk_copy_cplx32_v()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.cplx32_v.resize(
        this->_vars.iqblk.cplx32_v.size());
    for (std::size_t kk = 0; kk < this->_vars.iqblk.cplx32_v.size(); kk++)
    {
        this->vars.iqblk.cplx32_v[kk].i = this->_vars.iqblk.cplx32_v[kk].i;
        this->vars.iqblk.cplx32_v[kk].q = this->_vars.iqblk.cplx32_v[kk].q;
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}



////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_iqblk_copy_acq_info_type()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.acq_info_type.acqStatus          = this->_vars.iqblk.acq_info_type.acqStatus;
    this->vars.iqblk.acq_info_type.sample0Timestamp   = this->_vars.iqblk.acq_info_type.sample0Timestamp;
    this->vars.iqblk.acq_info_type.triggerSampleIndex = this->_vars.iqblk.acq_info_type.triggerSampleIndex;
    this->vars.iqblk.acq_info_type.triggerTimestamp   = this->_vars.iqblk.acq_info_type.triggerTimestamp;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}



////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_iqblk_copy_sample_rate()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.sample_rate = this->_vars.iqblk.sample_rate;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_iqblk_copy_bandwidth_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.bandwidth_hz = this->_vars.iqblk.bandwidth_hz;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 8 > private
*/
CODEZ rsa306b_class::_iqblk_copy_max_bandwidth_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.max_bandwidth_hz = this->_vars.iqblk.max_bandwidth_hz;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 9 > private
*/
CODEZ rsa306b_class::_iqblk_copy_min_bandwidth_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.min_bandwidth_hz = this->_vars.iqblk.min_bandwidth_hz;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 10 > private
*/
CODEZ rsa306b_class::_iqblk_copy_record_length()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.record_length = this->_vars.iqblk.record_length;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 11 > private
*/
CODEZ rsa306b_class::_iqblk_copy_max_record_length()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.iqblk.max_record_length = this->_vars.iqblk.max_record_length;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 12 > private
*/
CODEZ rsa306b_class::_iqblk_copy_acq_status_messages()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    for (int ii = 0; ii < IQBLK_BITCHECKS; ii++)
    {
        (void)strcpy(this->vars.iqblk.acq_status_messages[ii], this->_vars.iqblk.acq_status_messages[ii]);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_iqblk_copy.cpp
