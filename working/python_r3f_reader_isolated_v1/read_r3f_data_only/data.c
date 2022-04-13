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
#define DECODE_START 16384UL                // change, but keep >= 0 and < DECODE_CONTROL_LENGTH
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

const char input_file[BUF_32] = "../dummy.r3f";
const char output_file[BUF_32] = "dummy_data_out.txt";
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
long bytes_in_file;
uint8_t byte_getter[BUF_BYTE_GETTER];
uint16_t uint16_getter[2];
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
    bytes_in_file = ftell(fptr_read);
    printf("\n\t'%s' size in bytes:  %ld\n", input_file, bytes_in_file);
    fseek(fptr_read, 0L, SEEK_SET);
    fseek(fptr_read, BI_IQ_DATA, SEEK_CUR); // start at data
    byte_index = ftell(fptr_read);
    printf("\n\t%s on byte:  %ld  ,  making '%s'  ,  parsing begins...\n\n", 
        GET_NAME(fptr_read), byte_index, output_file);

    while (byte_index < bytes_in_file)
    {
        fread(&uint16_getter[0], sizeof(uint16_t), 1, fptr_read);
        fread(&uint16_getter[1], sizeof(uint16_t), 1, fptr_read);
        byte_index = ftell(fptr_read);
        snprintf(holder, BUF_HOLDER-1, "%6u  :  %6u\n", uint16_getter[0], uint16_getter[1]);
        fputs(holder, fptr_write);
        #ifdef DEBUG_PARSE
            printf("%s{%9ld}  %s", GET_NAME(fptr_read), ftell(fptr_read), holder);
        #endif
    }

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
