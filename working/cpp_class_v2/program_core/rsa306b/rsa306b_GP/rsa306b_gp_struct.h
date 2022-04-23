/*
    variables common to the "rsa306b" class
    these variables are used in multiple API function groups
*/

#include "../../control/resourcez.h"


struct rsa306b_gp_struct
{
    
    char helper[BUF_E];                  // string for utility
    char holder[BUF_F];                  // big string for utility
    
    int call_status;                     // set when calling non-API functions
    
    RSA_API::ReturnStatus api_status;    // enum, all API functions return this

};
typedef struct rsa306b_gp_struct rsa306b_gp_struct;


////////~~~~~~~~END>  rsa306b_gp_struct.h
