#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


void split_line(char* line)
{
    char* line_ptr = line;

    while (*line_ptr != '\0') {
        if (*line_ptr != ' ') {
            putchar(*line_ptr);
            if (*(line_ptr+1) == ' ') {
                putchar('\n');
            }
        }
        line_ptr++;
    }
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
        split_line(line);
        puts("");
    }

    fclose(test_file);

    exit(0);
}