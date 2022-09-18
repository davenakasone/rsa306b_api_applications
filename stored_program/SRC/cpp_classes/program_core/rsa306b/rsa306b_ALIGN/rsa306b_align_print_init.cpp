/*
    API group "ALIGN"

    public :
        < 1 >   print_align()
    
    private :
        < 1 >  _align_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    prints the "ALIGN" variables to stdout, 
        using the private struct
*/
CODEZ rsa306b_class::align_print()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)printf("\n'ALIGN' group >>>\n");
    (void)printf("\talignment is needed :  %d\n", this->_vars.align.is_needed);
    (void)printf("\tdevice is warmed-up :  %d\n", this->_vars.align.is_warmed);
    
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 1 > private
    initializes variables in the "ALIGN" group
*/
CODEZ rsa306b_class::_align_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_vars.align.is_needed = this->_vars.align._IS_NEEDED;
    this->_vars.align.is_warmed = this->_vars.align._IS_WARMED;

    return this->_align_copy_vars(); 
}


////////~~~~~~~~END>  rsa306b_align_print_init.cpp
