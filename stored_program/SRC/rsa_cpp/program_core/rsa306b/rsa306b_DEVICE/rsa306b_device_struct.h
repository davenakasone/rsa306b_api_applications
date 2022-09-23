/*
    variables needed for the API group "DEVICE" 
        DEVICE_Connect(), DEVICE_Disconnect()
        DEVICE_GetEnable()
        DEVICE_GetErrorString()
        DEVICE_GetInfo()
        DEVICE_GetOverTemperatureStatus()
        DEVICE_PrepareForRun()
        DEVICE_Reset()
        DEVICE_Run()
        DEVICE_Search()
        DEVICE_StartFrameTransfer()
        DEVICE_Stop()

    active :
        int                  id
        bool                 is_connected
        bool                 is_running
        char                 api_status_message[BUF_E]
        RSA_API::DEVICE_INFO info_type       
        bool                 is_over_temperature
        int                  event_id
        bool                 event_occured
        uint64_t             event_timestamp


    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"
*/

#ifndef H_rsa306b_device_struct
#define H_rsa306b_device_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_device_struct
{


// NO limiting constants


/*
    DEVICE_Connect(), DEVICE_Disconnect()
        the device can't acquire data unless Connect() is called, every API function needs a connected device
        "id" is found after the search, only 1 spectrum analyzer can connect per machine
        "is_connected" is not needed for the API, but good to track connect/disconnect calls
        when connected, DEVICE_Search() is called, and is the only time this function should be called
*/
    int       id;
    const int _ID = INIT_INT;    // DEFAULT

    bool       is_connected;    
    const bool _IS_CONNECTED = false;    // DEFAULT, this is the most important initializer value in the entire program
    

/*
    DEVICE_GetEnable()
        the device can only produce data (send measurements to your program) when in the run state
        if device is not running, data acquistion should not be attempted
        "true" means that the device is in the run state
*/
    bool       is_running;
    const bool _IS_RUNNING = false;    // DEFAULT


/*
    DEVICE_GetErrorString()
        use the current API status code 
        gets the corresponding message as a "const char*"
*/
    char        api_status_message[BUF_E];
    const char* _API_STATUS_MESSAGE = INIT_CHARP;


/*
    DEVICE_GetInfo(), calls through -->
        DEVICE_GetFPGAVersion()
        DEVICE_GetFWVersion()
        DEVICE_GetHWVersion()
        DEVICE_Nomenclature()
        Device_GetSerialNumber()
        Device_GetAPIVersion()
            <major>.<minor>.<revision>
*/
    RSA_API::DEVICE_INFO info_type;                               // struct with 6 strings
    const char*          _INFO_TYPE_apiVersion   = INIT_CHARP;    // DEFAULT
    const char*          _INFO_TYPE_fpgaVersion  = INIT_CHARP;    // DEFAULT
    const char*          _INFO_TYPE_fwVersion    = INIT_CHARP;    // DEFAULT
    const char*          _INFO_TYPE_hwVersion    = INIT_CHARP;    // DEFAULT
    const char*          _INFO_TYPE_nomenclature = INIT_CHARP;    // DEFAULT
    const char*          _INFO_TYPE_serialNum    = INIT_CHARP;    // DEFAULT
    

/*
    DEVICE_PrepareForRun()
        internal tasks to put system in a known run stated execute
        device is ready to stream data, but does not initiate a data transfer
        good for playback mode, lets other parts of application get ready to receive data
        use it to prepare a trigger, then "DEVICE_StartFrameTransfer()" will actually trigger
*/


/*
    DEVICE_GetOverTemperatureStatus()
        use to monitor the RSA, especially in a hot area
        "true" means device is too hot, and you should shut it down to avoid something bad
*/
    bool       is_over_temperature;   
    const bool _IS_OVER_TEMPERATURE = false;    // DEFAULT


/*
    DEVICE_Reset()
        this usually crashes the program because of how libusb is used
        good to call for the blinking green light (data transfer hung, device is frozen)
*/


/*
    DEVICE_Run()
        this will force the data acquisition to occur
*/
    

/*    
    DEVICE_Search()
        this search requires the client to provide the storage buffers
        the class manages this in the "device_connect()" method
        don't try the other search functions, they are for windows, matlab, and forms of savagery
*/


/*
    DEVICE_StartFrameTransfer()
        typically used as the trigger to start data streaming, after calling "DEVICE_PrepareForRun()"
        if the RSA is stopped, it will be placed into the run state
        no data or setting are changed; if no errors are detected, streaming begins after calling
*/


/*
    DEVICE_Stop()
        calling this ends the data acquisition
        must be called if settings are changed (value that affects signal is changed)
*/


/*
    DEVICE_GetEventStatus()
        RSA must be running when calling this (only time RSA updates this)
        DEVEVENT_OVERRANGE: ADC input signal exceeded allowable range, probably have clipping
        DEVEVENT_TRIGGER  : need to configure the trigger in hardware to use this
        DEVEVENT_1PPS...not for RSA306b
        timestamp is most recent transfer frame where event was detected
        event_id        ;  see the RSA_API enum "DEVEVENT_OVERRANGE = 0, DEVEVENT_TRIGGER = 1, DEVEVENT_1PPS = 2"
        event_occured   ;  true indicates that event occured, else false
        event_timestamp ;  holds event time stamp, only valid if "event_occured" == true
*/
    int       event_id;
    const int _EVENT_ID = INIT_INT;                  // DEFAULT

    bool       event_occured;
    const bool _EVENT_OCCURED = false;                // DEFAULT

    uint64_t       event_timestamp;
    const uint64_t _EVENT_TIMESTAMP = INIT_UINT64;    // DEFAULT   


}; 
typedef struct rsa306b_device_struct rsa306b_device_struct;


#endif


////////~~~~~~~~END>  rsa306b_device_struct.h
   