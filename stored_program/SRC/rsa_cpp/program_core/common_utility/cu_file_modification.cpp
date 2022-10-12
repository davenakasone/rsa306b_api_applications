/*
    class common_utility, file modification

    public :
        < 1 >  delete_files_in_directory()
        < 2 >  change_extension()
        < 3 >  switch_directory()
        < 4 >  insert_and_change_extension()
        < 5 >  batch_switch_directory_and_change_extension()
        < 6 >  batch_switch_directory_insert_and_change_extension()

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
CODEZ common_utility::delete_files_in_directory
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


////~~~~


/*
    < 2 > public
    changes valid file to a different extension
    do not include "."
    "r3f" "siq" "csv" ...

    could include a full file path name, but this is usually used for switching extensions
    and then redirecting to a new directory

    better to first call "batch_match_extension(directory, extension, include_directory=false)"
    then, call this function to change extension for each file
    finally, cat the desiried directory with this new file-name and redirect output

    [original path] [original name] . <new extension>
*/
CODEZ common_utility::change_extension
(
    char* file_name, 
    const char* new_extension
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        file_name == NULL ||
        new_extension == NULL       
    )
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    size_t file_chars = strlen(file_name);
    size_t counter = file_chars-1;

    while 
    (
        counter >= 0           &&
        file_name[counter] != '.'
    )
    {
        if (counter < file_chars-EXTENSION_LIMIT)
        {
            return this->report_status_code(CODEZ::_9_function_call_failed);
        }
        file_name[counter] = '\0';
        counter--;
    }
    (void)strcat(file_name, new_extension);

    return CODEZ::_0_no_errors;
}


////~~~~


/*
    < 3 > public
    given full file-path-name,
    changes to directory specified, while keeping filepath name
*/
CODEZ common_utility::switch_directory
(
    char* file_to_change, 
    const char* new_directory
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        (file_to_change == NULL) ||
        (new_directory == NULL)       
    )
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    
    std::string temp(file_to_change);
    std::vector<std::string> tokenz;
    std::stringstream check(temp);
    std::string results;
    while(getline(check, results, '/'))
    {
        tokenz.push_back(results);
    }
    auto v_size = tokenz.size();
    if (v_size < 1)
    {
        return CODEZ::_9_function_call_failed;
    }
    sprintf(file_to_change, "%s%s", new_directory, tokenz[v_size-1].c_str());
    return CODEZ::_0_no_errors;
}


////~~~~


/*
    < 4 > public
    changes valid file to a different extension
    do not include "."
    "r3f" "siq" "csv" ...

    could include a full file path name, but this is usually used for switching extensions
    and then redirecting to a new directory

    better to first call "h_batch_match_extension(directory, extension, include_directory=false)"
    then, call this function to change extension for each file
    finally, cat the desiried directory with this new file-name and redirect output

    [original path] [original name] <to insert> . <new extension>
*/
CODEZ common_utility::insert_and_change_extension
(
    char* file_path_name, 
    const char* to_insert, 
    const char* new_extension
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        (file_path_name == NULL) ||
        (to_insert == NULL)      ||
        (new_extension == NULL)   

    )
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    size_t file_chars = strlen(file_path_name);
    size_t counter = file_chars-1;

    while 
    (
        counter >= 0           &&
        file_path_name[counter] != '.'
    )
    {
        if (counter < file_chars-EXTENSION_LIMIT)
        {
            return this->report_status_code(CODEZ::_9_function_call_failed);
        }
        file_path_name[counter] = '\0';
        counter--;
    }
    file_path_name[counter] = '\0';
    (void)strcat(file_path_name, to_insert);
    (void)strcat(file_path_name, ".");
    (void)strcat(file_path_name, new_extension);

    return CODEZ::_0_no_errors;
}


////~~~~


/*
    < 5 > public
    used as a "call-through" when wanting to switch files of a specific extension in one directory to another
        naming the new files with a different (or can keep same) exetension
    
    1) calls find_files_with_extension() to files in the input directory that match the specified extension
    2) calls change_extension() on each file found
    3) concatenates desired output directory and files with changed extensions into "std::vector<std::string> new_filez"
*/
CODEZ common_utility::batch_switch_directory_and_change_extension
(
    const char* in_directory, 
    const char* in_extension, 
    const char* out_directory, 
    const char* out_extension, 
    std::vector<std::string>& new_filez
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        in_directory == NULL  || 
        in_extension == NULL  ||
        out_directory == NULL || 
        out_extension == NULL 
    )
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    new_filez.clear();
    std::vector<std::string> vfiles; 
    char temp[BUF_E];
    
    // in the specified directory, find the files with matching extension
    if (this->find_files_with_extension(in_directory, in_extension, vfiles, false) != CODEZ::_0_no_errors)
    {
        return this->report_status_code(CODEZ::_9_function_call_failed);
    }

    if (vfiles.size() < static_cast<std::size_t>(1))
    {
        return this->report_status_code(CODEZ::_19_result_not_found);
    }
    
    // change the directory + extension, then store the result
    for (std::size_t ii = 0; ii < vfiles.size(); ii++)
    {
        (void)sprintf(temp, "%s%s", 
            out_directory, 
            vfiles[ii].c_str());
        if (this->change_extension(temp, out_extension) != CODEZ::_0_no_errors)
        {
            return this->report_status_code(CODEZ::_9_function_call_failed);
        }
        new_filez.push_back(temp);
    }

    return CODEZ::_0_no_errors;
}


////~~~~


/*
    < 6 > public
    used as a "call-through" when wanting to switch files of a specific extension in one directory to another
        naming the new files with a different (or can keep same) exetension
    
    1) calls find_files_with_extension() to get files in the input directory that match the specified extension
    2) calls change_extension() on each file found
    3) inserts desired text ... use batch_switch_directory_and_change_extension() if no insersiton is needed
    3) concatenates desired output directory and files with changed extensions into "std::vector<std::string> new_filez"

    <out directory> <inserts> [old file name] . <out extension>
*/
CODEZ common_utility::batch_switch_directory_insert_and_change_extension
(
    const char* in_directory, 
    const char* in_extension, 
    const char* out_directory, 
    const char* inserts,
    const char* out_extension, 
    std::vector<std::string>& new_filez
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if 
    (
        in_directory  == NULL || 
        in_extension  == NULL ||
        inserts       == NULL ||
        out_directory == NULL || 
        out_extension == NULL 
    )
    {
        return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    new_filez.clear();
    std::vector<std::string> vfiles; 
    char temp[BUF_E];
    
    // in the specified directory, find the files with matching extension
    if (this->find_files_with_extension(in_directory, in_extension, vfiles, false) != CODEZ::_0_no_errors)
    {
        return this->report_status_code(CODEZ::_9_function_call_failed);
    }

    if (vfiles.size() < static_cast<std::size_t>(1))
    {
        return this->report_status_code(CODEZ::_19_result_not_found);
    }
    
    // change the directory + insert + extension, then store the result
    for (std::size_t ii = 0; ii < vfiles.size(); ii++)
    {
        (void)sprintf(temp, "%s%s%s", 
            out_directory, 
            inserts,
            vfiles[ii].c_str());
        if (this->change_extension(temp, out_extension) != CODEZ::_0_no_errors)
        {
            return this->report_status_code(CODEZ::_9_function_call_failed);
        }
        new_filez.push_back(temp);
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  cu_file_modification.cpp
