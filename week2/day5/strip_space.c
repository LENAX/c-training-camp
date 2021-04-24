#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char *new_string(size_t len)
{
    char *str = (char *)malloc((len + 1) * sizeof(char));
    str[len] = '\0';
    return str;
}

char* strip_space(char *line)
{
    char* striped = new_string(strlen(line));
    char* s = line, *striped_ptr = striped;

    while (*s == ' ' && *s != '\0') {
        s++;
    }

    if (*s == '\0') {
        striped = (char *) realloc(striped, sizeof(char));
        *striped = '\0';
        return striped;
    }

    while (*s != '\0') {
        if (!isspace(*s) || !isspace(*(s-1))) {
            *(striped_ptr++) = *(s++);
        } else {
            s++;
        }
    }

    return striped;
}


int main(int argc, char *argv[])
{
    FILE *test_file = NULL;
    if (argc < 2)
    {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        test_file = fopen("./test_data/escape_space.txt", "r");
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
        char *striped_str = strip_space(line);
        puts("===========");
        puts(line);
        puts(striped_str);
        free(striped_str);
    }

    fclose(test_file);
    exit(0);
}