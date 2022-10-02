/*
    common_utility, class 

    public :
        < 1 >  h_find_bytes_in_file()

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    FILE* must be closed and on NULL
*/
CODEZ common_utility::h_find_bytes_in_file
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


////////~~~~~~~~END>  cu_help_find_bytes_in_file.cpp
