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

    (void)printf("\n'TRIG' group >>>\n");
    (void)printf("\tIF power trigger level    :  %lf\n", this->_vars.trig.if_power_level);
    (void)printf("\ttrigger position percent  :  %lf\n", this->_vars.trig.position_percent);
    (void)printf("\tmode                      :  ");
    switch (this->_vars.trig.mode_select)
    {
        case (RSA_API::freeRun)   : (void)printf("free running\n"); break;
        case (RSA_API::triggered) : (void)printf("triggered\n");    break;
        default                   : (void)printf("unknown\n");      break;
    }
    (void)printf("\tsource                    :  ");
    switch (this->_vars.trig.source_select)
    {
        case (RSA_API::TriggerSourceExternal)     : (void)printf("externally triggered\n");          break;
        case (RSA_API::TriggerSourceIFPowerLevel) : (void)printf("IF power level causes trigger\n"); break;
        case (RSA_API::TriggerSourceTime)         : (void)printf("time-based trigger\n");            break;
        default                                   : (void)printf("unknown\n");                       break;
    }
    (void)printf("\ttransition                :  ");
    switch (this->_vars.trig.transition_select)
    {
        case(RSA_API::TriggerTransitionLH)     : (void)printf("low to high\n");         break;
        case(RSA_API::TriggerTransitionHL)     : (void)printf("high to low\n");         break;
        case(RSA_API::TriggerTransitionEither) : (void)printf("either level change\n"); break;
        default                                : (void)printf("unknown\n");             break;
    }
    (void)printf("\tstart_time_seconds        :  %ld\n", this->_vars.trig.start_time_seconds);
    (void)printf("\tstart_time_nano_seconds   :  %lu\n", this->_vars.trig.start_time_nano_seconds);
    (void)printf("\trepeat_time_nano_seconds  :  %lu\n", this->_vars.trig.repeat_time_nano_seconds);

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_trig_print.cpp
