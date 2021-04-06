#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_INT_BITS 31
#define MAX_UNSIGNED_INT 2147483647
#define MAX_HEX_LEN 100
#define BOOL int
#define TRUE 1
#define FALSE 0

/**
 * Function: decimal_to_binary
 * Convert a decimal number to a binary string
 *
 * @param value the integer value to be converted
 * @return converted binary string
*/
char* decimal_to_binary(int value)
{
    unsigned int digit = 0, pos = 0;
    char* result = (char *) malloc(sizeof(char) * (MAX_INT_BITS + 1));

    if (result == NULL)
        exit(EXIT_FAILURE);

    for (int i = MAX_INT_BITS - 1; i >= 0; i--) {
        digit = value >> i;
        if (digit & 1) {
            result[pos] = '1';
        } else {
            result[pos] = '0';
        }
        pos++;
    }
    result[pos] = '\0';
    return result;
}


/**
 * Function: format_bin_str
 * Truncates extra zeros before the highest bit
 *
 * @param bin_str
 * @return formatted binary string
*/
char* format_bin_str(char* bin_str)
{
    while (bin_str != NULL && *bin_str != '1' && *bin_str != '\0') {
        bin_str++;
    }
    return bin_str;
}

/**
 * Function: decimal_to_binary_conversion
 * Provides an interactive menu for decimal to binary conversion
*/
void decimal_to_binary_conversion()
{
    int dec = 0;
    char* bin_str = NULL;

    printf("Please enter a decimal number: ");
    scanf("%d", &dec);
    bin_str = decimal_to_binary(dec);

    if (bin_str != NULL)
    {
        printf("Converted binary is %s\n", format_bin_str(bin_str));
    }
    else
    {
        printf("Conversion failed.\n");
    }

    free(bin_str);
}

/**
 * Function: binary_to_decimal
 * Convert a binary string to decimal
 *
 * @param bin_str the binary string to be converted
 * @return converted decimal
*/
double binary_to_decimal(const char* bin_str)
{
    int str_length = strlen(bin_str);
    double result = 0, p = 0;
    const double base = 2;

    for (int i = str_length - 2; bin_str != NULL && i >= 0; i--) {
        if (bin_str[i] == ' ' && (str_length - i) % 5 == 0)
            p--;

        if (bin_str[i] - '0' == 1) {
            result += pow(base, p++);
        } else if (bin_str[i] - '0' == 0 || bin_str[i] == ' ' || bin_str[i] == '\n') {
            result += 0;
        } else {
            printf("Encountered non-binary character: %c @ location %d!", bin_str[i], i);
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

/**
 * Function: binary_to_decimal_conversion
 * Provides an interactive menu for converting binary value to decimal value
*/
void binary_to_decimal_conversion()
{
    double dec = 0;
    char* bin_str = (char *)malloc(sizeof(char) * MAX_INT_BITS);

    if (bin_str == NULL)
    {
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }

    printf("Please enter a binary: ");
    fgets(bin_str, MAX_INT_BITS, stdin);
    dec = binary_to_decimal(bin_str);
    printf("The decimal form is %.20g\n", dec);

    free(bin_str);
}


/**
 * Function: decimal_to_hex
 * 
*/
char* decimal_to_hex(int value)
{
    char* result = (char *) calloc(MAX_HEX_LEN, sizeof(char));
    result[MAX_HEX_LEN - 1] = '\0';

    int remainder = 0;

    for (int i = MAX_HEX_LEN - 2; value != 0 && i >= 0; i--) {
        remainder = value % 16;
        if (remainder < 10) {
            result[i] = (char) remainder + 48;  // to digital character
        } else {
            result[i] = (char) remainder + 55; // to alphabetic character
        }
        puts(result);
        value /= 16;
    }

    return result;
}

/**
 * Function: format_bin_str
 * Truncates extra zeros before the highest bit
 *
 * @param bin_str
 * @return formatted binary string
*/
char* format_hex_str(char *hex_str)
{
    while (hex_str != NULL && *hex_str == 0 && *hex_str != '\0') {
        hex_str++;
    }
    return hex_str;
}

int main(int argc, char **argv)
{
    int value = 255;
    char* hex = NULL;

    hex = decimal_to_hex(value);

    printf("The hex form of value %d is %c\n", value, hex[97]);

    free(hex);
    return 0;
}