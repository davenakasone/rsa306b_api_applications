/*
    designed to parse "*.r3f files"

    r3f_manager.cpp
        r3f_manager_class()
        ~r3f_manager_class()
    
    r3f_decode_printer.cpp
        decode_print()
        batch_decode_print()
    
    r3f_decode_writer.cpp
        decode_writer()
        batch_decode_writer()
    
    r3f_get.cpp
        _get_vars()
    
    r3f_loader.cpp
        load_file()
        _populate_header()
        _populate_data()

    r3f_init.cpp
        _init()

    r3f_helpers.cpp
        batch_load_file()
        _write_csv_adc()
        _write_csv_equalization()
    

*/

#ifndef H_r3f_manager_class
#define H_r3f_manager_class

#include "../common_utility/common_utility.h"
#include "r3f_manager_struct.h"
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


class r3f_manager_class
{
    public :

        common_utility cutil;       // public class instance, by composition, for "common utility" needs
        r3f_manager_struct vars;    // just a variable tap-point, if needed (changes are inert)

        r3f_manager_class();  
        ~r3f_manager_class();    

        // call to load "*.r3f" file and begin processing   (user only needs to call this, or the batch version)
        CODEZ load_file
        (
            const char* r3f_input,
            const char* output_parsed,
            const char* output_adc,
            const char* output_equalization
        );
        CODEZ batch_load_file
        (
            const char* r3f_input_directory,
            const char* output_directory,
            std::vector<std::string>& in_filez, 
            std::vector<std::string>& out_filez
        );

        // decoding, diagnostic tools to parse "*.r3f" files, byte-by-byte
        CODEZ decode_print
        (
            const char* r3f_file, 
            const long int start_byte, 
            const long int stop_byte
        );
        CODEZ batch_decode_print
        (
            const char* r3f_directory, 
            const long int start_byte, 
            const long int stop_byte, 
            std::vector<std::string>& filez
        );
        CODEZ decode_write
        (
            const char* r3f_file, 
            const char* decode_file, 
            const long int start_byte, 
            const long int stop_byte
        );
        CODEZ batch_decode_write
        (
            const char* r3f_directory, 
            const char* decode_directory, 
            const long int start_byte, 
            const long int stop_byte, 
            std::vector<std::string>& in_filez, 
            std::vector<std::string>& out_filez
        );
        
    private :
       
        r3f_manager_struct _vars;    // handler variables aligned to "*.r3f" file format
        char _helper[BUF_E];         // smaller string
        char _holder[BUF_F];         // larger string
        FILE* _fp_read;              // for reading provided "*.r3f" as input
        FILE* _fp_write;             // for writting results of a processed "*.r3f" file to output
        long int _bytes_in_file;     // total bytes in a file, found when first opening "*.r3f"
        long int _byte_index;        // assists processing functions to move position within "*.r3f" file

        CODEZ _init();                      // sets member variables to known values
        CODEZ _get_vars();                  // copies private struct into public struct
        CODEZ _populate_header();           // helps "load_file()"
        CODEZ _populate_data();             // helps "load_file()"
        CODEZ _write_csv_adc();             // write the ADC CSV for plotting
        CODEZ _write_csv_equalization();    // write the equalization CSV for plotting
};


#endif


////////~~~~~~~~END>  r3f_manager.h
