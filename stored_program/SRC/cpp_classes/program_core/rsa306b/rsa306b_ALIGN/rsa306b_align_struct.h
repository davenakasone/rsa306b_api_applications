/*
    variables needed for the API group "ALIGN" 
*/

#ifndef H_rsa306b_align_struct
#define H_rsa306b_align_struct


#include "../rsa306b_constants.h"


struct rsa306b_align_struct
{
/*
    ALIGN_GetAlignmentNeeded()
        based on difference of current temperature and 
        temperature from last alignment
*/
   bool is_needed;    // "true" indicates that alignment is needed

/*
    ALIGN_GetWarmupStatus()
        indicates if device warm-up interval has been reached
        devices start in the "warm-up" state, exiting when temperatures stabelize

*/
   bool is_warmed;    // "true" indicates that the device is warmed-up

/*
    ALIGN_RunAlignment()
        runs the device alignment procedure
        call if "is_needed == true"
*/

};
typedef struct rsa306b_align_struct rsa306b_align_struct;


#endif


////////~~~~~~~~END>  rsa306b_align_struct.h
