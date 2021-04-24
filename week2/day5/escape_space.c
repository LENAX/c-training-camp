#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_BUFFER_SIZE 1024

char *new_string(size_t len)
{
    char *str = (char *)malloc((len + 1) * sizeof(char));
    str[len] = '\0';
    return str;
}

int count_space(char *str)
{
    int n_spaces = 0;
    char* s = str;

    while (*s != '\0') {
        if (*s == ' ') n_spaces++;
        s++;
    }

    return n_spaces;
}

char *escape_space(char *line)
{
    const char *espace = "%020";
    char* escaped = new_string((size_t) (strlen(line) + 2 * count_space(line)));
    char *line_ptr = line, *espace_ptr = escaped;

    while (*line_ptr != '\0') {
        if (isspace(*line_ptr)) {
            strcpy(espace_ptr, espace);
            espace_ptr += 4;
        } else {
            *(espace_ptr++) = *line_ptr;
        }
        line_ptr++;
    }

    return escaped;
}

int main(int argc, char *argv[])
{
    FILE *test_file = NULL;
    if (argc < 2)
    {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        test_file = fopen("/Users/stevelan/Desktop/c_training/assignments/week2/day5/test_data/escape_space.txt", "r");
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
        char *escaped_str = escape_space(line);
        puts("===========");
        puts(line);
        puts(escaped_str);
        free(escaped_str);
    }

    fclose(test_file);
    exit(0);
}