/*
    "siq_manager_class", load the file into the class members

        public:
            < 1 >  load_file()

        private:
            #  none
            
*/

#include "siq_manager_class.h"


/*
    public < 1 >
    main worker of the class:
        - validates input
        - can be fed in batch from "batch_process_files()"
        - produces: parsed files, iq csv plot
    it is possible to not write anything, just make all 2 write options false
    a "false indicator" means that the file path name can be anything, just make it NULL to be safe

    ie
    to just load the member variables  : load_file(siq_input, NULL, NULL, false, false)
    to just write IQ  plot             : load_file(siq_input, NULL, output_iq, false, true)
    to load and write everything       : load_file(siq_input, output_parsed, output_iq, true, true)

    this is the only function in the class that calls 
    "fopen()" and "fclose()" 
    on the 2x member file pointers "_fp_read" and "_fp_write"
*/
CODEZ siq_manager_class::load_file
(
    const char* siq_input,
    const char* output_parsed,
    const char* output_iq,
    bool write_parsed,
    bool write_iq
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    (void)this->_init();    // re-initialize the member variables

    // guard begin
    if ((this->_fp_read != NULL) || (this->_fp_write != NULL))
    {
        return this->cutil.report_status_code(CODEZ::_17_file_pointer_busy);
    }
    if (this->cutil.extension_matched(siq_input, SIQ_RAW_EXT) == false)   // verify extension
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if(this->cutil.find_bytes_in_file(siq_input, this->_bytes_in_file) != CODEZ::_0_no_errors)    // check bytes
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    if(this->_bytes_in_file < static_cast<long>(SAMPLES_PER_FRAME))    // confirm bytes in file
    {
        return this->cutil.report_status_code(CODEZ::_5_called_with_bad_paramerters);
    }
    this->_fp_read = fopen(siq_input, "r");   // open siq
    if (this->_fp_read == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_13_fopen_failed);
    }
    // guard end

    (void)fseek(this->_fp_read, 0L, SEEK_SET);     // input file pointer set to start of file
    
    // load the header from the input file
    if (this->_populate_header() != CODEZ::_0_no_errors)
    {
        // close input and output files
        (void)fclose(this->_fp_read);
        this->_fp_read = NULL;
        return this->cutil.get_status_code();
    }

    // load the data from the input file
    if (this->_populate_data() != CODEZ::_0_no_errors)
    {
        // close input and output files
        (void)fclose(this->_fp_read);
        this->_fp_read = NULL;
        return this->cutil.get_status_code();
    }

    // close input file, data was successfully loaded
    (void)fclose(this->_fp_read);
    this->_fp_read = NULL;

    // make a parsed file, if requested
    if (write_parsed == true)
    {
        this->_fp_write = fopen(output_parsed, "w");
        if (this->_fp_write == NULL)
        {
            return this->cutil.report_status_code(CODEZ::_13_fopen_failed);
        }
        (void)fseek(this->_fp_write, 0L, SEEK_SET);     // output file pointer set to start of file
        if (this->_write_parsed() != CODEZ::_0_no_errors)
        {
            (void)fclose(this->_fp_write);
            this->_fp_write = NULL;
            return this->cutil.get_status_code();
        }
        (void)fclose(this->_fp_write);
        this->_fp_write = NULL;
    }

    // make the adc plot, if requsted
    if (write_iq == true)
    {
        this->_fp_write = fopen(output_iq, "w");
        if (this->_fp_write == NULL)
        {
            return this->cutil.report_status_code(CODEZ::_13_fopen_failed);
        }
        (void)fseek(this->_fp_write, 0L, SEEK_SET);     // output file pointer set to start of file
        if (this->_write_csv_iq() != CODEZ::_0_no_errors)
        {
            (void)fclose(this->_fp_write);
            this->_fp_write = NULL;
            return this->cutil.report_status_code(CODEZ::_9_function_call_failed);
        }
        (void)fclose(this->_fp_write);
        this->_fp_write = NULL;
    }
    
    return this->_copy_vars();    // update user's struct if "*.siq" file was successfully loaded
}


////////~~~~~~~~END>  siq_load_file.cpp
