/*
    test the CPU timer
        had to make a CPU timer to observe the clock
        API only uses time_t, this class uses clock_t
    
    clock_t handles the "processing time" required
*/

#include "../testz.h"

#ifdef UNIT_TESTINGG

#define T998_REPZ 7


void task_998()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  getting the core program structured\n", __func__);                    
#endif    
////~~~~


//     for (int ii = 0; ii < T998_REPZ; ii++)
//     {
//         X_timer.time_split_start();
//         printf("\nsleep 1 second...\n");
//         sleep(1);
//         X_timer.time_split_stop();
//         printf("\tsplit:  %0.12lf  ,  running:  %0.12lf  {CPU}\n",
//             X_timer.get_time_split(), 
//             X_timer.get_running_time());
//         printf("\tsplit:  %0.12lf  ,  running:  %0.12lf  {wall}\n\n",
//             X_timer.get_time_split_w(), 
//             X_timer.get_running_time_w());
//     }
    
//     for (int ii = 0; ii < T998_REPZ; ii++)
//     {
//         printf("\nsleep 2 seconds...\n");
//         X_timer.time_split_start();
//         sleep(2);
//         X_timer.time_split_stop();
//         X_timer.print_both();
//     }

// ////~~~~
// #ifdef WAIT_ENTER_CLEAR
// X_timer.time_split_stop();
// X_timer.print_both();
// printf("\n%s()  ,  test complete\n", __func__);
// wait_enter_clear();
// #endif
}


#endif


/////////~~~~~~~~END>  task_998.cpp
