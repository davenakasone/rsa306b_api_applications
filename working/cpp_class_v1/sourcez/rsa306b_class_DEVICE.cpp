/*
    implementation of the rsa306b_class
    using "DEVICE" function group of the API

        public:
            < 1 >  device_connect()
            < 2 >  device_disconnect()
            < 3 >  device_prepare_run()
            < 4 >  device_print_all()
            < 5 >  device_reset()
            < 6 >  device_run()
            < 7 >  device_start_frame_transfer()
            < 8 >  device_stop()
        
        private:
            # none
*/

#include "../includez/rsa306b_class.h"


/*
    public < 1 >
    first searches for suitable device to connect to
        there must be only one deveice connected
    this is the only function that should make "_device_is_connected == true"
    this is the only function that should assign "_device_id = <searched_ID>"
    basic checks and alignments updated when connection is successful
*/
void rsa306b::device_connect()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == true)
    {
        #ifdef DEBUG_MIN
            printf("\n\tthe device is already connected\n");
        #endif
        return;
    }
    int devices_found;
    int device_ids[RSA_API::DEVSRCH_MAX_NUM_DEVICES];
    char device_serials[RSA_API::DEVSRCH_MAX_NUM_DEVICES]
        [RSA_API::DEVSRCH_SERIAL_MAX_STRLEN];
    char device_types[RSA_API::DEVSRCH_MAX_NUM_DEVICES]
        [RSA_API::DEVSRCH_TYPE_MAX_STRLEN];

    this->_api_return_status = RSA_API::DEVICE_Search(
        &devices_found, 
        device_ids, 
        device_serials, 
        device_types);
    this->_api_error_check();

    if (devices_found == 1)
    {
        this->_device_set_id(device_ids[0]);
        this->_api_return_status = RSA_API::DEVICE_Connect(
            this->_device_id);
        this->_api_error_check();

        if (this->_api_return_status != RSA_API::noError) 
        {
            #ifdef DEBUG_MIN
                printf("\n\tconnection failure\n");
            #endif
            return;
        }
        #ifdef DEBUG_MIN
            printf("\n\t^^^ CONNECTED ^^^\n");
        #endif
        this->_device_set_is_connected(true);       // call once per connected session
        this->_device_set_info_type();
        this->_device_set_is_over_temperature();    
        this->_device_set_is_running();             
        this->_reftime_set_begin_type();            // call once per connected session
        this->_align_set_is_warmed();
        this->align_execute_alignment();
        this->_config_init();                       // call once per connected session
    }
    else if (devices_found > 1)
    {
        #ifdef DEBUG_MIN
            printf("\n\ttoo many devices, only connect one\n");
        #endif
    }
    else
    {
        #ifdef DEBUG_MIN
            printf("\n\tno devices were found\n");
        #endif
    }
}

////~~~~


/*
    public < 2 >
    disconnects device if connected
    should only be called by the constructor
        or if a hard reset is needed
*/
void rsa306b::device_disconnect()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == true)
    {
        this->device_stop();
        this->_api_return_status = RSA_API::DEVICE_Disconnect();
        this->_api_error_check();
        //sleep(1);
        //this->_init_member_variables();
    }
}


////~~~~

/*
    public < 3 >
    makes system ready to start streaming data
    good with "device_start_frame_transfer"
    data transfer not initiated, only prepares
*/
void rsa306b::device_prepare_run()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, can't prepare for run\n");
        #endif
        return;
    }

    this->device_stop();
    this->_api_return_status = RSA_API::DEVICE_PrepareForRun();
    this->_api_error_check();
    this->_device_set_is_running();
    #ifdef DEBUG_MIN
        printf("\n\tprepared device to run\n");
    #endif
}


////~~~~


/*
    public < 4 >
    call when device is connected, or no query is possible
    when called with a connected device
    basic info is printed to stdout
*/
void rsa306b::device_print_all()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, nothing to print\n");
        #endif
        return;
    }
    this->_device_set_info_type();
    this->_device_set_is_over_temperature();
    this->_device_set_is_running();

    printf("\nDEVICE information >>>\n");
    printf("\tAPI Version                :  %s\n", this->_device_info_type.apiVersion);
    printf("\tDevice ID                  :  %d\n", this->_device_id);
    printf("\tFirm Ware Version          :  %s\n", this->_device_info_type.fwVersion);
    printf("\tFPGA Version               :  %s\n", this->_device_info_type.fpgaVersion);
    printf("\tHardware Version           :  %s\n", this->_device_info_type.hwVersion);
    printf("\tNomenclature               :  %s\n", this->_device_info_type.nomenclature);
    printf("\tSerial Number              :  %s\n", this->_device_info_type.serialNum);
    printf("\tis connected               :  %d\n", this->_device_is_connected);
    printf("\tis running                 :  %d\n", this->_device_is_running);
    printf("\tis over temperature limit  :  %d\n", this->_device_is_over_temperature);
}


////~~~~


/*
    public < 5 >
    stops running device, if needed
    resets the device, if needed 
        uses blocking until reset is achieved
    you probably should not call this function, ever
        try doing a disconnect --> connect instead
*/
void rsa306b::device_reset()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, can't reset\n");
        #endif
        return;
    }

    this->device_stop();
    this->_api_return_status = RSA_API::DEVICE_Reset(this->_device_id);
    this->_api_error_check();

    /*
    if (this->_api_return_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\treset FAILURE\n");
        #endif
        while (this->_api_return_status != RSA_API::noError)
        {
            sleep(3);
            this->_api_return_status = RSA_API::DEVICE_Reset(this->_device_id);
        }
    }
    */
    #ifdef DEBUG_MIN
        printf("\n\treset complete\n");
    #endif
}


////~~~~


/*
    public < 6 >
    allows the device to run, if connected
    immediately starts data streaming without waiting for GO signal
*/
void rsa306b::device_run()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, can't run\n");
        #endif
        return;
    }

    this->_device_set_is_running();
    
    if (this->_device_is_running == true)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice was already running\n");
        #endif
        return;
    }
    else
    {
        this->_api_return_status = RSA_API::DEVICE_Run();
        this->_api_error_check();
        this->_device_set_is_running();
    }
    #ifdef DEBUG_MIN
        printf("\n\trunning device\n");
    #endif
}

////~~~~


/*
    public < 7 >
    trigger for data aquisition after calling "device_prepare_run()"
    if stopped, the system is automatically placed in the run state
    data stream begins if here are no errors
*/
void rsa306b::device_start_frame_transfer()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, can't start frame transfer\n");
        #endif
        return;
    }
    
    this->_api_return_status = RSA_API::DEVICE_StartFrameTransfer();
    this->_api_error_check();
    this->_device_set_is_running();
    #ifdef DEBUG_MIN
        printf("\n\tstarted frame transfer\n");
    #endif
}


////~~~~


/*
    public < 8 >
    stops the device, if connected
    must be called for changes that effect measurement
*/
void rsa306b::device_stop()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_device_is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected, nothing to stop\n");
        #endif
        return;
    }
    
    this->_device_set_is_running();

    if (this->_device_is_running == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice was already stopped\n");
        #endif
        return;
    }
    else
    {
        this->_api_return_status = RSA_API::DEVICE_Stop();
        this->_api_error_check();
        this->_device_set_is_running();
    }
    #ifdef DEBUG_MIN
        printf("\n\tstopped device\n");
    #endif
}


////////~~~~~~~~END>  rsa306b_class_DEVICE.cpp
