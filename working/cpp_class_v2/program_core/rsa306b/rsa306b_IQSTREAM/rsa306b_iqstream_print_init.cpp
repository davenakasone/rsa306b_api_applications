/*
    API group "IQSTREAM"

    public :
        < 1 >  print_iqstream()
    
    private :
        < 1 >  _iqstream_init()
*/

#include "../rsa306b_class.h"


/*
    < 1 > public
*/
void rsa306b_class::print_iqstream()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif
}


////~~~~


/*
    < 1 > private
*/
void rsa306b_class::_iqstream_init()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif  

}


////////~~~~~~~~END>  rsa306b_iqstream_print_init.cpp

double bandwidth;
        double bandwidth_max;    
        double bandwidth_min;
        double sample_rate;
        char name_of_file[BUF_C];      
        char name_of_header[BUF_C];   
        bool is_enabled;   
        void* data_buffer;         
        int pairs_copied;    
        RSA_API::IQSTRMIQINFO info_type;    
        std::vector<RSA_API::Cplx32> cplx32_v;
        std::vector<RSA_API::CplxInt16> cplxInt16_v;
        std::vector<RSA_API::CplxInt32> cplxInt32_v;
        int pairs_max;
        int record_time_ms;
        char* filename_base[BUF_C];
        int suffix_control;
        int pairs_requested;
        RSA_API::IQSOUTDEST destination_select;
        RSA_API::IQSOUTDTYPE datatype_select; 