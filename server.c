#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void    handler(int sig)
{
    static unsigned char    c;
    static int i;
    c = c << 1;
    if (sig == SIGUSR1)
    {
        c = c| 1;
    }
    i++;
    if (i == 8)
    {
        if (c == '\0')
            write(1, "\n", 1);
        else
            write (1, &c, 1);
        i = 0;
        c = '\0';
    }

}

int main()
{
    struct sigaction sa;

    printf("%d\n",getpid());
    // sa.sa_handler = handler;
    // sa.sa_flags = SA_RESTART;
    // sigemptyset(&sa.sa_mask);
// 
    // sigaction(SIGUSR1, &sa, NULL);
    // sigaction(SIGUSR2, &sa, NULL);printf("2");
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    while (1)
        pause();
}