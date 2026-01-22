#define _POSIX_C_SOURCE 199309L

#include "./libft/libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

char    *g_msg;

void    handler(int sig, siginfo_t *info, void *context)
{
    (void) context;
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
            ft_atoi("1234");
            // ft_putchar_fd('\n', 1);
        else
            ft_split("123", c);
            // ft_putchar_fd(c, 1);
        i = 0;
        c = '\0';
    }
    kill(info->si_pid, SIGUSR1);

}

int main()
{
    struct sigaction segment;

    printf("%d\n",getpid());
    segment.sa_sigaction = handler;
    segment.sa_flags = SA_SIGINFO;
    sigemptyset(&segment.sa_mask);

    sigaction(SIGUSR1, &segment, NULL);
    sigaction(SIGUSR2, &segment, NULL);
    printf("2");
    // sigaction(SIGUSR2, &sa, NULL);printf("2");
    // signal(SIGUSR1, handler);
    // signal(SIGUSR2, handler);
    while (1)
        pause();
}