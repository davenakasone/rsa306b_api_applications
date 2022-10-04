/*
    designed to parse "*.siq files"
*/

#ifndef H_siq_manager_class
#define H_siq_manager_class

#include "../common_utility/common_utility.h"
#include "siq_manager_struct.h"
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


class siq_manager_class
{
    public :

        common_utility     cutil;    // public class instance, by composition, for "common utility" needs
        siq_manager_struct vars;     // structured variables for parsing

        siq_manager_class ();    // see siq_manager.cpp
        ~siq_manager_class();    // see siq_manager.cpp                     
        CODEZ clear       ();    // re-initialize the class member variables, see siq_manager.cpp


        // call to load "*.siq" file and begin processing   (user only needs to call this, or the batch version)
        CODEZ load_file
        (
            const char* siq_input,
            const char* output_parsed,
            const char* output_iq,
            bool write_parsed,
            bool write_iq
        );
        CODEZ batch_process_files
        (
            const char* siq_input_directory,
            const char* output_directory,
            std::vector<std::string>& input_files_v, 
            std::vector<std::string>& output_files_v,
            bool write_parsed,
            bool write_iq
        );


    private :


        siq_manager_struct _vars;             // structured variables for parsing
        char               _helper[BUF_E];    // smaller string
        char               _holder[BUF_F];    // larger string
        FILE*              _fp_read;          // for reading provided "*.siq" as input
        FILE*              _fp_write;         // for writting results of a processed "*.siq" file to output
        long int           _bytes_in_file;    // total bytes in a file, found when first opening "*.siq"
        long int           _byte_index;       // assists processing functions to move position within "*.r3f" file

        CODEZ _init           ();    // sets member variables to known values, called at start of "load_file()"
        CODEZ _copy_vars      ();    // copies private struct into public struct, called at end of "load_file()"
        CODEZ _populate_header();    // helps "load_file()"
        CODEZ _populate_data  ();    // helps "load_file()"
        CODEZ _write_csv_iq   ();    // write the IQ CSV for plotting, "load_file()" calls if requested
        CODEZ _write_parsed   ();    // write the SIQ files into readable parsed output, "load_file()" calls if requested
};


#endif


////////~~~~~~~~END>  siq_manager_class.h
