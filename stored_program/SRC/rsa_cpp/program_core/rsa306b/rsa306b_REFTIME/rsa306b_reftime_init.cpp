/*
    API group "REFTIME"

    public :
        #  none
    
    private :
        < 1 >  _init_reftime()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_reftime_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.reftime.current.nanos     = this->_vars.reftime._CURRENT_nanos;
    this->_vars.reftime.current.seconds   = this->_vars.reftime._CURRENT_seconds;
    this->_vars.reftime.current.timestamp = this->_vars.reftime._CURRENT_timestamp;

    this->_vars.reftime.start.nanos     = this->_vars.reftime._START_nanos;
    this->_vars.reftime.start.seconds   = this->_vars.reftime._START_seconds;
    this->_vars.reftime.start.timestamp = this->_vars.reftime._START_timestamp;

    this->_vars.reftime.helper.nanos     = this->_vars.reftime._HELPER_nanos;
    this->_vars.reftime.helper.seconds   = this->_vars.reftime._HELPER_seconds;
    this->_vars.reftime.helper.timestamp = this->_vars.reftime._HELPER_timestamp;
    
    (void)memset(this->_vars.reftime.dts , '\0'      , sizeof(this->_vars.reftime.dts));
    (void)strcpy(this->_vars.reftime.dts, this->_vars.reftime._DTS);

    this->_vars.reftime.running_duration_seconds = this->_vars.reftime._RUNNING_DURATION_SECONDS;
    this->_vars.reftime.source_select            = this->_vars.reftime._SOURCE_SELECT;
    this->_vars.reftime.timestamp_rate           = this->_vars.reftime._TIMESTAMP_RATE;

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_reftime_init.cpp
