/*
    API group "IFSTREAM", user funcitons
    speed is sacrified for safety

    public :
        < 1 >  ifstream_check_acq_status()
    
    private :
        #  none
*/

#include "common_utility.h"

/*
    < 1 > public
    call at will to check the value stored in "vars.ifstream.data_info_type.acqStatus"
    also updates "vars.ifstream.acq_status_messages"
    automatically called when possible

    if char** results == NULL, no message updates occur
*/
CODEZ common_utility::ifstream_acq_status
(
    const uint32_t acq_status, 
    const int bitchecks,
    const char**messages, 
    char**results
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    uint32_t valid_bitmask = 
        static_cast<uint32_t>(RSA_API::IFSTRM_STATUS_OVERRANGE)        |
        static_cast<uint32_t>(RSA_API::IFSTRM_STATUS_XFER_DISCONTINUITY);
    if (results != NULL)
    {
        if (acq_status & valid_bitmask == BITCHECK_SUCCESS)    // the bitcheck was good for all bits
        {
            if (results != NULL)
            {
                for (int ii = 0; ii < bitchecks-1; ii++)
                {
                    (void)strcpy(results[ii], BITCHECK_SUCCESS_MESSAGE);    // update user's message
                }
            }
            return this->report_status_code(CODEZ::_0_no_errors);    // no further evaluation required
        }
    }
    else    // user just wants pass/fail result of the acquisition status code
    {
        if (acq_status & valid_bitmask == BITCHECK_SUCCESS)
        {
            return this->report_status_code(CODEZ::_0_no_errors);
        }
        else
        {
            return this->report_status_code(CODEZ::_28_bad_acquisition_code);
        }
    }
    
    // there was a bad acquisition status code and it needs to be evaluated further :

    (void)strcpy(results[bitchecks-1], messages[bitchecks-1]);
   
    if (acq_status & static_cast<uint32_t>(RSA_API::IFSTRM_STATUS_OVERRANGE) !=
        BITCHECK_SUCCESS                                                      )  // bit#0 is bad
    {
        (void)strcpy(results[0], messages[0]);
        (void)strcat(results[bitchecks-1], " b0 ");
    }

    if (acq_status & static_cast<uint32_t>(RSA_API::IFSTRM_STATUS_XFER_DISCONTINUITY) != 
        BITCHECK_SUCCESS                                                               )  // bit#1 is bad
    {
        (void)strcpy(results[1], messages[1]);
        (void)strcat(results[bitchecks-1], " b1 ");
    }
                             
    return this->report_status_code(CODEZ::_28_bad_acquisition_code);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_check_acq_status.cpp
