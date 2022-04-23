/*
    timer to supplement the API timing capbility
    the API does not monitor the CPU clock
    use an instance of this object as another reference for timing considerations

    "processing time" required, not wall clock
*/

#include "../control/resourcez.h"


class cpu_timer_class
{
    public :

        cpu_timer_class();
        ~cpu_timer_class();

        // user action
        void time_split_start();     // updates "trail" to mark beginning of a time split
        void time_split_stop();      // interval is stopped and duration is calculated
        void print_time_split();     // message with timesplit to stdout
        void print_running_time();    // message with total running time to stdout

        // getters
        double get_time_split();
        double get_running_time();
    
    private :

        bool _split_is_marked;                // tracks if user properly initiated a time split request
        clock_t _begin;                       // marks time object was created
        clock_t _lead;                        // set to current time, always ahead of "trail"
        clock_t _trail;                       // marks a past time, always behind "lead"
        double _running;                      // CPU time converted to seconds, current - begin
        double _split;                        // CPU time converted to seconds, current - trail
        double _temp;                         // helper
        const double _SPLIT_FAIL = -11.11;    // returned when state is unknown

        void _timer_init();    // initializes the timer
};


////////~~~~~~~~END>  cpu_timer_class.h
