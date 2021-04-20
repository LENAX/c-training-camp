#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


size_t word_count(char* str)
{
    size_t n_word = 0;
    char* s = str;
    bool word_start = false, word_end = false;

    while ((*s) != '\0') {
        if (!isspace(*s) && (isspace(*(s + 1)) || *(s+1) == '\0')) {
            n_word++;
        }
        s++;
    }
    return n_word;
}

void test_word_count(char *test_case)
{
    puts("\n======= word_count test =======\n");
    printf("number of words: %zu\n", word_count(test_case));
}

void run_my_word_count_tests(char *test_case)
{
    printf("===========\nTest paragraph: %s\n", test_case);
    test_word_count(test_case);
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
        printf("word count: %zu\n", word_count(line));
        total_words += word_count(line);
    }

    printf("There are %zu words in the test file\n", total_words);

    fclose(test_file);

    exit(0);
}