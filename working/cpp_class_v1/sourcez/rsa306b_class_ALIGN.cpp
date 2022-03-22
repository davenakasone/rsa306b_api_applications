/*
    implementation of the rsa306b_class
    using "ALIGN" function group of the API
        # rsa_check_alignment()
*/

#include "../includez/rsa306b_class.h"


/*
    public
    alignments may be needed during start-up or extended use
    the instance should call this method:
        - when starting the spectrum analyzer
        - after temperature changes
        - every 15 minutes of operation
    
    this function rejects calls if no device is connected
*/
void rsa306b::rsa_check_alignment()
{
    if (this->is_connected == false)
    {
        printf("can't align, there is no device connected\n");
        return;
    }
    this->api_return_status = RSA_API::ALIGN_GetWarmupStatus(&this->is_warmed_up);
    error_check();
    if (this->is_warmed_up == false)
    {
        while (is_warmed_up == false)
        {
            this->api_return_status = RSA_API::ALIGN_GetWarmupStatus(&this->is_warmed_up);
            sleep(1);
        }
    }

    this->api_return_status = RSA_API::ALIGN_GetAlignmentNeeded(&this->is_needed_alignment);
    error_check();
    
}

////////~~~~~~~~END>  rsa306b_class_ALIGN.cpp
