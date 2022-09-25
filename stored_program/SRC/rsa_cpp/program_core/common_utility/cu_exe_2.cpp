/*
    common_utility, class 

    public :
        < 1 >  exe_remove    

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
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

    if (remove(file_to_delete) != 0)
    {
        return this->report_status_code(CODEZ::_29_remove_failed);
    }

    return this->report_status_code(CODEZ::_0_no_errors);
}


////~~~~




////////~~~~~~~~END>  cu_exe_2.cpp
