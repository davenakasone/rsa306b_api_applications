/*
    common_utility, class

    public :
        < 1 >  wchar_2_char()
    
    private :
        #  none
        
*/

#include "common_utility.h"


/*
    < 1 > public
    the caller should ensure the destiation c-string 
    is allocated to the proper length before calling
*/
CODEZ common_utility::wchar_2_char
(
    const wchar_t* source, 
    char* destination
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    if (source == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "the wchar_t* is empty");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        this->_status_code = CODEZ::_7_parameter_not_allocated;
        this->_report_status_code();
        return this->_status_code;
    }
    if (destination == NULL)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "the char* is empty");
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        this->_status_code = CODEZ::_7_parameter_not_allocated;
        this->_report_status_code();
        return this->_status_code;
    }
    size_t w_len = (int)wcslen(source);
    int idx = 0;
    if (source[idx] == '\0' ||
        w_len <= 0           )
    {
        #ifdef DEBUG_MAX
            snprintf(X_ddts, sizeof(X_ddts), "small string, len()=  %lu", w_len);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(false);
        #endif
        memset(destination, '\0', 2);    // ensure NULL termination
        this->_status_code = CODEZ::_8_small_string_length;
        this->_report_status_code();
        return this->_status_code;
    }

    while (idx < w_len)
    {
        if (source[idx] <= 127 &&
            source[idx] >= 0   )    // ASCII range is 0:127
        {
            destination[idx] = source[idx];
        }
        else
        {
            #ifdef DEBUG_MAX
                snprintf(X_ddts, sizeof(X_ddts), "conversion not possible");
                snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(false);
            #endif
            destination[0] = '\0';    // ensure NULL termination
            this->_status_code = CODEZ::_9_function_call_failed;
            this->_report_status_code();
            return this->_status_code;
        }
        idx++;
    }
    destination[idx] = '\0';    // ensure NULL termination
}


////////~~~~~~~~END>  cu_wchar_2_char.cpp
