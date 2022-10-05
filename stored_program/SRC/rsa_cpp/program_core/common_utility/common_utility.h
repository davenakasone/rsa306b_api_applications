/*
    common untilities composed into the primary classes
    the composition allows:
        - common functions for common tasks are only writen 1 time (in this class)
    that is the purpose of this class, and all instances that are made

    inheritence and virtualization were considered
    this should be easy to change (if needed), more easy than changing the a similar function several times
    this class can also be used independently
    not too many variables are used

    Source:

        "cu_common_utility.cpp"
            common_utility()
            ~common_utility()
            clear()

        "cu_codez.cpp"
            get_status_code_string()
            get_status_code_number()
            get_status_code()
            report_status_code()
            codez_checker()
            codez_messages()

        "cu_exe_1.cpp"
            exe_strcpy()
            exe_remove()

        "cu_help_1.cpp"
            h_find_bytes_in_file()
            h_match_extension()
        
        "cu_batch_decode.cpp"
            batch_decode_print())
            batch_decode_write()

        "cu_decode.cpp"
            decode_print())
            decode_write()

        "timing.cpp"
            timer_split_start()
            timer_split_stop()
            timer_print_split()
            timer_print_running()
            timer_print_both()
            timer_get_split_cpu()
            timer_get_split_wall()
            timer_get_running_cpu()
            timer_get_running_wall()
            _timer_init()
            _timer_set_running_cpu()
            _timer_set_running_wall()
        
        "cu_wchar_2_char.cpp"
            whcar_2_char()
            _wchar_2_char_std()
            _wchar_2_char_unq()

    Notes:
        "clock_t" is processing time required, not wall clock
        "struct timespec" has seconds and nano seconds, it is a decent wall clock
        don't trust timers to provide high precision
        clock() will repeat about every 72 minutes, so adjust accordingly if program goes longer
*/

#ifndef H_common_utility
#define H_common_utility


#include "../control/resourcez.h"
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


constexpr char _TIMER_FORMAT_RUNNING[BUF_D] = "{{{timer}}}  total running  (seconds)  >>>  CPU:  %14.6lf  ,  wall:  %14.6lf  {{{timer}}}";
constexpr char _TIMER_FORMAT_SPLIT[BUF_D]   = "{{{timer}}}  split duration (seconds)  >>>  CPU:  %14.6lf  ,  wall:  %14.6lf  {{{timer}}}";


class common_utility
{
    public :

// core
        common_utility  ();    // destructor
        ~common_utility ();    // constructor
        CODEZ      clear();                    // re-initialize the object instance
        char helper[BUF_E];                    // for the user's convenience
        char holder[BUF_F];                    // for the user's convenience
        std::vector<std::string> filez_in;     // for the user's convenience, store results from file operations
        std::vector<std::string> filez_out;    // for the user's convenience, store results from file operations

// status code management
        const char* get_status_code_string();                                                  // getter for "_status_code" message
        int         get_status_code_number();                                                  // getter for "_status_code", casted to "int"
        CODEZ       get_status_code       ();                                                  // getter for "_status_code"
        CODEZ       report_status_code    (CODEZ current_code);                                // sets then gets "_status_code"
        CODEZ       codez_checker         (const CODEZ* codez_list, const int codez_count);    // evaluate batch of codez
        const char* codez_messages        (CODEZ lookup);                                      // lookup a status code and get char*

// string handling
        CODEZ wchar_2_char(char* destination, const wchar_t* source, bool use_std);    // convert wchar_t* to char*

// execute a specific library function + verify
        CODEZ exe_strcpy (char* destination, const char* source); 
        CODEZ exe_remove (const char* file_to_delete);

// getting file information
        CODEZ find_bytes_in_file       (const char* file_path_name, long& result);
        bool  extension_matched        (const char* file_path_name, const char* extension);
        CODEZ find_files_with_extension(const char* directory, const char* extension, std::vector<std::string>& filez, bool include_directory);
        
        
        
        
        
        
        CODEZ h_change_extension     (char* file_path_name, const char* new_extension);
        CODEZ h_batch_change_redirect(const char* in_directory, const char* in_extension, const char* out_directory, const char* out_extension, std::vector<std::string>& new_filez);
        CODEZ h_insert_and_change_extension(char* file_path_name, const char* to_insert, const char* new_extension);
        CODEZ h_switch_directory(char* file_to_change, const char* new_directory);
        CODEZ h_batch_redir_insert_ext_change(const char* in_directory, const char* in_extension, const char* out_directory, const char* inserts, const char* out_extension, std::vector<std::string>& new_filez);
        CODEZ h_delete_files_in_dir(const char* directory);

// decoding, diagnostic tools to parse raw files, byte-by-byte + batch
        CODEZ decode_print
        (
            const char*    raw_file_path_name, 
            const long int start_byte, 
            const long int stop_byte
        );
        CODEZ batch_decode_print
        (
            const char*               raw_directory,
            const char*               raw_extension, 
            const long int            start_byte, 
            const long int            stop_byte, 
            std::vector<std::string>& raw_files_v
        );
        CODEZ decode_write
        (
            const char*    raw_file_path_name, 
            const char*    decoded_file_path_name,
            const long int start_byte, 
            const long int stop_byte
        );
        CODEZ batch_decode_write
        (
            const char*               raw_directory,
            const char*               raw_extension, 
            const char*               decoded_directory,
            const char*               decoded_insert,
            const char*               decoded_extenstion,
            const long int            start_byte, 
            const long int            stop_byte, 
            std::vector<std::string>& raw_files_v, 
            std::vector<std::string>& decoded_files_v
        );

// timer, both CPU and wall-clock + date-timestamp as a string
        CODEZ  timer_split_start     ();                                          // updates "trail" to mark beginning of a time split
        CODEZ  timer_split_stop      ();                                          // interval is stopped and duration is calculated
        CODEZ  timer_print_split     (int new_lines_begin, int new_lines_end);    // message with timesplit to stdout
        CODEZ  timer_print_running   (int new_lines_begin, int new_lines_end);    // message with total running time to stdout
        CODEZ  timer_print_both      (int new_lines_begin, int new_lines_end);    // message with timesplit and running time to stdout
        double timer_get_split_cpu   ();                                          // updates "_split_cpu"
        double timer_get_split_wall  ();                                          // updates "_split_wall"
        double timer_get_running_cpu ();                                          // updates "_running_cpu"
        double timer_get_running_wall();                                          // updates "_running_wall"
        CODEZ  make_date_timestamp                                                // place desired time into formated "dts" string
        (
            const time_t* seconds,    // call with 0 to use current time
            const uint64_t nanos,     // call with 0 to use current time
            char* dts_string          // must be allocated
        );

// acqstatus bitchecking, the API has 6 bitcheck points in 5 API groups
        CODEZ ifstream_acq_status
        (
            const uint32_t acq_status, 
            const uint32_t valid_bitmask, 
            char results[IFSTREAM_BITCHECKS][BUF_D]
        );
        //CODEZ dpx_acq_status     (const uint32_t acq_status, const uint32_t valid_bitmask, char results[DPX_BITCHECKS][BUF_D]     );
        CODEZ iqblk_acq_status   
        (
            const uint32_t acq_status, 
            const uint32_t valid_bitmask, 
            char results[IQBLK_BITCHECKS][BUF_D]   
        );
        CODEZ iqstream_acq_status
        (
            const uint32_t acq_status, 
            const uint32_t valid_bitmask, 
            char results[IQSTREAM_BITCHECKS][BUF_D]
        );
        CODEZ spectrum_acq_status
        (
            const uint16_t acq_status, 
            const uint16_t valid_bitmask, 
            char results[SPECTRUM_BITCHECKS][BUF_D]
        );


    private :


        CODEZ _status_code;     // status code, reflects most recent call        
        char _worker[BUF_E];    // string for internal use

// wchar_t* and char* conversion
        CODEZ _wchar_2_char_std(char* destination, const wchar_t* source);    // string converter, wchar_t* to char*, using std::                        
        CODEZ _wchar_2_char_unq(char* destination, const wchar_t* source);    // string converter,  wchar_t* to char*, using something else

// timers
        CODEZ _timer_init();
        // timer, CPU
        CODEZ   _timer_set_running_cpu();    // calculates difference of current time and object creation time
        clock_t _begin_cpu;                  // marks the beginning time of the object's creation                    
        clock_t _lead_cpu;                   // used to mark the end of a split, will be used in a calculation
        double  _running_cpu;                // holds the difference of current time and object creation time , after calculation                     
        double  _split_cpu;                  // holds the difference of end of split and beginning of split, after calculation                  
        double  _trail_cpu;                  // used to mark the beginnng of a split, will be used in a calculation  
        // timer, wall-clock "w"
        CODEZ  _timer_set_running_wall();    // calculates difference of current time and object creation time
        struct timespec _begin_wall;         // marks the beginning time of the object's creation            
        struct timespec _lead_wall;          // used to mark the end of a split, will be used in a calculation
        double _running_wall;                // holds the difference of current time and object creation time , after calculation      
        double _split_wall;                  // holds the difference of end of split and beginning of split, after calculation                     
        double _trail_wall;                  // used to mark the beginnng of a split, will be used in a calculation 
};


#endif


////////~~~~~~~~END>  common_utility.h
