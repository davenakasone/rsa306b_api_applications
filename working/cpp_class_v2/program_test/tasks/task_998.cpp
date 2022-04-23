/*
    test the CPU timer
        had to make a CPU timer to observe the clock
        API only uses time_t, this class uses clock_t
    
    clock_t handles the "processing time" required
*/

#include "../testz.h"


void task_998()
{
    printf("\n%s()  ,  getting the core program structured\n", __func__);
    {
        cpu_timer_class cpu;

        cpu.time_split_start();
        sleep(1);
        cpu.time_split_stop();
        printf("split:  %lf  ,  running:  %lf\n",
            cpu.get_time_split(), cpu.get_running_time());

        cpu.time_split_start();
        sleep(2);
        cpu.time_split_stop();
        cpu.print_time_split();
        cpu.print_running_time();
    }
    printf("\n%s()  ,  test complete\n", __func__);
}


/////////~~~~~~~~END>  task_998.cpp
