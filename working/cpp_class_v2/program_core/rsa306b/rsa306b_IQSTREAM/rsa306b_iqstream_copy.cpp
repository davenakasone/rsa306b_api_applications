/*
    API group "IQSTREAM"

    public :
        #  none
    
    private :
        < 1 >   _iqstream_copy_vars()
        < 2 >   _iqstream_copy_acqStatus_message()
        < 3 >   _iqstream_copy_bandwidth()
        < 4 >   _iqstream_copy_bandwidth_max()
        < 5 >   _iqstream_copy_bandwidth_min()
        < 6 >   _iqstream_copy_sample_rate()
        < 7 >   _iqstream_copy_fileinfo_type()
        < 8 >   _iqstream_copy_is_enabled()        
        < 9 >   _iqstream_copy_pairs_copied()   
        < 10 >  _iqstream_copy_info_type() 
        < 11 >  _iqstream_copy_cplx32_v()
        < 12 >  _iqstream_copy_cplxInt16_v()
        < 13 >  _iqstream_copy_cplxInt32_v()
        < 14 >  _iqstream_copy_pairs_max()
        < 15 >  _iqstream_copy_record_time_ms()
        < 16 >  _iqstream_copy_filename_base()
        < 17 >  _iqstream_copy_suffix_control()
        < 18 >  _iqstream_copy_buffer_multiplier()
        < 19 >  _iqstream_copy_destination_select()
        < 20 >  _iqstream_copy_datatype_select()
*/

#include "../rsa306b_class.h"


/*
    < 1 > private
*/
void rsa306b_class::_iqstream_copy_vars()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_iqstream_copy_acqStatus_message();
    this->_iqstream_copy_bandwidth_max();
    this->_iqstream_copy_bandwidth_min();
    this->_iqstream_copy_sample_rate();
    this->_iqstream_copy_fileinfo_type();
    this->_iqstream_copy_is_enabled();       
    this->_iqstream_copy_pairs_copied();   
    this->_iqstream_copy_info_type();
    this->_iqstream_copy_cplx32_v();
    this->_iqstream_copy_cplxInt16_v();
    this->_iqstream_copy_cplxInt32_v();
    this->_iqstream_copy_pairs_max();
    this->_iqstream_copy_record_time_ms();
    this->_iqstream_copy_filename_base();
    this->_iqstream_copy_suffix_control();
    this->_iqstream_copy_buffer_multiplier();
    this->_iqstream_copy_destination_select();
    this->_iqstream_copy_datatype_select();
}


////~~~~


/*
    < 2 > private
*/
void rsa306b_class::_iqstream_copy_acqStatus_message()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    for (int ii = 0; ii < IQSTREAM_BITCHECKS; ii++)
    {
        strcpy(this->vars.iqstream.acqStatus_message[ii],
            this->_vars.iqstream.acqStatus_message[ii]);
    }
}


////~~~~


/*
    < 3 > private
*/
void rsa306b_class::_iqstream_copy_bandwidth()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.bandwidth = this->_vars.iqstream.bandwidth;
}


////~~~~


/*
    < 4 > private
*/
void rsa306b_class::_iqstream_copy_bandwidth_max()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.bandwidth_max = this->_vars.iqstream.bandwidth_max;
}


////~~~~


/*
    < 5 > private
*/
void rsa306b_class::_iqstream_copy_bandwidth_min()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.bandwidth_min = this->_vars.iqstream.bandwidth_min;
}


////~~~~


/*
    < 6 > private
*/
void rsa306b_class::_iqstream_copy_sample_rate()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.sample_rate = this->_vars.iqstream.sample_rate;
}


////~~~~


/*
    < 7 > private
*/
void rsa306b_class::_iqstream_copy_fileinfo_type()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.fileinfo_type.acqStatus = this->_vars.iqstream.fileinfo_type.acqStatus;
    this->vars.iqstream.fileinfo_type.numberSamples = this->_vars.iqstream.fileinfo_type.numberSamples;
    this->vars.iqstream.fileinfo_type.sample0Timestamp = this->_vars.iqstream.fileinfo_type.sample0Timestamp;
    this->vars.iqstream.fileinfo_type.triggerSampleIndex = this->_vars.iqstream.fileinfo_type.triggerSampleIndex;
    this->vars.iqstream.fileinfo_type.triggerTimestamp = this->_vars.iqstream.fileinfo_type.triggerTimestamp;

    //printf("boom: %s\n", this->_vars.iqstream.fileinfo_type.filenames[0]);
    //std::wstring temp0(this->_vars.iqstream.fileinfo_type.filenames[0]);
    //wcstombs(this->_vars.iqstream.name_of_file, this->_vars.iqstream.fileinfo_type.filenames[0], BUF_C);
    //strcpy(this->vars.iqstream.name_of_file, this->_vars.iqstream.name_of_file);
    //this->_vars.iqstream.name_of_file.clear();
    //this->_vars.iqstream.name_of_file.assign()
    //snprintf(this->vars.iqstream.fileinfo_type.filenames[0])
    //swprintf(this->vars.iqstream.fileinfo_type.filenames[0], 999, L"%ls", this->_vars.iqstream.fileinfo_type.filenames[0]);
    //strcpy(this->vars.iqstream.fileinfo_type.filenames[0], )
    /*
    wcscpy(this->vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX], 
        this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX]);
    wcscpy(this->vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX], 
        this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX]);
    */
    /*
    this->gp_wchar_2_char(this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX],
        this->_vars.iqstream.name_of_file);
    this->gp_wchar_2_char(this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX],
        this->_vars.iqstream.name_of_header);
    strcpy(this->vars.iqstream.name_of_file, this->_vars.iqstream.name_of_file);
    strcpy(this->vars.iqstream.name_of_header, this->_vars.iqstream.name_of_header);
    wcpcpy(this->vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX], 
        this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX]);
    wcpcpy(this->vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX], 
        this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX]);
    */
    /*
    if (this->vars.iqstream.fileinfo_type.filenames == NULL)
    {
        strcpy(this->vars.iqstream.name_of_file, this->constants.INIT_STR);
        strcpy(this->vars.iqstream.name_of_header, this->constants.INIT_STR);
    }
    else
    {
        this->gp_wchar_2_char(this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX],
            this->_vars.iqstream.name_of_file);
        this->gp_wchar_2_char(this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX],
            this->_vars.iqstream.name_of_header);
        strcpy(this->vars.iqstream.name_of_file, this->_vars.iqstream.name_of_file);
        strcpy(this->vars.iqstream.name_of_header, this->_vars.iqstream.name_of_header);
        wcpcpy(this->vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX], 
            this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_DATA_IDX]);
        wcpcpy(this->vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX], 
            this->_vars.iqstream.fileinfo_type.filenames[RSA_API::IQSTRM_FILENAME_HEADER_IDX]);
    }
    */
}


////~~~~


/*
    < 8 > private
*/
void rsa306b_class::_iqstream_copy_is_enabled()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.is_enabled = this->_vars.iqstream.is_enabled;
}


////~~~~


/*
    < 9 > private
*/
void rsa306b_class::_iqstream_copy_pairs_copied() 
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.pairs_copied = this->_vars.iqstream.pairs_copied;
}


////~~~~


/*
    < 10 > private
*/
void rsa306b_class::_iqstream_copy_info_type() 
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->_iqstream_bitcheck(this->_vars.iqstream.info_type.acqStatus);

    this->vars.iqstream.info_type.acqStatus = this->_vars.iqstream.info_type.acqStatus;
    this->vars.iqstream.info_type.scaleFactor = this->_vars.iqstream.info_type.scaleFactor;
    this->vars.iqstream.info_type.timestamp = this->_vars.iqstream.info_type.timestamp;
    this->vars.iqstream.info_type.triggerCount = this->_vars.iqstream.info_type.triggerCount;
    
    // take the address to the internal buffer, if availible
    if (this->_vars.iqstream.info_type.triggerCount <= 0)
    {
        this->vars.iqstream.info_type.triggerIndices = this->vars.iqstream.info_type.triggerIndices;
    }
    else
    {
        this->vars.iqstream.info_type.triggerIndices = NULL;
    }
}


////~~~~


/*
    < 11 > private
*/
void rsa306b_class::_iqstream_copy_cplx32_v()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.cplx32_v.resize(
        this->_vars.iqstream.cplx32_v.size());
    this->vars.iqstream.cplx32_v = this->vars.iqstream.cplx32_v;
}


////~~~~


/*
    < 12 > private
*/
void rsa306b_class::_iqstream_copy_cplxInt16_v()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.cplxInt16_v.resize(
        this->_vars.iqstream.cplxInt16_v.size());
    this->vars.iqstream.cplxInt16_v = this->vars.iqstream.cplxInt16_v;
}


////~~~~


/*
    < 13 > private
*/
void rsa306b_class::_iqstream_copy_cplxInt32_v()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.cplxInt32_v.resize(
        this->_vars.iqstream.cplxInt32_v.size());
    this->vars.iqstream.cplxInt32_v = this->vars.iqstream.cplxInt32_v;
}


////~~~~


/*
    < 14 > private
*/
void rsa306b_class::_iqstream_copy_pairs_max()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.pairs_max = this->_vars.iqstream.pairs_max;
}


////~~~~


/*
    < 15 > private
*/
void rsa306b_class::_iqstream_copy_record_time_ms()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.record_time_ms = this->_vars.iqstream.record_time_ms;
}


////~~~~


/*
    < 16 > private
*/
void rsa306b_class::_iqstream_copy_filename_base()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    strcpy(this->vars.iqstream.filename_base, this->_vars.iqstream.filename_base);
}


////~~~~


/*
    < 17 > private
*/
void rsa306b_class::_iqstream_copy_suffix_control()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.suffix_control = this->_vars.iqstream.suffix_control;
}


////~~~~


/*
    < 18 > private
*/
void rsa306b_class::_iqstream_copy_buffer_multiplier()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.buffer_multiplier = this->_vars.iqstream.buffer_multiplier;
}


////~~~~


/*
    < 19 > private
*/
void rsa306b_class::_iqstream_copy_destination_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.destination_select = this->_vars.iqstream.destination_select;
}


////~~~~


/*
    < 20 > private
*/
void rsa306b_class::_iqstream_copy_datatype_select()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

    this->vars.iqstream.datatype_select = this->_vars.iqstream.datatype_select;
}


////////~~~~~~~~END>  rsa306b_iqstream_copy.cpp
