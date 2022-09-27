/*
    API group "IQSTREAM"

    public :                   
        < 1 >  iqstream_write_csv()
    
    private :
        < 1 >  _iqstream_write_csv_cplx32()
        < 2 >  _iqstream_write_csv_cplxInt32()
        < 3 >  _iqstream_write_csv_cplxInt16()
*/


#include "../rsa306b_class.h"


/*
    < 1 > public
    designed to be use immidiatley after acquiring data direclty
    use the siq_manager if a file was made
    guards automatically determine the output requirement based on last acquisition settings
*/
CODEZ rsa306b_class::iqstream_write_csv
(
    char* file_path_name
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (this->_vars.iqstream.destination_select != RSA_API::IQSOD_CLIENT)
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "no data was output direct to client");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
    }
    if 
    (
        (this->_vars.iqstream.cplx32_v.size() <= 1) &&
        (
            this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE          ||
            this->_vars.iqstream.datatype_select == RSA_API::IQSODT_SINGLE_SCALE_INT32
        ) 
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "cplx32 vector has no data");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        (this->_vars.iqstream.cplxInt32_v.size() <= 1)  &&
        (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT32)
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "cplxInt32 vector has no data");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        (this->_vars.iqstream.cplxInt16_v.size() <= 1)  &&
        (this->_vars.iqstream.datatype_select == RSA_API::IQSODT_INT16) 
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "cplxInt16 vector has no data");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if 
    (
        this->_vars.iqstream.datatype_select != RSA_API::IQSODT_SINGLE             &&
        this->_vars.iqstream.datatype_select != RSA_API::IQSODT_SINGLE_SCALE_INT32 &&
        this->_vars.iqstream.datatype_select != RSA_API::IQSODT_INT32              &&
        this->_vars.iqstream.datatype_select != RSA_API::IQSODT_INT16 
    )
    {
        #ifdef DEBUG_MIN
            (void)snprintf(X_ddts, sizeof(X_ddts), "acquisition was in an unknow data format");
            (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    // guards are complete

    if (file_path_name[0] == '\0')    // using default output file_path_name
    {
        this->_reftime_get_current();
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s%s_%lu_%s",
            DATA_DIRECTORY_PROCESSED,
            IQSTREAM_FILE_NAME_BASE,
            this->_vars.reftime.current.timestamp,
            DATA_OUTPUT_EXTENSTION);
        (void)sprintf(file_path_name, "%s", this->_helper);
    }
    else   // using the given file-path-name
    {
        (void)snprintf(this->_helper, sizeof(this->_helper), "%s", file_path_name);
    }

    this->_fp_write = fopen(this->_helper, "w");
    if (this->_fp_write == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_13_fopen_failed);
    }
    // file is open

    (void)sprintf(this->_helper, "%s,%s,%s,\n",   // place the CSV header
        IQSTREAM_FIELD_1,
        IQSTREAM_FIELD_2,
        IQSTREAM_FIELD_3);
    (void)fputs(this->_helper, this->_fp_write);


    // call for writting
    CODEZ temp = CODEZ::_0_no_errors;
    switch (this->_vars.iqstream.datatype_select)
    {
        case (RSA_API::IQSODT_SINGLE)             : temp = this->_iqstream_write_csv_cplx32   (); break;
        case (RSA_API::IQSODT_SINGLE_SCALE_INT32) : temp = this->_iqstream_write_csv_cplx32   (); break;
        case (RSA_API::IQSODT_INT32)              : temp = this->_iqstream_write_csv_cplxInt32(); break;
        case (RSA_API::IQSODT_INT16)              : temp = this->_iqstream_write_csv_cplxInt16(); break;
        default :
            #ifdef DEBUG_MIN
                (void)snprintf(X_ddts, sizeof(X_ddts), "%s", this->cutil.codez_messages(CODEZ::_2_error_in_logic));
                (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(true);
            #endif
            (void)fclose(this->_fp_write);
            this->_fp_write = NULL;
            return this->cutil.report_status_code(CODEZ::_2_error_in_logic);
    }

    (void)fclose(this->_fp_write);
    this->_fp_write = NULL;
    return this->cutil.report_status_code(temp);
}

////~~~~


/*
    < 1 > private
    the cplx32_v was filled, dumping data to a csv
*/
CODEZ rsa306b_class::_iqstream_write_csv_cplx32()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    std::size_t v_size = this->_vars.iqstream.cplx32_v.size();
    for (std::size_t kk = 0; kk < v_size; kk++)
    {
        if (kk == v_size-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%0.9f,%0.9f\n",
                kk,
                this->_vars.iqstream.cplx32_v[kk].i,
                this->_vars.iqstream.cplx32_v[kk].q);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%0.9f,%0.9f,\n",
                kk,
                this->_vars.iqstream.cplx32_v[kk].i,
                this->_vars.iqstream.cplx32_v[kk].q);
        }
        fputs(this->_helper, this->_fp_write);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 2 > private
    the cplxInt32_v was filled, dumping data to a csv
*/
CODEZ rsa306b_class::_iqstream_write_csv_cplxInt32()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    std::size_t v_size = this->_vars.iqstream.cplxInt32_v.size();
    for (std::size_t kk = 0; kk < v_size; kk++)
    {
        if (kk == v_size-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d,%d\n",
                kk,
                this->_vars.iqstream.cplxInt32_v[kk].i,
                this->_vars.iqstream.cplxInt32_v[kk].q);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d,%d,\n",
                kk,
                this->_vars.iqstream.cplxInt32_v[kk].i,
                this->_vars.iqstream.cplxInt32_v[kk].q);
        }
        fputs(this->_helper, this->_fp_write);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////~~~~


/*
    < 3 > private
    the cplxInt16_v was filled, dumping data to a csv
*/
CODEZ rsa306b_class::_iqstream_write_csv_cplxInt16()
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    std::size_t v_size = this->_vars.iqstream.cplxInt16_v.size();
    for (std::size_t kk = 0; kk < v_size; kk++)
    {
        if (kk == v_size-1)
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d,%d\n",
                kk,
                this->_vars.iqstream.cplxInt16_v[kk].i,
                this->_vars.iqstream.cplxInt16_v[kk].q);
        }
        else
        {
            (void)snprintf(this->_helper, sizeof(this->_helper), "%lu,%d,%d,\n",
                kk,
                this->_vars.iqstream.cplxInt16_v[kk].i,
                this->_vars.iqstream.cplxInt16_v[kk].q);
        }
        fputs(this->_helper, this->_fp_write);
    }
    return this->cutil.report_status_code(CODEZ::_0_no_errors);
}


////////~~~~~~~~END>  rsa306b_iqstream_write_csv.cpp
