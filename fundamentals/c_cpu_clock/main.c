/*
    classic method to obtain CPU timing
    ensure functions are kept to DATA_TYPE_MAX
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t g_cpu_clk_start;

double get_running_time(void);  // for time splits or total running time


int main
(
    void
)
{
    g_cpu_clk_start = clock();               // record starting time
    for (int ii = 0; ii < 9e7; ii++){}       // do something
    double run_time = get_running_time();    // find elapsed time
    printf("\nthe program has been running for:  %lf  seconds\n", run_time);

    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


double get_running_time(void)
{
    clock_t cpu_clk_now = clock(); // get current time
    double running_time = 0;
    running_time = ((double)cpu_clk_now - (double)g_cpu_clk_start) / CLOCKS_PER_SEC;
    return running_time;
}


////////~~~~~~~~END>  main.c
