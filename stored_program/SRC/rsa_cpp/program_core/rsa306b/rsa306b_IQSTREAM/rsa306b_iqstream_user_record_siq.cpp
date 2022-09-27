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
CODEZ rsa306b_class::iqstream_record_siq()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // settings applied
    // device_run()
    // iqstream_start()

    bool is_complete = false;
    bool is_writing = false;
    if (this->_vars.trig.mode_select == RSA_API::freeRun)
    {
        while (is_complete == false)    // chances are data will eventually get there if untriggered, timeout if needed
        {
            this->_api_status =
                RSA_API::IQSTREAM_GetDiskFileWriteStatus
                (
                    &is_complete,
                    &is_writing
                );
        }
        this->_report_api_status();
    }
    else    // triggered mode
    {
        std::chrono::time_point<std::chrono::steady_clock> start_time;
        start_time = std::chrono::steady_clock::now();
        std::chrono::time_point<std::chrono::steady_clock> current_time;
        int elapsed_ms = 0;

        while 
        (
            elapsed_ms < this->_vars.iqstream.LOOP_LIMIT_MS &&
            is_complete == false
        )
        {
            this->_api_status =
                RSA_API::IQSTREAM_GetDiskFileWriteStatus   // when triggered, it is good to have a timer to breakout
                (
                    &is_complete,
                    &is_writing
                );
            current_time = std::chrono::steady_clock::now();    // this is supposed to be better than the "cutil" timers
            elapsed_ms = static_cast<int>
                (
                    std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count()
                );
        }
        this->_report_api_status();
    }
    // file was either made or timed out


    (void)this->_iqstream_get_disk_fileinfo();
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

    if (is_complete == false)    // timed-out
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "trigger event never occured...aborting output file");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        
        
        if (strcmp(this->_vars.iqstream.filenames_0_data, this->_vars.iqstream.filenames_1_header) == 0)
        {
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_0_data); // both files same, only delete 1
        }
        else
        {
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_0_data);  // delete both of the hung files
            (void)this->cutil.exe_remove(this->_vars.iqstream.filenames_1_header); 
        }
        this->_vars.iqstream.fileinfo_type.numberSamples = 0;
        this->vars.iqstream.fileinfo_type.numberSamples = this->_vars.iqstream.fileinfo_type.numberSamples;
        return this->cutil.report_status_code(CODEZ::_30_trigger_event_never_occured);
    }

    return this->cutil.report_status_code(CODEZ::_0_no_errors);

    // iqstream_stop()
    // device_stop()
}

             
////////~~~~~~~~END>  rsa306b_iqstream_user_record_siq.cpp
