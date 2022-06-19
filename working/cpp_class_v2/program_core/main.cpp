/*
	main() directs the unit testing
    when the program is validated, 
        main() will be restricted to the entery point
*/

#include "../program_test/testz.h"

// if the blinking green light won't go away (data being transfered)
//#define CRASH_AND_RESET 456    // forces reset, program crashes, but device gets reset

// turn off to run all unit tests
// turn on and change UT_NUMBER to run a specific unit test
#define UNIT_TEST_BY_NUMBER 2    // select # here
// sections        "unit_test_#"  : 0  , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 10 , 
//                                  11 ,
// specific tasks  "task_#"       : 999, 998, 997, 996, 995, 994, 993, 992, 991


int main
(
    int argc,
    char** argv,
    char** envp
)
{
    cpu_timer_class dummy_cpu;
    int objSize[3];
    {
        rsa306b_class dummy_rsa;
        #ifdef CRASH_AND_RESET
            dummy_rsa.device_connect();
            dummy_rsa.device_reset();
        #endif
        r3f_manager_class dummy_r3f;
        objSize[0] = (int)sizeof(dummy_rsa);
        objSize[1] = (int)sizeof(dummy_cpu);
        objSize[2] = (int)sizeof(dummy_r3f);
    }
    
    #ifdef UNIT_TEST_BY_NUMBER
        test_selector(UNIT_TEST_BY_NUMBER); 
    #else
        test_selector(0);      // place holder, default
        test_selector(1);      // test 'general purpose' section
        test_selector(2);      // test 'DEVICE' section
        test_selector(3);      // test 'ALIGN' section
        test_selector(4);      // test 'AUDIO' section
        test_selector(5);      // test 'TRIG' section
        test_selector(6);      // test 'REFTIME' section
        test_selector(7);      // test 'CONFIG' section
        test_selector(8);      // test 'SPECTRUM' section
        test_selector(9);      // test 'IFSTREAM' section
        test_selector(10);     // test 'IQBLK' section
        test_selector(11);     // test 'IQSTREAM' section
        test_selector(991);    // test the whchar_t 2 char converter
        test_selector(992);    // get 100MHz and 315 MHz, spectrum and ADC
        test_selector(993);    // generate spectrum and raw ADC for learning
        test_selector(994);    // develop IF stream direct to client
        test_selector(995);    // test YK3000 @ 315 MHz
        test_selector(996);    // get CSV for model
        test_selector(997);    // DSP demonstration
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
    printf("\n");
    printf("the 'rsa306b' object size      :  %d bytes\n", objSize[0]);
    printf("the 'cpu_timer' object size    :  %d bytes\n", objSize[1]);
    printf("the 'r3f_manager' object size  :  %d bytes\n", objSize[2]);
    printf("\n");
    return EXIT_SUCCESS;
}


////////~~~~~~~~END>  main.cpp
