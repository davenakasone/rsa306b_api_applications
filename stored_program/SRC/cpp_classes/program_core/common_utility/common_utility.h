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
        
        "cu_codez.cpp"
            get_code_string()
            get_code_number()
            _report_status()

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
            wchar_2_char()

    Notes:
        "clock_t" is processing time required, not wall clock
        "struct timespec" has seconds and nano seconds, it is a decent wall clock
        don't trust timers to provide high precision
        clock() will repeat about every 72 minutes, so adjust accordingly if program goes longer
*/

#ifndef H_common_utility
#define H_common_utility


#include "../control/resourcez.h"
#include "../control/codez.h"
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


constexpr char _TIMER_FORMAT_RUNNING[BUF_D] = "{{{timer}}}  total running  (seconds)  >>>  CPU:  %14.6lf  ,  wall:  %14.6lf  {{{timer}}}";
constexpr char _TIMER_FORMAT_SPLIT[BUF_D]   = "{{{timer}}}  split duration (seconds)  >>>  CPU:  %14.6lf  ,  wall:  %14.6lf  {{{timer}}}";


class common_utility
{
    public :
        common_utility();                        // destructor
        ~common_utility();                       // constructor
        const char* get_status_code_string();    // returns string with message describing current status code
        int         get_status_code_number();    // returns current value of status code, casted to "int"

        // timer, both CPU and wall-clock
        CODEZ timer_split_start     ();                                          // updates "trail" to mark beginning of a time split
        CODEZ timer_split_stop      ();                                          // interval is stopped and duration is calculated
        CODEZ timer_print_split     (int new_lines_begin, int new_lines_end);    // message with timesplit to stdout
        CODEZ timer_print_running   (int new_lines_begin, int new_lines_end);    // message with total running time to stdout
        CODEZ timer_print_both      (int new_lines_begin, int new_lines_end);    // message with timesplit and running time to stdout
        CODEZ timer_get_split_cpu   (double& c_split);                           // updates "_split_cpu"
        CODEZ timer_get_split_wall  (double& w_split);                           // updates "_split_wall"
        CODEZ timer_get_running_cpu (double& c_run);                             // updates "_running_cpu"
        CODEZ timer_get_running_wall(double& w_run);                             // updates "_running_wall"

        // string tools
        CODEZ wchar_2_char(const wchar_t* source, char* destination);    // string converter,  wchar_t* to char*

////~~~~


    private :

        CODEZ _status_code;                               // status code, usually from most recent call        
        CODEZ _report_status_code(CODEZ current_code);    // tool to track and update "_status_code" 

    // timer
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
