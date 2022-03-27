/*
    unit test # 1, "general purpose" section

    goals:
        - constructor initializes and connects
        - the "general purpose" section is operating correctly
        - public constants are accessed and printed
        - the destructor deallocates the instance and properly disconnects
*/

#include "unit_tests.h"


void unit_test_1 (void)
{
    printf("\n%s()  ,  testing the 'general purpose' section of the class\n", __func__);
    {
        int apiRet = -2;
        int clsRet = -3;
        char apiStr[256];
        rsa306b rsa;    // constructor is called

        apiRet = rsa.get_api_return_status();  
        clsRet = rsa.get_gp_return_status();
        rsa.get_api_return_status_string(apiStr);

        printf("\nget 'general purpose' variables >>>\n");
        printf("\tclass api return status         :  %d\n", apiRet);
        printf("\tclass api return status string  :  %s\n", apiStr);
        printf("\tclass gp return status          :  %d\n", clsRet); 

        printf("\nget class constants >>>\n");
        printf("\tCALL_SUCCESS             :  %d\n", rsa.CALL_SUCCESS);
        printf("\tCALL_FAILURE             :  %d\n", rsa.CALL_FAILURE);
        printf("\tINIT_CHAR                :  %c\n", rsa.INIT_CHAR);
        printf("\tINIT_DOUBLE              :  %lf\n", rsa.INIT_DOUBLE);
        printf("\tINIT_INT                 :  %d\n", rsa.INIT_INT);
        printf("\tINIT_STR                 :  %s\n", rsa.INIT_STR);
        printf("\tEXTERNAL_FREQUENCY       :  %lf  Hz\n", rsa.EXTERNAL_FREQUENCY);
        printf("\tEXTERNAL_AMPLITUDE_dbm   :  %lf +/- dbm\n", rsa.EXTERNAL_AMPLITUDE_dbm);
        printf("\tREFERENCE_LEVEL_MIN_dbm  :  %lf\n", rsa.REFERENCE_LEVEL_MIN_dbm);
        printf("\tREFERENCE_LEVEL_MAX_dbm  :  %lf\n", rsa.REFERENCE_LEVEL_MAX_dbm);
        printf("\tSPAN_MAX_HZ              :  %lf\n", rsa.SPAN_MAX_Hz);
        printf("\tSPAN_MIN_HZ              :  %lf\n", rsa.SPAN_MIN_Hz);
        rsa.print_all_const();
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_1.cpp
