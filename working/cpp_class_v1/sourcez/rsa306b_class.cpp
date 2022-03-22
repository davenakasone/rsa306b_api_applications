/*
    implementation of the essential components in the rsa306b class
        # rsa306b()
        # init_member_variables()
        # ~rsa306b()
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
    printf("\n\tallocating class instance....\n");
    rsa306b::init_member_variables();
}


////~~~~


/*
    public
    call any time member variables should be reset to known values
    deallocates dynamically member variables if needed, and places on NULL
    initialization values are in "rsa306b_class.h"
*/
void rsa306b::init_member_variables()
{
    // general purpose
    this->is_connected = false;
    memset(this->helper_string, '\0', BUF_E);
    memset(this->holder_string, '\0', BUF_F);
    this->api_return_status = RSA_API::errorPlaceholder;

    // ALIGN
    this->is_needed_alignment = true;
    this->is_warmed_up = false;

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
    printf("\n\tdeallocating class instance...\n");
    if (this->is_connected == true)
    {
        this->api_return_status = RSA_API::DEVICE_Disconnect();
        error_check();
    }
}


////////~~~~~~~~END>  rsa306b_class.cpp
