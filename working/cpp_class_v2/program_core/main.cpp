/*
	main() directs the unit testing
    when the program is validated, 
        main() will be restricted to the entery point
*/

#include "../program_test/testz.h"

// turn off to run all unit tests
// turn on and change UT_NUMBER to run a specific unit test
#define UNIT_TEST_BY_NUMBER 3    // select unit test # here
// sections        "unit_test_#"  : 0, 1, 2, 3
// specific tasks  "task_#"       : 999, 998


int main
(
    int argc,
    char** argv,
    char** envp
)
{
    cpu_timer_class runner;
    int objSize = 0;
    {
        rsa306b_class dummy;
        objSize = (int)sizeof(dummy);
    }
    
    #ifdef UNIT_TEST_BY_NUMBER
        test_selector(UNIT_TEST_BY_NUMBER); 
    #else
        test_selector(0);      // place holder, default
        test_selector(1);      // test 'general purpose' section
        test_selector(2);      // test 'DEVICE' section
        test_selector(3);      // test 'ALIGN' section
        
        test_selector(998);    // test the cpu_timer_class
        test_selector(999);    // test bench
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
