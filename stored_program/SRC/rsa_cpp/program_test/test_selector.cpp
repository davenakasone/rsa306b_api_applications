/*
    manages flow of unit test
    called from main()
*/


#include "testz.h"


#ifdef UNIT_TESTING


void test_selector
(
    int test_number
)
{
#ifdef WAIT_ENTER_CLEAR
    flush_io();
#endif

    printf("\n%s()  ,  begin unit test # %d\n", 
        __func__, test_number);

    switch (test_number)
    {
        case (1)   : unit_test_1()   ; break;
        case (2)   : unit_test_2()   ; break;
        case (3)   : unit_test_3()   ; break;
        case (4)   : unit_test_4()   ; break;
        case (5)   : unit_test_5()   ; break;
        case (6)   : unit_test_6()   ; break;
        case (7)   : unit_test_7()   ; break;
        case (8)   : unit_test_8()   ; break;
        case (9)   : unit_test_9()   ; break;
        case (10)  : unit_test_10()  ; break;
        case (11)  : unit_test_11()  ; break;
        case (12)  : unit_test_12()  ; break;
        case (13)  : unit_test_13()  ; break;
        case (14)  : unit_test_14()  ; break;
        
        case (994) : task_994()      ; break;
        case (995) : task_995()      ; break;
        case (996) : task_996()      ; break;
        case (997) : task_997()      ; break;
        case (998) : task_998()      ; break;
        case (999) : task_999()      ; break;

        default    : unit_test_0()   ; break;
    }

    printf("\n%s()  ,  end of unit testing\n", __func__); 
}


#endif


////////~~~~~~~~END>  test_selector.cpp
