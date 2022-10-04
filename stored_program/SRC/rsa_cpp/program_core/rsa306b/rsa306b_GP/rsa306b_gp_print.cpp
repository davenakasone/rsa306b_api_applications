/*
    printing functions for the "general purpose" group

        public :
            < 1 >  print_vars()
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
CODEZ rsa306b_class::print_vars()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int calls = 10;
    CODEZ caught_call[calls];

    caught_call[0]  = this->align_print    ();
    caught_call[1]  = this->audio_print    ();
    caught_call[2]  = this->config_print   ();
    caught_call[3]  = this->device_print   ();
    caught_call[4]  = this->ifstream_print ();
    caught_call[5]  = this->iqblk_print    ();
    caught_call[6]  = this->iqstream_print ();
    caught_call[7]  = this->reftime_print  ();
    caught_call[8]  = this->spectrum_print ();
    caught_call[9]  = this->trig_print     ();

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

    (void)printf("\nhardware constants >>>\n");
    (void)printf("\tTRACES_306B               :  %lu\n"  , TRACES_306B);
    (void)printf("\tBITCHECK_SUCCESS_MESSAGE  :  %s\n"   , BITCHECK_SUCCESS_MESSAGE);
    (void)printf("\tBITCHECK_SUCCESS          :  0x%X\n" , BITCHECK_SUCCESS);
    (void)printf("\tSAMPLES_PER_FRAME         :  %lu\n"  , SAMPLES_PER_FRAME);
    
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_print_constants.cpp
