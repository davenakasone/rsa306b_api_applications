/*
    common_utility, class 

    public :
        < 1 >  find_files_with_extension()

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
CODEZ common_utility::find_files_with_extension
(
    const char* directory, 
    const char* extension,
    std::vector<std::string>& filez,
    bool include_directory
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if (directory == NULL || extension == NULL)
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    filez.clear();
    DIR* p_dir = NULL;
    struct dirent* p_dread = NULL;
    char temp[BUF_E];

    p_dir = opendir(directory);
    if (p_dir == NULL)
    {
        return this->report_status_code(CODEZ::_32_opendir_failed);
    }

    while ( (p_dread = readdir(p_dir)) != NULL)
    {
        if (p_dread->d_name[0] != '.')
        {
            (void)snprintf(temp, sizeof(temp), "%s%s",
                directory,
                p_dread->d_name);
            if (this->extension_matched(temp, extension) == true)
            {
                if (include_directory == true)
                {
                    filez.push_back(temp);
                }
                else
                {
                    filez.push_back(p_dread->d_name);
                }
            }
        }
    }
    if (closedir(p_dir) != 0)
    {
        this->report_status_code(CODEZ::_33_closedir_failed);
    }
    p_dir = NULL;

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  cu_find_files_with_extension.cpp
