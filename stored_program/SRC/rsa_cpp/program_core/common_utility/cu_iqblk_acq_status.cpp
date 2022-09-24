/*
    API group "IQBLK", any bitcheck

    public :
        < 1 >  iqblk_acq_status()
    
    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    call to check any IQBLK acqStatus
    updates the "results" with messages to status of the bit
        if char** results == NULL, no updates occur
*/
CODEZ common_utility::iqblk_acq_status
(
    const uint32_t acq_status, 
    const uint32_t valid_bitmask,
    char results[IQBLK_BITCHECKS][BUF_D]
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    if ((acq_status & valid_bitmask) == BITCHECK_SUCCESS)               // the bitcheck was good for all bits
    {
        if (results != NULL)
        {
            for (int ii = 0; ii < IQBLK_BITCHECKS-1; ii++)
            {
                (void)strcpy(results[ii], BITCHECK_SUCCESS_MESSAGE);    // update user's acquisition messages
            }
        }
        return this->report_status_code(CODEZ::_0_no_errors);           // no further evaluation required
    }
    if (results == NULL                                &&
        (acq_status & valid_bitmask) != BITCHECK_SUCCESS)               // user just wants result and there is at least one failed bit
    {
        return this->report_status_code(CODEZ::_28_bad_acquisition_code);
    }
    
    // there was a bad acquisition status code an further evaluation was requested :

    (void)strcpy(results[IQBLK_BITCHECKS-1], IQBLK_BITCHECK_MESSAGES[IQBLK_BITCHECKS-1]);
   
    if ((acq_status & static_cast<uint32_t>(RSA_API::IQBLK_STATUS_INPUT_OVERRANGE)) !=
        BITCHECK_SUCCESS                                                             )    // bit#0 is bad
    {
        (void)strcpy(results[0], IQBLK_BITCHECK_MESSAGES[0]);
        (void)strcat(results[IQBLK_BITCHECKS-1], " b0 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQBLK_STATUS_FREQREF_UNLOCKED)) != 
        BITCHECK_SUCCESS                                                              )    // bit#1 is bad
    {
        (void)strcpy(results[1], IQBLK_BITCHECK_MESSAGES[1]);
        (void)strcat(results[IQBLK_BITCHECKS-1], " b1 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQBLK_STATUS_ACQ_SYS_ERROR)) != 
        BITCHECK_SUCCESS                                                           )    // bit#2 is bad
    {
        (void)strcpy(results[2], IQBLK_BITCHECK_MESSAGES[2]);
        (void)strcat(results[IQBLK_BITCHECKS-1], " b2 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQBLK_STATUS_DATA_XFER_ERROR)) != 
        BITCHECK_SUCCESS                                                             )    // bit#3 is bad
    {
        (void)strcpy(results[3], IQBLK_BITCHECK_MESSAGES[3]);
        (void)strcat(results[IQBLK_BITCHECKS-1], " b3 ");
    }

    #ifdef DEBUG_ACQ_STATUS
        for (int ii = 0; ii < IQBLK_BITCHECKS-1; ii++)
        {
            if (strcmp(results[ii], BITCHECK_SUCCESS_MESSAGE) != 0)
            {
                (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_ACQ_STATUS_FORMAT, results[ii]);
                debug_record(false);
            }
        }
    #endif       
    return this->report_status_code(CODEZ::_28_bad_acquisition_code);
}


////////~~~~~~~~END>  cu_iqblk_acq_status.cpp
