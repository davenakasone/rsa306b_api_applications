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

    Class source files, "./program_core/rsa306/rsa306_GP/"
        - rsa306b_class_cons_dest.cpp
            rsa306b()
            ~rsa306b()
        - rsa306b_gp_confirm.cpp
            _gp_confirm_api_status()
            _gp_confirm_error_code()
            _gp_confirm_call_status()
        - rsa306b_gp_copy.cpp
            get_everything()
            _gp_copy_vars()
            _gp_copy_vars_error_code()
            _gp_copy_vars_helper()
            _gp_copy_vars_holder()
            _gp_copy_vars_call_status()
            _gp_copy_vars_api_status()
        - rsa306b_gp_init.cpp
            _init_everything()
            _gp_init()
        - rsa306b_gp_print.cpp
            print_everything()
            print_constants()
            print_gp()
        - rsa306b_struct.h
            struct rsa306b_struct

    Purpose of this class:
        - automate API by abstracting mandatory procedures
        - enforce correct use of the API 
        - foundation for implementing future spectrum analyzer API interface needs

    Summary of this class:
        - does not own any specific capibility
        - only coordinates subordinate classes, using composition

    Other classes, included by composition:
        - API "DEVICE" function group  

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
        

    private : 

        rsa306b_struct _vars;    // private variables
    
    // general purpose
        void _init_everything();    // initialize all class variables
        void _gp_init();            // initialize the "general purpose" variables
        // monitor the program
        void _gp_confirm_api_status();     // called to check error conditions after API function calls
        void _gp_confirm_error_code();     // gets the API error code based on return status
        void _gp_confirm_call_status();    // called to check error conditions in the class
        // copiers, private --> public
        void _gp_copy_vars();
        void _gp_copy_vars_error_code();
        void _gp_copy_vars_helper();
        void _gp_copy_vars_holder();
        void _gp_copy_vars_call_status();
        void _gp_copy_vars_api_status();
        
        
};


#endif


////////~~~~~~~~END>  rsa306b.h
