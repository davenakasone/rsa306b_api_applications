/*
    the 2 global variables for debugging

    + debugging functions

    only applies if debugging activated
*/


#include "../resourcez.h"


#ifdef DE_BUG
    
    #ifndef H_de_bug
    #define H_de_bug

    #ifdef DEBUGS_WILL_WRITE
        extern FILE* X_dfp;
    #endif
    #if (defined (DEBUG_MIN) || defined (DEBUG_MAX) || defined (DEBUG_CLI) || defined (DEBUG_CALL_CHECKS))
        extern char X_dstr[2*DEBUG_WIDTH];
        extern char X_ddts[DEBUG_WIDTH];
        extern clock_t X_dstart;
    #endif

    void debug_init();                      // prepare program for debugging feedback
    void debug_stop();                      // end the debug session
    char* debug_dts();                      // places current date-time-stamp in X_ddts
    void debug_record(bool force_print);    // called after updating the debug string, manages the macros

    #endif

#endif


////////~~~~~~~~END>  de_bug.h