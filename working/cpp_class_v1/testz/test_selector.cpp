/*
    manages flow of unit test
    called from main()
*/

#include "unit_tests.h"


void test_selector
(
    int test_number
)
{
    printf("\n%s()  ,  begin unit test # %d\n", 
        __func__, test_number);

    switch (test_number)
    {
        case (1)    : unit_test_1()  ; break;
        case (2)    : unit_test_2()  ; break;
        case (3)    : unit_test_3()  ; break;
        case (4)    : unit_test_4()  ; break;
        case (5)    : unit_test_5()  ; break;
        case (6)    : unit_test_6()  ; break;
        case (7)    : unit_test_7()  ; break;

        case (997)  : vvv_997()      ; break;
        case (998)  : vvv_998()      ; break;
        case (996)  : vvv_996()      ; break;
        
        default   : unit_test_999(); break;
    }

    printf("\n%s()  ,  end of unit testing\n", __func__); 
}


////////~~~~~~~~END>  test_selector.cpp
