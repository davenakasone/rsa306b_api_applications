/*
    variables needed for the API group "ALIGN" 
*/

#ifndef H_rsa306b_align_struct
#define H_rsa306b_align_struct


#include "../rsa306b_constants.h"


struct rsa306b_align_struct
{
    
   bool is_needed;    // indicates if device alignment is needed
   bool is_warmed;    // indicates if the device is warmed-up

};
typedef struct rsa306b_align_struct rsa306b_align_struct;


#endif


////////~~~~~~~~END>  rsa306b_align_struct.h
