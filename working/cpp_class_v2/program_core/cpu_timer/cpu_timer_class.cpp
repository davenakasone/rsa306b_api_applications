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
        < 8 >  get_running_time()
    
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
    this->_trail = clock();
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
        this->_lead = clock();
        this->_temp = (double)((double)this->_lead - (double)this->_trail);
        this->_split =  (double)(this->_temp / (double)CLOCKS_PER_SEC);
        this->_split_is_marked = false;
    }
    else
    {
        this->_split = this->_SPLIT_FAIL;
    }
    
}


////~~~~


/*
    < 5 >
*/
void cpu_timer_class::print_time_split()
{
    printf("\nCPU processing time during interval:  %0.12lf seconds\n", 
        this->_split);
}


////~~~~


/*
    < 6 >
*/
void cpu_timer_class::print_running_time()
{
    this->get_running_time();
    printf("\nCPU total processing time:  %0.12lf seconds\n", 
        this->_running);
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
double cpu_timer_class::get_running_time()
{
    this->_lead = clock();
    this->_temp = (double)((double)this->_lead - (double)this->_begin);
    this->_running =  (double)(this->_temp / (double)CLOCKS_PER_SEC);
    return this->_running;
}


////~~~~


/*
    < 1 > private
*/
void cpu_timer_class::_timer_init()
{
    this->_split_is_marked = false;
    this->_lead = clock();
    this->_trail = clock();
    this->_running = this->_SPLIT_FAIL;
    this->_split = this->_SPLIT_FAIL;
    this->_temp = this->_SPLIT_FAIL;
}


////////~~~~~~~~END>  cpu_timer_class.cpp
