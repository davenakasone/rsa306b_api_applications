/*
    class common_utility

    public :
        < 1 >  wchar_2_char()
    
    private :
        < 1 >  _wchar_2_char_std()
        < 2 >  _wchar_2_char_unq()
        
*/


#include "common_utility.h"


/*
    < 1 > private
    directs user's request for conversion after verification
    wchar_t* types have been important to deal with for the API
    you have to handle them correctly or bad things will happen
*/
CODEZ common_utility::wchar_2_char
(
    char* destination,
    const wchar_t* source,
    bool use_std
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (source == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "the wchar_t* is empty");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }
    if (wcslen(source) < static_cast<size_t>(1))
    {
        return this->exe_strcpy(destination, INIT_CHARP);    // nothing to convert
    }
    if (destination == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "the char* is empty");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }
    // end guards


    if (use_std == true)
    {
        return this->_wchar_2_char_std(destination, source);
    }
    return this->_wchar_2_char_unq(destination, source);
}


////~~~~


/*
    < 1 > private
    can be used for most cases
    std::string and std::wstring are very robust
*/
CODEZ common_utility::_wchar_2_char_std
(
    char* destination,
    const wchar_t* source
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    std::wstring std_source(source);                                       // place wchar_t* into std::wstring
    std::string  std_destination(std_source.begin(), std_source.end());    // map the std::wstring to std::string
    return this->exe_strcpy(destination, std_destination.c_str());         // copy std::string into destination with strcpy()
}


////~~~~


/*
    < 2 > private
    the caller should ensure the destiation c-string 
    is allocated to the proper length before calling
    use when std::stringX calls are not reliable
*/
CODEZ common_utility::_wchar_2_char_unq
(
    char* destination,
    const wchar_t* source
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    size_t w_len = wcslen(source);
    size_t idx = 0;

    while (idx < w_len)
    {
        if 
        (
            (source[idx] <= 127) &&    // ASCII range is 0:127, null terminates
            (source[idx] >= 1)
        )
        {
            destination[idx] = source[idx];
        }
        else
        {
            #ifdef DEBUG_MIN
                (void)snprintf(X_ddts, sizeof(X_ddts), "conversion not possible");
                (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(true);
            #endif
            (void)this->exe_strcpy(destination, INIT_CHARP);    // abortion
            return this->report_status_code(this->_status_code = CODEZ::_9_function_call_failed);
        }
        idx++;
    }
    destination[idx] = '\0';    // ensure NULL termination
    return this->report_status_code(this->_status_code = CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  cu_wchar_2_char.cpp
