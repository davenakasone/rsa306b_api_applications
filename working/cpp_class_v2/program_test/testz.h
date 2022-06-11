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
*/

#ifndef H_testz
#define H_testz


#include "../program_core/control/resourcez.h"
#include "../program_core/rsa306b/rsa306b_class.h"
#include "../program_core/cpu_timer/cpu_timer_class.h"
#include "../program_core/r3f_manager/r3f_manager_class.h"


void test_selector (int test_number);    // controls the unit test being performed
void wait_enter_clear (void);            // flow separation between unit tests
void unit_test_0 (void);                 // place holder, default

void unit_test_1   (void);    // test 'general purpose' section
void unit_test_2   (void);    // test 'DEVICE' section
void unit_test_3   (void);    // test 'ALIGN' section
void unit_test_4   (void);    // test 'AUDIO' section
void unit_test_5   (void);    // test 'TRIG' section
void unit_test_6   (void);    // test 'REFTIME' section
void unit_test_7   (void);    // test 'CONFIG' section
void unit_test_8   (void);    // test 'SPECTRUM' section
void unit_test_9   (void);    // test 'IFSTREAM' section
void unit_test_10  (void);    // test 'IQBLK' section
void unit_test_11  (void);    // test 'IQSTREAM' section

void task_991 (void);    // test the whchar_t 2 char converter
void task_992 (void);    // get 100MHz and 315 MHz, spectrum and ADC
void task_993 (void);    // generate spectrum and raw ADC for learning
void task_994 (void);    // develop IF stream direct to client
void task_995 (void);    // test YK3000 @ 315 MHz
void task_996 (void);    // get CSV for model
void task_997 (void);    // DSP demonstration
void task_998 (void);    // test the cpu_timer_class
void task_999 (void);    // test bench          


#endif


////////~~~~~~~~END>  testz.h
