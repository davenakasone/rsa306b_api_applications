/*
    timer to supplement the API timing capbility
    the API does not monitor the CPU clock
    use an instance of this object as another reference for timing considerations

    "clock_t" is processing time required, not wall clock
    "struct timespec" has seconds and nano seconds, it is a decent wall clock
        but don't trust the nano second resolution
*/

#include "../control/resourcez.h"


class cpu_timer_class
{
    public :

        cpu_timer_class();
        ~cpu_timer_class();

        // user action
        void time_split_start();      // updates "trail" to mark beginning of a time split
        void time_split_stop();       // interval is stopped and duration is calculated
        void print_time_split();      // message with timesplit to stdout
        void print_running_time();    // message with total running time to stdout

        // get variable of interest
        double get_time_split();
        double get_time_split_w();
        double get_running_time();
        double get_running_time_w();
    
    private :

        void _timer_init();    // initializes the timer

        bool _split_is_marked;                
        const double _SPLIT_FAIL = -11.11;    

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


////////~~~~~~~~END>  cpu_timer_class.h
