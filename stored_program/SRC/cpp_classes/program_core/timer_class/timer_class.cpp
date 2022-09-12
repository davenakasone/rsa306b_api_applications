/*
    implementation, simple class, basic use, just need one file

    public :
        < 1 >   timer_class()
        < 2 >   ~timer_class()
        < 3 >   time_split_start()
        < 4 >   time_split_stop()
        < 5 >   get_time_split()
        < 6 >   get_time_split_W()
        < 7 >   get_running_time()
        < 8 >   get_running_time_w()
        < 9 >   print_time_split()
        < 10 >  print_running_time()
        < 11 >  print_both()
        < 12 >  return_split_string()
    
    private :
        < 1 >  _timer_init()
        < 2 >  _set_running_time()
        < 3 >  _set_running_time_w()
*/

#include "timer_class.h"


/*
    < 1 > public
    constructor
    start times (wall and CPU) are recorded
*/
timer_class::timer_class()
{
#ifdef DE_BUG
    debug_init();
#endif
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->_begin = clock();                             // wall-clock stating time is recorded
    clock_gettime(CLOCK_MONOTONIC, &this->_w_begin);    // CPU starting time is recorded
    this->_timer_init();
}


////~~~~


/*
    < 2 > public
    nice to print running duration if using a global instance
*/
timer_class::~timer_class()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->print_running_time(true);

#ifdef DE_BUG
    debug_stop();
#endif
}


////~~~~


/*
    < 3 > public
    user marks the start of a time-split of interest
    variables are updated
    overides previous start if user gets out of sequence
*/
void timer_class::time_split_start()
{
    this->_trail   = this->get_running_time();
    this->_w_trail = this->get_running_time_w();

    this->_split_is_marked = true;
    this->_split           = this->_SPLIT_FAIL;
    this->_w_split         = this->_SPLIT_FAIL;
}


////~~~~


/*
    < 4 > public
    user marks the end of a time-split of interest
    variables are updated
    if there was not a call to mark the start of the time-split,
        then results are invalid
*/
void timer_class::time_split_stop()
{
    if (this->_split_is_marked == false)
    {
        this->_split   = this->_SPLIT_FAIL;
        this->_w_split = this->_SPLIT_FAIL;
        return;
    }

    double temp_lead       = this->get_running_time();
    double temp_lead_w     = this->get_running_time_w();
    this->_split           = temp_lead - this->_trail;
    this->_w_split         = temp_lead_w - this->_w_trail;
    this->_split_is_marked = false;
}


////~~~~


/*
    < 5 > public
*/
double timer_class::get_time_split()
{
    return this->_split;
}


////~~~~


/*
    < 6 > public
*/
double timer_class::get_time_split_w()
{
    return this->_w_split;
}


////~~~~


/*
    < 7 > public
*/
double timer_class::get_running_time()
{
    this->_set_running_time();
    return this->_running;
}


////~~~~


/*
    < 8 > public
*/
double timer_class::get_running_time_w()
{
    this->_set_running_time_w();
    return this->_w_running;
}


////~~~~


/*
    < 9 > public
    only valid if a proper time-split was marked,
        called: time_split_start() and time_split_stop()
*/
void timer_class::print_time_split
(
    bool new_lines
)
{
    if (this->_split == this->_SPLIT_FAIL || 
        this->_w_split == this->_SPLIT_FAIL)
    {
        return;    // no split to print
    }
    if (new_lines == true)
    {
        printf("\n{{{timer}}}  split duration (seconds)  >>>  CPU:  %0.12lf  ,  wall:  %0.12lf  {{{timer}}}\n", 
            this->get_time_split(), 
            this->get_time_split_w());
    }
    else
    {
        printf("{{{timer}}}  split duration (seconds)  >>>  CPU:  %0.12lf  ,  wall:  %0.12lf  {{{timer}}}", 
            this->get_time_split(), 
            this->get_time_split_w());
    }
    
}


////~~~~


/*
    < 10 > public
    always valid if the object was constructed properly
*/
void timer_class::print_running_time
(
    bool new_lines
)
{
    if (new_lines == true)
    {
        printf("\n{{{timer}}}  total running (seconds)   >>>  CPU:  %0.12lf  ,  wall:  %0.12lf  {{{timer}}}\n",
            this->get_running_time(), 
            this->get_running_time_w());
    }
    else
    {
        printf("{{{timer}}}  total running (seconds)   >>>  CPU:  %0.12lf  ,  wall:  %0.12lf  {{{timer}}}", 
            this->get_running_time(), 
            this->get_running_time_w());
    }
}


////~~~~


/*
    < 11 > public
    print both, adding "\n"
*/
void timer_class::print_both()
{
    printf("\n");
    if (this->_split != this->_SPLIT_FAIL &&
        this->_w_split != this->_SPLIT_FAIL)
    {
        this->print_time_split(false);
        printf("\n");
    }
    this->print_running_time(false);
    printf("\n\n");
}


////~~~~


/*
    < 12 > public
*/
char* timer_class::return_split_string()
{
    memset(this->_helper, '\0', BUF_E);
    if (this->_split != this->_SPLIT_FAIL &&
        this->_w_split != this->_SPLIT_FAIL)
    {
        snprintf(this->_helper, BUF_E-1, "SPLIT FAILED");
    }
    else
    {
        snprintf(this->_helper, BUF_E-1, 
            "{{{ time-split }}}  CPU:  %0.9lf  ,  WALL:  %0.9lf",
            this->_split,
            this->_w_split);
    }
    return this->_helper;
}


////~~~~


/*
    < 1 > private
*/
void timer_class::_timer_init()
{
    this->_split_is_marked = false;

    this->_lead    = clock();
    this->_trail   = this->_SPLIT_FAIL;
    this->_running = this->_SPLIT_FAIL;
    this->_split   = this->_SPLIT_FAIL;

    clock_gettime(CLOCK_MONOTONIC, &this->_w_lead);
    this->_w_trail   = this->_SPLIT_FAIL;
    this->_w_running = this->_SPLIT_FAIL;
    this->_w_split   = this->_w_split;

    memset(this->_helper, '\0', BUF_E);
}


////~~~~


/*
    < 2 > private
*/
void timer_class::_set_running_time()
{
    this->_lead    = clock();                                       // "lead" is current time
    double temp    = (double)this->_lead - (double)this->_begin;    // find the difference (now - beginning) 
    this->_running =  temp / (double)CLOCKS_PER_SEC;                // convert the time and assign
}


////~~~~


/*
    < 3 > private
*/
void timer_class::_set_running_time_w()
{
    clock_gettime(CLOCK_MONOTONIC, &this->_w_lead);
    double temp_begin = (double)this->_w_begin.tv_sec + (double)this->_w_begin.tv_nsec / 1.0e9;
    double temp_lead  = (double)this->_w_lead.tv_sec + (double)this->_w_lead.tv_nsec / 1.0e9;
    this->_w_running  = temp_lead - temp_begin;
}


////////~~~~~~~~END>  timer_class.cpp
