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
    #include "./control/globalz.h"
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
                                        0      // unit test template
                                       
        specific tasks  "task_#"    :
                                        999    // temporary use test bench                           
    */
   
   //#define TEST_EVERYTHING 6969    // {on|off} turn on to run all unit tests

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
            (void)printf("\n\t!!! WITNESS ME !!!\n");
            (void)X_rsa.device_reset();
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
            test_selector(999);
        #else
            #ifdef UNIT_TEST_BY_NUMBER
                test_selector(static_cast<int>(UNIT_TEST_BY_NUMBER)); 
            #else
                if (argc > 1)
                {
                    int current_test = INIT_INT;
                    for (int xx = 1; xx < argc; xx++)
                    {
                        current_test = atoi(argv[xx]);
                        test_selector(current_test);
                    }
                }
            #endif
        #endif
    #endif


////~~~~
    if (X_rsa.vars.device.is_connected == true)
    {
        (void)X_rsa.reftime_get_vars();
        (void)printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~    %s\n %s\n",
            X_rsa.vars.reftime.dts,
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


////////~~~~~~~~END>  main.cpp
