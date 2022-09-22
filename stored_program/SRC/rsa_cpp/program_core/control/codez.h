/*
    program status codes with associated message

    compose, inherit, or virtualize the "common_utility" class for easiest use
    the status codes are already implement in the class
*/

#ifndef H_codez
#define H_codez


// program satus codes, messages
constexpr int ROWS_CODEZ = 99;    // number of status codes
constexpr int COLS_CODEZ = 88;      // largest width of the status code message
constexpr char CODEZ_MESSAGES[ROWS_CODEZ][COLS_CODEZ] =  
{
    "### 0   ,  no errors"                                  ,
    "### 1   ,  RSA API error"                              ,
    "### 2   ,  error in logic"                             ,
    "### 3   ,  clock() failed"                             ,
    "### 4   ,  clock_gettime() failed"                     ,
    "### 5   ,  called with bad paramerters"                ,
    "### 6   ,  returned initialized value"                 ,
    "### 7   ,  parameter not allocated"                    ,
    "### 8   ,  small string length"                        ,
    "### 9   ,  function call failed"                       ,
    "### 10  ,  fclose() failed"                            ,
    "### 11  ,  strcpy() failed"                            ,
    "### 12  ,  RSA not connected"                          ,
    "### 13  ,  fopen() failed"                             ,
    "### 14  ,  fseek() failed"                             ,
    "### 15  ,  ftell() failed"                             ,
    "### 16  ,  fclose() failed"                            ,
    "### 17  ,  FILE* is busy"                              ,
    "### 18  ,  FILE* not open"                             ,
    "### 19  ,  result not found"                           ,
    "### 20  ,  fread() failed"                             ,
    "### 21  ,  RSA API task failed"                        ,
    "### 22  ,  dynamic allocation failed"                  ,
    "### 23  ,  dynamic deallocation faile"                 ,
    "### 24  ,  pointer_not_null"                           ,
    "### 25  ,  pointer_is_null"                            ,
    "### 26  ,  rsa_too_hot"                                ,
    "### 27  ,  loop timed out"                             ,
    "### 28  ,  bad acquisition code"                       ,
    "### 29  ,  "

    "### 99  ,  unspecified"
};

// program status codes, code number (index corresponds to row in "CODEZ_MESSAGES")
enum CODEZ    
{
    _0_no_errors                         = 0  ,
    _1_rsa_api_error                     = 1  ,
    _2_error_in_logic                    = 2  ,
    _3_clock_failed                      = 3  ,
    _4_clock_gettime_failed              = 4  ,
    _5_called_with_bad_paramerters       = 5  ,
    _6_returned_initialized_value        = 6  ,
    _7_parameter_not_allocated           = 7  ,
    _8_small_string_length               = 8  ,
    _9_function_call_failed              = 9  ,
    _10_fclose_failed                    = 10 ,
    _11_strcpy_failed                    = 11 ,
    _12_rsa_not_connnected               = 12 ,
    _13_fopen_failed                     = 13 ,
    _14_fseek_failed                     = 14 ,
    _15_ftell_failed                     = 15 ,
    _16_fclose_failed                    = 16 ,
    _17_file_pointer_busy                = 17 ,
    _18_file_pointer_not_open            = 18 ,
    _19_result_not_found                 = 19 ,
    _20_fread_failed                     = 20 ,
    _21_rsa_api_task_failed              = 21 ,
    _22_dynamic_allocation_failed        = 22 ,
    _23_dynamic_deallocation_failed      = 23 ,
    _24_pointer_not_null                 = 24 ,
    _25_pointer_is_null                  = 25 , 
    _26_rsa_too_hot                      = 26 ,
    _27_loop_timed_out                   = 27 ,
    _28_bad_acquisition_code             = 28 ,
    _29 = 29,


    _99_unspecified                = 99
};


#endif


////////~~~~~~~~END>  codez.h
