/*
    implementation of the rsa306b_class
    using "ALIGN" function group of the API
    getters and setters for member variables
    includes two user-action function

        public:
            < 1 >  align_execute_alignment()
            < 2 >  align_print_all()
            < 3 >  align_get_is_warmed()
            < 4 >  align_get_need_alignment()

        private:
            < 1 >  _align_set_is_warmed()
            < 2 >  _align_set_need_alignment()
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    performs an alignment operation, usually works
        device must be connected
        device is stopped if running
        checks if alignment is needed
        executes alignment if needed
*/
void rsa306b::align_execute_alignment()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, alignments not possible\n");
        #endif
        return;
    }
    if (this->_device_is_running == true)
    {
        this->device_stop();
    }

    this->_align_set_need_alignment();
    if (this->_align_need_alignment == true)
    {
        this->_api_return_status = RSA_API::ALIGN_RunAlignment();
        this->_api_error_check();
        this->_align_set_need_alignment();
        if (this->_align_need_alignment == false)
        {
            #ifdef DEBUG_MIN
                printf("\n\talignment success\n");
            #endif
        }
        else
        {
            #ifdef DEBUG_MIN
                printf("\n\talignment failure\n");
            #endif
        }
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice was already aligned\n");
        #endif
        return;
    }
}


////~~~~


/*
    public < 2 >
    prints alignment conditions
*/
void rsa306b::align_print_all()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, alignments not possible\n");
        #endif
        return;
    }
    this->_align_set_is_warmed();
    this->_align_set_need_alignment();
    printf("\nALIGN information >>>\n");
    printf("\talignment is needed  :  %d\n", this->_align_need_alignment);
    printf("\tdevice is warmed up  :  %d\n", this->_align_is_warmed);
}


////~~~~


/*
    public < 3 >
    checks warm-up status
    returns result
*/
bool rsa306b::align_get_is_warmed()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, value as initialized\n");
        #endif
    }
    this->_align_set_is_warmed();
    return this->_align_is_warmed;
}


////~~~~


/*
    public < 4 >
    checks alignment status
    returns result
*/
bool rsa306b::align_get_need_alignment()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, value as initialized\n");
        #endif
    }
    this->_align_set_need_alignment();
    return this->_align_need_alignment;
}


////~~~~


/*
    private < 1 >
    checks warmup status
    sets "_align_is_warmed" accordingly
    don't worry about it too much, the device gets warm fast
*/
void rsa306b::_align_set_is_warmed()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, alignments not possible\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::ALIGN_GetWarmupStatus(
        &this->_align_is_warmed);
    this->_api_error_check();
}


////~~~~


/*
    private < 2 >
    checks aligment status
    sets "_align_need_alignment" accordingly
*/
void rsa306b::_align_set_need_alignment()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, alignments not possible\n");
        #endif
        return;
    }
    this->_api_return_status = RSA_API::ALIGN_GetAlignmentNeeded(
        &this->_align_need_alignment);
    this->_api_error_check();
}


////////~~~~~~~~END>  rsa306b_class_ALIGN.cpp
