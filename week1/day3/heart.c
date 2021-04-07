#include <stdio.h>
#include <stdlib.h>

void draw_twin_trapezoid()
{
    const int char_len = 5;

    for (int i = 3; i > 0; i--) {
        printf("%*c", i, ' ');

        for (int j = 0; j < char_len - i; j++)
            printf("* ");

        printf("%*c", (i+1) * 2, ' ');

        for (int j = 0; j < char_len - i; j++)
            printf("* ");

        printf("\n");
    }
}

void draw_triangle()
{
    const int char_len = 11;

    for (int i = 1; i < char_len; i++) {
        printf("%*c", i, ' ');

        for (int j = 0; j < char_len - i; j++)
            printf("* ");

        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    draw_twin_trapezoid();
    draw_triangle();
    return 0;
}