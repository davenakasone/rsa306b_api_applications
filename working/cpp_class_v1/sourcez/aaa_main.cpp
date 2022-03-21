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
    rsa306b my_spectrum_analyzer;
    int test = plus_1(6);

    RSA_API::DEVICE_Connect(0);
    sleep(3);
    RSA_API::DEVICE_Disconnect();
    
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~%d\n\n", test);
    return EXIT_SUCCESS;
}



////////~~~~~~~~END>  main.cpp
