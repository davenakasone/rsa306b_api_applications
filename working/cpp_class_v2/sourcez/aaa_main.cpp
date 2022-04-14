/*
    improving the RSA object
    refinment and further testing
    still need signal, worker thread, data writter, ...
        data parser and plotting should be a seperate program
*/

#include "../testz/unit_tests.h"

// turn off to run all unit tests
// turn on and change UT_NUMBER to run a specific unit test
#define UNIT_TEST_BY_NUMBER 994 // select unit test # here
// valid UT_NUMER, class sections  "unit_test_#" : 
// valid UT_NUMER, specific tasks  "vvv_#"       : 



int main
(
    int argc,
    char** argv,
    char** envp
)
{
    int objSize = 0;
    {
        rsa306b dummy;
        objSize = (int)sizeof(dummy);
    }
    

    #ifdef UNIT_TEST_BY_NUMBER
        test_selector(UNIT_TEST_BY_NUMBER); 
    #else
        test_selector(1);      // tests the "general purpose" section of the class
        test_selector(2);      // tests the "DEVICE" section of the class
        test_selector(3);      // tests the "REFTIME" section of the class
        test_selector(4);      // tests the "ALIGN" section of the class
        test_selector(5);      // tests the "CONFIG" section of the class
        test_selector(6);      // tests the "SPECTRUM" section of the class
        test_selector(7);      // tests the "TRIG" section of the class
        test_selector(8);      // tests the "AUDIO" section of the class

        
        test_selector(994);    // activate the IFSTREAM, save as "*.r3f", try to read with python
        test_selector(995);    // trying to find antenna range by moving spectrum
        test_selector(996);    // trying to find antenna range by moving spectrum
        test_selector(997);    // moving settings on the fly, 'SPECTRUM' group functions
        test_selector(998);    // seeing if the 'REFTIME' split-timer is good
        test_selector(999);    // catch all, just prints data 
    #endif
    

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    #ifdef __clang_major__
        printf("\nCompiler:  clang  ,  v %d.%d\n",
            __clang_major__, __clang_minor__);
    #endif
    #ifdef __GNUC__
        #ifdef __cplusplus
            printf("\nCompiler:  g++  ,  v %d.%d\n",
                __GNUC__, __GNUC_MINOR__);
        #else
            printf("\nCompiler:  gcc  ,  v %d.%d\n",
                __GNUC__, __GNUC_MINOR__);
        #endif
    #endif
    printf("\nthe 'rsa306b' object size:  %d bytes\n\n", objSize);
    return EXIT_SUCCESS;
}


////////~~~~~~~~END>  main.cpp
