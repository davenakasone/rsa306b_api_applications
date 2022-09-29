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
    printf("\n%s()  ,  begin unit test # %d\n", 
        __func__, test_number);

    switch (test_number)
    {
        case (1)   : unit_test_1()   ; break;
        
        case (999) : task_999()      ; break;

        default    : unit_test_0()   ; break;
    }

    printf("\n%s()  ,  end of unit testing\n", __func__); 
}


#endif


////////~~~~~~~~END>  test_selector.cpp
