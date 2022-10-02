/*
    common_utility, class 

    public :
        < 1 >  h_switch_directory()

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    do not include "."
    "r3f" "siq" "csv" ...
*/
CODEZ common_utility::h_switch_directory
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

    size_t file_chars = strlen(file_to_change);
    memset(this->_worker, '\0', sizeof(_worker));
    size_t counter = file_chars-1;
    (void)strcpy(this->_worker, file_to_change);

    char preserver[BUF_E];
    (void)memset(preserver, '\0', sizeof(preserver));

    while (counter >= 0                &&
           file_to_change[counter] != '/')
    {
        this->_worker[file_chars - 1 - counter] = file_to_change[counter];
        counter--;
    }
    file_chars = strlen(this->_worker);
    if (file_chars < 1)
    {
        return CODEZ::_9_function_call_failed;
    }
    counter = 0;
    while (counter < file_chars)
    {
        preserver[counter] = this->_worker[file_chars - 1 - counter];
        counter++;
    }
    (void)sprintf(file_to_change, "%s%s", new_directory, preserver);
    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  cu_help_switch_directory.cpp
