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
        siq_manager_class();
        ~siq_manager_class();
        int return_status;  // maps to _return_status
        siq_manager_struct vars;    // structured variables for parsing

        void decode_and_write
        (
            char* input_file, 
            char* output_file,
            unsigned long int byte_start,
            unsigned long int byte_stop
        );                                  
        void decode_and_print
        (
            char* input_file,
            unsigned long int byte_start,
            unsigned long int byte_stop
        );

        void load_file(char* input_file); // initiates population of "vars" struct, optional (no writting)
        void write_iq_header(char* input_file, char* output_file); // write the header section (if any), to an output file
        void write_iq_data_to_csv(char* input_file, char* output_file); // write the data block to an output file

    private :
        siq_manager_struct _vars;    // structured variables for parsing
        FILE* _fptr_read;
        FILE* _fptr_write;
        long int _byte_offset;
        long int _bytes_in_file;
        char _helper[BUF_E];
        char _holder[BUF_F];
        int _return_status;

        void _init();
        void _set_return_status(int current_status);  // set return status and display errors (if any)
        void _load_file(char* input_file);    // populates "_vars" struct, copies results to "vars" struct (when successful)
        void _populate_header();         // helps "_load_file()" parse header
        void _populate_data(); // helps "_load_file()" parse data block

};


////////~~~~~~~~END>  siq_manager_class.h