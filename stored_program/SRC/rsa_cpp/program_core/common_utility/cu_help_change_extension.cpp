/*
    common_utility, class 

    public :
        < 1 >  h_change_extension()

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    changes valid file to a different extension
    do not include "."
    "r3f" "siq" "csv" ...

    could include a full file path name, but this is usually used for switching extensions
    and then redirecting to a new directory

    better to first call "h_batch_match_extension(directory, extension, include_directory=false)"
    then, call this function to change extension for each file
    finally, cat the desiried directory with this new file-name and redirect output

    <original path> <original name> . <new extension>
*/
CODEZ common_utility::h_change_extension
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


////////~~~~~~~~END>  cu_help_change_extension.cpp
