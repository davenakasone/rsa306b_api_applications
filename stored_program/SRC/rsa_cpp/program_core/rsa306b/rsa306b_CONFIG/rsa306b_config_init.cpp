/*
    API group "CONFIG"

    public :
        #  none
    
    private :
        < 1 >  _config_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
    initialize "CONFIG" group variables to known values
*/
CODEZ rsa306b_class::_config_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.config.reference_level_dbm               = this->_vars.config._REFERENCE_LEVEL_DBM;
    this->_vars.config.center_frequency_hz               = this->_vars.config._CENTER_FREQUENCY_HZ;
    this->_vars.config.min_center_frequency_hz           = this->_vars.config._MIN_CENTER_FREQUENCY_HZ;
    this->_vars.config.max_center_frequency_hz           = this->_vars.config._MAX_CENTER_FREQUENCY_HZ;
    this->_vars.config.external_reference_frequency_hz   = this->_vars.config._EXTERNAL_REFERENCE_FREQUENCY_HZ;
    this->_vars.config.frequency_reference_source_select = this->_vars.config._FREQUENCY_REFERENCE_SOURCE_SELECT;

    return this->_config_copy_vars();
}


////////~~~~~~~~END>  rsa306b_config_init.cpp
       