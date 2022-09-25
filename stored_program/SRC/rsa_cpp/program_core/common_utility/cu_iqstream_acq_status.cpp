/*
    API group "IQSTREAM", any bitcheck

    public :
        < 1 >  iqstream_acq_status()
    
    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    call to check any IQSTREAM acqStatus
    updates the "results" with messages to status of the bit
        if char** results == NULL, no updates occur
*/
CODEZ common_utility::iqstream_acq_status
(
    const uint32_t acq_status, 
    const uint32_t valid_bitmask,
    char results[IQSTREAM_BITCHECKS][BUF_D]
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
            for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
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

    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        (void)strcpy(results[ii], BITCHECK_SUCCESS_MESSAGE);  
    }
    (void)strcpy(results[IQSTREAM_BITCHECKS-1], IQSTREAM_BITCHECK_MESSAGES[IQSTREAM_BITCHECKS-1]);
   
    // check each bit

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQSTRM_STATUS_OVERRANGE)) !=
        BITCHECK_SUCCESS                                                        )             // bit#0 is bad
    {
        (void)strcpy(results[0], IQSTREAM_BITCHECK_MESSAGES[0]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b0 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY)) != 
        BITCHECK_SUCCESS                                                                 )    // bit#1 is bad
    {
        (void)strcpy(results[1], IQSTREAM_BITCHECK_MESSAGES[1]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b1 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQSTRM_STATUS_IBUFF75PCT)) != 
        BITCHECK_SUCCESS                                                         )    // bit#2 is bad
    {
        (void)strcpy(results[2], IQSTREAM_BITCHECK_MESSAGES[2]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b2 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQSTRM_STATUS_IBUFFOVFLOW )) != 
        BITCHECK_SUCCESS                                                           )    // bit#3 is bad
    {
        (void)strcpy(results[3], IQSTREAM_BITCHECK_MESSAGES[3]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b3 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQSTRM_STATUS_OBUFF75PCT)) != 
        BITCHECK_SUCCESS                                                         )    // bit#4 is bad
    {
        (void)strcpy(results[4], IQSTREAM_BITCHECK_MESSAGES[4]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b4 ");
    }

    if ((acq_status & static_cast<uint32_t>(RSA_API::IQSTRM_STATUS_OBUFFOVFLOW)) != 
        BITCHECK_SUCCESS                                                                 )    // bit#5 is bad
    {
        (void)strcpy(results[5], IQSTREAM_BITCHECK_MESSAGES[5]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b5 ");
    }

    if ((acq_status & (RSA_API::IQSTRM_STATUS_OVERRANGE << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) != 
        BITCHECK_SUCCESS                                                                          )    // bit#16 is bad
    {
        (void)strcpy(results[6], IQSTREAM_BITCHECK_MESSAGES[6]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b16 ");
    }

    if ((acq_status & (RSA_API::IQSTRM_STATUS_XFER_DISCONTINUITY << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) != 
        BITCHECK_SUCCESS                                                                                   )    // bit#17 is bad
    {
        (void)strcpy(results[7], IQSTREAM_BITCHECK_MESSAGES[7]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b17 ");
    }

    if ((acq_status & (RSA_API::IQSTRM_STATUS_IBUFF75PCT << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) != 
        BITCHECK_SUCCESS                                                                           )    // bit#18 is bad
    {
        (void)strcpy(results[8], IQSTREAM_BITCHECK_MESSAGES[8]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b18 ");
    }

    if ((acq_status & (RSA_API::IQSTRM_STATUS_IBUFFOVFLOW << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) != 
        BITCHECK_SUCCESS                                                                            )    // bit#19 is bad
    {
        (void)strcpy(results[9], IQSTREAM_BITCHECK_MESSAGES[9]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b19 ");
    }

    if ((acq_status & (RSA_API::IQSTRM_STATUS_OBUFF75PCT << RSA_API::IQSTRM_STATUS_STICKY_SHIFT)) != 
        BITCHECK_SUCCESS                                                                                   )    // bit#20 is bad
    {
        (void)strcpy(results[10], IQSTREAM_BITCHECK_MESSAGES[10]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b20 ");
    }

    if ((acq_status & (RSA_API::IQSTRM_STATUS_OBUFFOVFLOW << RSA_API::IQSTRM_STATUS_STICKY_SHIFT) ) != 
        BITCHECK_SUCCESS                                                                            )    // bit#21 is bad
    {
        (void)strcpy(results[11], IQSTREAM_BITCHECK_MESSAGES[11]);
        (void)strcat(results[IQSTREAM_BITCHECKS-1], " b21 ");
    }

    #ifdef DEBUG_ACQ_STATUS
        for (int ii = 0; ii < IQSTREAM_BITCHECKS-1; ii++)
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


////////~~~~~~~~END>  cu_iqstream_acq_status.cpp
