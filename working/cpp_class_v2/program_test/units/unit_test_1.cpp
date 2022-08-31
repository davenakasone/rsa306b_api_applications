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


void unit_test_1 (void)
{
    printf("\n%s()  ,  testing the 'general purpose' section of the class\n", __func__);
    {
        rsa306b_class rsa;
        cpu_timer_class cpu;
        cpu.time_split_start();

        rsa.vars.gp.call_status = 3; 
        printf("\ncall status:  %d  ,  should have no effect\n",
            rsa.vars.gp.call_status);
        rsa.print_gp();

        rsa.get_everything();
        printf("\ncall status:  %d  ,  publics are updated when possilbe, or call 'get_everything()'\n",
            rsa.vars.gp.call_status);

        cpu.time_split_stop();
        printf("\nseems good, keep updating this section, time:  %lf s\n",
            cpu.get_time_split());
        
        rsa.device_connect();
        rsa.print_gp();
        
    }
    printf("\n%s()  ,  test complete\n", __func__);
    wait_enter_clear();
}


////////~~~~~~~~END>  unit_test_1.cpp
