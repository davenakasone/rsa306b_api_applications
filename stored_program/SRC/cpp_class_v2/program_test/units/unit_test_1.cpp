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
extern rsa306b_class X_rsa;


void unit_test_1 (void)
{
    printf("\n%s()  ,  testing the 'general purpose' section of the class\n", __func__);
    {
        cpu_timer_class cpu;
        cpu.time_split_start();
        X_rsa.device_disconnect();
        X_rsa.device_connect();

        X_rsa.vars.gp.call_status = 3; 
        printf("\ncall status:  %d  ,  should have no effect\n",
            X_rsa.vars.gp.call_status);
        X_rsa.print_gp();

        X_rsa.get_everything();
        printf("\ncall status:  %d  ,  publics are updated when possilbe, or call 'get_everything()'\n",
            X_rsa.vars.gp.call_status);

        cpu.time_split_stop();
        printf("\nseems good, keep updating this section, time:  %lf s\n",
            cpu.get_time_split());
        
        X_rsa.device_connect();
        X_rsa.print_gp();
        
    }
    printf("\n%s()  ,  test complete\n", __func__);
    #ifdef WAIT_ENTER_CLEAR
        wait_enter_clear();
    #endif
}


////////~~~~~~~~END>  unit_test_1.cpp
