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
        rsa306b my_spectrum_analyzer;    // constructor is called

        apiRet = my_spectrum_analyzer.get_api_return_status();  
        clsRet = my_spectrum_analyzer.get_internal_return_status();
        my_spectrum_analyzer.get_api_return_status_string(apiStr);

        printf("\nget public 'device' variables >>>\n");
        printf("\tclass api return status:         %d\n", apiRet);
        printf("\tclass api return status string:  %s\n", apiStr);
        printf("\tclass internal return status:    %d\n", clsRet); 

        printf("\nclass constants >>>\n");
        printf("\tCALL_SUCCESS            :  %d\n", my_spectrum_analyzer.CALL_SUCCESS);
        printf("\tCALL_FAILURE            :  %d\n", my_spectrum_analyzer.CALL_FAILURE);
        printf("\tINIT_CHAR               :  %c\n", my_spectrum_analyzer.INIT_CHAR);
        printf("\tINIT_DOUBLE             :  %lf\n", my_spectrum_analyzer.INIT_DOUBLE);
        printf("\tINIT_INT                :  %d\n", my_spectrum_analyzer.INIT_INT);
        printf("\tINIT_STR                :  %s\n", my_spectrum_analyzer.INIT_STR);
        printf("\tFREQUENCY_MIN_HZ        :  %lf\n", my_spectrum_analyzer.FREQUENCY_MIN_HZ);
        printf("\tFREQUENCY_MAX_HZ        :  %lf\n", my_spectrum_analyzer.FREQUENCY_MAX_HZ);
        printf("\tEXTERNAL_FREQUENCY      :  %lf\n", my_spectrum_analyzer.EXTERNAL_FREQUENCY);
        printf("\tREFERENCE_LEVEL_MIN_DB  :  %lf\n", my_spectrum_analyzer.REFERENCE_LEVEL_MIN_DB);
        printf("\tREFERENCE_LEVEL_MAX_DB  :  %lf\n", my_spectrum_analyzer.REFERENCE_LEVEL_MAX_DB);
        printf("\tSPAN_MAX_HZ             :  %lf\n", my_spectrum_analyzer.SPAN_MAX_HZ);
        printf("\tSPAN_MIN_HZ             :  %lf\n", my_spectrum_analyzer.SPAN_MIN_HZ);
    }
    // instance goes out of scope and destructor is called
    printf("\n%s()  ,  test complete\n", __func__);
}


////////~~~~~~~~END>  unit_test_1.cpp
