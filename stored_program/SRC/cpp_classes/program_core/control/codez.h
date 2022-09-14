/*
    program status codes with associated message

    compose, inherit, or virtualize the "common_utility" class for easiest use
    the status codes are already implement in the class
*/

#ifndef H_codez
#define H_codez


// program satus codes, messages
constexpr int ROWS_CODEZ = 1000;    // number of status codes
constexpr int COLS_CODEZ = 88;      // largest width of the status code message
constexpr char CODEZ_MESSAGES[ROWS_CODEZ][COLS_CODEZ] =  
{
    "### 0   ,  no errors",
    "### 1   ,  rsa api error",
    "### 2   ,  error in logic",
    "### 3   ,  clock() failed",
    "### 4   ,  clock_gettime() failed",
    "### 5   ,  called with bad paramerters",
    "### 6   ,  returned initialized value",
    "### 7   ,  parameter not allocated",
    "### 8   ,  small string length",
    "### 9   ,  function call failed",
};

// program status codes, code number (index corresponds to row in "CODEZ_MESSAGES")
enum CODEZ    
{
    _0_no_errors                   = 0,
    _1_rsa_api_error               = 1,
    _2_error_in_logic              = 2,
    _3_clock_failed                = 3,
    _4_clock_gettime_failed        = 4,
    _5_called_with_bad_paramerters = 5,
    _6_returned_initialized_value  = 6,
    _7_parameter_not_allocated     = 7,
    _8_small_string_length         = 8,
    _9_function_call_failed        = 9
};


#endif


////////~~~~~~~~END>  codez.h
