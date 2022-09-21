// /*
//     API group "TRIG"

//     public :
//         < 1 >  print_trig()
    
//     private :
//         < 1 >  _trig_init()
// */

// #include "../rsa306b_class.h"


// /*
//     < 1 > public
// */
// CODEZ rsa306b_class::print_trig()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif

//     printf("\n'TRIG' group >>>\n");
//     printf("\tIF power trigger level    :  %lf\n", this->_vars.trig.if_power_level);
//     printf("\ttrigger position percent  :  %lf\n", this->_vars.trig.position_percent);
//     printf("\tmode                      :  ");
//     switch (this->_vars.trig.mode_select)
//     {
//         case (RSA_API::freeRun)   : printf("free running\n"); break;
//         case (RSA_API::triggered) : printf("triggered\n");    break;
//         default                   : printf("unknown\n");      break;
//     }
//     printf("\tsource                    :  ");
//     switch (this->_vars.trig.source_select)
//     {
//         case (RSA_API::TriggerSourceExternal)     : printf("externally triggered\n");          break;
//         case (RSA_API::TriggerSourceIFPowerLevel) : printf("IF power level causes trigger\n"); break;
//         case (RSA_API::TriggerSourceTime)         : printf("time-based trigger\n");            break;
//         default                                   : printf("unknown\n");                       break;
//     }
//     printf("\ttransition                :  ");
//     switch (this->_vars.trig.transition_select)
//     {
//         case(RSA_API::TriggerTransitionLH)     : printf("low to high\n");         break;
//         case(RSA_API::TriggerTransitionHL)     : printf("high to low\n");         break;
//         case(RSA_API::TriggerTransitionEither) : printf("either level change\n"); break;
//         default                                : printf("unknown\n");             break;
//     }
// }


// ////~~~~


// /*
//     < 1 > private
// */
// CODEZ rsa306b_class::_trig_init()
// {
// #ifdef DEBUG_CLI
//     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
//     debug_record(false);
// #endif  

//     this->_vars.trig.if_power_level    = INIT_DOUBLE;
//     this->_vars.trig.position_percent  = INIT_DOUBLE;
//     this->_vars.trig.mode_select       = RSA_API::triggered;
//     this->_vars.trig.source_select     = RSA_API::TriggerSourceTime;
//     this->_vars.trig.transition_select = RSA_API::TriggerTransitionEither;

//     this->_trig_copy_vars();
// }


// ////////~~~~~~~~END>  rsa306b_trig_print_init.cpp
