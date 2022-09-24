/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >  _iqstream_get_vars()
        < 2 >  _iqstream_get_max_acq_bandwidth()
        < 3 >  _iqstream_get_min_acq_bandwidth()
        < 4 >  _iqstream_get_acq_parameters()
        < 5 >  _iqstream_get_disk_fileinfo()
        < 6 >  _iqstream_get_enabled()
        < 7 >  _iqstream_get_iq_data_buffer_size()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqstream_get_vars()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    
    this->_iqstream_get_max_acq_bandwidth();
    this->_iqstream_get_min_acq_bandwidth();
    this->_iqstream_get_acq_parameters();
    this->_iqstream_get_disk_fileinfo();
    this->_iqstream_get_enabled();
    this->_iqstream_get_iq_data_buffer_size();
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_iqstream_get_max_acq_bandwidth()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif   
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    this->_api_status = 
        RSA_API::IQSTREAM_GetMaxAcqBandwidth
        (
            &this->_vars.iqstream.bandwidth_max
        );
    this->_report_api_status();
    this->_iqstream_copy_bandwidth_max();
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_iqstream_get_min_acq_bandwidth()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    this->_api_status = 
        RSA_API::IQSTREAM_GetMinAcqBandwidth
        (
            &this->_vars.iqstream.bandwidth_min
        );
    this->_report_api_status();
    this->_iqstream_copy_bandwidth_min();
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_iqstream_get_acq_parameters()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    this->_api_status = 
        RSA_API::IQSTREAM_GetAcqParameters
        (
            &this->_vars.iqstream.bandwidth,
            &this->_vars.iqstream.sample_rate
        );
    this->_report_api_status();
    this->_iqstream_copy_bandwidth();
    this->_iqstream_copy_sample_rate();
}


////~~~~


/*
    < 5 > private
    double get, no copy, must handle wchar_t
*/
CODEZ rsa306b_class::_iqstream_get_disk_fileinfo()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    this->_api_status = 
        RSA_API::IQSTREAM_GetDiskFileInfo
        (
            &this->_vars.iqstream.fileinfo_type
        );
    this->_report_api_status();
    this->_iqstream_copy_fileinfo_type();
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_iqstream_get_enabled()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    this->_api_status = 
        RSA_API::IQSTREAM_GetEnable
        (
            &this->_vars.iqstream.is_enabled
        );
    this->_report_api_status();
    this->_iqstream_copy_is_enabled();
}


////~~~~


/*
    < 7 > private
    use the preset or RSA_API::IQSTREAM_SetIQDataBufferSize() before
    the number is samples to allocate
    bytes to allocates depend on data type used
*/
CODEZ rsa306b_class::_iqstream_get_iq_data_buffer_size()
{
#ifdef DEBUG_GETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_GETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
#endif
    this->_api_status =
        RSA_API::IQSTREAM_GetIQDataBufferSize
        (
            &this->_vars.iqstream.pairs_max
        );
    this->_report_api_status();
    this->_iqstream_copy_pairs_max();
}


////////~~~~~~~~END>  rsa306b_iqstream_get.cpp
 