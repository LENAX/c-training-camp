#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

static volatile int keepRunning = 1;

void  INThandler(int sig)
{
    char c;

    signal(sig, SIG_IGN);
    printf("OUCH, did you hit Ctrl-C?\n"
        "Do you really want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y')
        exit(0);
    else
        signal(SIGINT, INThandler);
    getchar(); // Get new line character
}


void printUpper()
{
    char c;
    printf("Please enter a character: ");
    c = getchar();

    if (c >= 97 && c <= 122)
        printf("The upper case is %c\n", c-32);
    else if (c >= 65 && c <= 90)
        puts("The character is already in uppercase!");
    else
        puts("Unrecognized character!");

    getchar();
}


int main(int argc, char const *argv[])
{
    signal(SIGINT, INThandler);
    while (1)
        printUpper();
    return 0;
}
