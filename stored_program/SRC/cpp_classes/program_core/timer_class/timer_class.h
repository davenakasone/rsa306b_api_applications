/*
    timer to supplement the API timing capbility
    the API does not monitor the CPU clock
    use an instance of this object as another reference for timing considerations

    "clock_t" is processing time required, not wall clock
    "struct timespec" has seconds and nano seconds, it is a decent wall clock
        but don't trust the nano second resolution
    
    monitor sub routines, processing times, etc
    provides running times and time splits for both CPU and wall-clock
    add whatever you need, it is just a utility
*/

#ifndef H_timer_class
#define H_timer_class


#include "../control/resourcez.h"
#ifdef DE_BUG
    #include "../control/de_bug/de_bug.h"
#endif


class timer_class
{
    public :

        timer_class();
        ~timer_class();

        // user action
        void time_split_start();                    // updates "trail" to mark beginning of a time split
        void time_split_stop();                     // interval is stopped and duration is calculated
        void print_time_split(bool new_lines);      // message with timesplit to stdout
        void print_running_time(bool new_lines);    // message with total running time to stdout
        void print_both();                          // message with timesplit and running time to stdout

        // get variable of interest
        double get_time_split();
        double get_time_split_w();
        double get_running_time();
        double get_running_time_w();
        char* return_split_string();

    private :

        void _timer_init();
        void _set_running_time();
        void _set_running_time_w();

        bool _split_is_marked;                
        const double _SPLIT_FAIL = -11.11;    
        char _helper[BUF_E];

        // CPU timing
        double _running;                      
        double _split;                        
        clock_t _begin;                       
        clock_t _lead;                        
        double _trail;                       
        
        // wall-clock timing "w"
        double _w_running;                    
        double _w_split;                      
        struct timespec _w_begin;            
        struct timespec _w_lead;                      
        double _w_trail;      
};


#endif 


////////~~~~~~~~END>  cpu_timer_class.h
