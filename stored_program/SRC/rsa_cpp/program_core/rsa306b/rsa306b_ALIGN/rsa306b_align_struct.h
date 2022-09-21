/*
    variables needed for the API group "ALIGN" 
        ALIGN_GetAlignmentNeeded()
        ALIGN_GetWarmupStatus   ()
        ALIGN_RunAlignment      ()
    
    active vars :
        bool is_needed
        bool is_warmed
        
    constexpr helpers  :  <GROUP>_<CONSTEXPR_NAME>    // with group reference since used outside struct instance
    limiting constants :  <CONSTANT_NAME>             // no leading underscore
    initializers       :  _<VARIABLE_NAME>            // leading underscore
*/


#ifndef H_rsa306b_align_struct
#define H_rsa306b_align_struct


#include "../../control/resourcez.h"


// NO constexpr helpers


struct rsa306b_align_struct
{


// NO limiting constants


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


};
typedef struct rsa306b_align_struct rsa306b_align_struct;


#endif


////////~~~~~~~~END>  rsa306b_align_struct.h
