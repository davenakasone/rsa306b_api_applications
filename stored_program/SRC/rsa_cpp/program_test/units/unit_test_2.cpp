/*
    unit test # 2, class [rsa_306b] section 'GP'

    goals:
    
        CODEZ clear           ();   
        CODEZ print_vars      ();   
        CODEZ print_constants ();    
        CODEZ get_everything  ();    
        int                   get_api_status_number                     ();    
        char*                 get_api_status_string                     ();   
        RSA_API::ReturnStatus get_api_status                            ();    
        CODEZ                 set_api_status(RSA_API::ReturnStatus result);    
*/

#include "../testz.h"

#ifdef UNIT_TESTING


static void ut2_basic();
static void ut2_status();


void unit_test_2()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] section 'GP'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    ut2_basic();
    ut2_status();

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut2_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic GP methods\n", __func__);
#endif                   
//~

    X_rsa.device_connect();
    X_rsa.print_vars();
    X_rsa.print_constants();
    X_rsa.get_everything();
    X_rsa.device_disconnect();

    printf("\nget_everything() fails, device is not connected, any key to continue:");
#ifdef WAIT_ENTER_CLEAR
    char dis[BUF_C];
    std::cin >> dis;
    flush_io();
#endif
    X_rsa.get_everything();

    printf("\nconnecting, clearing, then printing initialized/default values...\n");
    sleep(1);
    X_rsa.device_connect();
    X_rsa.clear();
    X_rsa.print_vars();
    printf("\ncleared RSA, initialized values, is_connected=  %d  {0=false, 1=true}\n",
        X_rsa.vars.device.is_connected);

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut2_status()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  , API status GP\n", __func__);
#endif                   
//~

    X_rsa.device_connect();
    printf("\nstatus number   :  %d\n", X_rsa.get_api_status_number());
    printf("status enum     :  %d\n", X_rsa.get_api_status());
    printf("%s\n", X_rsa.get_api_status_string());

    RSA_API::ReturnStatus temp = RSA_API::ReturnStatus::errorESTPathDoesntExist;
    printf("\nset an API error...\n");
    printf("CODEZ           :  %d\n", X_rsa.set_api_status(temp));
    printf("status number   :  %d\n", X_rsa.get_api_status_number());
    printf("status enum     :  %d\n", X_rsa.get_api_status());
    printf("%s\n", X_rsa.get_api_status_string());

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_2.cpp
