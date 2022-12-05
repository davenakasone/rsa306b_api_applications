/*
	main() directs the unit testing
    when the program is validated, 
        main() is only for stand-alone operation, mostly for testing
        this file is excluded from the shared object
    
    it is premissable to deactivate the "UNIT_TESTING" macro and use this as an entry point
*/


#include "./control/resourcez.h"
#ifdef UNIT_TESTING 
    #include "../program_test/testz.h"
#endif


/*
    this macro forces reset, program crashes, but device gets reset
    if the blinking green light won't go away (data being transfered)
    reset is also possible by running the program with a single argument from the command line
    first argument of executable must match "./SRC/control/constant_expresions.h" CL_ARG_RESET[] = "reset"
    for example:          $ ./oo reset
*/
//#define CRASH_AND_RESET 456    // {ON|OFF}, if reset through command line is not desired



#ifdef UNIT_TESTING
    // not needed if you are specifying unit tests from the command line
    // turn on and change number to run a specific unit test
    //#define UNIT_TEST_BY_NUMBER 999   // select # here
    /*
        sections    "unit_test_#"   : 
                                        0      // place holder, default, template...
                                        1      // test class [common_utility]
                                        2      // test class [rsa_306b] section 'GP'
                                        3      // test class [rsa_306b] API group 'DEVICE'
                                        4      // test class [rsa_306b] API group 'ALIGN'
                                        5      // test class [rsa_306b] API group 'CONFIG'
                                        6      // test class [rsa_306b] API group 'REFTIME'
                                        7      // test class [rsa_306b] API group 'TRIG'
                                        8      // test class [rsa_306b] API group 'AUDIO'
                                        9      // test class [rsa_306b] API group 'SPECTRUM'
                                        10     // test class [rsa_306b] API group 'IQBLK'
                                        11     // test class [rsa_306b] API group 'IQSTREAM'
                                        12     // test class [rsa_306b] API group 'IFSTREAM'
                                        13     // test class [r3f_manager]
                                        14     // test class [siq_manager]
                                       
        specific tasks  "task_#"    :
                                        995    // triggered_dump()
                                        995    // trigger evaluation
                                        996    // spectrum_scanner()
                                        997    // delete directories
                                        999    // temporary use test bench 
                                        998    // scan_dump()                        
    */
   
   //#define TEST_EVERYTHING 6969    // {on|off} turn on to run all unit tests

    #ifndef TEST_EVERYTHING
        static bool user_test_selection();
    #endif
#endif


int main
(
    int argc,
    char** argv,
    char** envp
)
{
#ifdef CRASH_AND_RESET
    goto witness_me;
#endif
    if (argc > 1)
    {
        // blinking green light occured, user wants to reset the device
        if (strcmp(argv[1], CL_ARG_RESET) == 0)
        {
            #ifdef CRASH_AND_RESET
                witness_me:
            #endif
            (void)X_rsa.device_connect();
            (void)X_rsa.device_reset();
            return EXIT_SUCCESS;
        }
    }
    int objSize[4];
    objSize[0] = static_cast<int>(sizeof(X_rsa));
    objSize[1] = static_cast<int>(sizeof(X_r3f));
    objSize[2] = static_cast<int>(sizeof(X_siq));
    objSize[3] = static_cast<int>(sizeof(X_util));
////~~~~


    #ifdef UNIT_TESTING
        #ifdef TEST_EVERYTHING
            test_selector(0);
            test_selector(1);
            test_selector(2);
            test_selector(3);
            test_selector(4);
            test_selector(5);
            test_selector(6);
            test_selector(7);
            test_selector(8);
            test_selector(9);
            test_selector(10);
            test_selector(11);
            test_selector(12);
            test_selector(13);
            test_selector(14);
            test_selector(994);
            test_selector(995);
            test_selector(996);
            test_selector(997);
            test_selector(998);
            test_selector(999);
        #else
            #ifdef UNIT_TEST_BY_NUMBER
                test_selector(static_cast<int>(UNIT_TEST_BY_NUMBER)); 
            #else
                if (argc > 1)    // user wants to run tests from command line
                {
                    int current_test = INIT_INT;
                    for (int xx = 1; xx < argc; xx++)
                    {
                        current_test = atoi(argv[xx]);
                        test_selector(current_test);
                    }
                }
                else    // user wants an "interactive" testing session
                {
                    bool keep_testing = true;
                    while (keep_testing == true)
                    {
                        keep_testing = user_test_selection();
                    }
                }
            #endif
        #endif
    #endif


////~~~~
    if (X_rsa.vars.device.is_connected == true)
    {
        (void)printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %s\n %s\n",
            X_rsa.reftime_make_dts(),
            UNLV_RSA_VERSION);
    }
    else
    {
        #ifdef DE_BUG
            (void)printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %s\n %s\n",
                debug_dts(),
                UNLV_RSA_VERSION);
        #else
            (void)printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %s\n",
                UNLV_RSA_VERSION);
        #endif
    }
    #ifdef __clang_major__
        (void)printf("\nCompiler:  clang  ,  v %d.%d\n",
            __clang_major__, __clang_minor__);
    #endif
    #ifdef __GNUC__
        #ifdef __cplusplus
            (void)printf("\nCompiler:  g++  ,  v %d.%d\n",
                __GNUC__, __GNUC_MINOR__);
        #else
            (void)printf("\nCompiler:  gcc  ,  v %d.%d\n",
                __GNUC__, __GNUC_MINOR__);
        #endif
    #endif
    (void)printf("\n");
    (void)printf("the 'rsa306b_class'  object size        :  %12d bytes\n", objSize[0]);
    (void)printf("the 'r3f_manager'    object size        :  %12d bytes\n", objSize[1]);
    (void)printf("the 'siq_manager'    object size        :  %12d bytes\n", objSize[2]);
    (void)printf("the 'common_utility' object size        :  %12d bytes\n", objSize[3]);
    #ifndef DE_BUG
        (void)printf("\n");
    #endif
    return EXIT_SUCCESS;
}


////~~~~


#ifndef TEST_EVERYTHING
static bool user_test_selection()
{
    int selection = -1;
    printf("\nall tests are complete, make a selection to keep testing :\n\n");
    printf("\t[0]      ut0()                // default\n");
    printf("\t[1]      ut1()                // common utility\n");
    printf("\t[2]      ut2()                // GP, general purpose\n");
    printf("\t[3]      ut3()                // API group 'DEVICE'\n");
    printf("\t[4]      ut4()                // API group 'ALIGN'\n");
    printf("\t[5]      ut5()                // API group 'CONFIG'\n");
    printf("\t[6]      ut6()                // API group 'REFTIME'\n");
    printf("\t[7]      ut7()                // API group 'TRIG'\n");
    printf("\t[8]      ut8()                // API group 'AUDIO'\n");
    printf("\t[9]      ut9()                // API group 'SPECTRUM'\n");
    printf("\t[10]     ut10()               // API group 'IQBLK'\n");
    printf("\t[11]     ut11()               // API group 'IQSTREAM'\n");
    printf("\t[12]     ut12()               // API group 'IFSTREAM'\n");
    printf("\t[13]     ut13()               // r3f manager\n");
    printf("\t[14]     ut14()               // siq manager\n");

    printf("\t[994]    task994()            // triggered_dump()\n");
    printf("\t[995]    task995()            // trigger evaluation\n");
    printf("\t[996]    task996()            // spectrum_scanner()\n");
    printf("\t[997]    task997()            // delete directories\n");
    printf("\t[998]    task998()            // scan_dump()\n");
    printf("\t[999]    task999()            // testbench\n");
   
    printf("\nor enter -1 to exit:    ");
    std::cin >> selection;
#ifdef WAIT_ENTER_CLEAR
    flush_io();
#endif

    switch(selection)
    {
        case(0)   : unit_test_0();   return true;
        case(1)   : unit_test_1();   return true;
        case(2)   : unit_test_2();   return true;
        case(3)   : unit_test_3();   return true;
        case(4)   : unit_test_4();   return true;
        case(5)   : unit_test_5();   return true;
        case(6)   : unit_test_6();   return true;
        case(7)   : unit_test_7();   return true;
        case(8)   : unit_test_8();   return true;
        case(9)   : unit_test_9();   return true;
        case(10)  : unit_test_10();  return true;
        case(11)  : unit_test_11();  return true;
        case(12)  : unit_test_12();  return true;
        case(13)  : unit_test_13();  return true;
        case(14)  : unit_test_14();  return true;
        
        case(994) : task_994(); return true;
        case(995) : task_995(); return true;
        case(996) : task_996(); return true;
        case(997) : task_997(); return true;
        case(998) : task_998(); return true;
        case(999) : task_999(); return true;

        default : return false;
    }
}
#endif


////////~~~~~~~~END>  main.cpp
