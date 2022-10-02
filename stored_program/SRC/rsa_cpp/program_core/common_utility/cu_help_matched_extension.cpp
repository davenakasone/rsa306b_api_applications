/*
    common_utility, class 

    public :
        < 1 >  h_matched_extension()

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    do not include "."
    "r3f" "siq" "csv" ...
*/
bool common_utility::h_matched_extension
(
    const char* file_path_name, 
    const char* extension
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    if (file_path_name == NULL ||
        extension == NULL       )
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


////////~~~~~~~~END>  cu_help_matched_extension.cpp
