/*
    the class to read and convert "*.r3f" files is validated
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main
(
    int argc,
    char** argv,
    char** envp
)
{
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    #ifdef __clang_major__
        printf("\nCompiler:  clang  ,  v %d.%d\n",
            __clang_major__, __clang_minor__);
    #endif
    #ifdef __GNUC__
        #ifdef __cplusplus
            printf("\nCompiler:  g++  ,  v %d.%d\n",
                __GNUC__, __GNUC_MINOR__);
        #else
            printf("\nCompiler:  gcc  ,  v %d.%d\n",
                __GNUC__, __GNUC_MINOR__);
        #endif
    #endif
    //printf("\nthe 'rsa306b' object size:  %d bytes\n\n", objSize);
    return EXIT_SUCCESS;
}
////////~~~~~~~~END>  main.cpp
