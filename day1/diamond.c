#include <stdio.h>

int abs(int x)
{
    int mask = x >> 31;
    return (mask & -x) | (~mask & x);
}

int main(int argc, char **argv)
{
    const int MAX_LINE_DIAMONDS = 9;
    const int MAX_STARS = 5;

    for (int i = 0; i < MAX_LINE_DIAMONDS; i++) {
        // loop for printing spaces
        printf("%*c%d", abs((MAX_STARS - 1) - i), ' ', abs((MAX_STARS - 1) - i));

        // loop for printing asterisk
        printf("%*c", i, '* ');

        // line completed, go to the next line
        printf("\n");
    }

    return 0;
}