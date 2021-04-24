#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char* new_string(size_t len)
{
    char *str = (char *)malloc((len+1) * sizeof(char));
    str[len] = '\0';
    return str;
}

/**
 * Reverse the word order in the line and return a copy of the line in reversed word order
 *
 * Example:
 *  Input: I____am__a__student
 *  Output: student__a__am____I
 *
 * @param line string
 * @return reversed_line
*/
char* reverse_word_order(char *line)
{
    char *word_start = line, *word_end = line, *space_ptr = NULL;
    size_t line_length = strlen(line);
    char *reversed_line = new_string(line_length);
    char *reversed_line_ptr = &reversed_line[line_length-1];

    while (*word_end != '\0') {
        // find a word
        while (*(word_end + 1) != ' ' &&
               *(word_end + 1) != '_' &&
               *(word_end + 1) != '\0') {
            word_end++;
        }

        // now line[word_start: word_end] should be a word
        // we write the word to the end of the reversed line
        for (int i = (word_end - word_start); i >= 0; i--) {
            *(reversed_line_ptr - i) = *(word_end - i);
        }
        reversed_line_ptr -= (word_end - word_start + 1);
        space_ptr = ++word_end;

        // write spaces
        while (*space_ptr == ' ' || *space_ptr == '_') {
            *reversed_line_ptr = *space_ptr;
            reversed_line_ptr--;
            space_ptr++;
        }

        // align pointers
        word_start = space_ptr;
        word_end = word_start;
    }

    return reversed_line;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        exit(1);
    }

    FILE *test_file = fopen(argv[1], "r");
    size_t len = 0, total_words = 0;
    ssize_t read;
    char *line = NULL;
    char *reversed_line = NULL;

    if (test_file == NULL)
    {
        printf("Failed to read the test cases!");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, test_file)) != -1)
    {
        line[strcspn(line, "\r\n")] = '\0';
        reversed_line = reverse_word_order(line);
        puts(line);
        puts(reversed_line);
        free(reversed_line);
    }

    fclose(test_file);

    exit(0);
}