/*
    use sparingly
    the entire program can see this
    extern where needed

    only need 1 instance of each for the entire library
*/

#include "globalz.h"


rsa306b_class X_rsa;        // to manage and control the RSA-306B 

r3f_manager_class X_r3f;    // to parse, process, and store "*.r3f" files

siq_manager_class X_siq;    // to parse, process, and store "*.siq" files

common_utility X_util;      // to use common utilities, and not interfere with composition objects

////////~~~~~~~~END>  globalz.c
