/*
    testing basic API use of C++

    $ cd example_cpp
    $ make
    $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../
    $ ./cppLoad
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
    //Uncomment the example you'd like to run.

	spectrum_example();
	//block_iq_example();
	//dpx_example();
	//iq_stream_example();
	//if_stream_example();
	//if_playback();

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


/////////~~~~~~~~END>  cppLoad.cpp
