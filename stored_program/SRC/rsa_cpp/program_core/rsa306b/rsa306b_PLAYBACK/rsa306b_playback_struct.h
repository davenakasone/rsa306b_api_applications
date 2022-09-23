/*
    variables needed for the API group "PLAYBACK" 
        PLAYBACK_OpenDiskFile()
        PLAYBACK_GetReplayComplete()

    active :
    
    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    RSA_API enum *     :  <name>_select               // any non-anonymous API enums are ended with "select"
    RSA_API struct *   :  <name>_type                 // any non-anonymous API structs are ended with "type"

    the API can only use "*.r3f" files for playback
*/


#ifndef H_rsa306b_playback_struct
#define H_rsa306b_playback_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_playback_struct
{


// limiting constants
    const int START_PERCENT_MIN = 0;
    const int START_PERCENT_MAX = 99;
    const int STOP_PERCENT_MIN  = 1;
    const int STOP_PERCENT_MAX  = 100;
    const double SKIP_TIME_MIN  = 0.0;


/*
    PLAYBACK_OpenDiskFile()
        opens "*.r3f" file
        prepares system for playback, based on the parameters
        you don't even need hardware, use the API to analyze a valid file
            file_path_name ; where to find the "*.r3f" file, utility confirms this
            start_percent  ; how much is skipped, will also skip in loops
            stop_percent   ; how much is skipped, will also skip in loops
            skip_time      ; how much time to skip, for fast forwarding, max depends on length, rounds up ~73us ...use 0
            loop_at_end    ; if the file playback wraps around, true == oo loop, until stop signal, else false == stop at stop %
            emulate_real_time ; tries to match real time if true, false puts a heavy load on the system and reads every frame
        limited by :
            START_PERCENT_MIN
            START_PERCENT_MAX
            STOP_PERCENT_MIN
            STOP_PERCENT_MAX
            SKIP_TIME_MIN

*/
    char        file_path_name[BUF_E];
    const char* _FILE_PATH_NAME   = INIT_CHARP;           // DEFAULT

    int       start_percent;
    const int _START_PERCENT      = START_PERCENT_MIN;    // DEFAULT

    int       stop_percent;
    const int _STOP_PERCENT       = STOP_PERCENT_MAX;     // DEFAULT

    double       skip_time;
    const double _SKIP_TIME       = SKIP_TIME_MIN;        // DEFAULT

    bool       loop_at_end;
    const bool _LOOP_AT_END       = false;                // DEFAULT

    bool       emulate_real_time;
    const bool _EMULATE_REAL_TIME = false;                // DEFAULT


/*
    PLAYBACK_GetReplayComplete()
        is_complete ; true means playback is done, remember it will always be false in loop mode
*/
    bool       is_complete;
    const bool _IS_COMPLETE = false;    // DEFAULT


};
typedef struct rsa306b_playback_struct rsa306b_playback_struct;


#endif


////////~~~~~~~~END>  rsa306b_playback_struct.h
