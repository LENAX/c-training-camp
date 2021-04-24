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

char* to_number_with_word(char* line)
{
    char numbers[MAX_BUFFER_SIZE];
    char words[MAX_BUFFER_SIZE];
    char* number_and_word = new_string(strlen(line));
    char *current_char = line,
         *number_string_ptr = &numbers[0],
         *word_string_ptr = &words[0];

    while (*current_char != '\0') {
        if (isdigit(*current_char)) {
            *(number_string_ptr++) = *(current_char++);
        } else if (isalpha(*current_char)) {
            *(word_string_ptr++) = *(current_char++);
        } else {
            current_char++;
        }
    }

    assert((numbers - number_string_ptr) < MAX_BUFFER_SIZE);
    assert((word_string_ptr - words) < MAX_BUFFER_SIZE);

    // copy number first, and then copy word to number_word
    memcpy(number_and_word, numbers, (number_string_ptr - numbers));
    memcpy(number_and_word + (number_string_ptr - numbers),
           words,
           word_string_ptr - words);

    return number_and_word;
}


int main(int argc, char *argv[])
{
    FILE *test_file = NULL;
    if (argc < 2) {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        test_file = fopen("/Users/stevelan/Desktop/c_training/assignments/week2/day5/test_data/num_word.txt", "r");
    } else {
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
        char* number_word = to_number_with_word(line);
        puts("===========");
        puts(line);
        puts(number_word);
        free(number_word);
    }

    fclose(test_file);
    exit(0);
}