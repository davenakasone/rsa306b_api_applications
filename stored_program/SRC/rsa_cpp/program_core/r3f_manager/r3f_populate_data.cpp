/*
    "r3f_manager_class", help populate the data frames

        public:
            #  none

        private:
            < 2 >  _populate_data()
            
*/

#include "r3f_manager_class.h"


/*
    private < 1 >
    header must have already been populated AND "*.r3f" file is open for reading
    if "write_parsed==true" a valid output file pointer must be open
    called only from "load_file()"
    as of now, the footer section of each frame is inert, but can be enhanced later
*/
CODEZ  r3f_manager_class::_populate_data
(
    bool write_parsed
)
{
#ifdef DEBUG_CLI
    (void)snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    if (this->_fp_read == NULL)
    {
        return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
    }
    if (write_parsed == true)
    {
        if (this->_fp_write == NULL)
        {
            return this->cutil.report_status_code(CODEZ::_18_file_pointer_not_open);
        }
    }

    int samples_to_get = (this->_bytes_in_file - 
                               this->_vars.size_of_frame_bytes) / 
                               this->_vars.size_of_frame_bytes;
    
    for (int ii = 1; ii <= samples_to_get; ii++)   // skips the header frame (start @ 1....already loaded it)
    {
        this->_byte_index = this->_vars.size_of_frame_bytes * ii;
        (void)fseek(this->_fp_read, 0L, SEEK_SET);
        (void)fseek(this->_fp_read, this->_byte_index, SEEK_CUR);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, "%s  frame:  %5d of %5d  { %9ld }\n", 
                R3F_BLOCK_SEPERATOR, ii, samples_to_get, ftell(this->_fp_read));
            (void)fputs(this->_holder, this->_fp_write);
        }

        for (int32_t jj = 0; jj < this->_vars.number_of_samples_per_frame; jj++)
        {
            (void)fread(&this->_vars.extracted_sample, sizeof(int16_t), 1, this->_fp_read);
            if(write_parsed == true)
            {
                (void)snprintf(this->_holder, sizeof(this->_holder)-1,"%6d)  %d\n", 
                    jj, this->_vars.extracted_sample);
                (void)fputs(this->_holder, this->_fp_write);
            }
            this->_vars.v_adc.push_back(this->_vars.extracted_sample);    // vector is loaded
        }

        for (int kk = 0; kk < R3F_FOOTER_DISCARD; kk++)
        {
            (void)fread(&this->_vars.discard[kk], sizeof(uint8_t), 1, this->_fp_read);
        }
        
        (void)fread(&this->_vars.frame_id, sizeof(uint32_t), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, 
                "Frame ID                                           :  %u\n", this->_vars.frame_id);
            (void)fputs(this->_holder, this->_fp_write);
        }
        
        (void)fread(&this->_vars.trigger_1_index, sizeof(uint16_t), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, 
                "Trigger 1 index                                    :  %u\n", this->_vars.trigger_1_index);
            (void)fputs(this->_holder, this->_fp_write);
        }
        
        (void)fread(&this->_vars.trigger_2_index, sizeof(uint16_t), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, 
                "Trigger 2 index                                    :  %u\n", this->_vars.trigger_1_index);
            (void)fputs(this->_holder, this->_fp_write);
        }
        
        (void)fread(&this->_vars.time_synchronization_index, sizeof(uint16_t), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, 
                "Time Synchronization index                         :  %u\n", this->_vars.time_synchronization_index);
            (void)fputs(this->_holder, this->_fp_write);
        }

        (void)fread(&this->_vars.frame_status, sizeof(uint16_t), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, 
                "Frame Status                                       :  %u\n", this->_vars.frame_status);
            (void)fputs(this->_holder, this->_fp_write);
        }

        (void)fread(&this->_vars.frame_timestamp, sizeof(uint64_t), 1, this->_fp_read);
        if(write_parsed == true)
        {
            (void)snprintf(this->_holder, sizeof(this->_holder)-1, 
                "Timestamp                                          :  %ld    { %12ld }\n", 
                ftell(this->_fp_read)-1,
                this->_vars.frame_timestamp);
            (void)fputs(this->_holder, this->_fp_write); 
        }                       
    }

    return CODEZ::_0_no_errors;
}


////////~~~~~~~~END>  r3f_populate_data.cpp
