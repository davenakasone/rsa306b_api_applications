/*
    API group "IFSTREAM", user funcitons
    speed is sacrified for safety

    public :
        < 1 >  ifstream_check_acq_status()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"

/*
    < 1 > public
    call at will to check the value stored in "vars.ifstream.data_info_type.acqStatus"
    also updates "vars.ifstream.acq_status_messages"
    automatically called when possible
*/
CODEZ rsa306b_class::ifstream_check_acq_status()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    this->
    
}


////////~~~~~~~~END>  rsa306b_ifstream_user_check_acq_status.cpp
