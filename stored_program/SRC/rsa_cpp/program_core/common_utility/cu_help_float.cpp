/*
    common_utility, class 

    public :
        < 1 >  h_new_float_d1()
        < 2 >  h_copy_float_to_vector_d1()
        < 3 >  h_delete_float_d1()

    private :
        #  none
*/

#include "common_utility.h"


/*
    < 1 > public
    allocate any float*, using new
    can change to malloc(), calloc(), etc
    main point is that allocations occur in 1 place
*/
CODEZ common_utility::h_new_float_d1
(
    float* array_pointer, 
    int allocation_size
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    // if (array_pointer != NULL)
    // {
    //     return this->report_status_code(CODEZ::_24_pointer_not_null);
    // }

    try
    {
        array_pointer = new float[allocation_size];
    }
    catch(...)
    {
        return this->report_status_code(CODEZ::_22_dynamic_allocation_failed);
    }
    return report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 2 > public
    copies array pointer elements into the std::vector
    main point is to ensure that copies occur in 1 place
*/
CODEZ common_utility::h_copy_float_to_vector_d1
(
    const float* array_pointer, 
    int elements, 
    std::vector<float>& destination
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    // if (array_pointer == NULL)
    // {
    //     return this->report_status_code(CODEZ::_25_pointer_is_null);
    // }
    // if (elements < 1)
    // {
    //     return this->report_status_code(CODEZ::_5_called_with_bad_paramerters);
    // }

    //destination.clear();
    destination.resize(static_cast<std::size_t>(elements));
    destination.assign(array_pointer, array_pointer + elements);
  
    return report_status_code(CODEZ::_0_no_errors);    
}


////~~~~


/*
    < 3 > public
    deallocate and float* that was allocated with new, using delete
    main point is that allocations occur in 1 place
*/
CODEZ common_utility::h_delete_float_d1
(
    float* array_pointer
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    // if (array_pointer == NULL)
    // {
    //     return report_status_code(CODEZ::_0_no_errors);
    // }

    delete [] array_pointer;
    array_pointer = NULL;
    return report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  cu_help_float.cpp