#include <stdio.h>
#include <stdlib.h>

int main() 
{
    const int MAX_LINES = 9;
    const int MAX_N_DIAMONDS = 5;
    const char* diamond = "* ";
    int padding_len = 0;
    int n_diamonds = 1;

    for (int i = 0; i < MAX_LINES; i++)
    {
        padding_len = abs(MAX_N_DIAMONDS - i - 1);
        if (padding_len > 0) {
            printf("%*c", padding_len, ' ');
        }

        n_diamonds = MAX_N_DIAMONDS - padding_len;
        for (int j = 0; j < n_diamonds; j++)
        {
            printf("%s", diamond);
        }
        
        printf("\n");
    }

    return 0;
}