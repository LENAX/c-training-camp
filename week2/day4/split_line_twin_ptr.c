#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char** split(char* str, char split_char)
{
    size_t str_len = strlen(str);
    char *s_slow = str, *s_fast = str;
    char** splitted_strings = calloc(str_len, sizeof(char*));
    char* si = splitted_strings;

    if (splitted_strings == NULL) {
        puts("Out of memory");
        exit(EXIT_FAILURE);
    }

    while ((*s_slow) != '\0' && (*s_fast) != '\0') {
        // find the first character that does not equal to split_char
        while (*s_fast == split_char)
            s_fast++;
        s_slow = s_fast;

        // start searching for the next split char
        while (*(s_fast + 1) != '\0' && *(s_fast + 1) != split_char)
            s_fast++;

        /**
         * Now s_slow should point to the start of a splitted string
         * s_fast should point to the the end of a splitted string
        */
        // Count the length of the splitted string
        int splitted_str_len = s_fast - s_slow + 1;

        // allocate memory for the splitted string
        (*si) = (char *)calloc((splitted_str_len + 1), sizeof(char));

        // copy the string to si
        char* src_ptr = s_slow, dest_ptr = **si;
        while (src_ptr <= s_fast) {
            *(dest_ptr++) = *(src_ptr++);
        }
        *dest_ptr = '\0';

        // increase si to the next cell containing splitted string
        si++;
    }
    return splitted_strings;
}

void test_str_split(char *test_case)
{
    char** splitted_strings = split(test_case, ' ');

    for (char **cptr = *splitted_strings; *cptr != NULL; cptr++) {
        printf("%s\n", *cptr);
    }

    // clean up
    for (char **cptr = *splitted_strings; *cptr != NULL; cptr++) {
        free(*cptr);
    }
    free(splitted_strings);
}

void run_str_split_tests(char *test_case)
{
    printf("===========\nTest paragraph: %s\n", test_case);
    test_str_split(test_case);
    puts("=================================================");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        exit(1);
    }

    FILE *test_file = fopen(argv[1], "r");
    char *line = NULL;
    size_t len = 0, total_words = 0;
    ssize_t read;

    if (test_file == NULL)
    {
        printf("Failed to read the test cases!");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, test_file)) != -1)
    {
        line[strcspn(line, "\r\n")] = '\0';
        puts(line);
        run_str_split_tests(line);
    }

    printf("There are %zu words in the test file\n", total_words);

    fclose(test_file);

    exit(0);
}