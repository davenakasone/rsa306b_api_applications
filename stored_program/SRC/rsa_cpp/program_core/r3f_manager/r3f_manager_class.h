/*
    "r3fc_public.cpp"
        r3f_manager_class()
        ~r3f_manager_class()
        get_bytes_in_file()
        time_split_begin()
        time_split_end()
        get_running_time()
        get_vars()
    
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
    
    "r3fc_plot_maker.cpp"
        prepare_plot_from_header()
        prepare_plot_from_iq()
        
    "r3fc_handle_adc.cpp"
        prepare_plot_from_adc()
        _adc_helper()
        _process_header_direct()
    
    //r3fc_past_present_adc_csv.cpp
    //    past_present_adc_csv()

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

#include "../common_utility/common_utility.h"
#include "r3f_manager_struct.h"    // <stdint.h>, <float.h>
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


class r3f_manager_class
{
    public :

        common_utility cutil;       // public class instance, by composition, for "common utility" needs
        r3f_manager_struct vars;    // just a variable tap-point, if needed (changes are inert)

        r3f_manager_class();     // constructor
        ~r3f_manager_class();    // destructor
        

        // CODEZ get_bytes_in_file();    // returns total bytes in file
        CODEZ load_vars();             // copy of parsing variables, if needed 
        
        // diagnostic tools to parse "*.r3f" files, byte-by-byte
        CODEZ decode_and_write(char* r3f_file, char* output_file, unsigned long int byte_start, unsigned long int byte_stop);    
        CODEZ decode_and_print(char* r3f_file, unsigned long int byte_start, unsigned long int byte_stop);  

        // optional (no writting), contents of the "*.r3f" file are loaded into "vars"
        CODEZ load_file(char* r3f_file); 

        // // CPU clock
        //     void time_split_begin();      // records start of CPU time split
        //     double time_split_end();      // measures CPU time split and returns result
        //     double get_running_time();    // returns CPU seconds since instance created

        // // call to process "*.r3f" file
        // void file_process(
        //     const char* r3f_input_path_file_name,
        //     const char* r3f_output_path_file_name,
        //     bool print_while_processing);

        // // aligns "char" and "int8" types to each byte of input file
        // void file_decode(                    
        //     const char* r3f_input_path_file_name,
        //     const char* decode_path_file_name, 
        //     long int decode_start_byte, 
        //     long int decode_stop_byte,
        //     bool print_while_decoding);    

        // further processing
        CODEZ prepar_plot_batch(const char* r3f_path, const char* csv_path, bool from_header, bool from_iq, bool from_adc);
        CODEZ prepare_plot_from_header(const char* r3f_file, const char* output_file);    // frequecny: amplitude and phase
        CODEZ prepare_plot_from_iq    (const char* r3f_file, const char* output_file);    // time : I and Q
        CODEZ prepare_plot_from_adc   (const char* r3f_file, const char* output_file);    // raw ADC, input file found automatically
        //void past_present_adc_csv(const char* input_file_path_name, const char* output_file_path_name); // time series ADC
        
    private :
        
        //int _return_status;             // communication between member functions
        //const int _CALL_FAILURE = 3;    // error in member function
        //const int _CALL_SUCCESS = 4;    // member function executed correctly
       
        bool _file_loaded;
        char _helper[BUF_E];            // smaller string
        char _holder[BUF_F];            // larger string
        //FILE* _fptr_decode;             // for writting decoded "*r3f" information to output
        FILE* _fptr_read;               // for reading provided "*.r3f" as input
        FILE* _fptr_write;              // for writting results of a processed "*.r3f" file to output
        long int _bytes_in_file;        // total bytes in a file, found when first opening "*.r3f"
        long int _byte_index;           // assists processing functions to move position within "*.r3f" file
        std::vector<std::string> batch_r3f;    // to store file-path-name of "*.r3f" files found in target directory

        // bool _time_split_is_marked;     // validates time split request
        // clock_t _cpu_start;             // maintians time the object was created
        // clock_t _cpu_mark;              // the trailing time split marker
        // clock_t _cpu_now;               // the leading time marker

        r3f_manager_struct _vars;       // handler variables aligned to "*.r3f" file format

        CODEZ _initialize();    // sets member variables to known values
        CODEZ _copy_vars();                                                
        //int _verify_r3f_extension(const char* r3f_input_path_file_name);    // enforces processing of only "*.r3f" files
        //int _find_input_file_size();                                        // determines bytes in the input file
        CODEZ _process_header();                  // helps "file_process()"
        CODEZ _process_data();                    // helps "file_process()"
        CODEZ _store_field();                     // helps all processing functions
        CODEZ _adc_helper(const char* input_fpn, const char* output_fpn);    // assits in preparing the ADC raw plot
        CODEZ _process_header_direct();                                      // processing of header with no output generation,
};


#endif


////////~~~~~~~~END>  r3f_manager.h
