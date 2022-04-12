/*
    try to read the "*.r3f" in C

    https://www.codingunit.com/c-tutorial-binary-file-io
    https://nachtimwald.com/2017/09/24/hex-encode-and-decode-in-c/
    https://stackoverflow.com/questions/15736497/how-to-print-an-unsigned-char-in-c

    $ iconv -f utf8 <filename> -t utf8 -o /dev/null
*/

#define DECODE                          // turn on or off
#define DECODE_START 0UL                // change, but keep >= 0 and < DECODE_CONTROL_LENGTH
#define DECODE_CONTROL_LENGTH 1000UL    // turn on or off

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GET_NAME(var) #var
#define HEADER_OFFSET_BYTES 16384

#define BUF_32 32
#define BUF_HELPER 256
#define BUF_HOLDER 512

const char input_file[BUF_32] = "dummy.r3f";
const char output_file[BUF_32] = "dummy_out.txt";
#ifdef DECODE
    const char output_file_decode[BUF_32] = "dummy_decoder.txt";
#endif
char helper[BUF_HELPER];
char holder[BUF_HOLDER];

#define BUF_FILE_ID 27

struct getter
{
    char file_id[BUF_FILE_ID];
}; typedef struct getter getter;


int main()
{
    getter get;
    memset(get.file_id, '\0', BUF_FILE_ID);

    long byte_index = 0;
    long bytes_in_file = 0;
    FILE* fptr_read = NULL;

    fptr_read = fopen(input_file, "r");
    if (fptr_read == NULL)
    {
        printf("\n\tfailed to open the input files\n");
        return EXIT_FAILURE;
    }
    FILE* fptr_write = fopen(output_file, "w");
    #ifdef DECODE
        FILE* fptr_decode = fopen(output_file_decode, "w");
    #endif
    fseek(fptr_read, 0L, SEEK_END);
    bytes_in_file = ftell(fptr_read);
    printf("\n\t'%s' size in bytes:  %ld\n", input_file, bytes_in_file);
    fseek(fptr_read, 0L, SEEK_SET);
    
    #ifdef DECODE
        printf("\nmaking %s\n<<< begin file decode >>>\n\n", output_file_decode);
        unsigned char test_uchar;
        uint8_t test_uint8;
        #ifdef DECODE_CONTROL_LENGTH
            fseek(fptr_read, DECODE_START, SEEK_CUR);
            for (long ii = DECODE_START; ii < DECODE_CONTROL_LENGTH; ii++)
        #else
            fseek(fptr_read, 0L, SEEK_SET);
            for (long ii = 0; ii < bytes_in_file; ii++)
        #endif
        {
            fread(&test_uint8, sizeof(uint8_t), 1, fptr_read);
            test_uchar = (unsigned char)test_uint8;
            switch (test_uint8)
            {
                case (0)  : snprintf(helper, BUF_HELPER-1, "%8ld)\t\t\t[NULL]    %u\n", ii, test_uint8);     break;
                case (10) : snprintf(helper, BUF_HELPER-1, "%8ld)\t\t\t[LF]      %u\n", ii, test_uint8);     break;
                case (13) : snprintf(helper, BUF_HELPER-1, "%8ld)\t\t\t[CR]      %u\n", ii, test_uint8);     break;
                default   : snprintf(helper, BUF_HELPER-1, "%8ld)\t%c    %u\n", ii, test_uchar, test_uint8); break;
            }
            fputs(helper, fptr_decode);
            #ifdef DECODE_CONTROL_LENGTH
                printf("%s", helper);
            #endif
        }
        fclose(fptr_decode); fptr_decode = NULL;
        printf("\n<<< end file decode >>>\n");
    #endif

    // the parsing of the *.r3f files begins
    fseek(fptr_read, 0L, SEEK_SET);
    byte_index = ftell(fptr_read);
    printf("\n\t%s on byte:  %ld  ,  making '%s'\n", 
        GET_NAME(fptr_read), byte_index, output_file);
    
    // the first string is aquired
     do 
    {
        fread(&get.file_id[byte_index], sizeof(char), 1, fptr_read);
        byte_index = ftell(fptr_read);
    }
    while(get.file_id[byte_index-1] != '\0');
    snprintf(helper, BUF_HELPER-1, "%s\n", get.file_id);
    fputs(helper, fptr_write);

    fclose(fptr_read); fptr_read = NULL;
    fclose(fptr_write); fptr_write = NULL;
    printf("\n\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
    return EXIT_SUCCESS;
}


////////~~~~~~~~END>  C_read_r3f.c


/*

    do 
    {
        fread(&get.file_id[ftell(fptr_read)], sizeof(char), 1, fptr_read);
    }
    while(get.file_id[ftell(fptr_read)] != '\0');
    snprintf(helper, BUF_HELPER-1, "%s\n", get.file_id);
    fputs(helper, fptr_write);

     #ifdef RAW_UINT8
        
        for (long ii = 0; ii < bytes_in_file; ii++)
        {
            fread(&test_uint8, sizeof(uint8_t), 1, fptr_read);
            printf("%u", test_uint8);
            snprintf(helper, BUF_HELPER-1, "%u\n", test_uint8);
            fputs(helper, fptr_write_uint8);
        }
        fclose(fptr_write_uint8); fptr_write_uint8 = NULL;
    #endif

    unsigned char test[2];
    for (long ii = 0; ii < bytes_in_file; ii++)
    {
        fread(&test, 2*sizeof(unsigned char), 1, fptr_read);
        printf("%c%c", test[0], test[1]);
    }

    // get the files ID
    while (index_a < BUF_FILE_ID)
    {
        fread(&get.file_id[index_a], sizeof(unsigned char), 1, fptr_read);
        *fptr_read++;
        if (get.file_id[index_a] == '\n') {break;}
    }
    snprintf(helper, BUF_HELPER-1, "%s", get.file_id);
    fputs(helper, fptr_write);
    printf("\n%s\n", helper);

    fread(&get.file_id, (BUF_FILE_ID-1)*sizeof(unsigned char), (BUF_FILE_ID-1), fptr_read);
    snprintf(helper, BUF_HELPER-1, "%s", get.file_id);
    fputs(helper, fptr_write);
    printf("\n%s\n", helper);

    index_a = 0;
    while (get.file_id[index_a] != '\n' &&
           index_a < BUF_FILE_ID         )
    {
        get.file_id[index_a] = getc(fptr_read);
        index_a++;
        printf("%c", get.file_id[index_a]);
    }

    // get the files ID
    fread(&get.file_id, BUF_FILE_ID, 1, fptr_read);
    snprintf(helper, BUF_HELPER-1, "%s", get.file_id);
    fputs(helper, fptr_write);

#define BUF_A 32
#define BUF_B 64
#define BUF_C 128
#define BUF_D 256
#define BUF_E 512
#define BUF_F 1024

#define LINE_FEEDS_HEADER 10
#define COLON_OCCURANCES 10


    while (line_feed_counter < LINE_FEEDS_HEADER)
    {
        get.chr = fgetc(fptr_read);
        if (get.chr == '\n') {line_feed_counter++;}
        fputc(get.chr, fptr_write);
    }



    while (get.chr != EOF)
    {
        get.chr = fgetc(fptr_read);
        if (get.chr == '\n') {line_feed_counter++;}
    }
    printf("\n\tnew line chars:  %d\n", line_feed_counter);



    int f_size = (int)sizeof(fptr_read);
    printf("\n\tthe .r3f files byte size:  %d\n", f_size);



*/