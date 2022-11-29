/*
    unit test # 3, class [rsa_306b] API group 'DEVICE'

    goals:
    
        CODEZ device_print               ();   
        CODEZ device_connect             ();    
        CODEZ device_disconnect          ();    
        CODEZ device_run                 ();    
        CODEZ device_stop                ();    
        CODEZ device_reset               ();    // do not touch this, it works fine    
        CODEZ device_check_run_state     ();   
        CODEZ device_check_temperature   ();    
        CODEZ device_check_event         ();    
        CODEZ device_prepare_for_run     ();    
        CODEZ device_start_frame_transfer();    
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut3 = 5;
static void ut3_con_dcon_print();
static void ut3_run_stop();
static void ut3_event();


void unit_test_3()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'DEVICE''\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~
    X_util.clear_data();
    
    ut3_con_dcon_print();
    ut3_run_stop();
    ut3_event();
//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut3_con_dcon_print()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  connecting, disconnecting, and state of variables\n", __func__);
#endif                   
//~

    for (int ii = 0; ii < bangz_ut3; ii++)
    {
        X_rsa.device_disconnect();
        printf("\n%2d of %2d)  device_disconnect()  ,  is_connected=  %d  {0=false, 1=true}\n",
            ii+1,
            bangz_ut3,
            X_rsa.vars.device.is_connected);

        X_rsa.device_connect();
        printf("\n%2d of %2d)  device_connect()     ,  is_connected=  %d  {0=false, 1=true}\n",
            ii+1,
            bangz_ut3,
            X_rsa.vars.device.is_connected);

        if (ii % 2 == 1)
        {
            X_rsa.device_disconnect();
            printf("\n%2d of %2d)  device_disconnect()  ,  is_connected=  %d  {0=false, 1=true}\n",
                ii+1,
                bangz_ut3,
                X_rsa.vars.device.is_connected);
        }
    }
    X_rsa.device_connect();
    X_rsa.device_print();

    (void)X_rsa.device_check_temperature();
    printf("\ndevice is over temperature?  %d  {0=false, 1=true}\n", X_rsa.vars.device.is_over_temperature);

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut3_run_stop()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  running and stopping\n", __func__);
#endif                   
//~
    
    X_rsa.device_connect();
    for (int ii = 0; ii < bangz_ut3; ii++)
    {
        X_rsa.device_stop();
        printf("\n%2d of %2d)  device_stop()                  ,  is_running=  %d  {0=false, 1=true}\n", 
            ii+1, bangz_ut3, X_rsa.device_check_run_state());

        X_rsa.device_run();
        printf("%2d of %2d)  device_run()                   ,  is_running=  %d  {0=false, 1=true}\n", 
            ii+1, bangz_ut3, X_rsa.device_check_run_state());

        X_rsa.device_stop();
        printf("%2d of %2d)  device_stop()                  ,  is_running=  %d  {0=false, 1=true}\n", 
            ii+1, bangz_ut3, X_rsa.device_check_run_state());

        X_rsa.device_prepare_for_run();
        printf("%2d of %2d)  device_prepare_for_run()       ,  is_running=  %d  {0=false, 1=true}\n", 
            ii+1, bangz_ut3, X_rsa.device_check_run_state());
        
        X_rsa.device_start_frame_transfer();
        printf("%2d of %2d)  device_start_frame_transfer()  ,  is_running=  %d  {0=false, 1=true}\n", 
            ii+1, bangz_ut3, X_rsa.device_check_run_state());
    }
    X_rsa.device_stop();
    X_rsa.device_disconnect();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut3_event()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  event detection capabilities\n", __func__);
#endif                   
//~
    
    X_rsa.device_connect();
    X_rsa.vars.device.event_id = static_cast<int>(RSA_API::DEVEVENT_TRIGGER);
    
    X_rsa.vars.trig.if_power_level = -12.2;
    X_rsa.vars.trig.mode_select = RSA_API::TriggerMode::triggered;
    X_rsa.vars.trig.position_percent = X_rsa.vars.trig.POSITION_PERCENT_MAX / 2;
    X_rsa.vars.trig.source_select = RSA_API::TriggerSource::TriggerSourceIFPowerLevel;
    X_rsa.vars.trig.transition_select = RSA_API::TriggerTransitionLH;
    X_rsa.trig_set_vars();

    X_rsa.device_run();

    for (int ii = 0; ii < 3*bangz_ut3; ii++)
    {
        if (ii % 2 == 1)
        {
            (void)X_rsa.trig_force();
        }
        sleep(1);    // important

            X_rsa.device_check_event();
            printf("\n%2d of %2d)  event:  %d  {0=overange, 1=trigger}  ,  occured?  %d  {0=false, 1=true}  ,  timestamp:  %lu\n",
                ii+1,
                3*bangz_ut3,
                X_rsa.vars.device.event_id,
                X_rsa.vars.device.event_occured,
                X_rsa.vars.device.event_timestamp);
    }
    X_rsa.device_stop();
    X_rsa.device_disconnect();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_3.cpp
