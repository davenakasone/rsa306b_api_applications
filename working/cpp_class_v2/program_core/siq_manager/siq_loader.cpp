/*
    for loading *.siq file into class members

    public:
        < 1 >  load_file()
        
    private:
        < 1 >  _populate_header()
        < 2 >  _populate_data()
*/

#include "siq_manager_class.h"


/*
    < 1 > public
    initiates loading the provided *.siq file 
    into the class member variables
*/
void siq_manager_class::load_file
(
    char* input_file
)
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
    
    this->_prepare_siq_input(input_file);
    if (this->_ec != no_error)
    {
        return;
    }
    this->_populate_header();
    this->_populate_data();
    this->_conclude_siq_input();
    this->_copy_vars();
}


////~~~~


/*
    < 1 > private
    parses an open *.siq file
    updates member variables with extracted information
    header fields only

    this is brute force...probably a good place to improve
*/
void siq_manager_class::_populate_header()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    uint8_t field_counter = 0;
    int idx = 0;
    int limit_length = 0;
    bool checker [SIQ_HEADER_FIELDS];
    for (int ii = 0; ii < SIQ_HEADER_FIELDS; ii++) 
    {
        checker[ii] = false;
    }
    char* line = NULL;
    char field_raw[BUF_C];
    char field_stripped[BUF_C];
    char field_name[BUF_C];

    while (field_counter < SIQ_HEADER_FIELDS)
    {
        idx = 0;
        limit_length = 0;
        memset(field_raw, '\0', BUF_C);
        memset(field_stripped, '\0', BUF_C);
        memset(field_name, '\0', BUF_C);
        memset(this->_helper, '\0', BUF_E);
        memset(this->_holder, '\0', BUF_F);
        line = fgets(field_raw, BUF_C-1, this->_fptr_read);    // get a line
        if (line == NULL)
        {
            this->_set_error_code(fgets_nothing);
        }
        for (int ii = 0; ii < (int)strnlen(field_raw, BUF_C-1); ii++)    // strip the line
        {
            if (isspace(field_raw[ii]) == 0)  // if character is not a space, then take it
            {
                snprintf(this->_helper, 2, "%c", field_raw[ii]);
                strncat(field_stripped, this->_helper, 2);
            }
        }
        for (int ii = 0; ii < (int)strnlen(field_stripped, BUF_C-1); ii++)    // isolate field name
        {
            if (field_stripped[ii] != ':')
            {
                snprintf(this->_helper, 2, "%c", field_stripped[ii]);
                strncat(field_name, this->_helper, 2);
            }
            else
            {
                field_name[ii] = '\0';
                break;
            }
        }
        idx = 0;
        limit_length = strnlen(field_stripped, BUF_C-1);
        while (field_stripped[idx] != ':' &&
               idx < limit_length          )
        {
            idx++;
        }
        idx++;
        memset(this->_holder, '\0', BUF_F);

        // given the field name on the line read, parse the entry to get the data -->
        if (strcmp(field_name, HEADER_FIELDS[RSASIQHT]) == 0)
        {
            while (field_stripped[idx] != ',' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f0_header_size_in_bytes = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f0_iq_file_version = atoi(this->_holder);
            checker[field_counter] = true;
        }
        else if (strcmp(field_name, HEADER_FIELDS[FileDateTime]) == 0)
        {
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f1_file_year = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f1_file_month = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != 'T' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f1_file_day = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f1_file_hour = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f1_file_minute = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '.' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f1_file_second = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f1_file_milli_second = atoi(this->_holder);

            printf("%d  %d  %d  --  %d  %d  %d .  %d",
                this->_vars.f1_file_year,
                this->_vars.f1_file_month,
                this->_vars.f1_file_day,
                this->_vars.f1_file_hour,
                this->_vars.f1_file_minute,
                this->_vars.f1_file_second,
                this->_vars.f1_file_milli_second);
            checker[field_counter] = true;
        }
        field_counter++;
    }
    
    bool result = true;
    for (int ii = 0; ii < SIQ_HEADER_FIELDS; ii++)
    {
        result = result && checker[ii];
    }
    if (result == false)
    {
        this->_set_error_code(failure_parsing_header_fields);
    }
}


////~~~~


/*
    < 2 > private
    parses an open *.siq file
    updates member variables with extracted information
    data block / samples only
*/
void siq_manager_class::_populate_data()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

}


////////~~~~~~~~END>  siq_loader.cpp
