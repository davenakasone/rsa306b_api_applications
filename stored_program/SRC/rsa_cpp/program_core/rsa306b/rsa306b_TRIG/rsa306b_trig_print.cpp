/*
    API group "TRIG"

    public :
        < 1 >  print_trig()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::trig_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    printf("\n'TRIG' group >>>\n");
    printf("\tIF power trigger level    :  %lf\n", this->_vars.trig.if_power_level);
    printf("\ttrigger position percent  :  %lf\n", this->_vars.trig.position_percent);
    printf("\tmode                      :  ");
    switch (this->_vars.trig.mode_select)
    {
        case (RSA_API::freeRun)   : printf("free running\n"); break;
        case (RSA_API::triggered) : printf("triggered\n");    break;
        default                   : printf("unknown\n");      break;
    }
    printf("\tsource                    :  ");
    switch (this->_vars.trig.source_select)
    {
        case (RSA_API::TriggerSourceExternal)     : printf("externally triggered\n");          break;
        case (RSA_API::TriggerSourceIFPowerLevel) : printf("IF power level causes trigger\n"); break;
        case (RSA_API::TriggerSourceTime)         : printf("time-based trigger\n");            break;
        default                                   : printf("unknown\n");                       break;
    }
    printf("\ttransition                :  ");
    switch (this->_vars.trig.transition_select)
    {
        case(RSA_API::TriggerTransitionLH)     : printf("low to high\n");         break;
        case(RSA_API::TriggerTransitionHL)     : printf("high to low\n");         break;
        case(RSA_API::TriggerTransitionEither) : printf("either level change\n"); break;
        default                                : printf("unknown\n");             break;
    }

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_trig_print.cpp
