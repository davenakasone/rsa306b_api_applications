/*
    there is a preliminary understanding of the API and its limitations 
	a class can help remove the abstraction
	main() here is a test bench
	next step is to put the instance in a worker thread, then configure it on the fly
*/

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include "../includez/rsa306b_class.h"
#include "../includez/tester.h"


int main
(
    int argc,
    char** argv,
    char** envp
)
{
    double center_f = 1.3e6;
    double reference_l = -10.2;
    {
        rsa306b my_spectrum_analyzer;    // automatic connection
        my_spectrum_analyzer.rsa_configure_cf_rl(center_f, reference_l);
        my_spectrum_analyzer.print_configuration();
        sleep(3);
    }

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n");
    #ifdef __clang_major__
        printf("\nCompiler:  clang  ,  v %d.%d\n\n",
            __clang_major__, __clang_minor__);
    #endif
    #ifdef __GNUC__
        #ifdef __cplusplus
            printf("\nCompiler:  g++  ,  v %d.%d\n\n",
                __GNUC__, __GNUC_MINOR__);
        #else
            printf("\nCompiler:  gcc  ,  v %d.%d\n\n",
                __GNUC__, __GNUC_MINOR__);
        #endif
    #endif
    return EXIT_SUCCESS;
}


////////~~~~~~~~END>  main.cpp
