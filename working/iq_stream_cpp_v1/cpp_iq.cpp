/*
    extends the basic use cases
    focus on IQ stream

    $ cd example_cpp
    $ make clean
    $ make
    $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
    $ ./cpp_iq
*/

#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "rsa_cpp.h"


int main
(
    int argc, 
    char** argv, 
    char** envp
)
{
#ifdef DEBUG_CLI
    printf("\n\t<<<  %s()  >>>\n", __func__);
#endif

    //Uncomment the example you'd like to run.

	spectrum_example();     // seems good
	//block_iq_example();     // seems good
	//dpx_example();          // seems good
	//iq_stream_example();    // seems good
	//if_stream_example();    // seems good
	//if_playback();          // need to work it out for Linux

#ifdef DEBUG_CLI
    printf("\n\t<<<  %s()  >>>\n", __func__);
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
#endif

    return EXIT_SUCCESS;
}


/////////~~~~~~~~END>  cppLoad.cpp
