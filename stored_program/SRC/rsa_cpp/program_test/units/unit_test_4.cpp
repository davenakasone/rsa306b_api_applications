/*
    unit test # 4, class [rsa_306b] API group 'ALIGN'

    goals:
    
        CODEZ align_print          ();
        bool  align_check_is_needed();
        bool  align_check_is_warmed();
        CODEZ align_run            ();
*/

#include "../testz.h"

#ifdef UNIT_TESTING


constexpr int bangz_ut4 = 5;
static void ut4_basic();
static void ut4_run();


void unit_test_4 (void)
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  class [rsa_306b] API group 'ALIGN'\n", __func__);
X_util.timer_split_start(); 
#endif                   
//~

    X_rsa.device_connect();
    ut4_basic();
    ut4_run();
    X_rsa.device_disconnect();

//~
#ifdef WAIT_ENTER_CLEAR
X_util.timer_split_stop();
X_util.timer_print_split(1,1);
printf("\n%s()  ,  test complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut4_basic()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  basic ALIGN methods\n", __func__);
#endif                   
//~

    X_rsa.align_print();
    printf("\nalign is needed?  %d  {0=false, 1=true}\n", X_rsa.vars.align.is_needed);
    printf("is warmed-up   ?  %d  {0=false, 1=true}\n", X_rsa.vars.align.is_warmed);

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


////~~~~


static void ut4_run()
{
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  running the alignment\n", __func__);
#endif                   
//~

    printf("\n");
    for (int ii = 0; ii < bangz_ut4; ii++)
    {
        X_rsa.align_run();
        printf("%2d of %2d)  align is needed?  %d  {0=false, 1=true}\n", 
            ii + 1,
            bangz_ut4,
            X_rsa.align_check_is_needed());
        printf("%2d of %2d)  is warmed-up   ?  %d  {0=false, 1=true}\n", 
            ii + 1,
            bangz_ut4,
            X_rsa.align_check_is_warmed());
    }
    X_rsa.align_print();

//~
#ifdef WAIT_ENTER_CLEAR
printf("\n%s()  ,  complete\n", __func__);
wait_enter_clear();
#endif
}


#endif    // UNIT_TESTING


////////~~~~~~~~END>  unit_test_4.cpp
