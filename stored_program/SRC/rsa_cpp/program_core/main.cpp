/*
	main() directs the unit testing
    when the program is validated, 
        main() is only for stand-alone operation, mostly for testing
        exclude this file form the shared object
*/


#include "../program_test/testz.h"
#ifndef UNIT_TESTINGG
    #include "./control/globalz.h"
#endif

// if the blinking green light won't go away (data being transfered)
//#define CRASH_AND_RESET 456    // forces reset, program crashes, but device gets reset
// reset is also possible by running the program with a single argument from the command line
// for example:          $ ./oo reset

#ifdef UNIT_TESTINGG
// turn off to run all unit tests
// turn on and change UT_NUMBER to run a specific unit test
#define UNIT_TEST_BY_NUMBER 991   // select # here
/*
    sections    "unit_test_#"   : 
                                    0
                                    1
                                    2
                                    3
                                    4
                                    5
                                    6
                                    7
                                    8
                                    9
                                    10
                                    11
    specific tasks  "task_#"    :
                                    999
                                    998
                                    997
                                    995
                                    994
                                    993
                                    992
*/
#endif


int main
(
    int argc,
    char** argv,
    char** envp
)
{
    if (argc >= 2)    // blinking green light occured, user wants to reset the device
    {
        #ifdef CRASH_AND_RESET
            witness_me:
        #endif
        (void)X_rsa.device_connect();
        printf("\n\t!!! WITNESS ME !!!\n");
        (void)X_rsa.device_reset();
    }
    #ifdef CRASH_AND_RESET
        goto witness_me;
    #endif

    int objSize[4];
    objSize[0] = static_cast<int>(sizeof(X_rsa));
    objSize[1] = static_cast<int>(sizeof(X_r3f));
    objSize[2] = static_cast<int>(sizeof(X_siq));
    objSize[3] = static_cast<int>(sizeof(X_util));
////~~~~


    #ifdef UNIT_TESTINGG
        #ifdef UNIT_TEST_BY_NUMBER
            test_selector(static_cast<int>(UNIT_TEST_BY_NUMBER)); 
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

            test_selector(992);    // develop the "siq_manager" file handler
            test_selector(993);    // see if the IQSTREAM API is good
            test_selector(994);    // test the whchar_t 2 char converter
            test_selector(995);    // test YK3000 @ 315 MHz
            test_selector(996);    // EE 498, Semptember 2022
            test_selector(997);    // DSP demonstration
            test_selector(998);    // test the cpu_timer_class
            test_selector(999);    // test bench
        #endif
    #endif


////~~~~
    if (X_rsa.vars.device.is_connected == true)
    {
        (void)X_rsa.reftime_get_vars();
        printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %s\n %s\n",
            X_rsa.vars.reftime.dts,
            UNLV_RSA_VERSION);
    }
    else
    {
        #ifdef DE_BUG
            printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %s\n %s\n",
                debug_dts(),
                UNLV_RSA_VERSION);
        #else
            printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %s\n",
                UNLV_RSA_VERSION);
        #endif
    }
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
    printf("the 'rsa306b_class'  object size        :  %12d bytes\n", objSize[0]);
    printf("the 'r3f_manager'    object size        :  %12d bytes\n", objSize[1]);
    printf("the 'siq_manager'    object size        :  %12d bytes\n", objSize[2]);
    printf("the 'common_utility' object size        :  %12d bytes\n", objSize[3]);
    printf("\n");
    return EXIT_SUCCESS;
}


////////~~~~~~~~END>  main.cpp
