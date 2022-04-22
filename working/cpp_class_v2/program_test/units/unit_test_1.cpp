/*
    unit test # 1, "general purpose" section

    goals:
        - constructor initializes and connects
        - the "general purpose" section is operating correctly
        - public constants are accessed and printed
        - the destructor deallocates the instance and properly disconnects
*/

#include "../testz.h"


void unit_test_1 (void)
{
    printf("\n%s()  ,  testing the 'general purpose' section of the class\n", __func__);
    {
       
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_1.cpp
