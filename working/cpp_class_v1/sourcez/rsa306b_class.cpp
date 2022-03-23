/*
    implementation of the essential components in the rsa306b class
        public:
            # rsa306b()
            # ~rsa306b()
        private:
            # init_member_variables()
*/

#include "../includez/rsa306b_class.h"


/*
    public
    the constructor for the class
    there is no need for multiple constructors (for now)
    ensures all variables are initialized to known values
*/
rsa306b::rsa306b()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  constructor\n",
        __LINE__, __FILE__, __func__);
#endif

    rsa306b::init_member_variables();
    this->rsa_connect();
}


////~~~~


/*
    public
    the desctructor for the class
    stops a running device, if running
    disconnects a connected device, if connected
    deallocates dynamic member variables if necessary
*/
rsa306b::~rsa306b()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s(),  destructor\n",
        __LINE__, __FILE__, __func__);
#endif

    if (this->is_connected == true)
    {
        this->api_return_status = RSA_API::DEVICE_Disconnect();
        this->error_check();
        sleep(1);
    }
}


////~~~~


/*
    private
    call any time member variables should be reset to known values
    deallocates dynamically member variables if needed, and places on NULL
    initialization values are in "rsa306b_class.h"
*/
void rsa306b::init_member_variables()
{
#ifdef DEBUG_CLI
    printf("\n<%d> %s/%s()\n",
        __LINE__, __FILE__, __func__);
#endif

    // general purpose
    this->is_connected = false;
    memset(this->helper_string, '\0', BUF_E);
    memset(this->holder_string, '\0', BUF_F);

    // ALIGN
    this->is_needed_alignment = true;
    this->is_warmed_up = false;

    // CONFIG
    this->center_frequency = INIT_DOUBLE;
    this->center_frequency_max = INIT_DOUBLE;
    this->center_frequency_min = INIT_DOUBLE;
    this->reference_level = INIT_DOUBLE;
    this->frequency_reference_source_select = RSA_API::FRS_INTERNAL;

    // DEVICE
    this->is_connected = false;
    this->is_over_temperature_limit = true;
    this->is_running = false;
    memset(this->device_api_version, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    memset(this->device_error_string, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    memset(this->device_firm_ware_version, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    memset(this->device_fpga_version, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    memset(this->device_hardware_version, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    memset(this->device_nomenclature, '\0', RSA_API::DEVINFO_MAX_STRLEN);
    for (int ii = 0; ii < RSA_API::DEVSRCH_MAX_NUM_DEVICES; ii++)
    {
        sprintf(this->device_serials[ii], "%s", INIT_STR);
        sprintf(this->device_types[ii], "%s", INIT_STR);
        this->device_ids[ii] = INIT_INT;
    }
    this->devices_found = INIT_INT;
}
       

////////~~~~~~~~END>  rsa306b_class.cpp
