/*
    basis for starting and stopping debugging

    < 1 >  debug_init()
    < 2 >  debug_stop()
    < 3 >  debug_dts()
    < 4 >  debug_record()
*/
#include "de_bug.h"
#ifdef DE_BUG


/*
    < 1 >
    initializes the debugging resources
    the static bool locks out any call attempt after the first

    designed to be placed in an object's constructor
    first object to initialize calls this function to:
        - open debug file (if writing is enabled)
        - initialize the debug variables
*/
void debug_init()
{
    static int objects_constructed = 0;
    objects_constructed++;
    
    #ifdef DEBUGS_WILL_PRINT
        if (objects_constructed == ACTIVE_OBJECTS)
        {
            (void)printf("\n\tall [ %d ] object instances are allocated\n", 
                ACTIVE_OBJECTS);
        }
    #endif

    static bool was_initialized = false;   // initiallay false
    if (was_initialized == true)
    {
        return;
    }
    was_initialized = true;     // after first call, always true, other calls are rejected
    
    #ifdef DEBUGS_WILL_WRITE    // file pointer remains open until destructors are called
        if (debug_dts() == NULL)
        {
            (void)printf("\n\tfailed to get date-time-stamp\n");
            return;
        }
        (void)snprintf(X_dstr, sizeof(X_dstr), "%s%sdebug.txt",
            DEBUG_FILEPATH,
            X_ddts);
        X_dfp = fopen(X_dstr, "w");
        if (X_dfp == NULL)
        {
            (void)printf("\n\tfailed to open debug log:  %s\n",
                X_dstr);
            return;
        }
        else
        {
            (void)printf("%s\n", X_dstr);
        }
        (void)snprintf(X_dstr, sizeof(X_dstr), "LOG OPEN %s\n\n", X_ddts);
        (void)fputs(X_dstr, X_dfp);
    #endif
}


////~~~~


/*
    < 2 >
    concludes debugging, only needed if writting is enabled
    last destructor activated calls
*/
void debug_stop()
{
    static int objects_destroyed = 0;
    objects_destroyed++;

    if (objects_destroyed != ACTIVE_OBJECTS)
    {
        return;
    }
    // last instance destroyed gets to close down the debugger

    #ifdef DEBUGS_WILL_PRINT
        (void)printf("\n\tall [ %d ] object instances are deallocated\n", 
            ACTIVE_OBJECTS);
    #endif
    #ifdef DEBUGS_WILL_WRITE
        if (X_dfp == NULL)
        {
            (void)printf("\n\tthe debug file was never opened\n");
            return;
        }
        if (debug_dts() == NULL)
        {
            (void)printf("\n\tfailed to get date-time-stamp\n");
        }
        (void)snprintf(X_dstr, sizeof(X_dstr), "\nLOG CLOSED %s\n", X_ddts);
        (void)fputs(X_dstr, X_dfp);
        (void)fclose(X_dfp);
        X_dfp = NULL;
    #endif
}


////~~~~


/*
    < 3 >
    anything with a char* allocated can get the DTS
    returned as char* for convienicne
*/
char* debug_dts()
{
    if (X_ddts == NULL)
    {
        (void)printf("\n\tdid not allocate %s\n", GET_NAME(X_ddts));
        return NULL;
    }
    (void)memset(X_ddts, '\0', DEBUG_WIDTH);

    struct tm * tm_ptr = NULL;
    time_t current;
    (void)time(&current);
    tm_ptr = localtime(&current);

    if (tm_ptr == NULL)
    {    
        (void)printf("\n\terror in <time.h>\n");
        return NULL;
    }
    (void)strftime(X_ddts, sizeof(X_ddts)-1,
        "_%Y_%m_%d_%a_%H_%M_%S_%Z__", tm_ptr);
    return X_ddts;
}


////~~~~


/*
    < 4 >
    caller should update the debug string "X_ddstr"
    function prints / records the result
*/
void debug_record(bool force_print)
{
    if (X_dstr[0] == '\0')
    {
        return; // empty string
    }
    
    clock_t t_now  = clock();
    double seconds = (static_cast<double>(t_now) - static_cast<double>(X_dstart)) /
        static_cast<double>(CLOCKS_PER_SEC);     
    
    char temp[3*DEBUG_WIDTH];
    (void)snprintf(temp, sizeof(temp), "[ %15.5lf ]  %s",
        seconds,
        X_dstr);

    #ifdef DEBUGS_WILL_PRINT
        (void)printf("%s", temp);
    #endif
    #ifdef DEBUGS_WILL_WRITE
        (void)fputs(temp, X_dfp);
        if (force_print == true)
        {
            (void)printf("%s", temp);
        }
    #endif

    (void)memset(X_dstr, '\0', sizeof(X_dstr));
    (void)memset(X_ddts, '\0', sizeof(X_ddts));
}


#endif


////////~~~~~~~~END>  debug_functions.cpp
