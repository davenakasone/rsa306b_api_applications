/*
    header of the compilation/translational unit for globals
    when used in the program, be ware that any "X_*" variable is "external" or global
*/

#ifndef H_globalz
#define H_globalz


#include "../rsa306b/rsa306b_class.h"
#include "../r3f_manager/r3f_manager_class.h"
#include "../siq_manager/siq_manager_class.h"
#include "../common_utility/common_utility.h"


// global instances :

extern rsa306b_class     X_rsa;
extern r3f_manager_class X_r3f;    
extern siq_manager_class X_siq;           
extern common_utility    X_util;


#endif


////////~~~~~~~~END>  globalz.h
