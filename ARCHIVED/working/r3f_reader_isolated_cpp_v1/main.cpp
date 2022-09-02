/*
    the class to read and convert "*.r3f" files is validated
*/

#include "r3f_manager_class.h"

#define NAME_SIZE 32

const char input_file_to_read[NAME_SIZE] = "dummy_in_1ms.r3f";    // this file is read by the class
const char output_processed[NAME_SIZE] = "processed.txt";         // the class processes the input file and writes here
const char output_decoded[NAME_SIZE] = "decoded.txt";             // the class processes the input file and decodes here
const char outputs_for_header[NAME_SIZE] = "plot_header.csv";     // use to plot the table data in the header of the "*.r3f" file
const char outputs_for_IQ[NAME_SIZE] = "plot_data.csv";           // use to plot the IQ data in the header of the "*.r3f" file

void demo_1();    // basic operation of the object "r3f_manager_class"
void demo_2();    // decode "*r3f" file
void demo_3();    // process "*.r3f" file
void demo_4();    // use the "*r3f" to make some data to plot

#define TEST_SELECT 2   // valid tests: 1, 2, 3, 4

int main
(
    int argc,
    char** argv,
    char** envp
)
{
    int objSize = 0;
    {
        r3f_manager_class dummy;
        objSize= sizeof(dummy);
    }

    #ifdef TEST_SELECT
        switch (TEST_SELECT)
        {
            case (1) : demo_1(); break;
            case (2) : demo_2(); break;
            case (3) : demo_3(); break;
            case (4) : demo_4(); break;
        }
    #else
        demo_1();
        demo_2();
        demo_3();
        demo_4();
    #endif
    

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
    printf("\nthe 'r3f_manager_class' object size:  %d bytes\n\n", objSize);
    return EXIT_SUCCESS;
}


////~~~~


void demo_1()
{
    r3f_manager_class manager;

    // check the stop watch
    manager.time_split_begin();
    for (int ii = 0; ii < INT32_MAX; ii++){}
    printf("\nelapsed time:  %lf seconds\n", manager.time_split_end());

    // check the public members
    manager.members.alignment_state = -9;
    printf("\nvariable is:  %d  ...updating, variable is:  ", 
        manager.members.alignment_state);
    manager.get_members(&manager.members);
    printf("%d\n", manager.members.alignment_state);
}


////~~~~


void demo_2()
{
    r3f_manager_class manager;
    //manager.file_decode(input_file_to_read, output_decoded, 0L, 0L, true);
    manager.file_decode(input_file_to_read, output_decoded, 0L, 16383L, true);
}


////~~~~


void demo_3()
{
    r3f_manager_class manager;
    manager.file_process(input_file_to_read, output_processed, true);
}


////~~~~


void demo_4()
{
    r3f_manager_class manager;
    manager.file_process(input_file_to_read, output_processed, false);
    manager.prepare_plot_from_header(outputs_for_header);
    manager.prepare_plot_from_data(input_file_to_read, outputs_for_IQ);
}


////////~~~~~~~~END>  main.cpp
