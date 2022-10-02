/*
    API group "IQSTREAM"

    public :
        < 1 >  iqstream_acquire_data()                   
        < 2 >  iqstream_clear_sticky()
        < 3 >  iqstream_good_bitcheck()
        < 4 >  iqstream_start()
        < 5 >  iqstream_stop()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
CODEZ rsa306b_class::iqstream_clear_sticky()
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
    
    RSA_API::IQSTREAM_ClearAcqStatus();    // implemented as void, hardware clears 
    
    // effective reset of both acqStatus bitcheckers
    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        (void)strcpy(this->_vars.iqstream.acq_status_messages[ii], BITCHECK_SUCCESS_MESSAGE);
    }
    this->_vars.iqstream.fileinfo_type.acqStatus = BITCHECK_SUCCESS;
    this->_vars.iqstream.info_type.acqStatus = BITCHECK_SUCCESS;
    this->_iqstream_copy_acq_status_messages();
    this->_iqstream_copy_fileinfo_type();
    this->_iqstream_copy_info_type();
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}



////~~~~


/*
    < 2 > public
    only checks most recent
*/
bool rsa306b_class::iqstream_good_bitcheck()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    CODEZ temp = CODEZ::_0_no_errors;
    if (this->_vars.iqstream.destination_select == RSA_API::IQSOD_FILE_SIQ)    // most recent acqusition was to a file
    {
        temp =
            this->cutil.iqstream_acq_status
            (
                this->_vars.iqstream.fileinfo_type.acqStatus,    // the file acqStatus
                this->_vars.iqstream.valid_bitmask,
                this->_vars.iqstream.acq_status_messages
            );
    }
    else    // most recent acquisition was to the client
    {
        temp =
            this->cutil.iqstream_acq_status
            (
                this->_vars.iqstream.info_type.acqStatus,    // the streaming acqStatus
                this->_vars.iqstream.valid_bitmask,
                this->_vars.iqstream.acq_status_messages
            );
    }
    
    (void)this->_ifstream_copy_acq_status_messages();

    if (temp == CODEZ::_0_no_errors)
    {
        return true;
    }
    else
    {
        return false;
    }
}



////~~~~


/*
    < 3 > public
    start IQSTREAM
    must have called device_run() before calling here
*/
CODEZ rsa306b_class::iqstream_start()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->set_api_status(RSA_API::IQSTREAM_Start());
}


////~~~~


/*
    < 4 > public
    stop IQSTREAM
    call device_stop() if done
*/
CODEZ rsa306b_class::iqstream_stop()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    return this->set_api_status(RSA_API::IQSTREAM_Stop());
}


////////~~~~~~~~END>  rsa306b_iqstream_user.cpp
