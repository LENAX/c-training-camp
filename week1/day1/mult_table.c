#include <stdio.h>

int main(int argc, char const *argv[])
{
    const int MAX_VAL = 9;

    for (int i = 1; i <= MAX_VAL; i++)
    {
        for (int j = 1; j <= i; j++) {
            printf("%dx%d = %d\t", j, i, i*j);
        }
        printf("\n");
    }
    

    return 0;
}
