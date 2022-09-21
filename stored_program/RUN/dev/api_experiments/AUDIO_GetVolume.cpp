/*
    this is used to see what happens when a "get" calls the API with an unconnected device
    call it a few times "repititions"
    see response both connected and disconnected 
*/

#include "juice.h"


int AUDIO_GetVolume
(
    int repitions
)
{
    printf("\n<%4d>  %s  %s()\n", __LINE__, __FILE__, __func__);

    float volume = 7.77;
   
    for (int ii = 0; ii < repitions; ii++)
    {
        RSA_API::ReturnStatus temp = 
            RSA_API::AUDIO_GetVolume(&volume);
        printf("status:  %4d  ,  message:  %s  ,  volume:  %f\n",
            static_cast<int>(temp),
            RSA_API::DEVICE_GetErrorString(temp),
            volume);
    }

    return CALL_GOOD;
}


////////~~~~~~~~~END>  AUDIO_GetVolume.cpp
