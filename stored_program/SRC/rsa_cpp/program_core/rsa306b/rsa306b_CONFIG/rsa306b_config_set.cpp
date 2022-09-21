/*
    API group "CONFIG", setters

    public :
        < 1 >  config_set_vars()
    
    private :
        < 1 >  _config_set_vars()
        < 2 >  _config_set_reference_level_dbm()
        < 3 >  _config_set_center_frequency_hz()
        < 4 >  _config_set_external_reference_frequency_source_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::config_set_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    return this->_config_set_vars();
}


////~~~~


/*
    < 1 > private
*/
CODEZ rsa306b_class::_config_set_vars()
{
#ifdef DEBUG_SETS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_SETS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 3;
    CODEZ caught_call[callz];

    caught_call[0] = this->_config_set_reference_level_dbm();
    caught_call[1] = this->_config_set_center_frequency_hz();
    caught_call[2] = this->_config_set_external_reference_frequency_source_select();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_config_set_reference_level_dbm()
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
    if (this->vars.config.reference_level_dbm < this->_vars.config.REFERENCE_LEVEL_MIN_DBM ||
        this->vars.config.reference_level_dbm > this->_vars.config.REFERENCE_LEVEL_MAX_DBM  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "reference level { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.config.reference_level_dbm,
                this->_vars.config.REFERENCE_LEVEL_MIN_DBM,
                this->_vars.config.REFERENCE_LEVEL_MAX_DBM);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    (void)this->device_stop();
    RSA_API::ReturnStatus temp =
        RSA_API::CONFIG_SetReferenceLevel(this->vars.config.reference_level_dbm);
    (void)this->_config_get_reference_level_dbm();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_config_set_center_frequency_hz()
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

    (void)this->_config_get_min_center_frequency_hz();
    (void)this->_config_get_max_center_frequency_hz();
    if (this->vars.config.center_frequency_hz < this->_vars.config.min_center_frequency_hz ||
        this->vars.config.center_frequency_hz > this->_vars.config.max_center_frequency_hz  )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "center frequency { %lf }  ,  out of range [ %lf , %lf ]",
                this->vars.config.center_frequency_hz,
                this->_vars.config.min_center_frequency_hz,
                this->_vars.config.max_center_frequency_hz);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    
    (void)this->device_stop();
    RSA_API::ReturnStatus temp =
        RSA_API::CONFIG_SetCenterFreq(
            this->vars.config.center_frequency_hz);
    (void)this->_config_get_center_frequency_hz();
    return this->set_api_status(temp);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_config_set_external_reference_frequency_source_select()
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

    if (this->vars.config.frequency_reference_source_select != RSA_API::FRS_EXTREF &&
        this->vars.config.frequency_reference_source_select != RSA_API::FRS_INTERNAL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "invalid frequency reference source:  %d",
                static_cast<int>(this->vars.config.frequency_reference_source_select));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    
    (void)this->device_stop();
    RSA_API::ReturnStatus temp =
        RSA_API::CONFIG_SetFrequencyReferenceSource(
            this->vars.config.frequency_reference_source_select);
    (void)this->_config_get_frequency_reference_source_select();
    return this->set_api_status(temp);
}


////////~~~~~~~~END>  rsa306b_config_set.cpp
