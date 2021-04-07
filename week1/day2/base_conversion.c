#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

#define MAX_INT_BITS 31
#define MAX_UNSIGNED_INT 2147483647
#define MAX_HEX_LEN 100
#define BOOL int
#define TRUE 1
#define FALSE 0
#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

/**
 * Reverse a string
 * 
 * @param str string to reverse
 * @return reversed string
*/
char* strrev(char* str)
{
    if (!str || ! *str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}


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
        if (bin_str[i] == ' ') {
            if ((str_length - i) % 5 == 0)
                p--;
            continue;
        }

        if (bin_str[i] - '0' == 1) {
            result += 1*pow(base, p++);
        } else if (bin_str[i] - '0' == 0 || bin_str[i] == '\n') {
            p++;
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
    char* bin_str = (char *) malloc(sizeof(char) * MAX_INT_BITS);

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
    char* result = (char *) malloc(MAX_HEX_LEN * sizeof(char));

    if (result == NULL) {
        fprintf(stderr, "%s", "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    int i, remainder = 0;

    for (i = 0; value > 0 && i < MAX_HEX_LEN - 1; i++) {
        remainder = value % 16;
        if (remainder < 10) {
            result[i] = (char) remainder + 48;  // to digital character
        } else {
            result[i] = (char) remainder + 55; // to alphabetic character
        }
        value /= 16;
    }

    result[i] = '\0';

    return strrev(result);
}


/**
 * Function: binary_to_decimal_conversion
 * Provides an interactive menu for converting binary value to decimal value
*/
void decimal_to_hex_conversion()
{
    unsigned int value = 0;
    char* hex = NULL;

    printf("Please enter a decimal number: ");

    scanf("%d", &value);
    hex = decimal_to_hex(value);

    printf("The hex form of value %d is %s\n", value, hex);

    free(hex);
}

/**
 * Function: binary_to_decimal
 * Convert a binary string to decimal
 *
 * @param hex_str the binary string to be converted
 * @return converted decimal
*/
double hex_to_decimal(const char* hex_str)
{
    int str_length = strlen(hex_str);
    double result = 0, p = 0, digit = 0;
    const double base = 16;

    for (int i = str_length - 2; hex_str[i] != '\n' && hex_str[i] != '\0' && i >= 0; i--) {
        if (isdigit(hex_str[i])) {
            digit = (double) (hex_str[i] - 48);
            result += digit * pow(base, p++);
        } else if (hex_str[i] >= 'a' && hex_str[i] <= 'f') {
            digit = (double) (hex_str[i] - 'a' + 10);
            result += digit * pow(base, p++);
        } else if (hex_str[i] >= 'A' && hex_str[i] <= 'F') {
            digit = (double) (hex_str[i] - 'A' + 10);
            result += digit * pow(base, p++);
        } else {
            printf("Encountered non-hex character: %c @ location %d!", hex_str[i], i);
            exit(EXIT_FAILURE);
        }
    }

    return result;
}


/**
 * Hexadecimal to decimal conversion
 * 
*/
void hex_to_decimal_conversion()
{
    char* hex_str = (char*) malloc(sizeof(char) * MAX_HEX_LEN);
    double dec = 0;

    if (hex_str == NULL) {
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }

    printf("Please enter a hex value: ");
    fgets(hex_str, MAX_HEX_LEN, stdin);
    dec = hex_to_decimal(hex_str);
    printf("The decimal form is %.20g\n", dec);

    free(hex_str);
}

/*
* A wrapper function that helps menu function staying in a loop until the given exit character is entered.
*/
void run_forever(void (*func)(), char exit_char)
{
    char c;

    while (c != exit_char) {
        func();
        usleep(100);

        // clear the screen
        printf("\e[1;1H\e[2J");

        usleep(100);
    }
}

/**
 * Main menu
 * 
*/
void base_conversion()
{
    const char* menu[10] = {
        "Welcome to this base conversion utility!",
        "Please select an option to continue...",
        "(1) Decimal to binary",
        "(2) Binary to decimal",
        "(3) Decimal to hexadecimal",
        "(4) Hexadecimal to decimal",
        "",
        "Press Ctrl+C or x to quit",
        "",
        "Your choice (1, 2, 3, 4): "
    };
    char user_option[512];

    for (int i = 0; i < LEN(menu); i++) {
        printf("%s\n", menu[i]);
    }

    scanf("%s", user_option);
    printf("Your choice is %s\n", user_option);

    switch (user_option[0]) {
        case '1': {
            run_forever(&decimal_to_binary_conversion, 'r');
            break;
        }

        case '2': {
            run_forever(&binary_to_decimal_conversion, 'r');
            break;
        }

        case '3':{
            run_forever(&decimal_to_hex_conversion, 'r');
            break;
        }

        case '4': {
            run_forever(&hex_to_decimal_conversion, 'r');
            break;
        }

        case 'x': {
            printf("Exit");
            exit(0);
        }

        default:
            printf("Unrecognized option: %s\nPlease try again.\n", user_option);
    }
}


int main(int argc, char *argv[])
{
    int c;

    while (1)
    {
        static struct option long_options[] =
            {
                /* These options don’t set a flag.
                   We distinguish them by their indices. */
                {"bin2dec", no_argument, 0, 'b'},
                {"dec2bin", no_argument, 0, 'd'},
                {"dec2hex", no_argument, 0, 'h'},
                {"hex2dec", no_argument, 0, 'x'},
                {0, 0, 0, 0}};
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long_only(argc, argv, "bdhx",
                             long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case 'b':
            decimal_to_binary_conversion();
            break;

        case 'd':
            binary_to_decimal_conversion();
            break;

        case 'h':
            decimal_to_hex_conversion();
            break;

        case 'x':
            hex_to_decimal_conversion();
            break;

        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            abort();
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        putchar('\n');
    }

    exit(0);
}