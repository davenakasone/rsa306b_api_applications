/*
    try to read the "*.r3f" in C

    https://www.codingunit.com/c-tutorial-binary-file-io
    https://nachtimwald.com/2017/09/24/hex-encode-and-decode-in-c/
    https://stackoverflow.com/questions/15736497/how-to-print-an-unsigned-char-in-c

    $ iconv -f utf8 <filename> -t utf8 -o /dev/null
    rewind() is bad
    fseek() is good

    current files is: 540,672 bytes, IQ start: 16,384
    it is more reliable to write IQ stream with now header and just read raw data "r3a"
*/

#define DEBUG_PARSE                     // turn on or off for stdout parsing outputs
#define DECODE                          // turn on or off to get a decoding in stdout and .txt
#define DECODE_START 0UL                // change, but keep >= 0 and < DECODE_CONTROL_LENGTH
#define DECODE_CONTROL_LENGTH 16400UL      // turn on or off, only valid if DECODE is on

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GET_NAME(var) #var                  


#define BUF_32 32
#define BUF_HELPER 256
#define BUF_HOLDER 512
#define BUF_BYTE_GETTER 4
#define BUF_REFTIME 7
#define UEOF 255             // the EOF value in uint8_t types (not -1)

const long BI_IQ_DATA = 16384;       // byte index where the IQ data starts, header is complete 
const long BI_INSTRUMENT = 1024;     // byte index where the instrument fields start, in header
const long BI_DATA_FORMAT = 2048;    // byte index where the data format fields start, in header

const char input_file[BUF_32] = "dummy.r3f";
const char output_file[BUF_32] = "dummy_out.txt";
#ifdef DECODE
    const char output_file_decode[BUF_32] = "dummy_decoder.txt";
    void decoding_assistant();
#endif

char helper[BUF_HELPER];
char holder[BUF_HOLDER];
double double_getter;
FILE* fptr_read;
FILE* fptr_write;
int idx;
long byte_index;
uint8_t byte_getter[BUF_BYTE_GETTER];
uint32_t uint32_getter;
uint32_t reftime_getter[BUF_REFTIME];
uint64_t uint64_getter;


int main()
{
    memset(helper, '\0', BUF_HELPER);
    memset(holder, '\0', BUF_HOLDER);

    // attempt to open the input file, verify total bytes, output file is opened
    fptr_read = fopen(input_file, "r");
    if (fptr_read == NULL)
    {
        printf("\n\tfailed to open the input files\n");
        return EXIT_FAILURE;
    }
    fptr_write = fopen(output_file, "w");
    
    // activate with macro, helpful for developing the parsing algorithm
    #ifdef DECODE
        decoding_assistant();
    #endif

    // the parsing of the *.r3f files begins
    fseek(fptr_read, 0L, SEEK_END);
    byte_index = ftell(fptr_read);
    printf("\n\t'%s' size in bytes:  %ld\n", input_file, byte_index);
    fseek(fptr_read, 0L, SEEK_SET);
    byte_index = ftell(fptr_read);
    printf("\n\t%s on byte:  %ld  ,  making '%s'  ,  parsing begins...\n\n", 
        GET_NAME(fptr_read), byte_index, output_file);
    
    // (1) aquire the "Field ID"
    idx = 0;
    do 
    {
        fread(&helper[idx], sizeof(char), 1, fptr_read);
        idx++;
    }
    while(helper[idx-1] != '\0');
    snprintf(holder, BUF_HOLDER-1, "%s\n", helper);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (2) aquire the "Endian Check"
    do
    {
        fread(&byte_getter[0], sizeof(uint8_t), 1, fptr_read);
    } while (byte_getter[0] == 0);
    byte_index = ftell(fptr_read);
    fseek(fptr_read, 0UL, SEEK_SET);
    fseek(fptr_read, byte_index-1, SEEK_CUR);
    for (int ii = 0; ii < BUF_BYTE_GETTER; ii++)
    {
        fread(&byte_getter[ii], sizeof(uint8_t), 1, fptr_read);
    }
    snprintf(holder, BUF_HOLDER-1, "0x%X%X%X%X\n",
        byte_getter[3], byte_getter[2], byte_getter[1], byte_getter[0]);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (3) aquire the "File Format Version"
    for (int ii = 0; ii < BUF_BYTE_GETTER; ii++)
    {
        fread(&byte_getter[ii], sizeof(uint8_t), 1, fptr_read);
    }
    snprintf(holder, BUF_HOLDER-1, "%u.%u.%u.%u\n",
        byte_getter[0], byte_getter[1], byte_getter[2], byte_getter[3]);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (4) aquire the "API Version"
    for (int ii = 0; ii < BUF_BYTE_GETTER; ii++)
    {
        fread(&byte_getter[ii], sizeof(uint8_t), 1, fptr_read);
    }
    snprintf(holder, BUF_HOLDER-1, "%u.%u.%u.%u\n",
        byte_getter[0], byte_getter[1], byte_getter[2], byte_getter[3]);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (5) aquire the "Firmware Version"
    for (int ii = 0; ii < BUF_BYTE_GETTER; ii++)
    {
        fread(&byte_getter[ii], sizeof(uint8_t), 1, fptr_read);
    }
    snprintf(holder, BUF_HOLDER-1, "%u.%u.%u.%u\n",
        byte_getter[0], byte_getter[1], byte_getter[2], byte_getter[3]);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (6) aquire the "FPGA Version"
    for (int ii = 0; ii < BUF_BYTE_GETTER; ii++)
    {
        fread(&byte_getter[ii], sizeof(uint8_t), 1, fptr_read);
    }
    snprintf(holder, BUF_HOLDER-1, "%u.%u.%u.%u\n",
        byte_getter[0], byte_getter[1], byte_getter[2], byte_getter[3]);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (7) aquire the "Device Serial Number"
    idx = 0;
    do 
    {
        fread(&helper[idx], sizeof(char), 1, fptr_read);
        idx++;
    }
    while(helper[idx-1] != '\0');
    snprintf(holder, BUF_HOLDER-1, "%s\n", helper);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (8) aquire the "Nomenclature"
    do
    {
        fread(&byte_getter[0], sizeof(uint8_t), 1, fptr_read);
    } while (byte_getter[0] == 0);
    byte_index = ftell(fptr_read);
    fseek(fptr_read, 0UL, SEEK_SET);
    fseek(fptr_read, byte_index-1, SEEK_CUR);
    idx = 0;
    do 
    {
        fread(&helper[idx], sizeof(char), 1, fptr_read);
        idx++;
    }
    while(helper[idx-1] != '\0');
    snprintf(holder, BUF_HOLDER-1, "%s\n", helper);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (9) jump to the instrument section and aquire "Reference Level"
    fseek(fptr_read, 0UL, SEEK_SET);
    fseek(fptr_read, BI_INSTRUMENT, SEEK_CUR);
    fread(&double_getter, sizeof(double), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%lf\n", double_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (10) aquire the "Center Frequency"
    fread(&double_getter, sizeof(double), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%lf\n", double_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (11) aquire the "Device Temperature"
    fread(&double_getter, sizeof(double), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%lf\n", double_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (12) aquire the "Alignment Status"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (13) aquire the "Frequency Reference Source"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (14) aquire the "Trigger Mode"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (15) aquire the "Trigger Source"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (16) aquire the "Trigger Transition"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (17) aquire the "Trigger Level"
    fread(&double_getter, sizeof(double), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%lf\n", double_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (18) jump to the data format section and aquire "Data Type / bytes per sample"
    fseek(fptr_read, 0UL, SEEK_SET);
    fseek(fptr_read, BI_DATA_FORMAT, SEEK_CUR);
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    if (uint32_getter == 161)
    {
        snprintf(holder, BUF_HOLDER-1, "%d  ....2 bytes per sample\n", uint32_getter);
        fputs(holder, fptr_write);
        #ifdef DEBUG_PARSE
            printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
        #endif
    }
    else
    {
        printf("\n\t[%d] unknown bytes per sample\n", __LINE__);
        return EXIT_FAILURE;
    }
    
    // (19) aquire the "Frame Offset, to first frame"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (20) aquire the "Frame Size"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (21) aquire the "Sample Size Offset"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (22) aquire the "Samples in Frame"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (23) aquire the "Offset to non-sample data"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (24) aquire the "size of non-sample data"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (25) aquire the "IF Center Frequency"
    fread(&double_getter, sizeof(double), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%lf\n", double_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (26) aquire the "Sampling Rate"
    fread(&double_getter, sizeof(double), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%lf\n", double_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (27) aquire the "Bandwidth"
    fread(&double_getter, sizeof(double), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%lf\n", double_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (28) aquire the "Data Corrected Status"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (29) aquire the "Time Type"
    fread(&uint32_getter, sizeof(uint32_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%d\n", uint32_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  [0=local, 1=remote] %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (30) aquire the "Reference Time"
    for (int ii = 0; ii < BUF_REFTIME; ii++)
    {
        fread(&reftime_getter[ii], sizeof(uint32_t), 1, fptr_read);
    }
    snprintf(holder, BUF_HOLDER-1, "%u/%u/%u _ %u:%u:%u.%u ...MM/DD/YYYY _ HH:MM:SS.s\n",
        reftime_getter[1], reftime_getter[2], reftime_getter[0], reftime_getter[3], 
        reftime_getter[4], reftime_getter[5], reftime_getter[6]);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (31) aquire the "Clock Tics"
    fread(&uint64_getter, sizeof(uint64_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%ld\n", uint64_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (32) aquire the "Sampling Rate"
    fread(&uint64_getter, sizeof(uint64_t), 1, fptr_read);
    snprintf(holder, BUF_HOLDER-1, "%ld\n", uint64_getter);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif

    // (31) aquire the "UTC Time"
    for (int ii = 0; ii < BUF_REFTIME; ii++)
    {
        fread(&reftime_getter[ii], sizeof(uint32_t), 1, fptr_read);
    }
    snprintf(holder, BUF_HOLDER-1, "%u/%u/%u _ %u:%u:%u.%u ...MM/DD/YYYY _ HH:MM:SS.s\n",
        reftime_getter[1], reftime_getter[2], reftime_getter[0], reftime_getter[3], 
        reftime_getter[4], reftime_getter[5], reftime_getter[6]);
    fputs(holder, fptr_write);
    #ifdef DEBUG_PARSE
        printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
    #endif





    fclose(fptr_read); fptr_read = NULL;
    fclose(fptr_write); fptr_write = NULL;
    printf("\n\tparsing complete, check '%s'\n", output_file);
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////~~~~

#ifdef DECODE
void decoding_assistant()
{
    FILE* fptr_decode = fopen(output_file_decode, "w");
    #ifdef DECODE_CONTROL_LENGTH
        if (DECODE_CONTROL_LENGTH < DECODE_START) {printf("\n\tfix yourself\n"); exit(1);}
        printf("\nmaking %s  ,  bytes [ %ld : %ld ]\n<<< begin file decode >>>\n\n", 
            output_file_decode, DECODE_START, DECODE_CONTROL_LENGTH);
        fseek(fptr_read, 0L, SEEK_SET);
        fseek(fptr_read, DECODE_START, SEEK_CUR);
        for (long ii = DECODE_START; ii < DECODE_CONTROL_LENGTH; ii++)
    #else
        fseek(fptr_read, 0L, SEEK_END);
        byte_index = ftell(fptr_read);
        printf("\nmaking %s  ,  byte inex [ 0 : %ld ]\n<<< begin file decode >>>\n\n", 
            output_file_decode, byte_index);
        fseek(fptr_read, 0L, SEEK_SET);
        for (long ii = 0; ii < byte_index; ii++)
    #endif
        {
            fread(&byte_getter[0], sizeof(uint8_t), 1, fptr_read);
            helper[0] = (char)byte_getter[0];
            switch (byte_getter[0])
            {
                case (0)    : snprintf(holder, BUF_HOLDER-1, "<><><>%8ld)\t\t\t[NULL]    %u\n", ii, byte_getter[0]);    break;
                case (10)   : snprintf(holder, BUF_HOLDER-1, "<><><>%8ld)\t\t\t[LF]      %u\n", ii, byte_getter[0]);    break;
                case (12)   : snprintf(holder, BUF_HOLDER-1, "<><><>%8ld)\t\t\t[FF]      %u\n", ii, byte_getter[0]);    break;
                case (13)   : snprintf(holder, BUF_HOLDER-1, "<><><>%8ld)\t\t\t[CR]      %u\n", ii, byte_getter[0]);    break;
                case (UEOF) : snprintf(holder, BUF_HOLDER-1, "<><><>%8ld)\t\t\t[EOF]     %u\n", ii, byte_getter[0]);    break;
                default     : snprintf(holder, BUF_HOLDER-1, "<><><>%8ld)\t%c    %u\n", ii, helper[0], byte_getter[0]); break;
            }
            fputs(holder, fptr_decode);
            #ifdef DECODE_CONTROL_LENGTH
                printf("%s{%9ld}  --->   %s", GET_NAME(fptr_read), ftell(fptr_read)-1, holder);
            #endif
        }
        printf("\n\tcheck '%s' for the results\n", output_file_decode);
        fclose(fptr_decode); fptr_decode = NULL;
        printf("\n<<< end file decode >>>\n");
}
#endif


////////~~~~~~~~END>  C_read_r3f.c
