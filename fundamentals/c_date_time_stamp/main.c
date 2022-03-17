/*
    basic technique to get a date-time-stamp
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define STATUS_GOOD 777
#define STATUS_BAD 666
#define BIG_BUF 256

int get_dts (char* dts_str);


int main
(
    void
)
{
    char my_dts[BIG_BUF] = "null";
    int ret = 0;
    ret = get_dts(my_dts);
    printf("\nstamp:  %s  ,  status:  %d\n", my_dts, ret);
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPELTE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~


int get_dts
(
    char* dts_str
)
{   
    if (dts_str == NULL) {return STATUS_BAD;}
    memset(dts_str, '\0', BIG_BUF);

    time_t currentTime;
    struct tm * ptr = NULL;
    currentTime = time(&currentTime);
    ptr = gmtime(&currentTime);          

    if (currentTime != -1 && ptr != NULL)
    {    
        strftime(dts_str, BIG_BUF,
            "_%Y_%m_%d_%A_%H_%M_%S_%Z", ptr);
        return STATUS_GOOD;
    }
    else
    {
        return STATUS_BAD;
    }
}


////////~~~~~~~~END>  main.c
