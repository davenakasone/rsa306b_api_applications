/*
    common_utility, class 

    public :
        < 1 >  h_batch_change_redirect()

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    used as a "call-through" when wanting to switch files of a specific extension in one directory to another
        naming the new files with a different (or can keep same) exetension
    
    1) calls h_batch_match_extension() to files in the input directory that match the specified extension
    2) calls h_change_extension() on each file found
    3) concatenates desired output directory and files with changed extensions into "std::vector<std::string> new_filez"
*/
CODEZ common_utility::h_batch_change_redirect
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
    if (this->h_batch_match_extension(in_directory, in_extension, vfiles, false) != CODEZ::_0_no_errors)
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
        if (this->h_change_extension(temp, out_extension) != CODEZ::_0_no_errors)
        {
            return this->report_status_code(CODEZ::_9_function_call_failed);
        }
        new_filez.push_back(temp);
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  cu_help_batch_change_redirect.cpp
