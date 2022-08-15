/*
    "siq_public.cpp"
        siq_handler_class()
        ~siq_handler_class()
    "siq_private.cpp"
        _set_return_status()
    
*/

#include "siq_manager_struct.h"


class siq_manager_class
{
    public :
        siq_manager_class();        // only constuctor used
        ~siq_manager_class();       // destructor
        siq_manager_struct vars;    // structured variables for parsing

        int decode_and_write(char* input_file, char* output_file, unsigned long int byte_start, unsigned long int byte_stop);    // diagnostic tool to decode and write "*.siq" file byte by byte    
        int decode_and_print(char* input_file, unsigned long int byte_start, unsigned long int byte_stop);                       // diagnostic tool to decode and print "*.siq" file byte by byte
        int load_file(char* input_file);                                                                                         // initiates population of "vars" struct, optional (no writting)
        int write_iq_to_csv(char* input_file, char* output_file);                                                                // write the data block to an output file to csv

    private :
        siq_manager_struct _vars;    // structured variables for parsing
        FILE* _fptr_read;
        FILE* _fptr_write;
        unsigned long int _byte_offset;
        unsigned long int _bytes_in_file;
        char _helper[BUF_E];
        char _holder[BUF_F];
        int _return_status;

        void _init();                                                // called to place all variables into a known state
        void _set_return_status(int current_status);                 // set return status and display errors (if any)
        void _load_file(char* input_file);                           // populates "_vars" struct, copies results to "vars" struct (when successful)
        unsigned long int get_file_byte_length(char* input_file);    // provides size in bytes of the input file
        void _populate_header();                                     // helps "_load_file()" parse header
        void _populate_data();                                       // helps "_load_file()" parse data block
};


////////~~~~~~~~END>  siq_manager_class.h