/*
    unit test # 1

    goals:
        - constructor initializes and connects
        - the general purpose section is operating correctly
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

        printf("\nclass api return status:         %d\n", apiRet);
        printf("class api return status string:  %s\n", apiStr);
        printf("class internal return status:    %d\n", clsRet); 

        printf("\nclass constants:\n");
        printf("CALL_SUCCESS      :  %d\n", my_spectrum_analyzer.CALL_SUCCESS);
        printf("CALL_FAILURE      :  %d\n", my_spectrum_analyzer.CALL_FAILURE);
        printf("INIT_CHAR         :  %c\n", my_spectrum_analyzer.INIT_CHAR);
        printf("INIT_DOUBLE       :  %lf\n", my_spectrum_analyzer.INIT_DOUBLE);
        printf("INIT_INT          :  %d\n", my_spectrum_analyzer.INIT_INT);
        printf("INIT_STR          :  %s\n", my_spectrum_analyzer.INIT_STR);
        printf("FREQUENCY_MIN_HZ  :  %lf\n", my_spectrum_analyzer.FREQUENCY_MIN_HZ);
        printf("FREQUENCY_MAX_HZ  :  %lf\n", my_spectrum_analyzer.FREQUENCY_MAX_HZ);
    }
    // instance goes out of scope and destructor is called

    printf("\n%s()  ,  test complete\n", __func__);
}


////////~~~~~~~~END>  unit_test_1.cpp

/*

            // device limits for the RSA-306B
            const double FREQUENCY_MIN_HZ = 9e3;           // lowest measurable frequency  
            const double FREQUENCY_MAX_HZ = 6.2e9;         // highest measurable frequency
            const double EXTERNAL_FREQUENCY = 10e6;        // external reference allows +/- 10 Hz
            const double REFERENCE_LEVEL_MIN_DB = -130;    // smallest measurable signal power
            const double REFERENCE_LEVEL_MAX_DB = 30;      // highest measurable signal power
            const double SPAN_MAX_HZ = 40e6;               // largest measurable bandwith
            const double SPAN_MIN_HZ = 10;                 // smallest measurable bandwith
*/