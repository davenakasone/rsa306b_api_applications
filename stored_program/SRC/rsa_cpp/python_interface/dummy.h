/*
    use this to get your compiling and dynamic linking correct for python

    probably should be careful allocating and deallocating
    free() and malloc() should be exposed if a lot of data will cross the interface

    extern C everything
*/

#ifndef H_dummy
#define H_dummy

#include "../program_core/control/globalz.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


void dummy_plus_plus_by_ref(int* input_int);
int dummy_plus_plus_by_val(int input_int);

double* dummy_array_ret();
void dummy_array_ref(double* input_array);

char* dummy_string_ret();
void dummy_string_ref(char* input_string);

void dcon();
void print_d();
//void destructor();   bad to expose to python


#ifdef __cplusplus      
}
#endif

#endif

#endif

////////~~~~~~~~END>  dummy.h
