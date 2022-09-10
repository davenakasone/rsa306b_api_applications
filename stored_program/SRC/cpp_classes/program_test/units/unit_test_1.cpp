/*
    unit test # 1, "general purpose" section

    this class has to be updated as sections are added
        test often

    goals:
        - constructor and destuctor operate correctly
        - copiers, getters, and setters operate correctly
        - 'gp*' member functions operate correctly
*/

#include "../testz.h"
// extern rsa306b_class X_rsa;
// extern timer_class X_timer;


void unit_test_1 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  testing the 'general purpose' section of the class\n", __func__);
X_timer.time_split_start();                      
#endif  
////~~~~

    X_rsa.device_disconnect();
    X_rsa.device_connect();

    X_rsa.vars.gp.call_status = 3; 
    printf("\ncall status:  %d  ,  should have no effect\n",
        X_rsa.vars.gp.call_status);
    X_rsa.print_gp();

    X_rsa.get_everything();
    printf("\ncall status:  %d  ,  publics are updated when possilbe, or call 'get_everything()'\n",
        X_rsa.vars.gp.call_status);

    sprintf(X_rsa.vars.gp.helper, "helper");
    sprintf(X_rsa.vars.gp.holder, "holder");
    printf("strings for the user:  %s  ,  %s\n", X_rsa.vars.gp.helper, X_rsa.vars.gp.holder);
    
    X_rsa.device_connect();
    X_rsa.print_gp();    // observe the public/private seperation of variables

////~~~~
#ifdef WAIT_ENTER_CLEAR
X_timer.time_split_stop();
X_timer.print_both();
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////////~~~~~~~~END>  unit_test_1.cpp
