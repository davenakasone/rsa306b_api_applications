/*
    all tests are independent of the class under test
    this testing section is designed to test the "rsa306b" class

    finished product should delete this entire directory "./testz"
        but it might be helpful to keep, so examples can be shown
        just pick the best unit tests and delete the rest?

    unit tests are important and should be conducted in parallel with development
    the intent is to identify problems early

    the unit test is driven by main()
    each test must operate independently

    all testing resource are confined to this header file
        libraries, headers, constants, global variables...
    
    "unit_test_*" are for general sections
    "vvv_*"       are for specific demonstrations, debugging, and feature developments
    no test should ever be broken
    passing all tests validates the program/class
*/

#ifndef H_unit_tests
#define H_unit_tests


#include <ostream>

#include "../includez/rsa306b_class.h"


void test_selector (int test_number);    // controls the unit test being performed
void wait_enter_clear();                 // flow separation between unit tests

void unit_test_1  (void);    // tests the "general purpose" section of the class
void unit_test_2  (void);    // tests the "DEVICE" section of the class
void unit_test_3  (void);    // tests the "REFTIME" section of the class
void unit_test_4  (void);    // tests the "ALIGN" section of the class
void unit_test_5  (void);    // tests the "CONFIG" section of the class
void unit_test_6  (void);    // tests the "SPECTRUM" section of the class
void unit_test_7  (void);    // tests the "SPECTRUM" section of the class

void unit_test_999 (void);    // place holder, data printer

void vvv_998 (void);          // seeing if the 'REFTIME' split-timer is good
void vvv_997 (void);          // moving settings on the fly, 'SPECTRUM' group functions
void vvv_996 (void);          // trying to find antenna range by moving spectrum


#endif


////////~~~~~~~~END>  unit_tests.h
