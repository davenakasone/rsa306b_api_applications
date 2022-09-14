/*

    "siq_common.cpp"
        siq_handler_class()
        ~siq_handler_class()
        unload_and_clear()
        get_file_byte_length()
        _verify_siq_extension()
        _prepare_siq_input()
        _conclude_siq_input()
        _prepare_any_output()
        _conclude_any_output()

    "siq_decode.cpp"
        decode_and_write()
        decode_and_print()

    "siq_error_codes.cpp"
        execution_success()
        _set_error_code()
        _check_error_code()

    "siq_init_copy.cpp"
        _init()
        _copy_vars()

    "siq_loader.cpp"
        load_file()
        _populate_header()
        _populate_data()

    "siq_printer()"
        print_header()
        print_data()
    
    "siq_write_csv.cpp"
        write_iq_to_csv()
        write_iq_to_csv_batch()
*/

#ifndef H_siq_manager_class
#define H_siq_manager_class


#include "siq_manager_struct.h"
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif

class siq_manager_class
{
    public :

        siq_manager_class();               // only constuctor used
        ~siq_manager_class();              // destructor
        struct siq_manager_struct vars;    // structured variables for parsing

        // diagnostic tools to parse "*.siq" files, byte-by-byte
        void decode_and_write(char* input_file, char* output_file, unsigned long int byte_start, unsigned long int byte_stop);    
        void decode_and_print(char* input_file, unsigned long int byte_start, unsigned long int byte_stop);                       
        
        // optional (no writting), initiates population of "vars" struct, user receives direct IQ data from file
        void load_file(char* input_file);    // contents of the *.siq file are accessable through class member variables

        // seperate IQ data and header data, ideal for obtaining "*.csv" from "*.siq" for further processing                                                                                         
        void write_iq_to_csv(char* input_file, char* output_file); 
        void write_iq_to_csv_batch(char* input_directory, char* output_directory);
        
        void print_header();                                             // called after loading a file for printing header fields
        void print_data(std::size_t idx_start, std::size_t idx_stop);    // called after loading a file for printing data block samples
        bool execution_success();                                        // user can call to confirm successful operation
        unsigned long int get_file_byte_length(char* input_file);        // provides size in bytes, of any file
        void unload_and_clear();                                         // re-initialize the class members to effectivley clear variables

    private :

        struct siq_manager_struct _vars;    // structured variables for parsing
        error_code_select _ec;              // tracks state of calls

        FILE* _fptr_read;
        FILE* _fptr_write;
        unsigned long int _byte_offset;
        unsigned long int _bytes_in_file;
        char _helper[BUF_E];
        char _holder[BUF_F];
        bool _file_loaded;

        // monitor return-error status while parsing
        void _set_error_code(error_code_select code);    
        void _check_error_code();

        // common helpers
        void _init();                                          // called to place all variables into a known state
        void _copy_vars();                                     // copies contents of private struct "_vars" to public struch "vars"
        void _verify_siq_extension(const char* input_file);    // verify that the user provided a "*.siq" file to parse  
        void _prepare_siq_input(char* input_file);             // opens a "*.siq" file for reading
        void _conclude_siq_input();                            // closes a "*.siq" file when reading is complete
        void _prepare_any_output(char* output_file);           // opens any file for text-writing
        void _conclude_any_output();                           // closes any file when text-writing is complete

        // for loading and parsing *.siq files           
        void _populate_header();    // helps "_load_file()" parse header
        void _populate_data();      // helps "_load_file()" parse data block
};


#endif


////////~~~~~~~~END>  siq_manager_class.h
