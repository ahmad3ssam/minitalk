#define _POSIX_C_SOURCE 199309L

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "./libft/libft.h"

char    *g_msg;

void    handler(int sig, siginfo_t *info, void *context)
{
    (void) context;
    static unsigned char    c[2];
    static int i;

    c[1] = '\0';
    c[0] = c[0] << 1;
    if (sig == SIGUSR1)
        c[0] = c[0]| 1;
    i++;
    kill(info->si_pid, SIGUSR1);
    if (i == 8)
    {
        if (c[0] == '\0')
        {
            g_msg = ft_strjoin(g_msg, (char*)c);
            ft_putendl_fd(g_msg, 1);
            free(g_msg);
            g_msg = NULL;
        }
        else
            g_msg = ft_strjoin(g_msg, (char*)c);
        i = 0;
        c[0] = '\0';
    }
}

int main()
{
    struct sigaction segment;

    g_msg = ft_itoa(getpid());
    ft_putendl_fd(g_msg, 1);
    free(g_msg);
    g_msg = NULL;
    segment.sa_sigaction = handler;
    segment.sa_flags = SA_SIGINFO ;
    sigemptyset(&segment.sa_mask);
    sigaction(SIGUSR1, &segment, NULL);
    sigaction(SIGUSR2, &segment, NULL);
    while (1);
    free(g_msg);
}