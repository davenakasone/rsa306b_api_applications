/*
    unit test # 1

    goals:
        - constructor initializes and connects
        - the general purpose section is operating correctly
        - public constants are accessed and printed
        - the destructor deallocates the instance and properly disconnects
*/

#include "unit_tests.h"


void unit_test_1 (void)
{
    printf("\n%s()  ,  testing the general purpose section of the class\n", __func__);
    {
        int apiRet = -2;
        int clsRet = -3;
        char apiStr[256];
        rsa306b my_rsa;    // constructor is called

        apiRet = my_rsa.get_api_return_status();  
        clsRet = my_rsa.get_gp_return_status();
        my_rsa.get_api_return_status_string(apiStr);

        printf("\nget 'general purpose' variables >>>\n");
        printf("\tclass api return status         :  %d\n", apiRet);
        printf("\tclass api return status string  :  %s\n", apiStr);
        printf("\tclass gp return status    :  %d\n", clsRet); 

        printf("\nclass constants >>>\n");
        printf("\tCALL_SUCCESS            :  %d\n", my_rsa.CALL_SUCCESS);
        printf("\tCALL_FAILURE            :  %d\n", my_rsa.CALL_FAILURE);
        printf("\tINIT_CHAR               :  %c\n", my_rsa.INIT_CHAR);
        printf("\tINIT_DOUBLE             :  %lf\n", my_rsa.INIT_DOUBLE);
        printf("\tINIT_INT                :  %d\n", my_rsa.INIT_INT);
        printf("\tINIT_STR                :  %s\n", my_rsa.INIT_STR);
        printf("\tFREQUENCY_MIN_HZ        :  %lf\n", my_rsa.FREQUENCY_MIN_HZ);
        printf("\tFREQUENCY_MAX_HZ        :  %lf\n", my_rsa.FREQUENCY_MAX_HZ);
        printf("\tEXTERNAL_FREQUENCY      :  %lf\n", my_rsa.EXTERNAL_FREQUENCY);
        printf("\tREFERENCE_LEVEL_MIN_DB  :  %lf\n", my_rsa.REFERENCE_LEVEL_MIN_DB);
        printf("\tREFERENCE_LEVEL_MAX_DB  :  %lf\n", my_rsa.REFERENCE_LEVEL_MAX_DB);
        printf("\tSPAN_MAX_HZ             :  %lf\n", my_rsa.SPAN_MAX_HZ);
        printf("\tSPAN_MIN_HZ             :  %lf\n", my_rsa.SPAN_MIN_HZ);
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_1.cpp
