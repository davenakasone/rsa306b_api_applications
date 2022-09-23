/*
    API group "TRIG"

    public :
        #  none
    
    private :
        < 1 >  _trig_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_trig_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    this->_vars.trig.if_power_level    = this->_vars.trig._IF_POWER_LEVEL;
    this->_vars.trig.position_percent  = this->_vars.trig._POSITION_PERCENT;

    this->_vars.trig.mode_select       = this->_vars.trig._MODE_SELECT;
    this->_vars.trig.source_select     = this->_vars.trig._SOURCE_SELECT;
    this->_vars.trig.transition_select = this->_vars.trig._TRANSITION_SELECT;

    this->_vars.trig.start_time_seconds       = this->_vars.trig._START_TIME_SECONDS;
    this->_vars.trig.start_time_nano_seconds  = this->_vars.trig._START_TIME_NANO_SECONDS;
    this->_vars.trig.repeat_time_nano_seconds = this->_vars.trig._REPEAT_TIME_NANO_SECONDS;

    return this->_trig_copy_vars();
}


////////~~~~~~~~END>  rsa306b_trig_init.cpp
