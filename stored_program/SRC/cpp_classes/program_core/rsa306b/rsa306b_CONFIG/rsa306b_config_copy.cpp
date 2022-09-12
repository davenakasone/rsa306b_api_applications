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
void rsa306b_class::_config_copy_vars()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_config_copy_reference_level_dbm();
    this->_config_copy_center_frequency_hz();
    this->_config_copy_min_center_frequency_hz();
    this->_config_copy_max_center_frequency_hz();
    this->_config_copy_external_reference_frequency_hz();
    this->_config_copy_frequency_reference_source_select();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_config_copy_reference_level_dbm()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.reference_level_dbm = this->_vars.config.reference_level_dbm;
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_config_copy_center_frequency_hz()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.center_frequency_hz= this->_vars.config.center_frequency_hz;
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_config_copy_min_center_frequency_hz()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.min_center_frequency_hz= this->_vars.config.min_center_frequency_hz;
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_config_copy_max_center_frequency_hz()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.max_center_frequency_hz= this->_vars.config.max_center_frequency_hz;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_config_copy_external_reference_frequency_hz()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.external_reference_frequency_hz = this->_vars.config.external_reference_frequency_hz;
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_config_copy_frequency_reference_source_select()
{
#ifdef DEBUG_COPYS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.config.frequency_reference_source_select = this->_vars.config.frequency_reference_source_select;
}


////////~~~~~~~~END>  rsa306b_config_copy.cpp
