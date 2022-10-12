/*
    common_utility, class 

    public :
        < 1 >  exe_strcpy()
        < 2 >  exe_remove()
        < 3 >  exe_mkdir()
        < 4 >  exe_rmdir()
        < 5 >  exe_rename()

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

    if 
    (
        destination == NULL ||
        source == NULL       
    )
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
    be careful with this function
    the file deleted will be very hard to get back
*/
CODEZ common_utility::exe_remove
(
    const char* file_to_delete
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (file_to_delete == NULL)
    {
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }

    FILE* fp = NULL;
    fp = fopen(file_to_delete, "r");
    if (fp == NULL)
    {
        return this->report_status_code(CODEZ::_13_fopen_failed);    // file is not there, or busy
    }
    (void)fclose(fp);
    fp = NULL;

    if (remove(file_to_delete) != 0)
    {
        return this->report_status_code(CODEZ::_29_remove_failed);
    }

    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > public
*/
CODEZ common_utility::exe_mkdir
(
    const char* directory_name
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (directory_name == NULL)
    {
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }

    if (mkdir(directory_name, FMODE) != 0)
    {
        return this->report_status_code(CODEZ::_34_mkdir_failed);
    }

    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 4 > public
    be careful with this function
    it will delete everything in the directory selected, then delete the directory
*/
CODEZ common_utility::exe_rmdir
(
    const char* directory_name
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (directory_name == NULL)
    {
        return this->report_status_code(CODEZ::_7_parameter_not_allocated);
    }

    if (this->delete_files_in_directory(directory_name) != CODEZ::_0_no_errors)
    {
        return this->get_status_code();
    }

    if (rmdir(directory_name) != 0)
    {
        return this->report_status_code(CODEZ::_34_mkdir_failed);
    }

    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 5 > public
*/
CODEZ common_utility::exe_rename
(
    const char* old_name,
    const char* new_name
)
{
#ifdef DEBUG_CALL_CHECKS
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CALL_CHECKS_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (rename(old_name, new_name) != 0)
    {
        return this->report_status_code(CODEZ::_36_rename_failed);
    }
    return this->report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  cu_exe_1.cpp
