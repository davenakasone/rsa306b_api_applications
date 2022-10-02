/*
    API group "IFSTREAM", user funcitons
    speed is sacrified for safety

    public :
        < 1 >  ifstream_record_file()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    produces "*.r3f" file

    0) user updated the public "vars.ifstream.*", ensuring "vars.ifstream.output_destination_select == RSA_API::IFSOD_FILE_R3F"
    1) user called "ifstream_set_vars()"  // successfuly 
    2) user called "device_run()"         // must be called for first iteration
    3) user calls this function for as many acquisitions (*.r3f outputs) as desired
    4) user calls "device_stop()" when done, unless another type of acquisition is desired
    5) use the "r3f_manager" to process the file(s)

    ifstream gets enabled and disabled in here

    all the guards are ommitted, at a minimum:
    - the device is connected 
    - the device is running

*/
CODEZ rsa306b_class::ifstream_record_r3f()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  
#ifdef SAFETY_CHECKS
    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                this->cutil.codez_messages(CODEZ::_12_rsa_not_connnected));
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_12_rsa_not_connnected);
    }
    if (this->_vars.ifstream.output_destination_select != RSA_API::IFSOUTDEST::IFSOD_FILE_R3F)
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
#endif

    this->_vars.ifstream.is_active = true;
    this->vars.ifstream.is_enabled = true;
    this->_ifstream_set_is_enabled();

#ifdef BLOCKING_TIMEOUT
    this->cutil.timer_split_start();
#endif

    while(this->_vars.ifstream.is_active == true)   // still writting
    {
        (void)this->_ifstream_get_is_active();
        #ifdef BLOCKING_TIMEOUT
            // probably just going to let this run
        #endif
    }
    // if this is blocking forever, no way a file can hang (only get stuck in infinite loop)

    this->vars.ifstream.is_enabled = false;
    this->_ifstream_set_is_enabled();

    #ifdef DEBUG_MAX
        (void)snprintf(X_ddts, sizeof(X_ddts), "\nsee:  %s%s*.r3f",
            this->_vars.ifstream.file_path,
            this->_vars.ifstream.file_name_base);
        (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(false);
    #endif

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_record_r3f.cpp
