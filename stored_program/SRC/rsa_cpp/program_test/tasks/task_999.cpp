/*
    temporary test bench
        don't keep anything permenant here
*/

#include "../testz.h"

#ifdef UNIT_TESTING


void task_999()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  test bench\n", __func__);
//X_timer.time_split_start();                      
#endif    
////~~~~

    
    X_rsa.device_disconnect();
    X_rsa.device_connect();


////~~~~
#ifdef WAIT_ENTER_CLEAR
// X_timer.time_split_stop();
// X_timer.print_both();
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


#endif

/////////~~~~~~~~END>  task_999.cpp