/*
    called after exiting "unit_test_X()"
        waits for user response
        clears stdout
        control returns to "test_selector()"
*/


#include "testz.h"


#ifdef WAIT_ENTER_CLEAR


    void wait_enter_clear
    (
        void
    )
    {
        fflush(stdin);
        fflush(stdout);
        sleep(1); 
        char burner;
        printf("\n\t\tpress any key to continue:  ");
        std::cin >> burner;
        printf("clearing stdout...  %c", burner);
        fflush(stdout);
        fflush(stdin);
        sleep(1);
        system("clear");
        sleep(1);
    }


#endif


////////~~~~~~~~END>  wait_enter_clear.cpp
