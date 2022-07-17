/*
    look at different bit shift effects in C
    be careful for undefined behavior
    see here:
        https://www.geeksforgeeks.org/left-shift-right-shift-operators-c-cpp/
        https://stackoverflow.com/questions/23323172/unsigned-bitwise-shift-operators-c11
        https://blog.regehr.org/archives/738 
    
    of note:
        # shifting past sign bit, even on uint* types, causes undefined behavior with some builds
        # not shifting into a data type usually implies an 'int' datatype, a promotion
        # care should be taken to cast or confine shifts to the target datatype
        # read about your implementation and test the code to be sure
        # know when an arithmetic or logical shift is applied
        # mask correctly, and confirm it works
    
    left shift (x << y)
        binary operator, 2 operands
        left shifts bits of first operand by the number of bits specified in the second operand
        equivalent to " x * pow(2, y) ", multipying [x] by [2^y]

    right shift (x >> y)
        binary operator, 2 operands
        right shifts bits of first operand by the number of bits specified in the second operand
        equivalent to " x / pow(2, y) ", dividing [x] by [2^y]

          Operation          |  signess   | number |          result
    ------------------------------------------------------------------------------------------------------
    number >> bits_to_shift  |  unsigned  |  >= 0  | number / (2^bits_to_shift)
    number >> bits_to_shift  |  signed    |  >= 0  | number / (2^bits_to_shift)
    number >> bits_to_shift  |  signed    |  < 0   | implementation-defined
    number << bits_to_shift  |  unsigned  |  >= 0  | [number * (2^bits_to_shift)] % [NUMBER_MAX + 1]
    number << bits_to_shift  |  signed    |  >= 0  | [number * (2^bits_to_shift)] // undefined on overflow
    number << bits_to_shift  |  signed    |  < 0   | UNDEFINED
    

    < 0 >  main()
    < 1 >  right_shift_corner_cases()
    < 2 >  left_shift_corner_cases()
    < 3 >  demo_random_shift_uint8()
    < 4 >  demo_random_shift_uint16()
    < 5 >  get_rand()
    < 6 >  make_bin_string_from_1byte()
    < 7 >  make_bin_string_from_2byte()
    < 8 >  make_bin_string_from_4byte()
    < 9 >  finish() 
*/

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define REPITITIONS 69                    // controls shifting operations performed
#define HELPER_SIZE 512                   // helper string size
#define HOLDER_SIZE (2 * HELPER_SIZE)     // holder string size
#define SEED 1917                         // changed seed if needed

const char out_file[] = "./outputz.txt";    // file to write data
char helper[HELPER_SIZE];                   // string for I/O
char holder[HOLDER_SIZE];                   // string to write data
FILE* fptr = NULL;                        

#define BYTE_TO_BINARY_STRING "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0')

void right_shift_corner_cases();                           // < 1 >
void left_shift_corner_cases();                            // < 2 >
void demo_random_shift_uint8();                            // < 3 >
void demo_random_shift_uint16();                           // < 4 >
int get_rand(int lower, int upper);                        // < 5 >
void make_bin_string_from_1byte(uint8_t input_uint8);      // < 6 >
void make_bin_string_from_2byte(uint16_t input_uint16);    // < 7 >
void make_bin_string_from_4byte(int input_int);            // < 8 >
void finish();                                             // < 9 >


/*
    < 0 >
    drive the program here
*/
int main
(
    int argc, 
    char** argv,
    char** envp
)
{
    fptr = fopen(out_file, "w");
    if (fptr == NULL) 
    {
        printf("\n\terror opening file\n"); 
        return EXIT_FAILURE;
    }

    srand(SEED);

    /*
        insert here

        any experiments you need
    */

    // demonstrates properties of the bit shift:
    right_shift_corner_cases();                  
    left_shift_corner_cases();                       
    demo_random_shift_uint8();
    demo_random_shift_uint16();

    finish();
    fclose(fptr);
    fptr = NULL;
    return EXIT_SUCCESS;
}


////~~~~


/*
    < 1 >
    right shifting
    a)  number >> bits_to_shift  |  unsigned  |  >= 0  | number / (2^bits_to_shift)
    b)  number >> bits_to_shift  |  signed    |  >= 0  | number / (2^bits_to_shift)
    c)  number >> bits_to_shift  |  signed    |  < 0   | implementation-defined
    work cases as needed
*/
void right_shift_corner_cases()
{
    snprintf(holder, HOLDER_SIZE, "\n%s() >>>\n", __func__);
    fputs(holder, fptr); printf("%s", holder);

    uint8_t number = 0xFF;
    uint8_t result = 0xAA;

    // a
    for (int ii = 0; ii < (8 * sizeof(uint8_t)) + 1; ii++)
    {
        snprintf(holder, HOLDER_SIZE, "------------------------------------\n");
            fputs(holder, fptr); printf("%s", holder);
        result = (number >> ii);
        make_bin_string_from_1byte(number);
        snprintf(holder, HOLDER_SIZE, "original      :  %s  ,  %u\n", helper, number);
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_1byte(result);
        snprintf(holder, HOLDER_SIZE, "%3u >> %3d    :  %s  ,  %u\n", number, ii, helper, result);
            fputs(holder, fptr); printf("%s", holder);
    }
    snprintf(holder, HOLDER_SIZE, "\n");
    fputs(holder, fptr); printf("%s", holder);
}


////~~~~


/*
    < 2 >
    left shifting
    a)  number << bits_to_shift  |  unsigned  |  >= 0  | [number * (2^bits_to_shift)] % [NUMBER_MAX + 1]
    b)  number << bits_to_shift  |  signed    |  >= 0  | [number * (2^bits_to_shift)] // undefined on overflow
    c)  number << bits_to_shift  |  signed    |  < 0   | UNDEFINED
    work cases as needed
*/
void left_shift_corner_cases()
{
    snprintf(holder, HOLDER_SIZE, "\n%s() >>>\n", __func__);
    fputs(holder, fptr); printf("%s", holder);
    uint8_t number = 0xFF;
    uint8_t result = 0xAA;

    // a
    for (int ii = 0; ii < (8 * sizeof(uint8_t)) + 1; ii++)
    {
        snprintf(holder, HOLDER_SIZE, "------------------------------------\n");
            fputs(holder, fptr); printf("%s", holder);
        result = (number << ii);
        make_bin_string_from_1byte(number);
        snprintf(holder, HOLDER_SIZE, "original      :  %s  ,  %u\n", helper, number);
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_1byte(result);
        snprintf(holder, HOLDER_SIZE, "%3u << %3d    :  %s  ,  %u\n", 
            number, ii, helper, result);
            fputs(holder, fptr); printf("%s", holder);
    }
    snprintf(holder, HOLDER_SIZE, "\n");
    fputs(holder, fptr); printf("%s", holder);
}   


////~~~~


/*
    < 3 >
    gets a random uint8_t
    shifts random uint8_t random amount
    values are checked
    right and left shift are validated
*/
void demo_random_shift_uint8()
{
    snprintf(holder, HOLDER_SIZE, "\n%s() >>>\n", __func__);
    fputs(holder, fptr); printf("%s", holder);
    for (int ii = 0; ii < REPITITIONS; ii++)
    {
        uint8_t number = (uint8_t)get_rand(0, UINT8_MAX);
        int bits_to_shift = get_rand(0, 8 * sizeof(uint8_t));
        uint8_t number_shifted_right = number >> bits_to_shift;
        uint8_t number_shifted_left = number << bits_to_shift;

        snprintf(holder, HOLDER_SIZE, "------------------------------------\n");
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_1byte(number);
        snprintf(holder, HOLDER_SIZE, "original    =  %s  ,  %3u\n", helper, number);
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_1byte(number_shifted_left);
        snprintf(holder, HOLDER_SIZE, "(%3u << %2d) =  %s  ,  %3u\n", 
            number, bits_to_shift, helper, number_shifted_left);
            fputs(holder, fptr); printf("%s", holder);

        snprintf(holder, HOLDER_SIZE, "------------------------------------\n");
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_1byte(number);
        snprintf(holder, HOLDER_SIZE, "original    =  %s  ,  %3u\n", helper, number);
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_1byte(number_shifted_right);
        snprintf(holder, HOLDER_SIZE, "(%3u >> %2d) =  %s  ,  %3u\n",
            number, bits_to_shift, helper, number_shifted_right);
            fputs(holder, fptr); printf("%s", holder);
    }
    snprintf(holder, HOLDER_SIZE, "\n");
    fputs(holder, fptr); printf("%s", holder);
}   


////~~~~


/*
    < 4 >
    gets a random uint16_t
    shifts random uint16_t random amount
    values are checked
    right and left shift are validated
*/
void demo_random_shift_uint16()
{
    snprintf(holder, HOLDER_SIZE, "\n%s() >>>\n", __func__);
    fputs(holder, fptr); printf("%s", holder);
    for (int ii = 0; ii < REPITITIONS; ii++)
    {
        uint16_t number = (uint16_t)get_rand(0, UINT16_MAX);
        int bits_to_shift = get_rand(0, 8 * sizeof(uint16_t));
        uint16_t number_shifted_right = number >> bits_to_shift;
        uint16_t number_shifted_left = number << bits_to_shift;

        snprintf(holder, HOLDER_SIZE, "-------------------------------------------------\n");
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_2byte(number);
        snprintf(holder, HOLDER_SIZE, "original       =  %s  ,  %5u\n", helper, number);
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_2byte(number_shifted_left);
        snprintf(holder, HOLDER_SIZE, "(%5u << %2d)  =  %s  ,  %5u\n", 
            number, bits_to_shift, helper, number_shifted_left);
            fputs(holder, fptr); printf("%s", holder);

        snprintf(holder, HOLDER_SIZE, "-------------------------------------------------\n");
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_2byte(number);
        snprintf(holder, HOLDER_SIZE, "original       =  %s  ,  %5u\n", helper, number);
            fputs(holder, fptr); printf("%s", holder);
        make_bin_string_from_2byte(number >> bits_to_shift);
        snprintf(holder, HOLDER_SIZE, "(%5u >> %2d)  =  %s  ,  %5u\n",
            number, bits_to_shift, helper, number_shifted_right);
            fputs(holder, fptr); printf("%s", holder);
    }
    snprintf(holder, HOLDER_SIZE, "\n");
    fputs(holder, fptr); printf("%s", holder);
}  


////~~~~


/*
    < 5 >
    get a random number within a range
    be sure to cast it
    unsigned only
*/
int get_rand(int lower, int upper)
{
    if (lower >= upper) 
    {
        printf("\n\t!!! upper=  %d  ,  lower=  %d  ,  illegal [ lower >= upper ]\n",
            upper, 
            lower); 
        return UINT8_MAX;
    }
    if (lower < 0 || upper < 0)
    {
        printf("\n\t!!! upper=  %d  ,  lower=  %d  ,  illegal [ unsigned only ]\n",
            upper, 
            lower); 
        return UINT8_MAX;
    }
    return ((rand() % (upper - lower + 1)) + lower);
}




////~~~~


/*
    < 6 >
    provide 1 byte
    populates the helper string to display binary number
*/
void make_bin_string_from_1byte(uint8_t input_uint8)
{
    snprintf(helper, HELPER_SIZE, 
        "8b'"BYTE_TO_BINARY_STRING, BYTE_TO_BINARY(input_uint8));
}


////~~~~


/*
    < 7 >
    provide 2 bytes
    populates the helper string to display binary number
*/
void make_bin_string_from_2byte(uint16_t input_uint16)
{
    snprintf(helper, HELPER_SIZE,
        "16b'"BYTE_TO_BINARY_STRING""BYTE_TO_BINARY_STRING, 
            BYTE_TO_BINARY((input_uint16 & 0xFF00) >> 8),
            BYTE_TO_BINARY(input_uint16 & 0x00FF));
}


////~~~~


/*
    < 8 >
    provide 8 bytes
    populates the helper string to display binary number
*/
void make_bin_string_from_4byte(int input_int)
{
    snprintf(helper, HELPER_SIZE,
        "32b'"BYTE_TO_BINARY_STRING"_"BYTE_TO_BINARY_STRING"_"BYTE_TO_BINARY_STRING"_"BYTE_TO_BINARY_STRING, 
            BYTE_TO_BINARY((input_int & 0xFF000000) >> 24),
            BYTE_TO_BINARY((input_int & 0x00FF0000) >> 16),
            BYTE_TO_BINARY((input_int & 0x0000FF00) >> 8) ,
            BYTE_TO_BINARY((input_int & 0x000000FF))      );
}


////~~~~


/*
    < 9 >
    gives compiler information when completing program
    see if changes effect bitshift behavior
*/
void finish (void)
{
    snprintf(holder, HOLDER_SIZE, "\n\t\t ~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n");
        fputs(holder, fptr); printf("%s", holder);
    snprintf(holder, HOLDER_SIZE, "bytes for 'int'       =  %ld\n", sizeof(int));
        fputs(holder, fptr); printf("%s", holder);
    snprintf(holder, HOLDER_SIZE, "bytes for 'uint_16_t' =  %ld\n", sizeof(uint16_t));
        fputs(holder, fptr); printf("%s", holder);
    snprintf(holder, HOLDER_SIZE, "bytes for 'uint_8_t'  =  %ld\n", sizeof(uint8_t));
        fputs(holder, fptr); printf("%s", holder);

    snprintf(holder, HOLDER_SIZE, "\nRAND_MAX (base 10)   =  %d\n", RAND_MAX);
        fputs(holder, fptr); printf("%s", holder);
    snprintf(holder, HOLDER_SIZE, "RAND_MAX (base 16)   =  0x%X\n", RAND_MAX);
        fputs(holder, fptr); printf("%s", holder);
    make_bin_string_from_4byte(RAND_MAX);
    snprintf(holder, HOLDER_SIZE, "RAND_MAX (base 2)    =  %s\n", helper);
        fputs(holder, fptr); printf("%s", holder);

    snprintf(holder, HOLDER_SIZE, "\nUINT16_MAX (base 10) =  %d\n", UINT16_MAX);
        fputs(holder, fptr); printf("%s", holder);
    snprintf(holder, HOLDER_SIZE, "UINT16_MAX (base 16) =  0x%X\n", UINT16_MAX);
        fputs(holder, fptr); printf("%s", holder);
    make_bin_string_from_2byte(UINT16_MAX);
    snprintf(holder, HOLDER_SIZE, "UINT16_MAX (base 2)  =  %s\n", helper);
        fputs(holder, fptr); printf("%s", holder);
    
    snprintf(holder, HOLDER_SIZE, "\nUINT8_MAX (base 10)  =  %d\n", UINT8_MAX);
        fputs(holder, fptr); printf("%s", holder);
    snprintf(holder, HOLDER_SIZE, "UINT8_MAX (base 16)  =  0x%X\n", UINT8_MAX);
        fputs(holder, fptr); printf("%s", holder);
    make_bin_string_from_1byte(UINT8_MAX);
    snprintf(holder, HOLDER_SIZE, "UINT8_MAX (base 2)   =  %s\n", helper);
        fputs(holder, fptr); printf("%s", holder);
        
    
    #ifdef __clang_major__
        printf("\nCompiler:  clang  ,  v %d.%d\n",
            __clang_major__, __clang_minor__);
    #endif
    #ifdef __GNUC__
        #ifdef __cplusplus
            printf("\nCompiler:  g++  ,  v %d.%d\n",
                __GNUC__, __GNUC_MINOR__);
        #else
            printf("\nCompiler:  gcc  ,  v %d.%d  ,  __STDC_VERSION__=  %ld\n",
                __GNUC__, __GNUC_MINOR__, __STDC_VERSION__);
        #endif
    #endif
    printf("\nsee:  %s\n\n", out_file);
}


////////~~~~~~~~END>  main.c
