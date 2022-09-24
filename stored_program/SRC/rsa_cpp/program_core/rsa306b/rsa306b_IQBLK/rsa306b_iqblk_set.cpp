/*
    API group "xxx"

    public :
        < 1 >  iqblk_set_vars()
    
    private :
        < 1 >  _iqblk_set_vars()
        < 2 >  _iqblk_set_getting_select()
        < 3 >  _iqblk_set_bandwidth_hz()
        < 4 >  _iqblk_set_record_length()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::iqblk_set_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_iqblk_set_vars();
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_iqblk_set_vars()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    constexpr int callz = 3;
    CODEZ caught_call[callz];

    caught_call[0] = this->_iqblk_set_getting_select();
    caught_call[1] = this->_iqblk_set_bandwidth_hz();
    caught_call[2] = this->_iqblk_set_record_length();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
    does not require API
*/
CODEZ rsa306b_class::_iqblk_set_getting_select()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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
    if (this->vars.iqblk.getting_select == this->_vars.iqblk.getting_select)
    {
        return this->cutil.report_status_code(CODEZ::_0_no_errors);    // already set
    }

    if (this->vars.iqblk.getting_select  != iqblkGetData::complex       &&
        this->vars.iqblk.getting_select  != iqblkGetData::deinterleaved &&
        this->vars.iqblk.getting_select  != iqblkGetData::interleaved    )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid getting, see iqblkGetData enum 'constant_expresions.h'");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        this->_vars.iqblk.getting_select  = this->_vars.iqblk._GETTING_SELECT;
        this->_iqblk_copy_getting_select();
    }
    this->_vars.iqblk.getting_select = this->vars.iqblk.getting_select;

    return this->cutil.report_status_code(CODEZ::_0_no_errors);    // always successful
}


////~~~~


/*
    < 3 > private
    should be set first
*/
CODEZ rsa306b_class::_iqblk_set_bandwidth_hz()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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

    if (this->vars.iqblk.bandwidth_hz < this->_vars.iqblk.min_bandwidth_hz ||
        this->vars.iqblk.bandwidth_hz > this->_vars.iqblk.max_bandwidth_hz  )
    {
        this->vars.iqblk.bandwidth_hz = this->_vars.iqblk.max_bandwidth_hz / 2;
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid IQ bandwidth, using:  %lf Hz",
                this->vars.iqblk.bandwidth_hz);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }
    (void)this->device_stop();

    this->_vars.iqblk.bandwidth_hz = this->vars.iqblk.bandwidth_hz;
    RSA_API::ReturnStatus temp =
        RSA_API::IQBLK_SetIQBandwidth
        (
            this->_vars.iqblk.bandwidth_hz
        );
    (void)this->_iqblk_get_bandwidth_hz();
    (void)this->_iqblk_get_min_bandwidth_hz();
    (void)this->_iqblk_get_max_bandwidth_hz();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 4 > private
    should be called after setting bandwidth
*/
CODEZ rsa306b_class::_iqblk_set_record_length()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
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

    (void)this->_iqblk_get_max_record_length();
    if (this->vars.iqblk.record_length < this->_vars.iqblk.RECORD_LENGTH_MIN ||
        this->vars.iqblk.record_length > this->_vars.iqblk.max_record_length  )
    {
        this->vars.iqblk.record_length = this->_vars.iqblk.max_record_length / 2;
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid IQ record length, using:  %d samples/pairs",
                this->vars.iqblk.record_length);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }
    (void)this->device_stop();

    this->_vars.iqblk.record_length = this->vars.iqblk.record_length;
    RSA_API::ReturnStatus temp = 
        RSA_API::IQBLK_SetIQRecordLength
        (
            this->_vars.iqblk.record_length
        );
    (void)this->_iqblk_get_record_length();
    (void)this->_iqblk_get_max_record_length();
    return this->set_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_iqblk_set.cpp
