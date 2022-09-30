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
    the settings, run device, start iqstream, and other checks should be done before calling
    user should stop IQSTREAM and device when done
    designed to be faster
*/
CODEZ rsa306b_class::iqstream_record_siq
(
    const int timeout_ms
)
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

int ms_timeout = timeout_ms;

#ifdef TIMEOUT_MS
    if (ms_timeout > TIMEOUT_MS)
    {
        ms_timeout = TIMEOUT_MS;
    }
    if (ms_timeout < 0)
    {
        ms_timeout = 1;
    }
#endif

    //(void)this->iqstream_start();    // IQSTREAM_Start()
    bool is_complete = false;
    bool is_writing = false;

#ifdef TIMEOUT_MS
    this->cutil.timer_split_start();
    while 
    (
        (this->cutil.timer_get_split_wall() / 1000.0) < static_cast<double>(ms_timeout) &&
        is_complete == false
    )
    {
        this->_api_status =
            RSA_API::IQSTREAM_GetDiskFileWriteStatus   // when triggered, it is good to have a timer to breakout
            (
                &is_complete,
                &is_writing
            );
    }
#else
    while (is_complete == false)    // this will block until the SIQ file is written
    {
        this->_api_status =
            RSA_API::IQSTREAM_GetDiskFileWriteStatus
            (
                &is_complete,
                &is_writing
            );
    }
#endif
this->_report_api_status();
//(void)this->iqstream_stop();    // IQSTREAM_Stop()

    (void)this->_iqstream_get_disk_fileinfo();
    this->_vars.iqstream.filenames_0_data[0] = '\0';
    this->cutil.wchar_2_char_std
        (
            this->_vars.iqstream.filenames_0_data,
            this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX]
            
        );
    this->cutil.wchar_2_char_std
        (
            this->_vars.iqstream.filenames_1_header,
            this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX]
            
        );

    if (is_complete != true)    // timed-out
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "trigger event never occured...aborting output file");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        
        if 
        (
            strcmp(this->_vars.iqstream.filenames_0_data, this->_vars.iqstream.filenames_1_header) == 0 &&
            this->_vars.iqstream.filenames_0_data[0] != '\0'
        )
        {
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_0_data);    // both files same, only delete 1
        }
        if 
        (
            strcmp(this->_vars.iqstream.filenames_0_data, this->_vars.iqstream.filenames_1_header) != 0 &&
            this->_vars.iqstream.filenames_0_data[0] != '\0'
        )
        {
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_0_data);      // delete both of the hung files
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_1_header); 
        }
        return this->cutil.report_status_code(CODEZ::_30_trigger_event_never_occured);
    }

    // iqstream_stop()
    // device_stop()
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}

             
////////~~~~~~~~END>  rsa306b_iqstream_user_record_siq.cpp
