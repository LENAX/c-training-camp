#include <stdio.h>

int main(int argc, char *argv[])
{
    int x, y;

    printf("Please enter two integers: ");
    scanf("%d %d", &x, &y);

    printf("%d | %d = %d\n", x, y, x | y);
    printf("%d & %d = %d\n", x, y, x & y);
    printf("%d ^ %d = %d\n", x, y, x ^ y);
    printf("~%d = %d\n", x, ~x);
    printf("~%d = %d\n", y, ~y);

    printf("%d << 1 = %d\n", x, x << 1);
    printf("%d >> 1 = %d\n", y, y >> 1);

    exit(0);
}
