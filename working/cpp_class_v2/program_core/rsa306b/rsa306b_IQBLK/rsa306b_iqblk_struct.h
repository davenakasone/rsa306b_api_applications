/*
    variables needed for the API group "IQBLK" 

    device is configured before use
*/

#ifndef H_rsa306b_iqblk_struct
#define H_rsa306b_iqblk_struct


#include "../../control/resourcez.h"


struct rsa306b_iqblk_struct
{
    // IQBLK_GetAcqInfo()
    RSA_API::IQBLK_ACQINFO acq_info_type;

    

};
typedef struct rsa306b_iqblk_struct rsa306b_iqblk_struct;


#endif


////////~~~~~~~~END>  rsa306b_iqblk_struct.h
