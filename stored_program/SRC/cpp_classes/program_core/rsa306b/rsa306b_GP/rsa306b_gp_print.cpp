/*
    printing functions for the "general purpose" group

        public :
            < 1 >  print_everything()
            < 2 >  print_constants()
        
        private :
            #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    prints class variables and constatns to stdout
    variables are displayed in current state
    uses the private struct
*/
CODEZ rsa306b_class::print_everything()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int calls = 11;
    CODEZ caught_call[calls];

    caught_call[0]  = this->print_constants();
    caught_call[1]  = this->align_print    ();
    caught_call[2]  = this->audio_print    ();
    caught_call[3]  = this->config_print   ();
    caught_call[4]  = this->device_print   ();
    caught_call[5]  = this->ifstream_print ();
    caught_call[6]  = this->iqblk_print    ();
    caught_call[7]  = this->iqstream_print ();
    caught_call[8]  = this->reftime_print  ();
    caught_call[9]  = this->spectrum_print ();
    caught_call[10] = this->trig_print     ();

    // INSERT

    return this->cutil.codez_checker(caught_call, calls);
} 


////~~~~


/*
    < 2 > public
    prints class constants to stdout
*/
CODEZ rsa306b_class::print_constants()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'constants' group >>>\n");
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_print_constants.cpp
