/*
    API group "ALIGN", copiers

    public :
        #  none
    
    private :
        < 1 >  _align_copy_vars()
        < 2 >  _align_copy_is_needed()
        < 3 >  _align_copy_is_warmed()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
CODEZ rsa306b_class::_align_copy_vars()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    constexpr int callz = 2;
    CODEZ caught_call[callz];

    caught_call[0] = this->_align_copy_is_needed();
    caught_call[1] = this->_align_copy_is_warmed();

    return this->cutil.codez_checker(caught_call, callz);
}


////~~~~


/*
    < 2 > private
*/
CODEZ rsa306b_class::_align_copy_is_needed()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.align.is_needed = this->_vars.align.is_needed;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
*/
CODEZ rsa306b_class::_align_copy_is_warmed()
{
#ifdef DEBUG_COPYS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_COPYS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->vars.align.is_warmed = this->_vars.align.is_warmed;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_align_copy.cpp
