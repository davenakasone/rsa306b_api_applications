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

    all the guards are ommitted, at a minimum:
    - the device is connected
    - the device is running
    - ifstream settings are correctly applied

*/
CODEZ rsa306b_class::ifstream_record_r3f()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif  

    #ifdef LOOP_TIMEOUT
        (void)this->cutil.timer_split_start();
    #endif

    this->set_api_status(RSA_API::IFSTREAM_SetEnable(true));
    this->_vars.ifstream.is_active = true;
    while(this->_vars.ifstream.is_active == true)   // still writting
    {
        (void)this->_ifstream_get_is_active();
        #ifdef LOOP_TIMEOUT
            if (this->cutil.timer_get_split_wall() > this->_vars.ifstream.LOOP_LIMIT_S)
            {
                #ifdef DEBUG_MIN
                    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__,
                        this->cutil.codez_messages(CODEZ::_27_loop_timed_out));
                    debug_record(true);
                #endif
                return this->cutil.report_status_code(CODEZ::_27_loop_timed_out);
            }
        #endif
    }
    

    #ifdef DEBUG_MAX
        (void)snprintf(X_ddts, sizeof(X_ddts), "r3f file should be ready, see:  %s%s*.r3f",
            this->_vars.ifstream.file_path,
            this->_vars.ifstream.file_name_base);
        (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
        debug_record(true);
    #endif

    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_record_r3f.cpp
