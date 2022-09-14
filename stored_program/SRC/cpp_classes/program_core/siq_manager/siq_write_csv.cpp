/*
    initializer of the 'siq_handler_class'
    copies private struct to the public struct

    public:
        < 1 >  write_iq_to_csv()
        < 2 >  write_iq_to_csv_batch()
        
    private:
        #  none
    

*/

#include "siq_manager_class.h"

//static void change_directory(char* file_path_name, char* new_directory);

/*
    < 1 > public
    given a valid "*.siq" file, 
    data is loaded and written to a CSV
    if "output_file" == NULL, then file name remains unchanged
*/
void siq_manager_class::write_iq_to_csv
(
    char* input_file, 
    char* output_file
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    this->load_file(input_file);
    if (this->_ec != no_error)
    {
        return;
    }

    char n_output_file[BUF_E];
    if (output_file == NULL)   // same name, just change extension
    {
        strncpy(n_output_file, input_file, BUF_E-1);
        n_output_file[strlen(input_file)-3] = 'c';
        n_output_file[strlen(input_file)-2] = 's';
        n_output_file[strlen(input_file)-1] = 'v';
    }
    else // enforce the CSV format
    {
        output_file[strlen(output_file)-3] = 'c';
        output_file[strlen(output_file)-2] = 's';
        output_file[strlen(output_file)-1] = 'v';
    }

    if (this->_vars.f8_iq_sample_pairs <= static_cast<int>(INIT_STL_LENGTH))
    {
        this->_set_error_code(file_loaded_with_no_data);
        return;
    }

    if (output_file == NULL)
    {
        this->_prepare_any_output(n_output_file);
    }
    else
    {
        this->_prepare_any_output(output_file);
    }
    if (this->_ec != no_error)
    {
        return;
    }
    snprintf(this->_holder, BUF_E-1, "I,Q\n");
    fputs(this->_holder, this->_fptr_write);

    if (strcmp(this->_vars.f9_number_format, NUMBER_FORMATS[NUMBER_FORMAT_SINGLE]) == 0)
    {
        for (int xx = 0; xx < this->_vars.f8_iq_sample_pairs; xx++)
        {
            if (xx == this->_vars.f8_iq_sample_pairs-1)
            {
                snprintf(this->_holder, BUF_E-1, "%f,%f",
                    this->_vars.data_block_cplx32_v[xx].i,
                    this->_vars.data_block_cplx32_v[xx].q);
            }
            else
            {
                snprintf(this->_holder, BUF_E-1, "%f,%f\n",
                    this->_vars.data_block_cplx32_v[xx].i,
                    this->_vars.data_block_cplx32_v[xx].q);
            }
            fputs(this->_holder, this->_fptr_write);
        }
    }
    else if (strcmp(this->_vars.f9_number_format, NUMBER_FORMATS[NUMBER_FORMAT_INT32]) == 0)
    {
        for (int xx = 0; xx < this->_vars.f8_iq_sample_pairs; xx++)
        {
            // use scale factor here (if wanted)
            if (xx == this->_vars.f8_iq_sample_pairs-1)
            {
                snprintf(this->_holder, BUF_E-1, "%d,%d",
                    static_cast<int>(this->_vars.data_block_cplxint32_v[xx].i),
                    static_cast<int>(this->_vars.data_block_cplxint32_v[xx].q));
            }
            else
            {
                snprintf(this->_holder, BUF_E-1, "%d,%d\n",
                    static_cast<int>(this->_vars.data_block_cplxint32_v[xx].i),
                    static_cast<int>(this->_vars.data_block_cplxint32_v[xx].q));
            }
            fputs(this->_holder, this->_fptr_write);
        }
    }
    else if (strcmp(this->_vars.f9_number_format, NUMBER_FORMATS[NUMBER_FORMAT_INT16]) == 0)
    {
        for (int xx = 0; xx < this->_vars.f8_iq_sample_pairs; xx++)
        {
            // use scale factor here (if wanted)
            if (xx == this->_vars.f8_iq_sample_pairs-1)
            {
                snprintf(this->_holder, BUF_E-1, "%d,%d",
                    static_cast<int>(this->_vars.data_block_cplxint16_v[xx].i),
                    static_cast<int>(this->_vars.data_block_cplxint16_v[xx].q));
            }
            else
            {
                snprintf(this->_holder, BUF_E-1, "%d,%d\n",
                    static_cast<int>(this->_vars.data_block_cplxint16_v[xx].i),
                    static_cast<int>(this->_vars.data_block_cplxint16_v[xx].q));
            }
            fputs(this->_holder, this->_fptr_write);
        }
    }
    else
    {
        this->_conclude_any_output();
        this->_set_error_code(data_load_mismatch);
        return;
    }
    this->_conclude_any_output();
}


////~~~~


/*
    < 2 > public
    given a valid directory with "*.siq" files,
    batch processes data after loading and generates equivelent CSV files
    CSV files maintian the same name as SIQ file, but change extension
*/
void siq_manager_class::write_iq_to_csv_batch
(
    char* input_directory, 
    char* output_directory
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    if (input_directory == NULL)
    {
        this->_set_error_code(directory_not_found);
        return;
    }

    std::vector<std::string> input_files;
    input_files.clear();
    std::vector<std::string> output_files;
    DIR* dir = NULL;
    struct dirent* diread = NULL;
    char temp[BUF_E];
    dir = opendir(input_directory);
    if (dir == NULL)
    {
        this->_set_error_code(directory_not_found);
        return;
    }

    while ( (diread = readdir(dir)) != NULL)
    {
        this->_set_error_code(no_error);
        if (diread->d_name[0] != '.')
        {
            snprintf(temp, BUF_E-1, "%s%s",
                input_directory,
                diread->d_name);
            input_files.push_back(temp);
            
            if (output_directory != NULL)
            {
                snprintf(temp, BUF_E-1, "%s%s",
                    output_directory,
                    diread->d_name);
            }
            output_files.push_back(temp);
        }
    }
    if (closedir(dir) != 0)
    {
        #ifdef DEBUG_MIN
            snprintf(X_ddts, sizeof(X_ddts), "failed to close directory:  %s", input_directory);
            snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
            debug_record(true);
        #endif
    }
    dir = NULL;

    char f_in[BUF_E];
    char f_out[BUF_E];
    for (std::size_t xx = 0; xx < input_files.size(); xx++)
    {
        this->_set_error_code(no_error);
        snprintf(f_in, BUF_E-1, "%s", input_files[xx].c_str()); 
        snprintf(f_out, BUF_E-1, "%s", output_files[xx].c_str());
        this->write_iq_to_csv(f_in, f_out);
    }
}


////////~~~~~~~~END>  siq_write_csv.cpp
