/*
    API group "xxx"

    public :
        < 1 >  iqblk_set_vars()
    
    private :
        < 1 >  _iqblk_set_vars()
        < 2 >  _iqblk_set_getter()
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->_iqblk_set_vars();
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    this->device_stop();
    
    this->_iqblk_set_getter();
    this->_iqblk_set_bandwidth_hz();
    this->_iqblk_set_record_length();
}


////~~~~


/*
    < 2 > private
    does not require API
*/
CODEZ rsa306b_class::_iqblk_set_getter()
{
#ifdef DEBUG_SETS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->vars.iqblk.getter == this->_vars.iqblk.getter)
    {
        #ifdef DEBUG_MAX
            printf("\n\tgetter already set\n");
        #endif
        return;
    }

    if (this->vars.iqblk.getter != this->constants.IQBLK_GET_IQ_DATA               &&
        this->vars.iqblk.getter != this->constants.IQBLK_GET_IQ_DATA_CPLX          &&
        this->vars.iqblk.getter != this->constants.IQBLK_GET_IQ_DATA_DEINETERLEAVED )
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "invalid getting, see const class");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        this->_vars.iqblk.getter = this->constants.IQBLK_GETTER_DEFAULT;
        this->_iqblk_copy_getter();
        return;
    }
    this->_vars.iqblk.getter = this->vars.iqblk.getter;
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->vars.iqblk.bandwidth_hz == this->_vars.iqblk.bandwidth_hz)
    {
        return;
    }

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
    this->_vars.iqblk.bandwidth_hz = this->vars.iqblk.bandwidth_hz;
    this->_vars.gp.api_status =
        RSA_API::IQBLK_SetIQBandwidth(
            this->_vars.iqblk.bandwidth_hz);
    this->_gp_confirm_api_status();
    this->_iqblk_get_bandwidth_hz();
    this->_iqblk_get_min_bandwidth_hz();
    this->_iqblk_get_max_bandwidth_hz();
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

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->vars.iqblk.record_length == this->_vars.iqblk.record_length)
    {
        #ifdef DEBUG_MAX
            (void)printf("\n\trecord length already set\n");
        #endif
        return;
    }

    this->_iqblk_get_max_record_length();
    if (this->vars.iqblk.record_length < this->constants.IQBLK_MIN_PAIRS ||
        this->vars.iqblk.record_length > this->_vars.iqblk.max_record_length    )
    {
        this->vars.iqblk.record_length = this->_vars.iqblk.max_record_length / 2;
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid IQ record length, using:  %d samples/pairs",
                this->vars.iqblk.record_length);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }

    this->_vars.iqblk.record_length = this->vars.iqblk.record_length;
    this->_vars.gp.api_status =
        RSA_API::IQBLK_SetIQRecordLength(
            this->_vars.iqblk.record_length);
    this->_gp_confirm_api_status();
    this->_iqblk_get_record_length();
    this->_iqblk_get_max_record_length();

    this->_vars.iqblk.cplx32_v.resize(
        static_cast<std::size_t>(this->_vars.iqblk.record_length));
    for (size_t ii = 0; ii < this->_vars.iqblk.cplx32_v.size(); ii++)
    {
        this->_vars.iqblk.cplx32_v[ii].i = INIT_FLOAT;
        this->_vars.iqblk.cplx32_v[ii].q = INIT_FLOAT;
    }
    this->_iqblk_copy_cplx32_v();
}


////////~~~~~~~~END>  rsa306b_iqblk_set.cpp
