/*
    implementation, simple class, basic use, just need one file

    public :
        < 1 >  cpu_timer_class()
        < 2 >  ~cpu_timer_class()
        < 3 >  time_split_start()
        < 4 >  time_split_stop()
        < 5 >  print_time_split()
        < 6 >  print_running_time()
        < 7 >  get_time_split()
        < 8 >  get_time_split_W()
        < 9 >  get_running_time()
        < 10 >  get_running_time_w()
    
    private :
        < 1 >  _timer_init()
*/

#include "cpu_timer_class.h"


/*
    < 1 >
*/
cpu_timer_class::cpu_timer_class()
{
    this->_begin = clock();
    clock_gettime(CLOCK_MONOTONIC, &this->_w_begin);
    this->_timer_init();
}


////~~~~


/*
    < 2 >
*/
cpu_timer_class::~cpu_timer_class()
{
    this->print_running_time();
}


////~~~~


/*
    < 3 >
*/
void cpu_timer_class::time_split_start()
{
    this->_trail = this->get_running_time();
    this->_w_trail = this->get_running_time_w();
    this->_split_is_marked = true;
}


////~~~~


/*
    < 4 >
*/
void cpu_timer_class::time_split_stop()
{
    if (this->_split_is_marked == true)
    {
        double temp_lead = this->get_running_time();
        double temp_lead_w = this->get_running_time_w();
        this->_split = temp_lead - this->_trail;
        this->_w_split = temp_lead_w - this->_w_trail;
        this->_split_is_marked = false;
    }
    else
    {
        this->_split = this->_SPLIT_FAIL;
        this->_w_split = this->_SPLIT_FAIL;
    }
    
}


////~~~~


/*
    < 5 >
*/
void cpu_timer_class::print_time_split()
{
    printf("\n{{{timer}}}  split duration (seconds)  >>>  CPU:  %0.12lf  ,  wall:  %0.12lf  {{{timer}}} \n", 
        this->_split, this->_w_split);
}


////~~~~


/*
    < 6 >
*/
void cpu_timer_class::print_running_time()
{
    printf("\n{{{timer}}}  total running (seconds)  >>>  CPU:  %0.12lf  ,  wall:  %0.12lf  {{{timer}}} \n", 
        this->get_running_time(), this->get_running_time_w());
}


////~~~~


/*
    < 7 >
*/
double cpu_timer_class::get_time_split()
{
    return this->_split;
}


////~~~~


/*
    < 8 >
*/
double cpu_timer_class::get_time_split_w()
{
    return this->_w_split;
}


////~~~~


/*
    < 9 >
*/
double cpu_timer_class::get_running_time()
{
    this->_lead = clock();
    double temp = (double)this->_lead - (double)this->_begin;
    this->_running =  temp / (double)CLOCKS_PER_SEC;
    return this->_running;
}


////~~~~


/*
    < 9 >
*/
double cpu_timer_class::get_running_time_w()
{
    clock_gettime(CLOCK_MONOTONIC, &this->_w_lead);
    double temp_begin = (double)this->_w_begin.tv_sec + (double)this->_w_begin.tv_nsec / 1.0e9;
    double temp_lead = (double)this->_w_lead.tv_sec + (double)this->_w_lead.tv_nsec / 1.0e9;
    this->_w_running = temp_lead - temp_begin;
    return this->_w_running;
}


////~~~~


/*
    < 1 > private
*/
void cpu_timer_class::_timer_init()
{
    this->_split_is_marked = false;

    this->_lead = clock();
    this->_trail = this->_SPLIT_FAIL;
    this->_running = this->_SPLIT_FAIL;
    this->_split = this->_SPLIT_FAIL;

    this->_w_trail = this->_SPLIT_FAIL;
    clock_gettime(CLOCK_MONOTONIC, &this->_w_lead);
    this->_w_running = this->_SPLIT_FAIL;
    this->_w_split = this->_w_split;
}


////////~~~~~~~~END>  cpu_timer_class.cpp
