/*
    this is the attemp to scan a spectrum in 40 MHz spans
    the real-time adjustments will come later using:
    signal --> from CLI
        update start, stop, center
    also will add CLI argc, argv later

    the goal now is to ensure that the RSA-306B can be
    programmed to span and scan

    $ cd scanning_C_v1
    $ make
    $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
    $ ./scan
*/

#include <stdlib.h>
#include <stdio.h>
#include "RSA_API.h"


int main
(
    int argc,
    char** argv,
    char** envp
)
{

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}

/////////~~~~~~~~END> scan.c
