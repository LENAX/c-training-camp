#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_BUFFER_SIZE 1024

/**
 * Strips the given character inline
*/
char *strip_char(char *line, char c)
{
    char *t = line, *s = line;
    while (*s != '\0')
    {
        if (*s != c)
        {
            *t++ = *s;
        }
        s++;
    }
    *t = '\0';
    return line;
}

int main(int argc, char *argv[])
{
    FILE *test_file = NULL;
    if (argc < 2)
    {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        test_file = fopen("/Users/stevelan/Desktop/c_training/assignments/week2/day5/test_data/strip_char.txt", "r");
    }
    else
    {
        test_file = fopen(argv[1], "r");
    }

    size_t len = 0, total_words = 0;
    ssize_t read;
    char *line = NULL;

    if (test_file == NULL)
    {
        printf("Failed to read the test cases!");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, test_file)) != -1)
    {
        line[strcspn(line, "\r\n")] = '\0';
        puts("===========");
        puts(line);
        puts(strip_char(line, 'a'));
    }

    fclose(test_file);
    exit(0);
}