/*
    "r3fc_public.cpp"
        r3f_manager_class()
        ~r3f_manager_class()
        get_bytes_in_file()
        time_split_begin()
        time_split_end()
        get_running_time()
        get_members()
    
    "r3fc_private.cpp"
        _verify_r3f_extension()
        _find_file_size()
        _initialize()

    "r3fc_file_process.cpp"
        file_process()
        _process_header()
        _process_data()
        _store_field()

    "r3fc_file_decode.cpp"
        file_decode()


    this object is made for "*.r3f" files
    it will extract the IF data and place it into an output file
    data processing is also possbile

    adjust as needed
    "*.r3a" and "*.r3h" files are undesirable (for now)

    commonly used techniques:

        int fseek(FILE *stream, long int offset, int whence)
            int whence == SEEK_SET, go to the beginning of the file, resets EOF // call often
            int whence == SEEK_CUR, set the file pointer to the offset position
            int whence == SEEK_END, set the file pointer to EOF
        
        size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)

        long int ftell(FILE *stream)

        FILE *fopen(const char *filename, const char *mode)

        int fclose(FILE *stream)

        int snprintf ( char * s, size_t n, const char * format, ... );

        int fputs(const char *str, FILE *stream)

        not even going to try, catch, throw file not found, just going to halt program
        ...need a file management capability
*/


#ifndef H_r3f_manager_class
#define H_r3f_manager_class


#include <cmath>
#include <queue>
#include <stack>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "r3f_manager_struct.h"    // <stdint.h>, <float.h>

//#define DEBUG_CLI 1776    // print callstack to stdout while program executes
#define DEBUG_MIN 1787    // print only essential information to stdout

#define BUF_HELPER 256
#define BUF_HOLDER 512


class r3f_manager_class
{
    public :

        r3f_manager_class();           // constructor
        ~r3f_manager_class();          // destructor
        r3f_manager_struct members;    // just a variable tap-point, if needed (changes are inert)

        long int get_bytes_in_file();                  // returns total bytes in file
        void get_members(r3f_manager_struct* sptr);    // copy of parsing variables, if needed 
        
        // CPU clock
            void time_split_begin();      // records start of CPU time split
            double time_split_end();      // measures CPU time split and returns result
            double get_running_time();    // returns CPU seconds since instance created

        // call to process "*.r3f" file
        void file_process(
            const char* r3f_input_path_file_name,
            const char* r3f_output_path_file_name,
            bool print_while_processing);

        // aligns "char" and "int8" types to each byte of input file
        void file_decode(                    
            const char* r3f_input_path_file_name,
            const char* decode_path_file_name, 
            long int decode_start_byte, 
            long int decode_stop_byte,
            bool print_while_decoding);    

        // further processing
        void prepare_plot_from_header(const char* output_file);                          // frequecny: amplitude and phase
        void prepare_plot_from_data(const char* input_file, const char* output_file);    // time : I and Q
    

    private :
        
        int _return_status;             // communication between member functions
        const int _CALL_FAILURE = 3;    // error in member function
        const int _CALL_SUCCESS = 4;    // member function executed correctly
        const char _BLOCK_SEPERATOR[BUF_HELPER/2] = "------------------------------------------------------------------------------------------";
        
        char _helper[BUF_HELPER];       // smaller string
        char _holder[BUF_HOLDER];       // larger string
        FILE* _fptr_decode;             // for writting decoded "*r3f" information to output
        FILE* _fptr_read;               // for reading provided "*.r3f" as input
        FILE* _fptr_write;              // for writting results of a processed "*.r3f" file to output
        long int _bytes_in_file;        // total bytes in a file, found when first opening "*.r3f"
        long int _byte_index;           // assists processing functions to move position within "*.r3f" file

        bool _time_split_is_marked;     // validates time split request
        clock_t _cpu_start;             // maintians time the object was created
        clock_t _cpu_mark;              // the trailing time split marker
        clock_t _cpu_now;               // the leading time marker

        r3f_manager_struct _members;    // handler variables aligned to "*.r3f" file format

        void _initialize();                                                 // sets member variables to known values
        int _verify_r3f_extension(const char* r3f_input_path_file_name);    // enforces processing of only "*.r3f" files
        int _find_input_file_size();                                        // determines bytes in the input file
        void _process_header(bool print_while_processing);                  // helps "file_process()"
        void _process_data(bool print_while_processing);                    // helps "file_process()"
        void _store_field(bool print_while_processing);                     // helps all processing functions
};


#endif


////////~~~~~~~~END>  r3f_manager.h
