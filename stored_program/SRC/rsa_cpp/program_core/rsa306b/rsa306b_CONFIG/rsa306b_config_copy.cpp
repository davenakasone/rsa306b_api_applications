/*
    API group "CONFIG"

    public :
        #  none
    
    private :
        < 1 >  _config_copy_vars()
        < 2 >  _config_copy_reference_level_dbm()
        < 3 >  _config_copy_center_frequency_hz()
        < 4 >  _config_copy_min_center_frequency_hz()
        < 5 >  _config_copy_max_center_frequency_hz()
        < 6 >  _config_copy_external_reference_frequency_hz()
        < 7 >  _config_copy_frequency_reference_source_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::_config_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef DEBUG_FUNC
    printf("\n%s()\n", __func__);
#endif

    constexpr int callz = 6;
    CODEZ caught_call[callz];

    caught_call[0] = this->_config_copy_reference_level_dbm();
    caught_call[1] = this->_config_copy_center_frequency_hz();
    caught_call[2] = this->_config_copy_min_center_frequency_hz();
    caught_call[3] = this->_config_copy_max_center_frequency_hz();
    caught_call[4] = this->_config_copy_external_reference_frequency_hz();
    caught_call[5] = this->_config_copy_frequency_reference_source_select();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_config_copy_reference_level_dbm()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.reference_level_dbm = this->_vars.config.reference_level_dbm;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_config_copy_center_frequency_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.center_frequency_hz = this->_vars.config.center_frequency_hz;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > private
*/
CODEZ rsa306b_class::_config_copy_min_center_frequency_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.min_center_frequency_hz = this->_vars.config.min_center_frequency_hz;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > private
*/
CODEZ rsa306b_class::_config_copy_max_center_frequency_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.max_center_frequency_hz = this->_vars.config.max_center_frequency_hz;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 6 > private
*/
CODEZ rsa306b_class::_config_copy_external_reference_frequency_hz()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.external_reference_frequency_hz = this->_vars.config.external_reference_frequency_hz;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 7 > private
*/
CODEZ rsa306b_class::_config_copy_frequency_reference_source_select()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.frequency_reference_source_select = this->_vars.config.frequency_reference_source_select;
    return cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_config_copy.cpp
