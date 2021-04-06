#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    const int MAX_LINES = 9;
    const int MAX_N_DIAMONDS = 5;
    const char* diamond = "*";
    int padding_len = 0;
    int n_diamonds = 1;

    for (int i = 0; i < MAX_LINES; i++)
    {
        padding_len = abs(MAX_N_DIAMONDS - i - 1);
        if (padding_len > 0) {
            printf("%*c", padding_len, ' ');
        }

        // 1, 2, 4, 8, 4, 2, 1
        if (padding_len < MAX_N_DIAMONDS - 1) {
            // print the other half of the diamond
            printf("*");
            
            if (abs(MAX_N_DIAMONDS - padding_len) > 1) {
                printf("%*c*", abs(MAX_N_DIAMONDS - padding_len - 1)*2-1, ' ');
            } else {
                printf(" *");
            }
        } else {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
