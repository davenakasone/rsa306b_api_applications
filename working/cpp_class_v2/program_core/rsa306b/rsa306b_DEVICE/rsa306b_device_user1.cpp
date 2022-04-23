/*
    API group "DEVICE", user functions 1 of 2

    public :
        < 1 >  device_connect()
        < 2 >  device_disconnect()
        < 3 >  device_run()
        < 4 >  device_stop()
        < 5 >  device_reset()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
    user must call this function to use the spectrum analyzer
    the API can only mange one connected device per computer
    device search begins, device must succesfully connect
    information is taken fromt he device after connection
*/
void rsa306b_class::device_connect()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->_vars.device.is_connected == true)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice already connected\n");
        #endif
        return;
    }
    int devices_found;
    int device_ids[RSA_API::DEVSRCH_MAX_NUM_DEVICES];
    char device_serials[RSA_API::DEVSRCH_MAX_NUM_DEVICES]
        [RSA_API::DEVSRCH_SERIAL_MAX_STRLEN];
    char device_types[RSA_API::DEVSRCH_MAX_NUM_DEVICES]
        [RSA_API::DEVSRCH_TYPE_MAX_STRLEN];

    this->_vars.gp.api_status = 
        RSA_API::DEVICE_Search(
            &devices_found, 
            device_ids, 
            device_serials, 
            device_types);
    this->_gp_confirm_api_status();
    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\tsearch failure\n");
        #endif
        return;
    }
    if (devices_found > 1)
    {
        #ifdef DEBUG_MIN
            printf("\n\ttoo many devices\n");
        #endif
        return;
    }
    if (devices_found < 1)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno devices found\n");
        #endif
        return;
    }

    this->_vars.device.id = device_ids[0];
    this->_device_copy_id();
    this->_vars.gp.api_status = 
        RSA_API::DEVICE_Connect(this->_vars.device.id);
    this->_gp_confirm_api_status();
    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\tconnection failure\n");
        #endif
        return;
    }
    this->_vars.device.is_connected = true;    // this is very important
    this->_device_copy_is_connected();
    #ifdef DEBUG_MIN
        printf("\n\t^^^ CONNECTED ^^^\n");
    #endif
    this->_device_get_vars();
    //
    ///
    ////
}


////~~~~


/*
    < 2 > public
    the device is disconnected, iff it is connected
    member variables are initialzied
*/
void rsa306b_class::device_disconnect()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice already disconnected\n");
        #endif
        return;
    }
    this->device_stop();
    this->_vars.gp.api_status = RSA_API::DEVICE_Disconnect();
    this->_gp_confirm_api_status();
    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdisconnection failure\n");
        #endif
        return;
    }
    this->_init_everything();
}


////~~~~


/*
    < 3 > public
    device is put into the run state, if connected
    if error occurs, run state is never activated
    running initiates data transfer
*/
void rsa306b_class::device_run()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    if (this->_vars.device.is_running == true)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice already running\n");
        #endif
        return;
    }

    this->_vars.gp.api_status = RSA_API::DEVICE_Run();
    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\terror running device\n");
        #endif
        return;
    }
    this->_device_get_is_running();
}


////~~~~


/*
    < 4 > public
    the run state is deactivated, if device is connected and running
    errors stopping the device force a return
*/
void rsa306b_class::device_stop()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->_device_get_is_running();
    if (this->_vars.device.is_running == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tdevice was already stopped\n");
        #endif
        return;
    }
    this->_vars.gp.api_status = RSA_API::DEVICE_Stop();
    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\terror stopping device\n");
        #endif
        return;
    }
    this->_device_get_is_running();
}


////~~~~


/*
    < 5 > public
    use sparingly, resets device
    most likely will crash program if resources are not released
    might want to rethink the prompt
*/
void rsa306b_class::device_reset()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    if (this->_vars.device.is_connected == false)
    {
        #ifdef DEBUG_MIN
            printf("\n\tno device connected\n");
        #endif
        return;
    }
    this->device_stop();
    this->_vars.gp.api_status = RSA_API::DEVICE_Reset(this->_vars.device.id);
    this->_gp_confirm_api_status();
    if (this->_vars.gp.api_status != RSA_API::noError)
    {
        #ifdef DEBUG_MIN
            printf("\n\treset failure\n");
        #endif
        return;
    }
    this->_init_everything();
    #ifdef DEBUG_MIN
        printf("\n\treset success\n");
    #endif
    prompt:
    int discard = 7;
    printf("enter: [ 1 ] to continue  ,  [ 0 ] to quit\n");
    std::cin >> discard;
    if (discard != 0 && discard != 1) {goto prompt;}
    if (discard == 0) {exit(0);}
    if (discard == 1)
    {
        sleep(10);
        this->device_connect();
    }
}


////////~~~~~~~~END>  rsa306b_device_user1.cpp
