/*
    called after exiting "unit_test_X()"
        waits for user response
        clears stdout
        control returns to "test_selector()"
*/


#include "testz.h"


#ifdef UNIT_TESTING


    #ifdef WAIT_ENTER_CLEAR


        void wait_enter_clear
        (
            void
        )
        {
            char burner;

            (void)fflush(stdin);
            (void)fflush(stdout);
            (void)sleep(1); 
            
            (void)printf("\n\t\tpress any key to continue:  ");
            std::cin >> burner;
            
            (void)printf("clearing stdout...  %c", burner);
            (void)fflush(stdout);
            (void)fflush(stdin);
            (void)sleep(1);
            (void)system("clear");
            (void)sleep(1);
        }


    #endif


#endif


////////~~~~~~~~END>  wait_enter_clear.cpp
