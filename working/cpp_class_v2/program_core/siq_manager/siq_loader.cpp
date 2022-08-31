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
*/
void siq_manager_class::_populate_header()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    uint8_t field_counter = 0;
    uint8_t idx = 0;
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
        memset(field_raw, '\0', BUF_C);
        memset(field_stripped, '\0', BUF_C);
        memset(field_name, '\0', BUF_C);
        memset(this->_helper, '\0', BUF_E);
        memset(this->_holder, '\0', BUF_F);
        line = fgets(field_raw, BUF_C-1, this->_fptr_read);
        if (line == NULL)
        {
            this->_set_error_code(fgets_nothing);
        }
        for (int ii = 0; ii < (int)strnlen(field_raw, BUF_C-1); ii++)
        {
            if (isspace(field_raw[ii]) == 0)  // if character is not a space
            {
                snprintf(this->_helper, 2, "%c", field_raw[ii]);
                strncat(field_stripped, this->_helper, 2);
            }
        }
        for (int ii = 0; ii < (int)strnlen(field_stripped, BUF_C-1); ii++)
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
        if (strcmp(field_name, HEADER_FIELDS[RSASIQHT]) == 0)
        {
            idx = strnlen(field_name, 255);
            while (field_stripped[idx] != ',')
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            
            checker[field_counter] = true;
        }
        field_counter++;
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
