/*
    source code for the python interface
    common utilities for the python user

        < 1 >  delete_data()
*/

#include "python_interface.h"

#ifdef BUILD_PYTHON

#ifdef __cplusplus 
extern "C"      
{
#endif


// < 1 >
void delete_data()
{
    
    if 
    (
        X_util.rm_rf(DATA_DIRECTORY, FILLER_NAME, FILLER_CONTENTS, true)           == CODEZ::_0_no_errors &&
        X_util.rm_rf(DATA_DIRECTORY_PROCESSED, FILLER_NAME, FILLER_CONTENTS, true) == CODEZ::_0_no_errors &&
        X_util.rm_rf(DATA_DIRECTORY_RAW, FILLER_NAME, FILLER_CONTENTS, true)       == CODEZ::_0_no_errors &&
        X_util.rm_rf(DATA_DIRECTORY_SEQUENCED, FILLER_NAME, FILLER_CONTENTS, true) == CODEZ::_0_no_errors
    )
    {
        printf("\n%s* successfully cleared and reset\n", DATA_DIRECTORY);
    }
    else
    {
        printf("\nFAILED to delete %s\n", DATA_DIRECTORY);
    }
}


#ifdef __cplusplus      
}
#endif

#endif    // BUILD_PYTHON


////////~~~~~~~~END>  c_utility.cpp
