/*
    API group "IQSTREAM"

    public :
        < 1 >  iqstream_record_siq()

    private :
        #  none
    
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    data goes to a "*.siq" file
    the settings, run device, and other checks should be done before calling
    user should stop IQSTREAM and device when done
    designed to be faster
    must call start and stop inside the function, otherwise only 1 write operation occurs
*/
CODEZ rsa306b_class::iqstream_record_siq()
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
#endif

    (void)this->iqstream_start();    // IQSTREAM_Start()
    bool is_complete = false;
    bool is_writing = false;

    while (is_complete == false)    // will block until data is ready
    {
        this->_api_status =
            RSA_API::IQSTREAM_GetDiskFileWriteStatus
            (
                &is_complete,
                &is_writing
            );
    }

// #ifdef BLOCKING_TIMEOUT
//     (void)this->cutil.timer_split_start();
//     while 
//     (
//         this->cutil.timer_get_split_wall() < TIMEOUT_LIMIT_S &&
//         is_complete == false
//     )
//     {
//         this->_api_status =
//             RSA_API::IQSTREAM_GetDiskFileWriteStatus
//             (
//                 &is_complete,
//                 &is_writing
//             );
//     }
// #else
//     while (is_complete == false)    // will block until data is ready
//     {
//         this->_api_status =
//             RSA_API::IQSTREAM_GetDiskFileWriteStatus
//             (
//                 &is_complete,
//                 &is_writing
//             );
//     }
// #endif
    (void)this->_report_api_status();
    (void)this->_iqstream_get_disk_fileinfo();
    //this->_vars.iqstream.filenames_0_data[0] = '\0';
    
    if (is_complete == false)    // file never finished (could be hung or never started because trigger did not occur)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "...aborting output '*.siq' file(s)");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        if 
        (
            (strcmp(this->_vars.iqstream.filenames_0_data, this->_vars.iqstream.filenames_1_header) == 0) &&
            (strcmp(this->_vars.iqstream.filenames_0_data, INIT_CHARP) != 0)
        )
        {
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_0_data);    // both files same, only delete 1
        }
        if 
        (
            (strcmp(this->_vars.iqstream.filenames_0_data, this->_vars.iqstream.filenames_1_header) != 0) &&
            (strcmp(this->_vars.iqstream.filenames_0_data, INIT_CHARP) != 0)                              &&
            (strcmp(this->_vars.iqstream.filenames_1_header, INIT_CHARP) != 0)
        )
        {
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_0_data);      // delete both of the hung files
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_1_header); 
        }
        return this->cutil.report_status_code(CODEZ::_27_loop_timed_out);
    }

    //(void)this->iqstream_good_bitcheck();
    (void)this->iqstream_stop();    // IQSTREAM_Stop()
    // device_stop()
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}

             
////////~~~~~~~~END>  rsa306b_iqstream_user_record_siq.cpp
