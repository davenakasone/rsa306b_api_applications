/*
    common_utility, class 

    public :
        < 1 >  exe_strcpy()
        < 2 >  exe_fopen()
        < 3 >  exe_fseek()
        < 4 >  exe_ftell()        
        < 5 >  exe_fclose()    

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
*/
CODEZ common_utility::exe_strcpy
(
    char* destination, 
    const char* source
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (destination == NULL ||
        source == NULL       )
    {
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }
    if (strcpy(destination, source) == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_11_strcpy_failed));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_11_strcpy_failed);
    }
    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 2 > public
    FILE* must be closed
*/
CODEZ common_utility::exe_fopen
(
    const char* file_path_name, 
    const char* mode, 
    FILE* fp
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // check parameter strings
    if (file_path_name == NULL ||
        mode == NULL            )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_7_parameter_not_allocated));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }

    // see if the FILE* is available
    if (fp != NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_17_file_pointer_busy));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_17_file_pointer_busy);
    }

    // try to open the file
    fp = fopen(file_path_name, mode);
    if (fp == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "failed to open:  %s", file_path_name);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_13_fopen_failed);
    }
    return this->report_status_code(CODEZ::_0_no_errors);  // FILE* is on an open file, if successful
}


////~~~~


/*
    < 3 > public
    FILE* must be open
*/
CODEZ common_utility::exe_fseek
(
    FILE* fp, 
    long int offset, 
    int origin
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // check numberical parameters
    if (offset < 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_5_called_with_bad_paramerters));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if (origin != SEEK_CUR && origin != SEEK_SET && origin != SEEK_END)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_5_called_with_bad_paramerters));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    // see if the FILE* has a valid file open
    if (fp == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_18_file_pointer_not_open));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_18_file_pointer_not_open);
    }

    // try to move position in the file
    if (fseek(fp, offset, origin) != 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_14_fseek_failed));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_14_fseek_failed);
    }
    return this->report_status_code(CODEZ::_0_no_errors);  // FILE* is placed on requested positon
}


////~~~~


/*
    < 4 > public
    FILE* must be open
*/
CODEZ common_utility::exe_ftell
(
    FILE* fp, 
    long int& position
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // see if the FILE* has a valid file open
    if (fp == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_18_file_pointer_not_open));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_18_file_pointer_not_open);
    }

    position = ftell(fp);
    if (position < 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_15_ftell_failed));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_15_ftell_failed);
    }
    return this->report_status_code(CODEZ::_0_no_errors);  // position was found
}


////~~~~


/*
    < 5 > public
    FILE* must be open
*/
CODEZ common_utility::exe_fclose
(
    FILE* fp
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // see if the FILE* has a valid file open
    if (fp == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_18_file_pointer_not_open));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_18_file_pointer_not_open);
    }

    if (fclose(fp) != 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_16_fclose_failed));
            debug_record(true);
        #endif
        return this->report_status_code(CODEZ::_16_fclose_failed);    // a segmentation fault will occur soon
    }
    fp = NULL;
    return this->report_status_code(CODEZ::_0_no_errors);  // file was closed
}


////////~~~~~~~~END>  cu_exe_1.cpp
