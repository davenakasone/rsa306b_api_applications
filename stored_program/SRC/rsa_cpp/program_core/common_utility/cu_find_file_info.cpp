/*
    class common_utility, finding infomation about files
    these functions are repetitive by design, but can be consolidated (if needed)

    public :
        < 1 >  find_bytes_in_file()
        < 2 >  extension_matched()
        < 3 >  tag_matched()
        < 4 >  extension_and_tag_matched()
        < 5 >  find_files_with_extension()
        < 6 >  find_files_with_tag()
        < 7 >  find_files_with_extension_and_tag()  
        < 8 >  find_files_in_directory()

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    FILE* must be closed and on NULL
*/
CODEZ common_utility::find_bytes_in_file
(
    const char* file_path_name, 
    long& result
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    FILE* fp = NULL;
    fp = fopen(file_path_name, "r");                                  // open the file
    if (fp == NULL)
    {
        return this->report_status_code(CODEZ::_13_fopen_failed);
    }
    if (fseek(fp, 0L, SEEK_END) != 0)                                 // go to the end of the file
    {
        (void)fclose(fp);
        return this->report_status_code(CODEZ::_14_fseek_failed);
    }

    result = ftell(fp);                                               // record byte index of last byte in the file
    if (result < 0)
    {
        return this->report_status_code(CODEZ::_15_ftell_failed);
    }
    
    if (fseek(fp, 0L, SEEK_SET) != 0)                                 // reset the file position
    {
        return this->report_status_code(CODEZ::_14_fseek_failed);
    }
    if (fclose(fp) != 0)                                              // close the file
    {
        return this->report_status_code(CODEZ::_10_fclose_failed);
    }
    fp = NULL;

    return report_status_code(CODEZ::_0_no_errors);                   // "result" is successfully updated
}


////~~~~


/*
    < 2 > public
    do not include "."
    "r3f" "siq" "csv" ...
    this function is uniquley written to ensure searching from end of "file_path_name"
    not for batch analysis, but can be used in a loop
*/
bool common_utility::extension_matched
(
    const char* file_path_name, 
    const char* extension
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        (file_path_name == NULL) ||
        (extension == NULL)
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_7_parameter_not_allocated));
            debug_record(true);
        #endif
        return false;
    }

    size_t file_chars = strlen(file_path_name);
    memset(this->_worker, '\0', sizeof(_worker));
    size_t counter = file_chars-1;
    char compare_to[EXTENSION_LIMIT];
    memset(compare_to, '\0', EXTENSION_LIMIT);
    while (counter >= 0                 &&
           file_path_name[counter] != '.')
    {
        if (counter < file_chars-EXTENSION_LIMIT)
        {
            return false;
        }
        this->_worker[file_chars-1-counter] = file_path_name[counter];
        counter--;
    }
    file_chars = strlen(this->_worker);
    if (file_chars < 1 || file_chars > EXTENSION_LIMIT)
    {
        return false;
    }
    counter = 0;
    while (counter < file_chars)
    {
        compare_to[counter] = this->_worker[file_chars-1-counter];
        counter++;
    }
    if (strcmp(compare_to, extension) != 0)
    {
        return false;
    }
    return true;    // the exentension matched
}


////~~~~


/*
    < 3 > public
    char* strstr(haystack, needle)   // haystack==file_path_name, needle==tag "substring"
    only looks for 1 occurance of the substring
    not for batch analysis, but can be used in a loop
*/
bool common_utility::tag_matched
(
    const char* file_path_name, 
    const char* tag
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        (file_path_name == NULL) ||
        (tag == NULL)
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_7_parameter_not_allocated));
            debug_record(true);
        #endif
        return false;
    }

    if (strstr(file_path_name, tag) == NULL)
    {
        return false;
    }
    return true;
}


////~~~~


/*
    < 4 > public
    char* strstr(haystack, needle)   // haystack==file_path_name, needle==tag "substring"
    only looks for 1 occurance of the substring
    not for batch analysis, but can be used in a loop
*/
bool common_utility::extension_and_tag_matched              
(
    const char* file_path_name, 
    const char* extension,
    const char* tag
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        (file_path_name == NULL) ||
        (extension == NULL)      ||
        (tag == NULL)            
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->codez_messages(CODEZ::_7_parameter_not_allocated));
            debug_record(true);
        #endif
        return false;
    }

    if 
    (
        (this->extension_matched(file_path_name, extension) == true) &&
        (this->tag_matched(file_path_name, tag) == true)
    )
    {
        return true;
    }
    return false;
}


////~~~~


/*
    < 5 > public
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
    
    if 
    (
        (directory == NULL) || 
        (extension == NULL)
    )
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


////~~~~


/*
    < 6 > public
    given a directory and tag,
    populates "std::vector<std::string> filez" with results (if any)
        "include_directory == true", vetor is updated with full file-path-name
        "include_directory == false", vetor is updated with only file-name (no directory)
*/
CODEZ common_utility::find_files_with_tag
(
    const char* directory, 
    const char* tag,
    std::vector<std::string>& filez,
    bool include_directory
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        (directory == NULL) || 
        (tag == NULL)
    )
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
            if (this->tag_matched(p_dread->d_name, tag) == true)
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


////~~~~


/*
    < 7 > public
    given a directory, extension, and tag
    populates "std::vector<std::string> filez" with results (if any)
        "include_directory == true", vetor is updated with full file-path-name
        "include_directory == false", vetor is updated with only file-name (no directory)
*/
CODEZ common_utility::find_files_with_extension_and_tag     
(
    const char* directory, 
    const char* extension, 
    const char* tag, 
    std::vector<std::string>& filez, 
    bool include_directory
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        (directory == NULL) || 
        (tag == NULL)       ||
        (extension == NULL)
    )
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
            if (this->extension_and_tag_matched(temp, extension, tag) == true)
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


////~~~~


/*
    < 8 > public
    given a directory, find every file in there (not suitable for sub-directories)
    populates "std::vector<std::string> filez" with results (if any)
        "include_directory == true", vetor is updated with full file-path-name
        "include_directory == false", vetor is updated with only file-name (no directory)
*/
CODEZ common_utility::find_files_in_directory
(
    const char* directory, 
    std::vector<std::string>& filez, 
    bool include_directory
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
    if (closedir(p_dir) != 0)
    {
        this->report_status_code(CODEZ::_33_closedir_failed);
    }
    p_dir = NULL;

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  cu_find_file_info.cpp
