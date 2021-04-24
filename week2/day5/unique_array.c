#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_BUFFER_SIZE 65535

char *new_string(size_t len)
{
    char *str = (char *)malloc((len + 1) * sizeof(char));
    str[len] = '\0';
    return str;
}

int count_space(char *str)
{
    int n_spaces = 0;
    char *s = str;

    while (*s != '\0')
    {
        if (*s == ' ')
            n_spaces++;
        s++;
    }

    return n_spaces;
}

int *unique(int *arr, size_t len, size_t *n_unique)
{
    int bitmap[MAX_BUFFER_SIZE];
    memset(bitmap, 0, sizeof(bitmap));

    int unique_arr[len];
    size_t unique_num_count = 0;

    for (size_t i = 0; i < len; i++) {
        if (bitmap[arr[i]] == 0) {
            unique_arr[unique_num_count++] = arr[i];
            bitmap[arr[i]] = 1;
        }
    }

    int *result = (int*)malloc(sizeof(int)*unique_num_count);
    memcpy(result, unique_arr, unique_num_count*sizeof(int));
    *n_unique = unique_num_count;

    return result;
 }

int main(int argc, char *argv[])
{
    FILE *test_file = NULL;
    if (argc < 2)
    {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        test_file = fopen("/Users/stevelan/Desktop/c_training/assignments/week2/day5/test_data/unique_array.txt", "r");
    }
    else
    {
        test_file = fopen(argv[1], "r");
    }

    size_t len = 0, total_words = 0;
    ssize_t read;
    char *line = NULL;
    int buffer[MAX_BUFFER_SIZE];
    int *unique_array = NULL;

    if (test_file == NULL)
    {
        printf("Failed to read the test cases!");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, test_file)) != -1)
    {
        line[strcspn(line, "\r\n")] = '\0';

        int i = 0;
        char* num_str = strtok(line, ",");
        while (num_str != NULL && i < MAX_BUFFER_SIZE) {
            int num = atoi(num_str);
            buffer[i++] = num;
            num_str = strtok(NULL, ",");
        }

        int *original_arr = (int*) calloc(i+1, sizeof(int));
        size_t n_unique = 0;
        memcpy(original_arr, buffer, sizeof(int)*i);
        unique_array = unique(original_arr, (size_t)i, &n_unique);

        for (size_t j = 0; j < n_unique; j++) {
            printf("%d ", unique_array[j]);
        }
        puts("");
        free(original_arr);
        free(unique_array);
    }

    fclose(test_file);
    exit(0);
}