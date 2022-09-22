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

    this->_vars.trig.if_power_level    = INIT_DOUBLE;
    this->_vars.trig.position_percent  = INIT_DOUBLE;
    this->_vars.trig.mode_select       = RSA_API::triggered;
    this->_vars.trig.source_select     = RSA_API::TriggerSourceTime;
    this->_vars.trig.transition_select = RSA_API::TriggerTransitionEither;

    return this->_trig_copy_vars();
}


////////~~~~~~~~END>  rsa306b_trig_init.cpp
