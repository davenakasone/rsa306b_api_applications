/*
    implementation of the rsa306b_class
    using "ALIGN" function group of the API
        public:
            # print_alignment()
            # rsa_alignment()
        private:
            # execute_alignment()
            # execute_warm_up()
        
*/

#include "../includez/rsa306b_class.h"


/*
    public
    called to print alignment information,
    includes warm-up status
*/
void rsa306b::print_alignment()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("can't print alignment information, there is no device connected\n");
        #endif
        return;
    }
    this->api_return_status = RSA_API::ALIGN_GetAlignmentNeeded(&this->is_needed_alignment);
    this->error_check();
    this->api_return_status = RSA_API::ALIGN_GetWarmupStatus(&this->is_warmed_up);
    this->error_check();
    printf("\ndevice alignment status >>>\n");
    if (this->is_needed_alignment == false)
    {
        printf("\tno alignment is needed\n");
    }
    else
    {
        printf("\talignment IS needed\n");
    }
    if (this->is_warmed_up == true)
    {
        printf("\twarm-up is complete\n");
    }
    else
    {
        printf("\twarm-up is NOT complete\n");
    }
}


////~~~~


/*
    public
    alignments may be needed during start-up or extended use
    the instance should call this method:
        - when starting the spectrum analyzer
        - after temperature changes
        - every 15 minutes of operation
    
    this function rejects calls if no device is connected
    the device is then stopped
    if the device is not warm, the program halts until it is
    aligment is ran, if needed
*/
void rsa306b::rsa_align()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("can't align, there is no device connected\n");
        #endif
        return;
    }
    this->rsa_stop();
    this->execute_alignment();
    this->execute_warm_up();
}


////~~~~


/*
    private
    alignment ensures general calibration
    for serious problems, send in to be recalibrated
*/
void rsa306b::execute_alignment()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->api_return_status = RSA_API::ALIGN_GetAlignmentNeeded(&this->is_needed_alignment);
    this->error_check();
    if (is_needed_alignment == true)
    {
        this->api_return_status = RSA_API::ALIGN_RunAlignment();
        this->error_check();
        this->is_needed_alignment = false;
    }
    #ifdef DEBUG_MIN
        printf("aligment complete\n");
    #endif
}


////~~~~


/*
    private
    the spectrum analyzers can take 30 minutes to warm up
    it is safe to get data if not completley warmed up
*/
void rsa306b::execute_warm_up()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    this->api_return_status = RSA_API::ALIGN_GetWarmupStatus(&this->is_warmed_up);
    this->error_check();
    if (this->is_warmed_up == false)
    {
        sleep(3);
        this->api_return_status = RSA_API::ALIGN_GetWarmupStatus(&this->is_warmed_up);
        this->error_check();
        if (this->is_warmed_up == false)
        {
            #ifdef DEBUG_MIN
                printf("the device will be warmed up soon...\n");
            #endif
        }
        this->is_warmed_up = true;
    }
    #ifdef DEBUG_MIN
        printf("warm-up complete ?\n");
    #endif
}


////////~~~~~~~~END>  rsa306b_class_ALIGN.cpp
