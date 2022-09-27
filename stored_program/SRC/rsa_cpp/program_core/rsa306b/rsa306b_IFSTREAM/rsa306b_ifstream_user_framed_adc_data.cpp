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
    populates "vars.ifstream.framed_adc_data_v", std::vector
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
    - ifstream settings are correctly applied (IFSTREAM was enabled)
    first frame might be a header ?
    
    there is a lot of footer information in each frame, is it needed?
*/
CODEZ rsa306b_class::ifstream_acquire_framed_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif 

    uint8_t* frame_data = NULL;
    
    RSA_API::ReturnStatus temp = 
        RSA_API::IFSTREAM_GetIFFrames
        (
            &frame_data, 
            &this->_vars.ifstream.frame_bytes, 
            &this->_vars.ifstream.number_of_frames
        );
    
    int bytes_per_frame = 
        this->_vars.ifstream.frame_bytes / this->_vars.ifstream.number_of_frames;
    this->_vars.ifstream.framed_adc_data_v.resize(
        static_cast<std::size_t>(this->_vars.ifstream.number_of_frames));
    std::size_t placer = 0;
    
    for (int ii = 0; ii < this->_vars.ifstream.number_of_frames; ii++)
    {
        this->_vars.ifstream.framed_adc_data_v[ii].resize(SAMPLES_PER_FRAME);

        for (int jj = 0; jj < bytes_per_frame-1; jj++)
        {
            this->_vars.ifstream.framed_adc_data_v[ii][placer] =    // MSB first "start with most significant" big-endian
                static_cast<int16_t>
                (
                    (frame_data[ii*jj + jj]     << 8) |
                    (frame_data[ii*jj + jj + 1] << 0)
                );
            placer++;
            if (placer == SAMPLES_PER_FRAME)    // jump over the frame footer
            {
                placer = 0;
                break;    // get the next frame
            }
        }
    }

    (void)this->_ifstream_copy_frame_bytes();
    (void)this->_ifstream_copy_number_of_frames();
    (void)this->_ifstream_copy_framed_adc_data_v();
    frame_data = NULL;
    return this->set_api_status(temp);    // bitcheck is not applicable unless footer of each frame is checked
}


////~~~~


/*
    < 2 > public
    write a csv file after framed acquisition
    can't write regular acquisition
    must have successfully called "ifstream_acquire_framed_data()"
    be sure the file_path_name is allocated, even if it is on NULL
        that is how the output file is tracked
        output file either uses provided name, or default (if NULL)
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

    if (file_path_name == NULL)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "%s", this->cutil.codez_messages(CODEZ::_25_pointer_is_null));
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_25_pointer_is_null);
    }

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
    
    if (file_path_name[0] == '\0')    // using default output file_path_name
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

    this->_fp_write = fopen(this->_helper, "w");
    if (this->_fp_write == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_13_fopen_failed);
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

    (void)fclose(this->_fp_write);
    this->_fp_write = NULL;
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_ifstream_user_acquire_framed_adc_data.cpp
