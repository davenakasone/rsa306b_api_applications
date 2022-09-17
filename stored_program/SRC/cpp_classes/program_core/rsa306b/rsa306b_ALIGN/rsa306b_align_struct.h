/*
    variables needed for the API group "ALIGN" 

    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    initializers       :  _<VARIABLE_NAME>            // leading underscore
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
*/


#ifndef H_rsa306b_align_struct
#define H_rsa306b_align_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_align_struct
{
/*
    ALIGN_GetAlignmentNeeded()
        based on difference of current temperature and temperature from last alignment
        "true" indicates that alignment is needed
*/
    bool       is_needed;    
    const bool _IS_NEEDED = true;    // DEFAULT


/*
    ALIGN_GetWarmupStatus()
        indicates if device warm-up interval has been reached
        "true" indicates that the device is warmed-up
        devices start in the "warm-up" state, exiting when temperatures stabelize
*/
    bool       is_warmed;
    const bool _IS_WARMED = false;    // DEFAULT

    
/*
    ALIGN_RunAlignment()
        runs the device alignment procedure
        call if "is_needed == true"
*/


// NO limiting constants


};
typedef struct rsa306b_align_struct rsa306b_align_struct;


#endif


////////~~~~~~~~END>  rsa306b_align_struct.h
