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
        printf("\nsleep 1 second...\n");
        sleep(1);
        cpu.time_split_stop();
        printf("split:  %0.12lf  ,  running:  %0.12lf  {CPU}\n",
            cpu.get_time_split(), cpu.get_running_time());
        printf("split:  %0.12lf  ,  running:  %0.12lf  {wall}\n",
            cpu.get_time_split_w(), cpu.get_running_time_w());

        printf("\nsleep 2 seconds...\n");
        cpu.time_split_start();
        sleep(2);
        cpu.time_split_stop();
        cpu.print_time_split();
        cpu.print_running_time();

        printf("\ndestructor...\n");
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


/////////~~~~~~~~END>  task_998.cpp
