#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigint(int sig)
{
    printf("Uzenet visszateresi erteke: %d\n", sig);
 }

void handle_sigquit(int sig)
{
    printf("Uzenet visszateresi erteke: %d\n", sig);
}

int main()
{
    signal(SIGQUIT, handle_sigquit);
    signal(SIGINT, handle_sigint);
    while(1)
    {
    }
    return 0;
}
