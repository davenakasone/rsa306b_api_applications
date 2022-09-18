/*
    common_utility, class 

    public :
        < 1 >  get_status_code_string()
        < 2 >  get_status_code_number()
        < 3 >  get_status_code()
        < 4 >  report_status_code()
        < 5 >  codez_checker()
        < 6 >  codez_messages()

    private :
        #  none
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
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
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
     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return static_cast<int>(this->_status_code);

}


////~~~~


/*
    < 3 > public
    getter
*/
CODEZ common_utility::get_status_code()
{
#ifdef DEBUG_CALL_CHECKS
     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->_status_code;
}


////~~~~


/*
    < 4 > public
    for private management of the status code
    has provisions for debugging
    used to update the status code and interface with the debugger

    first sets, then gets
*/
CODEZ common_utility::report_status_code
(
    CODEZ current_code
)
{
#ifdef DEBUG_CALL_CHECKS
     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_status_code = current_code;

    if (this->_status_code != CODEZ::_0_no_errors)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "%4d %s",
                this->get_status_code_number(),
                this->get_status_code_string());
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }

    return this->get_status_code();
}


////~~~~


/*
    < 5 > public
    checks a batch
    designed to be used with a top-level member function that received several status codes
    returns "_0_no_error" if an error-free call sequence was executed
    else, returns first error found
*/
CODEZ common_utility::codez_checker
(
    const CODEZ* codez_list, 
    const int codez_count
)
{
#ifdef DEBUG_CALL_CHECKS
     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (codez_count < 1       || 
        codez_count > 999     ||
        codez_list == NULL)
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    for (int ii = 0; ii < codez_count; ii++)
    {
        if (codez_list[ii] != CODEZ::_0_no_errors)
        {
            return report_status_code(codez_list[ii]);    // report first bad code, and exit
        }
    }
    return report_status_code(CODEZ::_0_no_errors);    // will be "_0_no_error" if error free if it gets here
}


////~~~~


/*
    < 6 > public
    for looking up a status code and getting a string
*/
const char* common_utility::codez_messages
(
    CODEZ lookup
)
{
#ifdef DEBUG_CALL_CHECKS
     (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    int code_to_find = static_cast<int>(lookup);
    if (code_to_find < 0 || code_to_find > ROWS_CODEZ)
    {
        (void)this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
        return NULL;
    }
    (void)memset(this->_worker, '\0', sizeof(this->_worker));
    (void)snprintf(this->_worker, sizeof(this->_worker), "%4d %s",
        code_to_find,
        CODEZ_MESSAGES[code_to_find]);
    return this->_worker;
}


////////~~~~~~~~END>  cu_codez.cpp
