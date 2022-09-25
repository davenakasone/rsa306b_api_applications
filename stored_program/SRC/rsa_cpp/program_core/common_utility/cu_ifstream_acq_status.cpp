/*
    API group "IFSTREAM", any bitcheck

    public :
        < 1 >  ifstream_acq_status()
    
    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    call to check any IFSTREAM acqStatus
    updates the "results" with messages to status of the bit
        if char** results == NULL, no updates occur
*/
CODEZ common_utility::ifstream_acq_status
(
    const uint32_t acq_status, 
    const uint32_t valid_bitmask,
    char results[IFSTREAM_BITCHECKS][BUF_D]
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
            for (int ii = 0; ii < IFSTREAM_BITCHECKS; ii++)
            {
                (void)strcpy(results[ii], BITCHECK_SUCCESS_MESSAGE);    // update user's acquisition messages
            }
        }
        return this->report_status_code(CODEZ::_0_no_errors);           // no further evaluation required
    }
    if    // user just wants result and there is at least one failed bit
    (
        results == NULL                               &&
        (acq_status & valid_bitmask) != BITCHECK_SUCCESS
    )               
    {
        return this->report_status_code(CODEZ::_28_bad_acquisition_code);
    }
    
    // there was a bad acquisition status code an further evaluation was requested

    for (int ii = 0; ii < IFSTREAM_BITCHECKS; ii++)
    {
        (void)strcpy(results[ii], BITCHECK_SUCCESS_MESSAGE);    // update user's acquisition messages
    }
    (void)strcpy(results[IFSTREAM_BITCHECKS-1], IFSTREAM_BITCHECK_MESSAGES[IFSTREAM_BITCHECKS-1]);
   
    // check each bit

    if ((acq_status & static_cast<uint32_t>(RSA_API::IFSTRM_STATUS_OVERRANGE)) !=
        BITCHECK_SUCCESS                                                        )             // bit#0 is bad
    {
        (void)strcpy(results[0], IFSTREAM_BITCHECK_MESSAGES[0]);
        (void)strcat(results[IFSTREAM_BITCHECKS-1], " b0 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IFSTRM_STATUS_XFER_DISCONTINUITY)) != 
        BITCHECK_SUCCESS                                                                 )    // bit#1 is bad
    {
        (void)strcpy(results[1], IFSTREAM_BITCHECK_MESSAGES[1]);
        (void)strcat(results[IFSTREAM_BITCHECKS-1], " b1 ");
    }

    // report failures if activated
    #ifdef DEBUG_ACQ_STATUS
        for (int ii = 0; ii < IFSTREAM_BITCHECKS-1; ii++)
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


////////~~~~~~~~END>  cu_ifstream_acq_status.cpp
