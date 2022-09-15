/*
    common_utility, class 

    public :
        < 1 >  timer_split_start()
        < 2 >  timer_split_stop()
        < 3 >  timer_print_split()
        < 4 >  timer_print_running()
        < 5 >  timer_print_both()
        < 6 >  timer_get_split_cpu()
        < 7 >  timer_get_split_wall()
        < 8 >  timer_get_running_cpu()
        < 9 >  timer_get_running_wall()
    
    private :
        < 1 >  _timer_init()
        < 2 >  _timer_set_running_cpu()
        < 3 >  _timer_set_running_wall()
*/

#include "common_utility.h"


/*
    < 1 > public
    user marks the start of a time-split of interest
    "_trail_cpu" and "_trail_wall" are set to the current running times

    user is responsible for calling "timer_split_start()" and "timer_split_stop()"
    an initial call to "timer_split_start()" and multiple "timer_split_stops()" can
    be used to mark multiple points in time for an interval of interest

    otherwise, use a single call to "timer_split_start()" and conclude with
    a single call to "timer_split_stop"
    this process can be repeated to measure the duration for tasks
*/
CODEZ common_utility::timer_split_start()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_timer_set_running_cpu() != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    this->_trail_cpu = this->_running_cpu;

    if (this->_timer_set_running_wall() != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    this->_trail_wall = this->_running_wall;

    this->_split_cpu  = INIT_DOUBLE;
    this->_split_wall = INIT_DOUBLE;
    return this->_status_code;
}


////~~~~


/*
    < 2 > public
    user marks the end of a time-split of interest
    calculations are made to reflect the measured interval of time


    user is responsible for calling "timer_split_start()" and "timer_split_stop()"
    an initial call to "timer_split_start()" and multiple "timer_split_stops()" can
    be used to mark multiple points in time for an interval of interest

    otherwise, use a single call to "timer_split_start()" and conclude with
    a single call to "timer_split_stop"
    this process can be repeated to measure the duration for tasks
*/
CODEZ common_utility::timer_split_stop()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_trail_cpu < 0 || this->_trail_wall < 0)
    {
        #ifdef DEBUG_MIN
             (void)snprintf(X_ddts, sizeof(X_ddts), "trail timers are negative");
             (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_status_code(CODEZ::_2_error_in_logic);
    }
    if (this->_timer_set_running_cpu() != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    if (this->_timer_set_running_wall() != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }
    this->_split_cpu  = this->_running_cpu - this->_trail_cpu;
    this->_split_wall = this->_running_wall - this->_trail_wall;
    return this->_status_code;
}


////~~~~


/*
    < 3 > public
*/
CODEZ common_utility::timer_print_split
(
    int new_lines_begin, 
    int new_lines_end
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (new_lines_begin < 0 || new_lines_end < 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "bad parameters:  %d  ,  %d",
                new_lines_begin,
                new_lines_end);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    for (int ii = 0; ii < new_lines_begin; ii++)
    {
        (void)printf("\n");
    }
    (void)printf(_TIMER_FORMAT_SPLIT, this->_split_cpu, this->_split_wall);
    for (int ii = 0; ii < new_lines_end; ii++)
    {
        (void)printf("\n");
    }
    return this->_status_code;
}


////~~~~


/*
    < 4 > public
*/
CODEZ common_utility::timer_print_running
(
    int new_lines_begin, 
    int new_lines_end
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (new_lines_begin < 0 || new_lines_end < 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "bad parameters:  %d  ,  %d",
                new_lines_begin,
                new_lines_end);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    if (this->_timer_set_running_cpu()!= CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }

    if (this->_timer_set_running_wall() != CODEZ::_0_no_errors)
    {
        return this->_status_code;
    }

    for (int ii = 0; ii < new_lines_begin; ii++)
    {
        (void)printf("\n");
    }
    (void)printf(_TIMER_FORMAT_RUNNING, this->_running_cpu, this->_running_wall);
    for (int ii = 0; ii < new_lines_end; ii++)
    {
        (void)printf("\n");
    }
    return this->_status_code;
}


////~~~~


/*
    < 5 > public
*/
CODEZ common_utility::timer_print_both
(
    int new_lines_begin, 
    int new_lines_end
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (new_lines_begin < 0 || new_lines_end < 0)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "bad parameters:  %d  ,  %d",
                new_lines_begin,
                new_lines_end);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->_report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }

    for (int ii = 0; ii < new_lines_begin; ii++)
    {
        (void)printf("\n");
    }
    (void)this->timer_print_split(0,1);
    (void)this->timer_print_running(0,1);
    for (int ii = 0; ii < new_lines_end; ii++)
    {
        (void)printf("\n");
    }
    return this->_status_code;
}


////~~~~


/*
    < 6 > public
*/
CODEZ common_utility::timer_get_split_cpu
(
    double& c_split
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_split_cpu > 0)
    {
        c_split = this->_split_cpu;
        return this->_report_status_code(CODEZ::_0_no_errors);
    }
    else
    {
        #ifdef DEBUG_MAX
            (void)snprintf(X_ddts, sizeof(X_ddts), "returning initialized timesplit:  %lf",
                this->_split_cpu);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(false);
        #endif
        c_split = INIT_DOUBLE;
        return this->_report_status_code(CODEZ::_6_returned_initialized_value);
    }
}


////~~~~


/*
    < 7 > public
*/
CODEZ common_utility::timer_get_split_wall
(
    double& w_split
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_split_wall > 0)
    {
        w_split = this->_split_wall;
        return this->_report_status_code(CODEZ::_0_no_errors);
    }
    else
    {
        #ifdef DEBUG_MAX
            (void)snprintf(X_ddts, sizeof(X_ddts), "returning initialized timesplit:  %lf",
                this->_split_wall);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MAX_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(false);
        #endif
        w_split = INIT_DOUBLE;
        return this->_report_status_code(CODEZ::_6_returned_initialized_value);
    }
}


////~~~~


/*
    < 8 > public
*/
CODEZ common_utility::timer_get_running_cpu
(
    double& c_run
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_timer_set_running_cpu() == CODEZ::_0_no_errors)
    {
        c_run = this->_running_cpu;
    }
    else
    {
        c_run = INIT_DOUBLE;
    }
    return this->_status_code;
}


////~~~~


/*
    < 9 > public
*/
CODEZ common_utility::timer_get_running_wall
(
    double& w_run
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_timer_set_running_wall() == CODEZ::_0_no_errors)
    {
        w_run = this->_running_wall;
    }
    else
    {
        w_run = INIT_DOUBLE;
    }
    return this->_status_code;
}


////~~~~


/*
    < 1 > private
    note that the beginning CPU and wall-clock updated once
    see the constructor
*/
CODEZ common_utility::_timer_init()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_begin_cpu = clock();                                  // CPU starting time is recorded
    (void)clock_gettime(CLOCK_MONOTONIC, &this->_begin_wall);    // wall-clock stating time is recorded

    this->_lead_cpu    = clock();
    this->_running_cpu = INIT_DOUBLE;
    this->_split_cpu   = INIT_DOUBLE;
    this->_trail_cpu   = INIT_DOUBLE;

    (void)clock_gettime(CLOCK_MONOTONIC, &this->_lead_wall);
    this->_running_wall = INIT_DOUBLE;
    this->_split_wall   = INIT_DOUBLE;
    this->_trail_wall   = INIT_DOUBLE;

    return this->_report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 2 > private
    records the current time
    calculates difference from current time to object's creation
    result is stored in "_running_cpu"
    success is returned if a time difference was detected, 
        else failure in clock()
*/
CODEZ common_utility::_timer_set_running_cpu()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // store the current time
    this->_lead_cpu = clock();

    // find the difference (now - beginning) 
    double temp = static_cast<double>(this->_lead_cpu) - static_cast<double>(this->_begin_cpu); 

    // convert difference from ticks to seconds, and store the result
    this->_running_cpu =  temp / static_cast<double>(CLOCKS_PER_SEC); 

    // evaluate the success of the calculation and return the result
    if (this->_running_cpu > 0) 
    {
        return this->_report_status_code(CODEZ::_0_no_errors);
    }
    else
    {
        return this->_report_status_code(CODEZ::_3_clock_failed);
    }
}


////~~~~


/*
    < 3 > private
    records the current time
    calculates difference from current time to object's creation
    result is stored in "_running_wall"
    success is returned if a time difference was detected, 
        else failure in clock_gettime() 
*/
CODEZ common_utility::_timer_set_running_wall()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    // store the current time
    (void)clock_gettime(CLOCK_MONOTONIC, &this->_lead_wall);

    // combined seconds + nano seconds, for both points in time
    double temp_begin = static_cast<double>(this->_begin_wall.tv_sec) + 
        static_cast<double>(this->_begin_wall.tv_nsec) / 1.0e9;
    double temp_lead  = static_cast<double>(this->_lead_wall.tv_sec) + 
        static_cast<double>(this->_lead_wall.tv_nsec) / 1.0e9;

    // find difference and store the result
    this->_running_wall = temp_lead - temp_begin;

    // evaluate the success of the calculation and return the result
    if (this->_running_wall > 0) 
    {
        return this->_report_status_code(CODEZ::_0_no_errors);
    }
    else
    {
        return this->_report_status_code(CODEZ::_4_clock_gettime_failed);
    }
}


////////~~~~~~~~END>  common_utility.cpp
