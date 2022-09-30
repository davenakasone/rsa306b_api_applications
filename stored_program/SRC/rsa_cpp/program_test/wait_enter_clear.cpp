/*
    called after exiting "unit_test_X()"
        waits for user response
        clears stdout
        control returns to "test_selector()"
*/


#include "testz.h"


#ifdef UNIT_TESTING

    
    #ifdef WAIT_ENTER_CLEAR


        void flush_io()
        {
            (void)fflush(stdin);
            (void)fflush(stdout);
            (void)usleep(100);
            (void)system("clear");
            (void)usleep(100);
        }


        void wait_enter_clear()
        {
            char burner[BUF_C];
            (void)printf("\n\t\tpress any key to continue:  ");
            std::cin >> burner;
            (void)printf("clearing stdout...  %s", burner);
            usleep(100000);
            flush_io();
        }


    #endif


#endif


////////~~~~~~~~END>  wait_enter_clear.cpp
