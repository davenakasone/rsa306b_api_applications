/*
    common_utility, class 

    public :
        < 1 >  h_delete_files_in_dir

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    given a directory and extension,
    populates "std::vector<std::string> filez" with results (if any)
        "include_directory == true", vetor is updated with full file-path-name
        "include_directory == false", vetor is updated with only file-name (no directory)
*/
CODEZ common_utility::h_delete_files_in_dir
(
    const char* directory
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if (directory == NULL)
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    DIR* dir = NULL;
    struct dirent* diread = NULL;
    char temp[BUF_E];

    dir = opendir(directory);
    if (dir == NULL)
    {
        return this->report_status_code(CODEZ::_32_opendir_failed);
    }

    while ( (diread = readdir(dir)) != NULL)
    {
        if (diread->d_name[0] != '.')
        {
            (void)snprintf(temp, sizeof(temp), "%s%s",
                directory,
                diread->d_name);
            if (this->exe_remove(temp) != CODEZ::_0_no_errors)
            {
                return this->get_status_code();
            }
        }
    }
    if (closedir(dir) != 0)
    {
        this->report_status_code(CODEZ::_33_closedir_failed);
    }
    dir = NULL;

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  cu_help_delete_files_in_dir.cpp
