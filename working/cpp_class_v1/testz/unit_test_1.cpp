/*
    unit test # 1

    goals:
        - constructor initializes and connects
        - basic data is populated to member variables and printed
        - no unsafe conditions are observed in the outputs
        - the destructor deallocates the instance and properly disconnects
*/

#include "unit_tests.h"


void unit_test_1 (void)
{
    printf("\n%s()  ,  testing basic class operations\n", __func__);
    
    {
        double center_f = 1.3e6;
        double reference_l = -10.2;
        rsa306b my_spectrum_analyzer;    // connection is automatic for new instance
        // some information is printed in constructor
        
        my_spectrum_analyzer.rsa_configure_cf_rl(center_f, reference_l);    // apply basic configuration
        my_spectrum_analyzer.print_configuration();                         // print basic info
        my_spectrum_analyzer.print_time_info();                             // print more info
    }
    // instance goes out of scope and destructor is called

    printf("\n%s()  ,  test complete\n", __func__);
}


////////~~~~~~~~END>  unit_test_1.cpp
