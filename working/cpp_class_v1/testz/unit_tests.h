/*
    all tests are independent of the class under test
    this testing section is designed to test the "rsa306b" class

    finished product should delete this entire directory "./testz"

    unit tests are important and should be conducted in parallel with development
    the intent is to identify problems early

    the unit test is driven by main()
    each test must operate independently

    all testing resource are confined to this header file
        libraries, headers, constants, global variables...
*/

#ifndef H_unit_tests
#define H_unit_tests

#include "../includez/rsa306b_class.h"


void test_selector (int test_number);

void unit_test_1 (void);    // constructor, printing, destructor

void unit_test_999 (void);    // place holder


#endif


////////~~~~~~~~END>  unit_tests.h
