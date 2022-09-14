/*
    common_utility, class 

    public :
        < 1 >  get_status_code_string()
        < 2 >  get_status_code_number()
        
    private :
        < 1 >  _report_status_code()
*/

#include "common_utility.h"


/*
    < 1 > public
    designed for user to call immidiatley after making a function call
    returns string with message describing current status code
*/
const char* common_utility::get_status_code_string()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return CODEZ_MESSAGES[static_cast<int>(this->_status_code)];
}


////~~~~


/*
    < 2 > public
    designed for user to call immidiatley after making a function call
    returns current value of status code, casted to "int"
*/
int common_utility::get_status_code_number()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return static_cast<int>(this->_status_code);

}


////~~~~


/*
    < 1 > private
    for private management of the status code
    has provisions for debugging
*/
void common_utility::_report_status_code()
{
#ifdef DEBUG_CALL_CHECKS
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_status_code == CODEZ::_0_no_errors)
    {
        return;
    }

    #ifdef DEBUG_MIN
        snprintf(X_ddts, sizeof(X_ddts), "%4d %s",
            static_cast<int>(this->_status_code),
            CODEZ_MESSAGES[static_cast<int>(this->_status_code)]);
        snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(true);
    #endif
}


////////~~~~~~~~END>  cu_codez.cpp
