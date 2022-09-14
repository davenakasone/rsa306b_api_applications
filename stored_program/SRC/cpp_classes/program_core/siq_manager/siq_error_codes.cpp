/*
    initializer of the 'siq_handler_class'
    copies private struct to the public struct

    public:
        < 1 >  execution_success()
        
    private:
        < 1 >  _set_error_code()
        < 2 >  _check_error_code()
    

*/

#include "siq_manager_class.h"


/*
    < 1 > public
    returns "true" if there are no errors detected
    returns "false" if an error was detected
    useful to call after a long parsing operation
*/
bool siq_manager_class::execution_success()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    if (this->_ec != no_error)
    {
        //this->_check_error_code();
        return false;
    }
    return true;
}


////~~~~


/*
    < 1 > private
    updates error-code tracker to most recent status
*/
void siq_manager_class::_set_error_code
(
    error_code_select code
)
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_ec = code;
    #ifdef DEBUG_MIN
        if (this->_ec != no_error)
        {
            this->_check_error_code();
        }
    #endif
}


////~~~~


/*
    < 2 > private
    prints fault, if detected
    must have "DEBUG_MIN" activated
*/
void siq_manager_class::_check_error_code()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_ec != no_error)
    {
        snprintf(X_dstr, sizeof(X_dstr), "siq_manager ERROR %2d:  %s",
            static_cast<int>(this->_ec),
            ERROR_CODES[this->_ec]);
        debug_record(true);
    }
}


////////~~~~~~~~END>  siq_error_codes.cpp
