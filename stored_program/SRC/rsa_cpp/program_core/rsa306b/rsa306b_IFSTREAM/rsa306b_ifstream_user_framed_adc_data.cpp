/*
    API group "IFSTREAM", user funcitons

    public :
        < 1 >  ifstream_acquire_framed_adc_data()
        < 2 >  ifstream_write_csv_framed_data()
    
    private :
        #  none
*/

#include "../rsa306b_class.h"

/*
    < 1 > public
    populates "vars.ifstream.adc_data_v", std::vector
    user can make a csv when done or conduct what ever processing is desired
    equalization and scaling parameters are already available if procedure was followed

    0) user updated the public "vars.ifstream.*", ensuring "vars.ifstream.output_destination_select == RSA_API::IFSOD_CLIENT"
    1) user called "ifstream_set_vars()"  // successfully 
    2) user called "device_run()"         // must be called for first iteration
    3) user calls this function for as many acquisitions as desired (the vector is over-wrtiten every call)
    4) user calls "device_stop()" when done, unless another type of acquisition is desired

    all the guards are ommitted, at a minimum:
    - the device is connected
    - the device is running
    - ifstream settings are correctly applied

    IFSTREAM_SetEnable() is only for files ?
*/
CODEZ rsa306b_class::ifstream_acquire_framed_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    

    //return this->set_api_status(temp);    // see bitcheck result
}


////~~~~


/*
    < 2 > public
*/
CODEZ rsa306b_class::ifstream_write_csv_framed_data
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    std::size_t v_rows = this->_vars.ifstream.framed_adc_data_v.size();
    std::size_t v_cols = this->_vars.ifstream.framed_adc_data_v[0].size();

    if ((v_rows < 1LU) || (v_cols < 1LU)) 
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "ifstream.adc_framed_data_v.size() =  %lu x %lu", 
                v_rows, 
                v_cols);
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    
    if (file_path_name == NULL)
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_%lu_%s",
            DATA_DIRECTORY_PROCESSED,
            IFSTREAM_FILE_NAME_BASE,
            this->_vars.reftime.current.timestamp,
            DATA_OUTPUT_EXTENSTION);
        (void)sprintf(file_path_name, "%s", this->_helper);
    }
    else
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s", file_path_name);
    }

    if (this->cutil.exe_fopen(this->_helper, "w", this->_fp_write) != CODEZ::_0_no_errors)
    {
        return this->cutil.get_status_code();
    }
    
    (void)sprintf(this->_helper, "%s,%s,\n",
        IFSTREAM_FIELD_1,
        IFSTREAM_FIELD_2);
    (void)fputs(this->_helper, this->_fp_write);

    for (std::size_t rowz = 0; rowz < v_rows; rowz++)
    {
        for (std::size_t colz = 0; colz < v_cols; colz++)
        {
            if ((rowz == v_rows-1) && 
                (colz == v_cols-1)  )
            {
                (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d\n", 
                    colz + colz*rowz,
                    this->_vars.ifstream.framed_adc_data_v[rowz][colz]);
            }
            else
            {
                (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d,\n", 
                    colz + colz*rowz,
                    this->_vars.ifstream.framed_adc_data_v[rowz][colz]);
            }
            (void)fputs(this->_helper, this->_fp_write);
        }
    }

    return this->cutil.exe_fclose(this->_fp_write);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_acquire_framed_adc_data.cpp
