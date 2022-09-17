/*
    debugging variables

    they are global

    already extern-ed into the header "de_bug.h"
*/


#include "de_bug.h"

#ifdef DE_BUG

    #ifdef DEBUGS_WILL_WRITE
        FILE* X_dfp = NULL;    // file pointer to manage writing to the debug log
    #endif

    #if (defined (DEBUG_MIN) || defined (DEBUG_MAX) || defined (DEBUG_CLI) || defined (DEBUG_CALL_CHECKS))
        char X_dstr[2*DEBUG_WIDTH];    // string to contain the current debug message, used as a holder
        char X_ddts[DEBUG_WIDTH];      // string to contain the debug date-time-stamp, also used as a helper
        clock_t X_dstart = clock();    // recording time marked as soon as program is loaded
    #endif

#endif


////////~~~~~~~~END>  de_bug.cpp
