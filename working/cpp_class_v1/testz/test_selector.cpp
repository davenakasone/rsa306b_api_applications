/*
    manages flow of unit test
    called from main()
*/

#include "unit_tests.h"


void test_selector(int test_number)
{
    printf("\n%s()  ,  begin unit test # %d\n", 
        __func__, test_number);

    switch (test_number)
    {
        case (1) :
            unit_test_1();
            break;
        default :
            unit_test_999();
    }

    printf("\n%s()  ,  end unit test # %d\n", 
        __func__, test_number);
}


////////~~~~~~~~END>  test_selector.cpp
