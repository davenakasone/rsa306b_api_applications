/*
    there is a preliminary understanding of the API and its limitations 
	a class can help remove the abstraction and make analysis efficient
	main() directs the unit tests
	next step is to put the instance in a worker thread, 
        allowing the user to manipulate it during run time
*/

#include "../testz/unit_tests.h"

// turn off to run all unit tests
// turn on and change UT_NUMBER to run a specific unit test
#define UNIT_TEST_BY_NUMBER 996 // select unit test # here
// valid UT_NUMER, class sections  "unit_test_#" : 1, 2, 3, 4, 5, 6
// valid UT_NUMER, specific tasks  "vvv_#"       : 999, 998, 997, 996



int main
(
    int argc,
    char** argv,
    char** envp
)
{
    #ifdef UNIT_TEST_BY_NUMBER
        test_selector(UNIT_TEST_BY_NUMBER); 
    #else
        test_selector(1);      // tests the "general purpose" section of the class
        test_selector(2);      // tests the "DEVICE" section of the class
        test_selector(3);      // tests the "REFTIME" section of the class
        test_selector(4);      // tests the "ALIGN" section of the class
        test_selector(5);      // tests the "CONFIG" section of the class
        test_selector(6);      // tests the "SPECTRUM" section of the class
        test_selector(998);    // seeing if the 'REFTIME' split-timer is good
        test_selector(997);    // moving settings on the fly, 'SPECTRUM' group functions
        test_selector(996);    // trying to find antenna range by moving spectrum
        test_selector(999);    // catch all, just prints data 
    #endif
    
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    #ifdef __clang_major__
        printf("\nCompiler:  clang  ,  v %d.%d\n\n",
            __clang_major__, __clang_minor__);
    #endif
    #ifdef __GNUC__
        #ifdef __cplusplus
            printf("\nCompiler:  g++  ,  v %d.%d\n\n",
                __GNUC__, __GNUC_MINOR__);
        #else
            printf("\nCompiler:  gcc  ,  v %d.%d\n\n",
                __GNUC__, __GNUC_MINOR__);
        #endif
    #endif
    return EXIT_SUCCESS;
}


////////~~~~~~~~END>  main.cpp
