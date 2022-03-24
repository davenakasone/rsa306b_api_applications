/*
    there is a preliminary understanding of the API and its limitations 
	a class can help remove the abstraction
	main() directs the unit tests
	next step is to put the instance in a worker thread, 
        allowing the user to manipulate it during run time
*/

#include "../testz/unit_tests.h"


int main
(
    int argc,
    char** argv,
    char** envp
)
{
    
    test_selector(1);  // tests the "general purpose" section of the class


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
