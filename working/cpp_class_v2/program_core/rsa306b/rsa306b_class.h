/*
    this is the top-level class of the program
    subordinate classes (included by composition) not designed to be used independently
    this class uses a provided API to interface with the RSA-306B Spectrum Analyzer
    Tektronix requires 2 shared objects (dynamic libraries) to be linked and the RSA_API.h header
    the API is designed to run on a 64-bit Linux OS using an intel processor
    only one instance of this class can connect to the spectrum analyzer
    for most use cases, only one instance of this class is required

    see documentation for general details
    see the test section for examples 



    Class source files, 
    
        "./program_core/rsa306b"
            - rsa306b_struct.h
                struct rsa306b_struct
            - rsa306b_class.h
                class rsa306b_class

        "./program_core/rsa306b/rsa306_GP/"
            - rsa306b_gp_struct.h
                struct rsa306b_gp_struct
            - rsa306b_class_cons_dest.cpp
                rsa306b_class()
                ~rsa306b_class()
            - rsa306b_gp_confirm.cpp
                _gp_confirm_api_status()
                _gp_confirm_call_status()
            - rsa306b_gp_copy.cpp
                get_everything()
                _gp_copy_vars()
                _gp_copy_helper()
                _gp_copy_holder()
                _gp_copy_call_status()
                _gp_copy_api_status()
            - rsa306b_gp_init.cpp
                _init_everything()
                _gp_init()
            - rsa306b_gp_print.cpp
                print_everything()
                print_constants()
                print_gp()

        "./program_core/rsa306b/rsa306b_CONST"
            - rsa306b_constants_class.h
                class rsa306b_constants_class
            - rsa306b_constants_constructor.cpp
                rsa306b_constants_class()
                ~rsa306b_constants_class()
        
        "./program_core/rsa306b/rsa306_ALIGN"
            - rsa306b_align_struct.h
                struct rsa306b_align_struct.h
            - rsa306b_align_print_init.cpp
                print_align()
                _align_init()
            - rsa306b_align_get_copy.cpp
                _align_get_vars()       
                _align_get_is_needed()
                _align_get_is_warmed()
                _align_copy_vars()
                _align_copy_is_needed()
                _align_copy_is_warmed()
            - rsa306b_align_user.cpp
                align_run()
                align_check_is_needed()
                align_check_is_warmed()

        "./program_core/rsa306b/rsa306_DEVICE/"
            - rsa306b_device_struct.h
                struct rsa306b_device_struct.h
            - rsa306b_device_print_init.cpp
                print_device()
                _device_init()
            - rsa306b_device_copy.cpp
                _device_copy_vars()
                _device_copy_is_connected()
                _device_copy_is_over_temperature()
                _device_copy_is_running()
                _device_copy_event_occured()
                _device_copy_error_string()
                _device_copy_id()
                _device_copy_event_id()
                _device_copy_info_type()
                _device_copy_event_timestamp()
            - rsa306b_device_get.cpp
                _device_get_vars()
                _device_get_is_running()
                _device_get_error_string()
                _device_get_info_type()
                _device_get_is_over_temperature()
                _device_get_event()
            - rsa306b_device_user1.cpp
                device_connect()
                device_disconnect()
                device_run()
                device_stop()
                device_reset()
            - rsa306b_device_user2.cpp
                device_check_run_state()
                device_check_temperature()
                device_check_event()
                device_prepare_for_run()
                device_start_frame_transfer()


    Purpose of this class:
        - automate API by abstracting mandatory procedures
        - enforce correct use of the API 
        - foundation for implementing future spectrum analyzer API interface needs

    TODO:
        # clock_t CPU timer class
        # bring in the "*.r3f" class
        # bring in the "*.sig" class
        # bring in the spectrogram handler
        # DEBUG logger .txt
        # helper classes by composition
        # keep building and testing the API function groups
        # time series, spectrogram, and other user requests
        # worker thread, request thread --> mutex control
        # DPX
        # IFSTREAM
        # IQBLK
        # IQSTREAM
        # PLAYBACK
*/

#ifndef H_rsa306b_class
#define H_rsa306b_class


#include "../control/resourcez.h"
#include "rsa306b_struct.h"


class rsa306b_class
{
    public :

        rsa306b_struct vars;    // public variables

    // general purpose
        rsa306b_class();            // constructor
        ~rsa306b_class();           // destructor
        void get_everything();      // updates user's variable struct
        void print_everything();    // prints all variables, using the private struct
        void print_constants();     // prints the constant variables of the class
        void print_gp();            // prints the "general purpose" variables, using the private struct
    
    // API group "ALIGN"
        void print_align();              // prints the "ALIGN" variables to stdout, using the private struct
        void align_check_is_needed();    // see if the spectrum analyzer needs to be aligned
        void align_check_is_warmed();    // see if the spectrum analyser is warmed-up
        void align_run();                // execute the device alignment procedure

    // API group "DEVICE"
        void print_device();                   // prints the "DEVICE" variables to stdout, using the private struct
        void device_connect();                 // searches and connects to a device, must call to use spectum analyzer
        void device_disconnect();              // disconnect from the spectrum analyzer
        void device_run();                     // the spectrum analyzer runs, configuration should have been applied
        void device_stop();                    // stop aquiring data
        void device_reset();                   // disconnects, makes spectrum analyzer restart, use sparingly
        void device_check_run_state();         // query run state of the spectrum analyzer
        void device_check_temperature();       // see if the spectrum analyzer it too hot
        void device_check_event();             // determine if an event occurred {0: ADC overange, 1: trigger}
        void device_prepare_for_run();         // make the device ready to run / trigger
        void device_start_frame_transfer();    // initiates run, data transfer begins

        

    private : 

        rsa306b_struct _vars;    // private variables
    
    // general purpose
        void _init_everything();    // initialize all class variables
        void _gp_init();            // initialize the "general purpose" variables
        // monitor the program
        void _gp_confirm_api_status();     // called to check error conditions after API function calls     
        void _gp_confirm_call_status();    // called to check error conditions in the class
        // copiers, private --> public
        void _gp_copy_vars();
        void _gp_copy_helper();
        void _gp_copy_holder();
        void _gp_copy_call_status();
        void _gp_copy_api_status();
    
    // API group "ALIGN"
        void _align_init();
        // copiers, private --> public
        void _align_copy_vars();
        void _align_copy_is_needed();
        void _align_copy_is_warmed();
        // getters, API is used
        void _align_get_vars();         // calls all of the API getters
        void _align_get_is_needed();    // query "alignment is needed", with API
        void _align_get_is_warmed();    // query "device is warmed-up", with API

    // API group "DEVICE"
        void _device_init();
        // copiers, private --> public
        void _device_copy_vars();
        void _device_copy_is_connected();
        void _device_copy_is_over_temperature();
        void _device_copy_is_running();
        void _device_copy_event_occured();
        void _device_copy_error_string();
        void _device_copy_id();
        void _device_copy_event_id();
        void _device_copy_info_type();
        void _device_copy_event_timestamp();
        // getters, API is used
        void _device_get_vars();                   // calls all of the API getters
        void _device_get_is_running();             // query the run state
        void _device_get_error_string();           // gets the API error code based on return status
        void _device_get_info_type();              // fill strings with device information
        void _device_get_is_over_temperature();    // query temerature warning
        void _device_get_event();                  // query an event of interest
};


#endif


////////~~~~~~~~END>  rsa306b.h
