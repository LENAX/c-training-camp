#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

char* my_strcpy(const char *src, const size_t src_len, char *dest, const size_t dest_len)
{
    assert(src && src != NULL);
    assert(dest && dest != NULL);
    assert(dest_len > 0);
    assert(src_len <= dest_len);

    bool mem_overlapped = false;
    size_t i;

    for (i = 0; i < src_len && i < dest_len; i++)
    {
        assert(&dest[i] != &src[i]);
        dest[i] = src[i];
    }

    if (i <= dest_len - 1) {
        dest[i] = '\0';
    }

    return dest;
}


bool my_strcmp(const char* s1, const char* s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        i++;
    }

    return (s1[i] == s2[i]);
}


char* rand_string(size_t size)
{
    char* random_string = (char *) malloc(sizeof(char)*(size+1));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";

    if (random_string == NULL) {
        puts("Out of memory");
        exit(EXIT_FAILURE);
    }

    if (size)
    {
        --size;
        for (size_t n = 0; n < size; n++)
        {
            int key = rand() % (int)(sizeof charset - 1);
            random_string[n] = charset[key];
        }
        random_string[size] = '\0';
    }
    return random_string;
}

size_t my_strlen(const char* s)
{
    size_t len;

    for (len = 0; s[len] != '\0'; len++)
        continue;

    return len;
}

void test_my_strcpy(char* test_case, size_t line_length)
{
    char *dest = (char *) malloc(sizeof(char) * line_length);
    char *ans = (char *)malloc(sizeof(char) * line_length);

    if (dest == NULL) {
        puts("Out of memory");
        exit(EXIT_FAILURE);
    }

    puts("\n======= Test my_strcpy =======");
    printf("Copying string %s to location %p\n", test_case, dest);

    char *_dest = my_strcpy(test_case, line_length, dest, line_length + 1);

    assert(dest == _dest && dest != NULL);

    printf(
        "Result: %s @ %p has been copied to %s @ %p\n",
        test_case, test_case, dest, dest);

    strcpy(ans, test_case);
    assert(strcmp(test_case, ans) == 0);

    free(dest);
}

void test_my_strcmp(char *test_case, size_t line_length)
{
    char *identical_string = (char *) malloc(sizeof(char) * line_length);
    char* different_string = rand_string(line_length);

    if (identical_string == NULL)
    {
        puts("Out of memory");
        exit(EXIT_FAILURE);
    }

    puts("\n======= strcmp test =======\n");

    strcpy(identical_string, test_case);
    printf("%s equals %s? %s\n",
           test_case,
           identical_string,
           (my_strcmp(test_case, identical_string) ? "true": "false"));
    printf("%s equals %s? %s\n",
           test_case,
           different_string,
           (my_strcmp(test_case, different_string) ? "true" : "false"));
    printf("Using strcpy: %s equals %s? %s\n",
           test_case,
           different_string,
           ((my_strcmp(test_case, identical_string) && strcmp(test_case, identical_string)) ? "true" : "false"));

    assert(my_strcmp(test_case, identical_string) && (strcmp(test_case, identical_string) == 0));
    assert(!(my_strcmp(test_case, different_string) || strcmp(test_case, different_string) == 0));

    free(identical_string);
    free(different_string);
}

char *my_strcat(char *dest, const char *src)
{
    char *rdest = dest;

    while (*dest)
        dest++;
    while (*dest++ = *src++)
        ;
    return rdest;
}

void test_my_strcat(char *test_case, size_t line_length)
{
    char* suffix = "___";
    size_t suffix_len = strlen(suffix);
    char *new_str = (char *) malloc(sizeof(char) * (line_length + suffix_len));
    char *ans = (char *)malloc(sizeof(char) * (line_length + suffix_len));

    puts("\n======= concat test =======\n");

    strcpy(ans, test_case);
    strcat(ans, suffix);

    strcpy(new_str, test_case);
    my_strcat(new_str, suffix);

    printf("concat %s with %s:\n%s\n", test_case, suffix, new_str);
    printf("correct: %s\n", ans);
    printf("my result: %s\n", new_str);
    printf("Correct? %s\n", (strcmp(new_str, ans) == 0) ? "Yes" : "No");

    free(new_str);
    free(ans);
}

void test_my_strlen(char *test_case, size_t line_length)
{
    size_t str_len = my_strlen(test_case);
    puts("\n======= strlen test =======\n");
    printf("The length of %s is %zu.\n", test_case, str_len);
    printf("Expected length: %zu. Correct? %s\n",
           strlen(test_case), (strlen(test_case) == str_len) ? "true" : "false");
    assert(strlen(test_case) == str_len);
}

void run_my_str_methods_tests(char* test_case)
{
    printf("=========== Test word: %s ===========\n", test_case);
    test_my_strlen(test_case, strlen(test_case));
    test_my_strcpy(test_case, strlen(test_case));
    test_my_strcmp(test_case, strlen(test_case));
    test_my_strcat(test_case, strlen(test_case));
    puts("=================================================");
}


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: str_process /dir/to/test_file.txt\n");
        exit(1);
    }

    FILE* test_file = fopen(argv[1], "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (test_file == NULL) {
        printf("Failed to read the test cases!");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, test_file)) != -1) {
        line[strcspn(line, "\r\n")] = '\0';
        run_my_str_methods_tests(line);
    }

    fclose(test_file);

    exit(0);
}