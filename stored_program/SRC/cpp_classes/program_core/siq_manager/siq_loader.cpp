/*
    for loading *.siq file into class members

    public:
        < 1 >  load_file()
        
    private:
        < 1 >  _populate_header()
        < 2 >  _populate_data()
*/

#include "siq_manager_class.h"

#if (defined (DEBUG_SIQ_LOADER_HEADER) || defined (DEBUG_SIQ_LOADER_DATA))
    static char transfer[BUF_D];
#endif


/*
    < 1 > public
    initiates loading the provided *.siq file 
    into the class member variables
*/
CODEZ siq_manager_class::load_file
(
    char* input_file
)
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
    
    this->_init();
    this->_prepare_siq_input(input_file);
    if (this->_ec != no_error)
    {
        return;
    }
    
    #if (defined (DEBUG_SIQ_LOADER_HEADER) || defined (DEBUG_SIQ_LOADER_DATA))
        if (snprintf(transfer, BUF_D-1, "%s", input_file) <= 0)
        {
            this->_set_error_code(snprintf_failed);
        }
    #endif
    
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
CODEZ siq_manager_class::_populate_header()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif
#ifdef DEBUG_SIQ_LOADER_HEADER
    printf("\nHEADER, for '%s'  >>>\n\n", transfer);
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
        if (strcmp(field_name, HEADER_FIELDS[RSASIQHT]) == 0)    // field index 0 of 21
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
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%d,%d\n",
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f0_header_size_in_bytes,
                    this->_vars.f0_iq_file_version);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[FileDateTime]) == 0)    // field index 1 of 21
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
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%04d-%02d-%02dT%02d:%02d:%02d.%d\n",
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f1_file_year,
                    this->_vars.f1_file_month,
                    this->_vars.f1_file_day,
                    this->_vars.f1_file_hour,
                    this->_vars.f1_file_minute,
                    this->_vars.f1_file_second,
                    this->_vars.f1_file_milli_second);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[Hardware]) == 0)    // field index 2 of 21
        {
            while (field_stripped[idx] != ',' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            idx++;
            strncpy(this->_vars.f2_instrument_nomenclature, this->_holder, BUF_A-1);
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ',' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            idx++;
            strncpy(this->_vars.f2_serial_number, this->_holder, BUF_A-1);
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            strncpy(this->_vars.f2_version, this->_holder, BUF_A-1);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%s,%s,%s\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f2_instrument_nomenclature, 
                    this->_vars.f2_serial_number,
                    this->_vars.f2_version);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[Software_Firmware]) == 0)    // field index 3 of 21
        {
            while (field_stripped[idx] != ',' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            idx++;
            strncpy(this->_vars.f3_version_api, this->_holder, BUF_A-1);
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ',' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            idx++;
            strncpy(this->_vars.f3_version_usb, this->_holder, BUF_A-1);
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            strncpy(this->_vars.f3_version_fpga, this->_holder, BUF_A-1);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%s,%s,%s\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f3_version_api, 
                    this->_vars.f3_version_usb,
                    this->_vars.f3_version_fpga);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[ReferenceLevel]) == 0)    // field index 4 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f4_reference_level_dbm = strtod(this->_holder, NULL);
            if (this->_vars.f4_reference_level_dbm == 0)
            {
                this->_set_error_code(strtod_failed);
                if (errno == ERANGE) {printf("\n\tvalue out of range\n");}
            }
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%lf\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f4_reference_level_dbm);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[CenterFrequency]) == 0)    // field index 5 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f5_center_frequency_hz = strtod(this->_holder, NULL);
            if (this->_vars.f5_center_frequency_hz == 0)
            {
                this->_set_error_code(strtod_failed);
                if (errno == ERANGE) {printf("\n\tvalue out of range\n");}
            }
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%lf\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f5_center_frequency_hz);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[SampleRate]) == 0)    // field index 6 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f6_samples_per_second = strtod(this->_holder, NULL);
            if (this->_vars.f6_samples_per_second == 0)
            {
                this->_set_error_code(strtod_failed);
                if (errno == ERANGE) {printf("\n\tvalue out of range\n");}
            }
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%lf\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f6_samples_per_second);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[AcqBandwidth]) == 0)    // field index 7 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f7_bandwidth_hz = strtod(this->_holder, NULL);
            if (this->_vars.f7_bandwidth_hz == 0)
            {
                this->_set_error_code(strtod_failed);
                if (errno == ERANGE) {printf("\n\tvalue out of range\n");}
            }
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%lf\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f7_bandwidth_hz);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[NumberSamples]) == 0)    // field index 8 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f8_iq_sample_pairs = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%d\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f8_iq_sample_pairs);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[NumberFormat]) == 0)    // field index 9 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            strncpy(this->_vars.f9_number_format, this->_holder, BUF_A-1);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%s\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f9_number_format);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[DataScale]) == 0)    // field index 10 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f10_scale_factor = strtod(this->_holder, NULL);
            if (this->_vars.f10_scale_factor == 0)
            {
                this->_set_error_code(strtod_failed);
                if (errno == ERANGE) {printf("\n\tvalue out of range\n");}
            }
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%lf\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f10_scale_factor);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[DataEndian]) == 0)    // field index 11 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            strncpy(this->_vars.f11_endian, this->_holder, BUF_A-1);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%s\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f11_endian);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[RecordUtcSec]) == 0)    // field index 12 of 21
        {
            while (field_stripped[idx] != '.' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            idx++;
            this->_vars.f12_first_sample_utc_seconds = atoi(this->_holder);
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f12_first_sample_utc_nano_seconds = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%d.%d\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f12_first_sample_utc_seconds,
                    this->_vars.f12_first_sample_utc_nano_seconds);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[RecordUtcTime]) == 0)    // field index 13 of 21
        {
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f13_first_sample_utc_timestamp_year = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f13_first_sample_utc_timestamp_month = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != 'T' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f13_first_sample_utc_timestamp_day = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f13_first_sample_utc_timestamp_hour= atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f13_first_sample_utc_timestamp_minute = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '.' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f13_first_sample_utc_timestamp_second = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f13_first_sample_utc_timestamp_nano_second = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%04d-%02d-%02dT%02d:%02d:%02d.%d\n",
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f13_first_sample_utc_timestamp_year,
                    this->_vars.f13_first_sample_utc_timestamp_month,
                    this->_vars.f13_first_sample_utc_timestamp_day,
                    this->_vars.f13_first_sample_utc_timestamp_hour,
                    this->_vars.f13_first_sample_utc_timestamp_minute,
                    this->_vars.f13_first_sample_utc_timestamp_second,
                    this->_vars.f13_first_sample_utc_timestamp_nano_second);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[RecordLclTime]) == 0)    // field index 14 of 21
        {
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f14_first_sample_local_timestamp_year = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f14_first_sample_local_timestamp_month = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != 'T' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f14_first_sample_local_timestamp_day = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f14_first_sample_local_timestamp_hour = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f14_first_sample_local_timestamp_minute = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '.' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f14_first_sample_local_timestamp_second = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f14_first_sample_local_timestamp_nano_second = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%04d-%02d-%02dT%02d:%02d:%02d.%d\n",
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f14_first_sample_local_timestamp_year,
                    this->_vars.f14_first_sample_local_timestamp_month,
                    this->_vars.f14_first_sample_local_timestamp_day,
                    this->_vars.f14_first_sample_local_timestamp_hour,
                    this->_vars.f14_first_sample_local_timestamp_minute,
                    this->_vars.f14_first_sample_local_timestamp_second,
                    this->_vars.f14_first_sample_local_timestamp_nano_second);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[TriggerIndex]) == 0)    // field index 15 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f15_tigger_index = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%d\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f15_tigger_index);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[TriggerUtcSec]) == 0)    // field index 16 of 21
        {
            while (field_stripped[idx] != '.' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            idx++;
            this->_vars.f16_trigger_utc_seconds = atoi(this->_holder);
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f16_trigger_utc_nano_seconds = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%d.%d\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f16_trigger_utc_seconds,
                    this->_vars.f16_trigger_utc_nano_seconds);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[TriggerUtcTime]) == 0)    // field index 17 of 21
        {
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f17_trigger_utc_timestamp_year = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f17_trigger_utc_timestamp_month = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != 'T' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f17_trigger_utc_timestamp_day = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f17_trigger_utc_timestamp_hour = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f17_trigger_utc_timestamp_minute = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '.' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f17_trigger_utc_timestamp_second = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f17_trigger_utc_timestamp_nano_second = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%04d-%02d-%02dT%02d:%02d:%02d.%d\n",
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f17_trigger_utc_timestamp_year,
                    this->_vars.f17_trigger_utc_timestamp_month,
                    this->_vars.f17_trigger_utc_timestamp_day,
                    this->_vars.f17_trigger_utc_timestamp_hour,
                    this->_vars.f17_trigger_utc_timestamp_minute,
                    this->_vars.f17_trigger_utc_timestamp_second,
                    this->_vars.f17_trigger_utc_timestamp_nano_second);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[TriggerLclTime]) == 0)    // field index 18 of 21
        {
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f18_trigger_local_timestamp_year = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '-' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f18_trigger_local_timestamp_month = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != 'T' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f18_trigger_local_timestamp_day = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f18_trigger_local_timestamp_hour = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != ':' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f18_trigger_local_timestamp_minute = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (field_stripped[idx] != '.' &&
                   idx < limit_length          )
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f18_trigger_local_timestamp_second = atoi(this->_holder);
            idx++;
            memset(this->_holder, '\0', BUF_F);
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f18_trigger_local_timestamp_nano_second = atoi(this->_holder);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%04d-%02d-%02dT%02d:%02d:%02d.%d\n",
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f18_trigger_local_timestamp_year,
                    this->_vars.f18_trigger_local_timestamp_month,
                    this->_vars.f18_trigger_local_timestamp_day,
                    this->_vars.f18_trigger_local_timestamp_hour,
                    this->_vars.f18_trigger_local_timestamp_minute,
                    this->_vars.f18_trigger_local_timestamp_second,
                    this->_vars.f18_trigger_local_timestamp_nano_second);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[AcqStatus]) == 0)    // field index 19 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            this->_vars.f19_acq_status = 
                static_cast<uint32_t>(strtoul(this->_holder, NULL, 0));
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:0x%08X\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f19_acq_status);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[RefTimeSource]) == 0)    // field index 20 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            strncpy(this->_vars.f20_reference_time_source, this->_holder, BUF_A-1);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%s\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f20_reference_time_source);
            #endif
        }
        else if (strcmp(field_name, HEADER_FIELDS[FreqRefSource]) == 0)    // field index 21 of 21
        {
            while (idx < limit_length)
            {
                snprintf(this->_helper, 2, "%c", field_stripped[idx]);
                strncat(this->_holder, this->_helper, 2);
                idx++;
            }
            strncpy(this->_vars.f21_frequency_reference_source, this->_holder, BUF_A-1);
            checker[field_counter] = true;
            #ifdef DEBUG_SIQ_LOADER_HEADER
                printf("\tf[%2d of %2d]  %s:%s\n", 
                    field_counter,
                    SIQ_HEADER_FIELDS,
                    field_name,
                    this->_vars.f21_frequency_reference_source);
            #endif
        }
        else
        {
            this->_set_error_code(failed_to_find_field);
        }
        field_counter++;
    }
    
    bool result = true;
    for (int ii = 0; ii < SIQ_HEADER_FIELDS; ii++)
    {
        result = result && checker[ii];
        #ifdef DEBUG_MIN
            if (checker[ii] == false)
            {
                snprintf(X_ddts, sizeof(X_ddts), "missing field [%2d of %2d]  %s", 
                    ii, SIQ_HEADER_FIELDS, HEADER_FIELDS[ii]);
                snprintf(X_dstr, sizeof(X_dstr), DEBUG_MIN_FORMAT, __LINE__, __FILE__, __func__, X_ddts);
                debug_record(true);
            }
        #endif
        
    }
    if (result == false)
    {
        this->_set_error_code(failure_parsing_header_fields);
        return;
    }
    this->_set_error_code(no_error);
}


////~~~~


/*
    < 2 > private
    parses an open *.siq file
    updates member variables with extracted information
    data block / samples only
*/
CODEZ siq_manager_class::_populate_data()
{
#ifdef DEBUG_CLI
    snprintf(X_dstr, sizeof(X_dstr), DEBUG_CLI_FORMAT, 
        __LINE__, __FILE__, __func__);
    debug_record(false);
#endif

    std::size_t idx = 0;
    std::size_t idx_limit = 0;
    if (fseek(this->_fptr_read, 0L, SEEK_SET) != 0)
    {
        this->_set_error_code(fseek_returned_non_zero);
        return;
    }
    if (fseek(this->_fptr_read, 
              static_cast<long>(this->_vars.f0_header_size_in_bytes),
              SEEK_CUR)                                    
        != 0)
    {
        this->_set_error_code(fseek_returned_non_zero);
        return;
    }

    if (strcmp(this->_vars.f9_number_format, NUMBER_FORMATS[NUMBER_FORMAT_SINGLE]) == 0)
    {
        float temp = 0;
        this->_vars.data_block_cplx32_v.clear();
        this->_vars.data_block_cplx32_v.resize(static_cast<std::size_t>(this->_vars.f8_iq_sample_pairs));
        idx_limit = this->_vars.data_block_cplx32_v.size();
        if (idx_limit > INIT_STL_LENGTH)
        {
             while(idx < idx_limit)
            {
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("\tbyte %15ld  ", ftell(this->_fptr_read));
                #endif
                fread(
                    &temp,
                    sizeof(float),
                    1, 
                    this->_fptr_read);
                this->_vars.data_block_cplx32_v[idx].i = temp;
                fread(
                    &temp, 
                    sizeof(float),
                    1, 
                    this->_fptr_read);
                this->_vars.data_block_cplx32_v[idx].q = temp;
                idx++;
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("[%9ld  of  %9ld]  %14.7f, %14.7f\n",
                    idx,
                    idx_limit,
                    this->_vars.data_block_cplx32_v[idx-1].i,
                    this->_vars.data_block_cplx32_v[idx-1].q);
                #endif
            }
        }
        else
        {
            this->_set_error_code(data_load_mismatch);
            return;
        }
    }
    else if (strcmp(this->_vars.f9_number_format, NUMBER_FORMATS[NUMBER_FORMAT_INT32]) == 0)
    {
        int32_t temp = 0;
        this->_vars.data_block_cplxint32_v.clear();
        this->_vars.data_block_cplxint32_v.resize(static_cast<std::size_t>(this->_vars.f8_iq_sample_pairs));
        idx_limit = this->_vars.data_block_cplxint32_v.size();
        if (idx_limit > INIT_STL_LENGTH)
        {
             while(idx < idx_limit)
            {
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("\tbyte %15ld  ", ftell(this->_fptr_read));
                #endif
                fread(
                    &temp, 
                    sizeof(int32_t),
                    1, 
                    this->_fptr_read);
                this->_vars.data_block_cplxint32_v[idx].i = temp;
                fread(
                    &temp, 
                    sizeof(int32_t),
                    1, 
                    this->_fptr_read);
                this->_vars.data_block_cplxint32_v[idx].q = temp;
                idx++;
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("[%9ld  of  %9ld]  %15d, %15d\n",
                    idx,
                    idx_limit,
                    static_cast<int>(this->_vars.data_block_cplxint32_v[idx-1].i),
                    static_cast<int>(this->_vars.data_block_cplxint32_v[idx-1].q));
                #endif
            }
        }
        else
        {
            this->_set_error_code(data_load_mismatch);
            return;
        }
    }
    else if (strcmp(this->_vars.f9_number_format, NUMBER_FORMATS[NUMBER_FORMAT_INT16]) == 0)
    {
        int16_t temp = 0;
        this->_vars.data_block_cplxint16_v.resize(static_cast<std::size_t>(this->_vars.f8_iq_sample_pairs));
        idx_limit = this->_vars.data_block_cplxint16_v.size();
        if (idx_limit > INIT_STL_LENGTH)
        {
             while(idx < idx_limit)
            {
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("\tbyte %15ld  ", ftell(this->_fptr_read));
                #endif
                fread(
                    &temp, 
                    sizeof(int16_t),
                    1, 
                    this->_fptr_read);
                this->_vars.data_block_cplxint16_v[idx].i = temp;
                fread(
                    &temp, 
                    sizeof(int16_t),
                    1, 
                    this->_fptr_read);
                this->_vars.data_block_cplxint16_v[idx].q = temp;
                idx++;
                #ifdef DEBUG_SIQ_LOADER_DATA
                    printf("[%9ld  of  %9ld]  %15d, %15d\n",
                    idx,
                    idx_limit,
                    static_cast<int>(this->_vars.data_block_cplxint16_v[idx-1].i),
                    static_cast<int>(this->_vars.data_block_cplxint16_v[idx-1].q));
                #endif
            }
        }
        else
        {
            this->_set_error_code(data_load_mismatch);
            return;
        }
    }
    else
    {
        this->_set_error_code(file_loaded_with_no_data);
        return;
    }
    this->_set_error_code(no_error);
}


////////~~~~~~~~END>  siq_loader.cpp
