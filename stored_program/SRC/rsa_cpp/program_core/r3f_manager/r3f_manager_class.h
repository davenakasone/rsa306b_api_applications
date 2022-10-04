/*
    designed to parse "*.r3f files"
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


        common_utility     cutil;    // public class instance, by composition, for "common utility" needs
        r3f_manager_struct vars;     // variables that represent the "*.r3f" file, see r3f_manager_struct.h

        r3f_manager_class ();    // rs3_manager.cpp 
        ~r3f_manager_class();    // rs3_manager.cpp    
        CODEZ        clear();    // re-initialize the member variables, see r3f_manager.cpp

        // call to load "*.r3f" file and begin processing   (user only needs to call this, or the batch version)
        CODEZ load_file
        (
            const char* r3f_input,
            const char* output_parsed,
            const char* output_adc,
            const char* output_equalization,
            bool write_parsed,
            bool write_equalization,
            bool write_adc
        );
        CODEZ batch_process_files
        (
            const char* r3f_input_directory,
            const char* output_directory,
            std::vector<std::string>& input_files_v, 
            std::vector<std::string>& output_files_v,
            bool write_parsed,
            bool write_equalization,
            bool write_adc
        );
        

    private :
       

        r3f_manager_struct _vars;             // handler variables aligned to "*.r3f" file format
        char               _helper[BUF_E];    // smaller string
        char               _holder[BUF_F];    // larger string
        FILE*              _fp_read;          // for reading provided "*.r3f" as input
        FILE*              _fp_write;         // for writting results of a processed "*.r3f" file to output
        long int           _bytes_in_file;    // total bytes in a file, found when first opening "*.r3f"
        long int           _byte_index;       // assists processing functions to move position within "*.r3f" file

        CODEZ _init                                  ();    // sets member variables to known values
        CODEZ _copy_vars                             ();    // copies private struct into public struct
        CODEZ _populate_header(const bool write_parsed);    // helps "load_file()"
        CODEZ _populate_data  (const bool write_parsed);    // helps "load_file()"
        CODEZ _write_csv_adc                         ();    // write the ADC CSV for plotting
        CODEZ _write_csv_equalization                ();    // write the equalization CSV for plotting
};


#endif


////////~~~~~~~~END>  r3f_manager.h
