/*
    finished product should delete this entire directory "./program_test/"
    the directory could be kept if examples are needed
    core source code in "./program_core/" should never depend on these tests

    unit tests are important and should be conducted with development
    it is best to identify problems early
    development should not proceed until the source code is validated by testing

    the unit test is driven by main()
    each "unit_test_*" or "task_*" is made to operate independently
    "unit_test_*" are for specific sections of the core source code
    "task_*"      are for specific tasks such as: development ideas, demonstrations, and corner cases
    no test should ever be broken
    passing all tests validates the program/class

    when validated, the top-level module can interact with this program through:
        - main()
        - as a library
        - a library that has python bindings
*/

#ifndef H_testz
#define H_testz


#include "../program_core/control/globalz.h"
#ifdef BUILD_PYTHON
    #include "../python_interface/python_interface.h"
#endif

    #ifdef UNIT_TESTING


        #ifdef WAIT_ENTER_CLEAR
            void wait_enter_clear ();    // flow separation between unit tests, waits for user input
            void flush_io();             // flush stdin and stdout, without waiting for user input
        #endif


        void test_selector (int test_number);    // controls the unit test or task being executed


        void unit_test_0   ();    // place holder, default, template...
        void unit_test_1   ();    // test class [common_utility]
        void unit_test_2   ();    // test class [rsa_306b] section 'GP'
        void unit_test_3   ();    // test class [rsa_306b] API group 'DEVICE'
        void unit_test_4   ();    // test class [rsa_306b] API group 'ALIGN'
        void unit_test_5   ();    // test class [rsa_306b] API group 'CONFIG'
        void unit_test_6   ();    // test class [rsa_306b] API group 'REFTIME'
        void unit_test_7   ();    // test class [rsa_306b] API group 'TRIG'
        void unit_test_8   ();    // test class [rsa_306b] API group 'AUDIO'
        void unit_test_9   ();    // test class [rsa_306b] API group 'SPECTRUM'
        void unit_test_10  ();    // test class [rsa_306b] API group 'IQBLK'
        void unit_test_11  ();    // test class [rsa_306b] API group 'IQSTREAM'
        void unit_test_12  ();    // test class [rsa_306b] API group 'IFSTREAM'
        void unit_test_13  ();    // test class [r3f_manager]
        void unit_test_14  ();    // test class [siq_manager]

        void task_997();    // deleting directories, recursilvley + force
        void task_998();    // scan_dump()
        void task_999();    // temporary use test bench 


    #endif


#endif


////////~~~~~~~~END>  testz.h


/*
15 - PLAYBACK
16 - DPX

500 - september summary

997 - total capture from a scan
998 - demo YK3000 @ 315 MHz
*/